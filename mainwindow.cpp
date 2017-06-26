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
    ui->tabela_abastecimento->setColumnHidden(0,true);
    ui->tabela_automoveis->setEditTriggers( QAbstractItemView::NoEditTriggers );

    FillTable();
    FillTable_pecas();
    FillTable_manutencao();
    FillTable_automoveis();
    FillTable_abastecimento();
    FillTable_revisao();

    ui->tabela_automoveis->selectRow(0);
    ui->tabela_caracteristicas->selectColumn(0);
    ui->tabela_abastecimento->selectColumn(0);
    ui->tabela_revisao->selectColumn(0);
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    switch( index )
    {
    case 0:
        FillTable_automoveis();
        ui->tabela_automoveis->selectRow(0);
        break ;
    case 1 :
        ui->tabela_caracteristicas->selectRow(0);
        break ;
    case 2 :
        FillTable_abastecimento();
        ui->tabela_abastecimento->selectRow(0);
        break ;
    case 3:

        break ;
    case 4:
        FillTable_revisao();
        ui->tabela_revisao->selectRow(0);
        break ;

    }


}

/***** Login Logout *****/
void MainWindow::on_loginbutton_clicked()
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

        ui->tabWidget->setTabEnabled(1, true);
        ui->tabWidget->setTabEnabled(5, true);

        //ui->tabela_automoveis->setEditTriggers(QAbstractItemView::EditTriggers());
        ui->data_venda->show();
        ui->preco_venda->show();
        ui->label_14->show();
        ui->label_15->show();
        ui->vender->show();
        ui->adicionar_automovel->show();
        ui->apagar_automovel->show();

        ui->tabela_abastecimento->setEditTriggers(QAbstractItemView::EditTrigger(true));
        ui->adicionar_abastecimento->show();
        ui->apagar_abastecimento->show();

        ui->tabela_pecas->setEditTriggers(QAbstractItemView::EditTrigger(true));
        ui->adicionar_peca->show();
        ui->apagar_peca->show();
        ui->tabela_manutencao->setEditTriggers(QAbstractItemView::EditTrigger(true));
        ui->adicionar_manutencao->show();
        ui->apagar_manutencao->show();

        ui->tabela_revisao->setEditTriggers(QAbstractItemView::EditTrigger(true));
        ui->adicionar_revisao->show();
        ui->apagar_revisao->show();

        ui->tabela_detalhes_revisao->setEditTriggers(QAbstractItemView::EditTrigger(true));
        ui->adicionar_detalhe->show();
        ui->apagar_detalhe->show();

        ui->comboBox_peca->show();
        ui->comboBox_manutencao->show();
        ui->quantidade_peca->show();
        ui->quantidade_manutencao->show();
        ui->preco_peca->show();
        ui->preco_manutencao->show();

        ui->label_peca->show();
        ui->label_12->show();
        ui->label_tipo_manutencao->show();
        ui->label_13->show();
        ui->label_16->show();
        ui->label_17->show();
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

    if (!query.exec("SELECT idabastecimento, idmatricula,local, data, kms, litros, precolitro FROM abastecimento"))
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

            ui->tabela_abastecimento->setItem(l,7, new QTableWidgetItem(total_string+"€"));
        }
    }
    loaded = true;

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);

}

void MainWindow::on_adicionar_abastecimento_clicked()
{
    QSqlQuery query(db);
    QSqlQuery query2(db);
        if (!query2.exec("SELECT idabastecimento FROM abastecimento")) qDebug() << query2.lastError().text();
        if(!query.exec("INSERT INTO abastecimento(idmatricula,local, data,kms,litros,precolitro) VALUES('', '', '','','','')"))  qDebug() << query.lastError().text();

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
        sql = "SELECT idmatricula FROM automoveis WHERE status=0";
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
        ui->tabela_abastecimento->setCellWidget (numregistos-1, 1, combo_box);

        dateEdit = new QDateEdit();
        dateEdit->setDate(QDate::currentDate());
        dateEdit->setCalendarPopup(true);
        ui->tabela_abastecimento->setCellWidget(numregistos-1,3,dateEdit);
}

