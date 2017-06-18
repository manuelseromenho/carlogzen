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

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    bool loaded;
    //QComboBox* aa;
    //QDateEdit *dateEdit;
    void FillTable();
};

#endif // MAINWINDOW_H
