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
    db.setDatabaseName("carlogzendb.db");
    db.open();
    if (!db.open()){
        qDebug() << "Erro a abrir base dados" << db.lastError().text();
        ui->statusBar->showMessage("Database connection failure!");
        this->close();
    }else{ui->statusBar->showMessage("Database connection OK!");};

    FillTable();
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

void MainWindow::FillTable(){

    int num_result, l, c;
    QSqlQuery consulta(db);
    loaded = false;

    if(!consulta.exec("SELECT count(idcaracteristicas) as num_result FROM caracteristicas")) qDebug() << consulta.lastError().text();

    consulta.first();
    num_result = consulta.value(0).toInt();

    ui->tabela_caracteristicas->setRowCount(num_result);

    if (!consulta.exec("SELECT marca, modelo, cilindrada, cor, combustivel  FROM caracteristicas"))
    {
        qDebug() << consulta.lastError().text();
        return ;
    }

    for(l=0, consulta.first(); consulta.isValid(); consulta.next(), ++l){
        for(c=0; c<10; c++)
        {
            ui->tabela_caracteristicas->setItem(l, c, new QTableWidgetItem( consulta.value(c).toString()));
        }
    }
    loaded = true;

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);

}

void MainWindow::on_adicionar_caracteristica_clicked()
{
    QSqlQuery consulta(db);
    if(!consulta.exec("INSERT INTO caracteristicas(marca, modelo, cilindrada, cor, combustivel) VALUES('','', '', '','')"))  qDebug() << consulta.lastError().text();

    FillTable();

    ui->tabela_caracteristicas->scrollToBottom();
}

void MainWindow::on_apagar_caracteristica_clicked()
{
    int del_id = ui->tabela_caracteristicas->item(ui->tabela_caracteristicas->currentRow(), 0)->text().toInt();

    QSqlQuery consulta(db);
    consulta.prepare("DELETE FROM caracteristicas WHERE idcaracteristica = :id");
    consulta.bindValue(":id", del_id);

    if (!consulta.exec()) qDebug() << consulta.lastError().text();
    FillTable();
}

void MainWindow::on_tabela_caracteristicas_cellChanged(int row, int column)
{
    if(!loaded) return;

        // get record id from column 0
        int id = ui->tabela_caracteristicas->item(row, 0)->text().toInt();
        QSqlQuery consulta(db) ;

        consulta.prepare("UPDATE caracteristicas SET marca=:n, modelo=:e, cilindrada=:c, cor=:f, combustivel=:d WHERE idcaracteristicas=:i" );
        consulta.bindValue (":n", ui->tabela_caracteristicas->item(row, 1)->text());
        consulta.bindValue (":e", ui->tabela_caracteristicas->item (row, 2)->text());
        consulta.bindValue (":c", ui->tabela_caracteristicas->item (row, 3)->text());
        consulta.bindValue (":f", ui->tabela_caracteristicas->item (row, 4)->text());
        consulta.bindValue (":d", ui->tabela_caracteristicas->item (row, 5)->text());
        consulta.bindValue (":i", id);

        if (!consulta.exec())
        qDebug() << consulta.lastError().text();
}