void MainWindow::on_apagar_abastecimento_clicked()
{
    int del_id = ui->tabela_abastecimento->item(ui->tabela_abastecimento->currentRow(), 0)->text().toInt();
    ui->tabela_abastecimento->removeRow(ui->tabela_abastecimento->currentRow());

    QSqlQuery query(db);
    query.prepare("DELETE FROM abastecimento WHERE idabastecimento = :id");
    query.bindValue(":id", del_id);

    if (!query.exec()) qDebug() << query.lastError().text();
    FillTable_abastecimento();
}

void MainWindow::on_tabela_abastecimento_cellChanged(int row, int column)
{
    if(!loaded) return;

    QSqlQuery q1(db);
    if (!q1.exec("SELECT idabastecimento FROM abastecimento")) qDebug() << q1.lastError().text();
    int numregistos = 0;
    while( q1.next() )
    {
        numregistos++;
    }

    QSqlQuery query(db) ;
    QString matricula, data;

    if(numregistos <= row+1)
    {
        matricula = combo_box->currentText();
        data = dateEdit->date().toString("dd/MM/yyyy");
    }


    // get record id from column 0
    int id = ui->tabela_abastecimento->item(row, 0)->text().toInt();
    //QString id_string = QString::number(id);
    //ui->label_abas->setText(id_string);



    query.prepare("UPDATE abastecimento SET idmatricula=:idmatricula,local=:local, data=:data, kms=:kms, litros=:litros, precolitro=:preco WHERE idabastecimento=:idabastecimento" );

    if(numregistos <= row+1)
    {
        query.bindValue (":idmatricula", matricula);
        query.bindValue (":data", data);
    }
    else
    {
        query.bindValue (":idmatricula", ui->tabela_abastecimento->item(row, 1)->text());
        query.bindValue (":data", ui->tabela_abastecimento->item(row, 3)->text());
    }
    query.bindValue (":local", ui->tabela_abastecimento->item(row, 2)->text());
    query.bindValue (":kms", ui->tabela_abastecimento->item (row, 4)->text());
    query.bindValue (":litros", ui->tabela_abastecimento->item (row, 5)->text());
    query.bindValue (":preco", ui->tabela_abastecimento->item (row, 6)->text());
    query.bindValue (":idabastecimento", id);

    //QString total_string = ui->tabela_abastecimento->item (row, 5)->text();
    if (!query.exec())
    qDebug() << query.lastError().text();

    //FillTable_abastecimento();

    //double litros = ui->tabela_abastecimento->item(row,6)->text().toDouble();
    //double preco = ui->tabela_abastecimento->item(row,7)->text().toDouble();
    //int total = 5 * 6;
    //QString total_string = QString::number(total);

    //ui->label_abas->setText("total_string");
    //ui->tabela_abastecimento->setItem(row,8, new QTableWidgetItem(total_string+"€"));


}

/*************************/


/***** Revisão *****/
void MainWindow::FillTable_revisao(){

    int num_rows, r, c;
    QSqlQuery q(db);
    loaded = false;

    if(!q.exec("SELECT count(idrevisao) as num_rows FROM revisoes")) qDebug() << q.lastError().text();

    q.first();
    num_rows = q.value(0).toInt();

    ui->tabela_revisao->setRowCount(num_rows);

    if (!q.exec("SELECT idrevisao, idmatricula,oficina,kms, datarevisao,observacoes FROM revisoes"))
    {
        qDebug() << q.lastError().text();
        return ;
    }


    for(r=0, q.first();q.isValid(); q.next(), ++r)
    {
        for(c=0; c<6; c++)
        {
                ui->tabela_revisao->setItem(r, c, new QTableWidgetItem( q.value(c).toString()));
        }
    }

    loaded = true;
}

