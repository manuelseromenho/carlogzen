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
}
