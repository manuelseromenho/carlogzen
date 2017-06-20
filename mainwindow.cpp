#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("CarLogZen - Gestão de Frotas");
    //this->setStyleSheet("background-color: white;");
    QStackedWidget *stack = ui->stackedWidget;
    stack->setCurrentIndex(0);

    ui->tabWidget->setCurrentWidget(ui->tab_automoveis); //inicia no primeiro tab (automoveis)

    //ligar à base dados
    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("../carlogzen/tempo/carlogzendb3.db");
    db.setDatabaseName("../carlogzen/carlogzendb.db");
    db.open();
    if (!db.open()){
        qDebug() << "Erro a abrir base dados" << db.lastError().text();
        ui->statusBar->showMessage("Erro na ligação à base de dados!");
        this->close();
    }else{ui->statusBar->showMessage("Ligação ok");};

    ui->tabela_caracteristicas->setColumnHidden(0, true);
    ui->tabela_pecas->setColumnHidden(0, true);
    ui->tabela_manutencao->setColumnHidden(0,true);
    ui->tabela_automoveis->setEditTriggers( QAbstractItemView::NoEditTriggers );

    FillTable();
    FillTable_pecas();
    FillTable_manutencao();
    FillTable_automoveis();
    FillTable_abastecimento();

    ui->tabela_automoveis->selectRow(0);
    ui->tabela_caracteristicas->selectColumn(0);
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

/***** Login Logout *****/
void MainWindow::on_pushButton_clicked()
{
    QTabWidget *tabs = ui->tabWidget;
    QStackedWidget *stack = ui->stackedWidget;

    QSqlQuery query(db);

    if (!query.exec("SELECT iduser,username,password FROM users")) qDebug() << query.lastError().text();

    int iduser;
    QString username;
    QString password;
    int numregistos = 0;
    while( query.next() )
    {
        numregistos++;
    }

    query.first();
    for (int x=0;x<numregistos;x++)
    {
        iduser = query.value(0).toInt();
        username = query.value(1).toString();
        password= query.value(2).toString();

        if (ui->username->text()==username && ui->password->text()==password)
        {
            QMessageBox::information(this,"Login","Login efetuado!","ok");
            stack->setCurrentIndex(1);
            tabs->setCurrentIndex(0);
            x=numregistos;
        }
        else
        {
            query.next();
        }
    }

    if (ui->username->text()!=username || ui->password->text()!=password)
    {
        QMessageBox::warning(this,"Login","Login inválido","ok");
        stack->setCurrentIndex(0);
    }
}

void MainWindow::on_logout_clicked()
{
    int op = QMessageBox::question(this,"Logout","Deseja fazer logout?","Ok", "Cancelar");

    if (op == 0)
    {
        QStackedWidget *stack = ui->stackedWidget;
        stack->setCurrentIndex(0);
        ui->username->setText("");
        ui->password->setText("");
    }
}
/************************/

/***** Caracteristicas ****/
void MainWindow::FillTable(){

    int num_result, l, c;
    QSqlQuery query(db);
    loaded = false;


    if(!query.exec("SELECT count(idcaracteristica) as num_result FROM caracteristicas")) qDebug() << query.lastError().text();

    query.first();
    num_result = query.value(0).toInt();

    //ui->countrows->setText(QString::number(num_result));

    ui->tabela_caracteristicas->setRowCount(num_result);

    if (!query.exec("SELECT idcaracteristica, marca, modelo, cilindrada, cor, combustivel  FROM caracteristicas"))
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

        query.prepare("UPDATE caracteristicas SET marca=:n, modelo=:e, cilindrada=:c, cor=:f, combustivel=:d WHERE idcaracteristica=:i" );
        //query.prepare("UPDATE INTO caracteristicas(marca, modelo, cilindrada, cor, combustivel) VALUES(marca=:n, modelo=:e, cilindrada=:c, cor=:f, combustivel=:d WHERE idcaracteristica=:i)");
        query.bindValue (":n", ui->tabela_caracteristicas->item(row, 1)->text());
        query.bindValue (":e", ui->tabela_caracteristicas->item (row, 2)->text());
        query.bindValue (":c", ui->tabela_caracteristicas->item (row, 3)->text());
        query.bindValue (":f", ui->tabela_caracteristicas->item (row, 4)->text());
        query.bindValue (":d", ui->tabela_caracteristicas->item (row, 5)->text());
        query.bindValue (":i", id);

        if (!query.exec())
        qDebug() << query.lastError().text();
}
/*************************/