void MainWindow::on_adicionar_revisao_clicked()
{

    QSqlQuery q(db);
    QSqlQuery q1(db);

        if (!q1.exec("SELECT idrevisao FROM revisoes")) qDebug() << q.lastError().text();
        if(!q.exec("INSERT INTO revisoes (idmatricula, oficina, kms, datarevisao, observacoes) VALUES('', '', '','', '')"))  qDebug() << q.lastError().text();
        FillTable_revisao();
        int numregistos = 0;
        while( q1.next() )
        {
            numregistos++;
        }
        //qDebug() << numregistos;
        ui->tabela_revisao->scrollToBottom();
        QSqlQueryModel *model = new QSqlQueryModel();
        QString sql;
        sql = "SELECT  idmatricula FROM automoveis WHERE status=0";
        QSqlQuery* query = new QSqlQuery(db);
        query->prepare(sql);

        if(!query->exec()){
            qDebug () << "Query Error: " << query->lastError();
        }else{
            qDebug () << "Query Successful: " << query->lastQuery();
        }

        model->setQuery(*query);
        combo_box = new QComboBox(ui->tabela_revisao);
        combo_box->setModel(model);

        dateEdit = new QDateEdit();
        dateEdit->setDate(QDate::currentDate());
        dateEdit->setCalendarPopup(true);


        /*if(numregistos == 0)
        {
            ui->tabela_revisao->setCellWidget (numregistos, 1, combo_box);
            ui->tabela_revisao->setCellWidget(numregistos,4,dateEdit);
        }*/

        //if(numregistos >0)
        //{
            ui->tabela_revisao->setCellWidget (numregistos-1, 1, combo_box);
            ui->tabela_revisao->setCellWidget(numregistos-1,4,dateEdit);
        //}



}

void MainWindow::on_tabela_revisao_cellChanged(int row, int column)
{
    if(!loaded) return;

        QSqlQuery query(db) ;
        QSqlQuery query1(db);
        if (!query1.exec("SELECT idrevisao FROM revisoes")) qDebug() << query1.lastError().text();
        int numregistos = 0;
        while( query1.next() )
        {
            numregistos++;
        }

        int numrows = 0;
        numrows = ui->tabela_revisao->rowCount();

        QString idmatricula, data;
        int id = ui->tabela_revisao->item(row, 0)->text().toInt();
        idmatricula = ui->tabela_revisao->item(row, 1)->text();

        query.prepare("UPDATE revisoes SET idmatricula=:m,oficina=:o, kms=:k, datarevisao=:d, observacoes=:l WHERE idrevisao=:i" );

        if(idmatricula == "" && data == "")
        {
            idmatricula = combo_box->currentText();
            data = dateEdit->date().toString("dd/MM/yyyy");
            query.bindValue (":m", idmatricula);
            query.bindValue (":d", data);
        }
        else
        {
            query.bindValue (":m", ui->tabela_revisao->item(row, 1)->text());
            query.bindValue (":d", ui->tabela_revisao->item(row, 4)->text());
        }
        query.bindValue (":o", ui->tabela_revisao->item (row, 2)->text());
        query.bindValue (":k", ui->tabela_revisao->item (row, 3)->text());
        query.bindValue (":l", ui->tabela_revisao->item (row, 5)->text());
        query.bindValue (":i", id);

        if (!query.exec())
        qDebug() << query.lastError().text();
}

void MainWindow::on_apagar_revisao_clicked()
{
    int del_id = ui->tabela_revisao->item(ui->tabela_revisao->currentRow(), 0)->text().toInt();
    ui->tabela_revisao->removeRow(ui->tabela_revisao->currentRow());

    QSqlQuery query(db);
    query.prepare("DELETE FROM revisoes WHERE idrevisao = :id");
    query.bindValue(":id", del_id);

    if (!query.exec()) qDebug() << query.lastError().text();
    FillTable_revisao();
}
/*******************/



