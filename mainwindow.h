#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QPixmap>
#include <QTableWidget>
#include <QDateEdit>
#include <QPrinter>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:

    void on_adicionar_caracteristica_clicked();
    void on_apagar_caracteristica_clicked();
    void on_tabela_caracteristicas_cellChanged(int row, int column);

    void on_loginbutton_clicked();
    void on_logout_clicked();

    void on_adicionar_peca_clicked();
    void on_apagar_peca_clicked();
    void on_tabela_pecas_cellChanged(int row, int column);

    void on_adicionar_manutencao_clicked();

    void on_apagar_manutencao_clicked();

    void on_tabela_manutencao_cellChanged(int row, int column);

    void on_comprar_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_vender_clicked();

    void on_adicionar_abastecimento_clicked();

    void on_apagar_abastecimento_clicked();

    void on_tabela_abastecimento_cellChanged(int row, int column);

    void on_adicionar_revisao_clicked();

    void on_tabela_revisao_cellChanged(int row, int column);

    void on_apagar_revisao_clicked();

    void on_adicionar_detalhes_clicked();

    void on_sair_detalhe_clicked();

    void on_adicionar_detalhe_clicked();

    void on_comboBox_peca_currentIndexChanged(int index);

    void on_comboBox_manutencao_currentIndexChanged(int index);

    void on_alterar_password_clicked();

    void on_criar_user_clicked();
    
    void on_pushButton_2_clicked();

    void on_imprimir_abastecimento_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    bool loaded;
    QComboBox *combo_box;
    QComboBox *combo_box_a;
    QDateEdit *dateEdit;
    void FillTable();
    void FillTable_pecas();
    void FillTable_manutencao();
    void FillTable_automoveis();
    void FillTable_abastecimento();
    void FillTable_revisao();
    void FillTable_detalhes_revisao();


};

#endif // MAINWINDOW_H