/***** PEÇAS ****/
void MainWindow::FillTable_pecas()
{
    int num_result, l, c;
    QSqlQuery query(db);
    loaded = false;

    if(!query.exec("SELECT count(idpeca) as num_result FROM pecas")) qDebug() << query.lastError().text();

    query.first();
    num_result = query.value(0).toInt();

    //ui->countrows->setText(QString::number(num_result));

    ui->tabela_pecas->setRowCount(num_result);


    if (!query.exec("SELECT idpeca, peca, precopeca FROM pecas"))
    {
        qDebug() << query.lastError().text();
        return ;
    }

    for(l=0, query.first(); query.isValid(); query.next(), ++l)
    {
        for(c=0; c<10; c++)
        {
            ui->tabela_pecas->setItem(l, c, new QTableWidgetItem( query.value(c).toString()));
        }
    }
    loaded = true;

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);

}

void MainWindow::on_adicionar_peca_clicked()
{
    QSqlQuery query(db);
    if(!query.exec("INSERT INTO pecas(peca, precopeca) VALUES('','')"))  qDebug() << query.lastError().text();

    FillTable_pecas();

    ui->tabela_pecas->scrollToBottom();
}

void MainWindow::on_apagar_peca_clicked()
{
    int del_id = ui->tabela_pecas->item(ui->tabela_pecas->currentRow(), 0)->text().toInt();
    ui->tabela_pecas->removeRow(ui->tabela_pecas->currentRow());

    QSqlQuery query(db);
    query.prepare("DELETE FROM pecas WHERE idpeca = :id");
    query.bindValue(":id", del_id);

    if (!query.exec()) qDebug() << query.lastError().text();
    FillTable_pecas();
}

void MainWindow::on_tabela_pecas_cellChanged(int row, int column)
{
    if(!loaded) return;

        // get record id from column 0
        int id = ui->tabela_pecas->item(row, 0)->text().toInt();
        QSqlQuery query(db) ;

        query.prepare("UPDATE pecas SET peca=:f, precopeca=:d WHERE idpeca=:i" );
        query.bindValue (":f", ui->tabela_pecas->item (row, 1)->text());
        query.bindValue (":d", ui->tabela_pecas->item (row, 2)->text());
        query.bindValue (":i", id);

        if (!query.exec())
        qDebug() << query.lastError().text();
}
/****************/

/***** Manutenção ****/
void MainWindow::FillTable_manutencao()
{
    int num_result, l, c;
    QSqlQuery query(db);
    loaded = false;

    if(!query.exec("SELECT count(idmanutencao) as num_result FROM manutencao")) qDebug() << query.lastError().text();

    query.first();
    num_result = query.value(0).toInt();

    ui->tabela_manutencao->setRowCount(num_result);

    if (!query.exec("SELECT idmanutencao, tipomanutencao, preco FROM manutencao"))
    {
        qDebug() << query.lastError().text();
        return ;
    }

    for(l=0, query.first(); query.isValid(); query.next(), ++l)
    {
        for(c=0; c<10; c++)
        {
            ui->tabela_manutencao->setItem(l, c, new QTableWidgetItem( query.value(c).toString()));
        }
    }
    loaded = true;

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);

}

void MainWindow::on_adicionar_manutencao_clicked()
{
    QSqlQuery query(db);
    if(!query.exec("INSERT INTO manutencao(tipomanutencao, preco) VALUES('','')"))  qDebug() << query.lastError().text();

    FillTable_manutencao();

    ui->tabela_manutencao->scrollToBottom();
}