/***** Detalhes Revisão *****/
void MainWindow::FillTable_detalhes_revisao()
{
    QSqlQuery q,q1(db);
    //int id = ui->tabela_revisao->curr;
    int id = ui->tabela_revisao->item(ui->tabela_revisao->currentRow(), 0)->text().toInt();
    int num_rows, r, c;
    QString id_string = ui->tabela_revisao->item(ui->tabela_revisao->currentRow(), 0)->text();

    if(!q.prepare("SELECT count(idrevisao) as num_rows FROM detalhes_revisao WHERE idrevisao=:i")) qDebug() << q.lastError().text();
    q.bindValue(":i",id);
    q.exec();
    q.first();
    num_rows = q.value(0).toInt();

    ui->tabela_detalhes_revisao->setRowCount(num_rows);

    //detalhes_revisao.idpeca, detalhes_revisao.idmanutencao,
    if(!q.prepare("SELECT  iddetalhe, peca, tipomanutencao, quantidade_peca, quantidade_manutencao, precopeca, preco "
                  "FROM detalhes_revisao "
                  "Left JOIN pecas ON detalhes_revisao.idpeca=pecas.idpeca "
                  "Left JOIN manutencao ON detalhes_revisao.idmanutencao = manutencao.idmanutencao "
                  " WHERE idrevisao=:i")) qDebug() << q.lastError().text();
    q.bindValue (":i",id);
    q.exec();
    q.first();

    for(r=0, q.first();q.isValid(); q.next(), ++r){

        ui->tabela_detalhes_revisao->setItem(r, 0, new QTableWidgetItem(q.value(0).toString()));//id detalhe
        ui->tabela_detalhes_revisao->setItem(r, 1, new QTableWidgetItem(id_string));//id revisao
        ui->tabela_detalhes_revisao->setItem(r, 2, new QTableWidgetItem(q.value(1).toString()));//nome peça
        ui->tabela_detalhes_revisao->setItem(r, 3, new QTableWidgetItem(q.value(2).toString()));//nome manutenção
        ui->tabela_detalhes_revisao->setItem(r, 4, new QTableWidgetItem(q.value(3).toString()));//quantidade peça
        ui->tabela_detalhes_revisao->setItem(r, 5, new QTableWidgetItem(q.value(4).toString()));//quantidade manutenção
        //ui->tabela_detrev->setItem(r, 6, new QTableWidgetItem(q.value(4).toString()));
        float x =(q.value(3).toFloat() * q.value(5).toFloat()) + (q.value(4).toFloat() * q.value(6).toFloat());
        QString s = QString::number(x);
        ui->tabela_detalhes_revisao->setItem(r, 6, new QTableWidgetItem(s));
    }
}

void MainWindow::on_adicionar_detalhes_clicked()
{
    FillTable_detalhes_revisao();
    QStackedWidget *stack = ui->stackedWidget;
    stack->setCurrentIndex(2);

    int id_revisao = ui->tabela_revisao->item(ui->tabela_revisao->currentRow(), 0)->text().toInt();

    QSqlQueryModel *model_peca = new QSqlQueryModel();
    model_peca->setQuery("SELECT peca, idpeca, precopeca FROM pecas");
    model_peca->setHeaderData(0,Qt::Horizontal, tr("idpeca"));
    model_peca->setHeaderData(1, Qt::Horizontal, tr("peca"));
    model_peca->setHeaderData(2, Qt::Horizontal, tr("precopeca"));
    ui->comboBox_peca->setModel(model_peca);

    QSqlQueryModel *model_manu = new QSqlQueryModel();
    model_manu->setQuery("SELECT tipomanutencao, idmanutencao, preco FROM manutencao");
    model_manu->setHeaderData(0 ,Qt::Horizontal, tr("idmanutencao"));
    model_manu->setHeaderData(1, Qt::Horizontal, tr("tipomanutencao"));
    model_manu->setHeaderData(3, Qt::Horizontal, tr("preco"));
    ui->comboBox_manutencao->setModel(model_manu);
}

void MainWindow::on_sair_detalhe_clicked()
{
    QTabWidget *tabs = ui->tabWidget;
    QStackedWidget *stack = ui->stackedWidget;
    stack->setCurrentIndex(1);
    tabs->setCurrentIndex(4);
}

