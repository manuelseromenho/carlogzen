#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("CarLogZen - Gestão de Frotas");
    //this->setStyleSheet("background-color: white;");
    //QStackedWidget *stack = ui->stackedWidget;
    //stack->setCurrentIndex(0);

    //ligar à base dados
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../carlogzen/carlogzendb.db");
    db.open();
    if (!db.open()){
        qDebug() << "Erro a abrir base dados" << db.lastError().text();
        ui->statusBar->showMessage("Database connection failure!");
        this->close();
    }else{ui->statusBar->showMessage("Database connection OK!");};

    //ui->tabela_caracteristicas->hideColumn(ui->tabela_caracteristicas->column(1));
    ui->tabela_caracteristicas->setColumnHidden(0, true);

    FillTable();
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

void MainWindow::FillTable(){

    int num_result, l, c;
    QSqlQuery query(db);
    loaded = false;

    if(!query.exec("SELECT count(idcaracteristicas) as num_result FROM caracteristicas")) qDebug() << query.lastError().text();

    query.first();
    num_result = query.value(0).toInt();

    //ui->countrows->setText(QString::number(num_result));

    ui->tabela_caracteristicas->setRowCount(num_result);

    if (!query.exec("SELECT idcaracteristicas, marca, modelo, cilindrada, cor, combustivel  FROM caracteristicas"))
    {
        qDebug() << query.lastError().text();
        return ;
    }

    for(l=0, query.first(); query.isValid(); query.next(), ++l)
    {
        for(c=0; c<num_result; c++)
        {
            ui->tabela_caracteristicas->setItem(l, c, new QTableWidgetItem( query.value(c).toString()));
        }
    }
    loaded = true;

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);

}



void MainWindow::on_adicionar_caracteristica_clicked()
{
    QSqlQuery query(db);
    if(!query.exec("INSERT INTO caracteristicas(marca, modelo, cilindrada, cor, combustivel) VALUES('','', '', '','')"))  qDebug() << query.lastError().text();

    FillTable();

    ui->tabela_caracteristicas->scrollToBottom();
}

void MainWindow::on_apagar_caracteristica_clicked()
{
    int del_id = ui->tabela_caracteristicas->item(ui->tabela_caracteristicas->currentRow(), 0)->text().toInt();
    ui->tabela_caracteristicas->removeRow(ui->tabela_caracteristicas->currentRow());

    /*ui->tabela_caracteristicas->setRowCount(0);*/
    /*ui->tabela_caracteristicas->model()->removeRows(0, ui->tabela_caracteristicas->rowCount());*/


    QSqlQuery query(db);
    query.prepare("DELETE FROM caracteristicas WHERE idcaracteristica = :id");
    query.bindValue(":id", del_id);

    if (!query.exec()) qDebug() << query.lastError().text();
    FillTable();
}

void MainWindow::on_tabela_caracteristicas_cellChanged(int row, int column)
{
    if(!loaded) return;

        // get record id from column 0
        int id = ui->tabela_caracteristicas->item(row, 0)->text().toInt();
        QSqlQuery query(db) ;

        query.prepare("UPDATE caracteristicas SET marca=:n, modelo=:e, cilindrada=:c, cor=:f, combustivel=:d WHERE idcaracteristicas=:i" );
        query.bindValue (":n", ui->tabela_caracteristicas->item(row, 1)->text());
        query.bindValue (":e", ui->tabela_caracteristicas->item (row, 2)->text());
        query.bindValue (":c", ui->tabela_caracteristicas->item (row, 3)->text());
        query.bindValue (":f", ui->tabela_caracteristicas->item (row, 4)->text());
        query.bindValue (":d", ui->tabela_caracteristicas->item (row, 5)->text());
        query.bindValue (":i", id);

        if (!query.exec())
        qDebug() << query.lastError().text();
}