void MainWindow::on_apagar_manutencao_clicked()
{
    int del_id = ui->tabela_manutencao->item(ui->tabela_manutencao->currentRow(), 0)->text().toInt();
    ui->tabela_manutencao->removeRow(ui->tabela_manutencao->currentRow());

    QSqlQuery query(db);
    query.prepare("DELETE FROM manutencao WHERE idmanutencao = :id");
    query.bindValue(":id", del_id);

    if (!query.exec()) qDebug() << query.lastError().text();
    FillTable_manutencao();
}

void MainWindow::on_tabela_manutencao_cellChanged(int row, int column)
{
    if(!loaded) return;

        // get record id from column 0
        int id = ui->tabela_manutencao->item(row, 0)->text().toInt();
        QSqlQuery query(db) ;

        query.prepare("UPDATE manutencao SET tipomanutencao=:f, preco=:d WHERE idmanutencao=:i" );
        query.bindValue (":f", ui->tabela_manutencao->item (row, 1)->text());
        query.bindValue (":d", ui->tabela_manutencao->item (row, 2)->text());
        query.bindValue (":i", id);

        if (!query.exec())
        qDebug() << query.lastError().text();
}
/*********************/

/***** Automoveis *****/
void MainWindow::FillTable_automoveis()
{
    int num_rows, r, c;
    QSqlQuery query(db);
    loaded = false;

    if(!query.exec("SELECT count(idmatricula) as num_rows FROM automoveis")) qDebug() << query.lastError().text();

    query.first();
    num_rows = query.value(0).toInt();

    ui->tabela_automoveis->setRowCount(num_rows);

    if (!query.exec("SELECT idmatricula, marca, modelo, cilindrada,cor, combustivel, data_aquisicao,preco_aquisicao,data_venda,preco_venda "
                "FROM caracteristicas "
                "INNER JOIN automoveis "
                "ON automoveis.idcaracteristica=caracteristicas.idcaracteristica")){
        qDebug() << query.lastError().text();
        return ;
    }

    for(r=0, query.first();query.isValid(); query.next(), ++r){
        for(c=0; c<15; c++){
            ui->tabela_automoveis->setItem(r, c, new QTableWidgetItem( query.value(c).toString()));
        }
    }
    loaded = true;
}

/**********************/

/***** Compra *****/
void MainWindow::on_comprar_clicked()
{
    /*QSqlQuery query(db);
    if(!query.exec("INSERT INTO automoveis"
                   "(idmatricula,idcaracteristica,data_aquisicao, data_venda, preco_aquisicao, preco_venda) "
                   "VALUES('','','','','','')"))  qDebug() << query.lastError().text();*/

    //int id = ui->tabela_caracteristicas->item(currentrow, 0)->text().toInt();
    int id = ui->tabela_caracteristicas->item(ui->tabela_caracteristicas->currentRow(), 0)->text().toInt();
    //QString alert_string = ui->tabela_caracteristicas->item(ui->tabela_caracteristicas->currentRow(), 0)->text();
    //int alert= QMessageBox::question(this,"Comprar",alert_string,"Ok","Cancelar");
    QSqlQuery query(db);
    int op= QMessageBox::question(this,"Comprar","Deseja comprar?","Ok","Cancelar");

    if(op==0)
    {
        query.prepare("INSERT INTO automoveis (idmatricula, idcaracteristica, data_aquisicao, preco_aquisicao) VALUES(:idmatricula , :idcaracteristica, :data,:preco)");
        query.bindValue(":idmatricula", ui->matricula->text());
        query.bindValue(":idcaracteristica", id);
        query.bindValue(":data", ui->data_compra->text());
        query.bindValue(":preco", ui->preco_compra->text().toInt());
        query.exec();
    }

    if (!query.exec())
    qDebug() << query.lastError().text();
/*****************/


}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
   if(index == 0)
   {
       ui->tabela_automoveis->selectRow(0);
       FillTable_automoveis();
   }
   if(index == 1)
       ui->tabela_caracteristicas->selectRow(0);

}