void MainWindow::on_adicionar_detalhe_clicked()
{
    QSqlQuery q(db);

    int idrevisao = ui->tabela_revisao->item(ui->tabela_revisao->currentRow(), 0)->text().toInt();
    int row = ui->comboBox_peca->currentIndex();
    QModelIndex idx = ui->comboBox_peca->model()->index(row, 1); // first column
    QVariant data = ui->comboBox_peca->model()->data(idx);
    int idpeca = data.toInt();

    int row_manu = ui->comboBox_manutencao->currentIndex();
    QModelIndex idx_manu = ui->comboBox_manutencao->model()->index(row_manu, 1); // first column
    QVariant data_manu = ui->comboBox_manutencao->model()->data(idx_manu);
    int idmanutencao = data_manu.toInt();

    QString quantidade_peca= ui->quantidade_peca->text();
    QString quantidade_manutencao = ui->quantidade_manutencao->text();

    int iddetalhe = NULL;

    q.prepare("INSERT INTO detalhes_revisao (idrevisao, idpeca, idmanutencao, quantidade_peca, quantidade_manutencao ) VALUES(:idrevisao , :idpeca, :idmanutencao, :qtdpeca, :qtdmanu)");
    q.bindValue(":idrevisao", idrevisao);
    q.bindValue(":idpeca", idpeca);
    q.bindValue(":idmanutencao", idmanutencao);
    q.bindValue(":qtdpeca", quantidade_peca);
    q.bindValue(":qtdmanu", quantidade_manutencao);
    if (!q.exec())
    qDebug() << q.lastError().text();

    FillTable_detalhes_revisao();

}

void MainWindow::on_comboBox_peca_currentIndexChanged(int index)
{
    int row = ui->comboBox_peca->currentIndex();
    QModelIndex idx = ui->comboBox_peca->model()->index(row, 2); // first column
    QVariant data = ui->comboBox_peca->model()->data(idx);
    //int type_id = data.toInt();
    QString preco = data.toString();

    ui->preco_peca->setText(preco);
    ui->preco_peca->setDisabled(true);
    //QMessageBox::information(this,"Login","precopeca = " + preco,"ok");
}

void MainWindow::on_comboBox_manutencao_currentIndexChanged(int index)
{
    int row = ui->comboBox_manutencao->currentIndex();
    QModelIndex idx = ui->comboBox_manutencao->model()->index(row, 2); // first column
    QVariant data = ui->comboBox_manutencao->model()->data(idx);
    //int type_id = data.toInt();
    QString preco = data.toString();

    ui->preco_manutencao->setText(preco);
    ui->preco_manutencao->setDisabled(true);
    //QMessageBox::information(this,"Login","precopeca = " + preco,"ok");
}
/****************************/

/***** User *****/
void MainWindow::on_alterar_password_clicked()
{
    QSqlQuery q = QSqlQuery(db);
    QSqlQuery updateQuery = QSqlQuery(db);

    if (!q.exec("SELECT iduser,username,password FROM users")) qDebug() << q.lastError().text();

    QString username;
    QString password;
    int iduser;
    int numregistos = 0;
    while( q.next() )
    {
        numregistos++;
    }

    qDebug() << numregistos;

    q.first();
    for (int x=0;x<numregistos;x++)
    {

        iduser = q.value(0).toInt();
        username = q.value(1).toString();
        password= q.value(2).toString();
        //qDebug() << id << nome << password;

        if (ui->alt_username->text()==username && ui->alt_password->text()==password && ui->alt_new_password->text()==ui->alt_conf_new_password->text()){

            updateQuery.prepare("UPDATE users SET password=:p WHERE username=:n" );
            updateQuery.bindValue (":p", ui->alt_conf_new_password->text());
            updateQuery.bindValue (":n", ui->alt_username->text());
            updateQuery.exec();
            QMessageBox::information(this,"Password","Password alterada com sucesso!","ok");
            x=numregistos;
        }
        else
        {
            q.next();
        }
    }

    if (!updateQuery.exec())
        qDebug() << updateQuery.lastError().text();

    if (ui->alt_username->text().isEmpty() || ui->alt_password->text().isEmpty() || ui->alt_username->text()!=username || ui->alt_password->text()!=password
        )
    {
        QMessageBox::warning(this,"Password","Utilizador inexistente ou erro na password!","ok");
    }
}

void MainWindow::on_criar_user_clicked()
{
    if (ui->nov_password->text() != ui->nov_conf_password->text()){
        QMessageBox::warning(this,"Criar","Password não corresponde!","ok");

    } else if(ui->nov_username->text().isEmpty() || ui->nov_password->text().isEmpty()){
        QMessageBox::warning(this,"Criar","User ou password em branco!","ok");

    }else{

    QSqlQuery insertQuery = QSqlQuery(db);
    insertQuery.prepare("INSERT INTO users (username, password) VALUES(:username , :password)");
    insertQuery.bindValue(":username", ui->nov_username->text());
    insertQuery.bindValue(":password", ui->nov_password->text());
    if(!insertQuery.exec())
        QMessageBox::warning(this, "Aviso", "User já existente! Tente de novo..", "ok");

    else
        QMessageBox::information(this, "Info", "Novo user criado com sucesso!", "ok");
    }
}

/***************/


void MainWindow::on_pushButton_2_clicked()
{
    QTabWidget *tabs = ui->tabWidget;
    QStackedWidget *stack = ui->stackedWidget;

    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(5, false);

    //ui->tabela_automoveis->setEnabled(false);
    ui->tabela_automoveis->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->data_venda->hide();
    ui->preco_venda->hide();
    ui->label_14->hide();
    ui->label_15->hide();
    ui->vender->hide();
    ui->adicionar_automovel->hide();
    ui->apagar_automovel->hide();

    /*
    ui->data_compra->hide();
    ui->preco_compra->hide();
    ui->comprar->hide();
    ui->adicionar_caracteristica->hide();
    ui->apagar_caracteristica->hide();*/

    ui->tabela_abastecimento->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->adicionar_abastecimento->hide();
    ui->apagar_abastecimento->hide();

    ui->tabela_pecas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->adicionar_peca->hide();
    ui->apagar_peca->hide();
    ui->tabela_manutencao->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->adicionar_manutencao->hide();
    ui->apagar_manutencao->hide();

    ui->tabela_revisao->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->adicionar_revisao->hide();
    ui->apagar_revisao->hide();

    ui->tabela_detalhes_revisao->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->adicionar_detalhe->hide();
    ui->apagar_detalhe->hide();

    ui->comboBox_peca->hide();
    ui->comboBox_manutencao->hide();
    ui->quantidade_peca->hide();
    ui->quantidade_manutencao->hide();
    ui->preco_peca->hide();
    ui->preco_manutencao->hide();

    ui->label_peca->hide();
    ui->label_12->hide();
    ui->label_tipo_manutencao->hide();
    ui->label_13->hide();
    ui->label_16->hide();
    ui->label_17->hide();


    stack->setCurrentIndex(1);
    tabs->setCurrentIndex(0);



}




void MainWindow::on_imprimir_abastecimento_clicked()
{
    int num_rows, r,c;
    QSqlQuery q(db);
    QString data = QDate::currentDate().toString();

    if(!q.exec("SELECT count(idabastecimento) FROM abastecimento")) qDebug() << q.lastError().text();

    q.first();
    num_rows = q.value(0).toInt();
    qDebug() << num_rows;

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOrientation(QPrinter::Landscape);
    printer.setPageSize(QPrinter::A4);
    const QString desktopFolder = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    printer.setOutputFileName(desktopFolder + "/frota.pdf");
    QPainter painter;
    if (! painter.begin(&printer)){
        qWarning("failed to open file");
    }

    QImage logo("../carlog_logo.png");
    QImage logo1 = logo.scaled(100,300,Qt::KeepAspectRatio);
    painter.drawImage(10,10,logo1);

    QFont fonte;
    fonte.setPixelSize(30);
    QFont fonte2;
    fonte2.setPixelSize(20);
    fonte2.setBold(true);
    QFont fonte3;
    fonte3.setPixelSize(15);

    painter.setFont(fonte3);
    for(r=0; r<num_rows; r++){
        for(c=0; c<8; c++){
            painter.drawText(c*100,170+(r*15),(ui->tabela_abastecimento->item(r,c)->text()));
        }
    }

    painter.drawText(Qt::AlignLeft,750, data);
    painter.setFont(fonte);
    painter.drawText(Qt::AlignCenter,100, "Abastecimentos");

    painter.setFont(fonte2);
    for(c=0; c<8; c++){
        painter.drawText(c*100,150,(ui->tabela_abastecimento->horizontalHeaderItem(c)->text()));
    }
    painter.end();

    QMessageBox::information(this,"PDF","Documento gerado no seu Ambiente de Trabalho!","ok");
}