/***** Venda *****/
void MainWindow::on_vender_clicked()
{

    //QString matricula = ui->comboBox_frota->currentText();
    QString matricula = ui->tabela_automoveis->item(ui->tabela_automoveis->currentRow(), 0)->text();

    QSqlQuery query2(db);

    query2.prepare("SELECT status FROM automoveis WHERE idmatricula=:matricula");
    query2.bindValue (":matricula", matricula);

    if(!query2.exec())
    {
        qDebug() << query2.lastError().text();
        return ;
    }

    query2.first();
    int status = query2.value(0).toInt();
    QString status_string = query2.value(0).toString();

    if(status == 1)
    {
        QMessageBox::warning(this,"Atenção", "O automovel com a matricula: " + matricula + " já foi vendido!","Ok");
    }
    else
    {
        QSqlQuery query(db);
        int op= QMessageBox::question(this,"Vender","Deseja vender o automóvel com a matricula: " + matricula,"Ok","Cancelar");

        if(op==0 )
        {
            query.prepare("UPDATE automoveis SET data_venda=:data, preco_venda=:preco,status=1 WHERE idmatricula=:matricula");
            query.bindValue(":data", ui->data_venda->text());
            query.bindValue(":preco", ui->preco_venda->text());
            query.bindValue (":matricula", matricula);

            if (!query.exec())
            qDebug() << query.lastError().text();
         }

        FillTable_automoveis();
    }
}
/*****************/


/***** Abastecimento *****/
void MainWindow::on_adicionar_abastecimento_clicked()
{
    QSqlQuery query(db);
    QSqlQuery query2(db);
        if (!query2.exec("SELECT idabastecimento FROM abastecimento")) qDebug() << query2.lastError().text();
        if(!query.exec("INSERT INTO abastecimento(local, data,kms,litros,precolitro, idmatricula) VALUES('', '', '','','','')"))  qDebug() << query.lastError().text();

        FillTable_abastecimento();
        int numregistos = 0;
        while( query2.next() )
        {
            numregistos++;
        }
        //qDebug() << numregistos;

        ui->tabela_abastecimento->scrollToBottom();
        QSqlQueryModel *model = new QSqlQueryModel();
        QString sql;
        sql = "SELECT idmatricula FROM automoveis WHERE flag=0";
        QSqlQuery* query3 = new QSqlQuery(db);
        query3->prepare(sql);

        if(!query3->exec())
        {
            qDebug() << "Query Error: " << query3->lastError();
        }else
        {
            qDebug() << "Query Successful: " << query3->lastQuery();
        }

        model->setQuery(*query3);
        combo_box = new QComboBox(ui->tabela_abastecimento);
        combo_box->setModel(model);
        ui->tabela_abastecimento->setCellWidget ( numregistos-1, 1, combo_box);

        dateEdit = new QDateEdit();
        dateEdit->setDate(QDate::currentDate());
        dateEdit->setCalendarPopup(true);
        ui->tabela_abastecimento->setCellWidget(numregistos-1,3,dateEdit);
}

void MainWindow::FillTable_abastecimento()
{

    int num_result, l, c;
    QSqlQuery query(db);
    loaded = false;

    if(!query.exec("SELECT count(idabastecimento) as num_result FROM abastecimento")) qDebug() << query.lastError().text();

    query.first();
    num_result = query.value(0).toInt();
    ui->tabela_abastecimento->setRowCount(num_result);

    /*if (!query.exec("SELECT idabastecimento, idmatricula, local, data, kms, litros, precolitro "
                "FROM abastecimento "
                "INNER JOIN automoveis "
                "ON automoveis.idmatricula=abastecimento.idmatricula"))
    {
        qDebug() << query.lastError().text();
        return ;
    }*/

    if (!query.exec("SELECT idabastecimento, idmatricula, local, data, kms, litros, precolitro "
                "FROM abastecimento "))
    {
        qDebug() << query.lastError().text();
        return ;
    }

    for(l=0, query.first(); query.isValid(); query.next(), ++l)
    {
        for(c=0; c<15; c++)
        {
            ui->tabela_abastecimento->setItem(l, c, new QTableWidgetItem( query.value(c).toString()));
            float total = query.value(5).toFloat() * query.value(6).toFloat();
            QString total_string = QString::number(total);
            ui->tabela_abastecimento->setItem(l,7, new QTableWidgetItem(total_string+",00€"));
        }
    }
    loaded = true;

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);

}
/*************************/
