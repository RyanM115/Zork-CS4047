#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::on_pushButton_clicked()
{
    goRoom("north");
}

void MainWindow::on_pushButton_2_clicked()
{
    goRoom("south");
}

void MainWindow::on_pushButton_3_clicked()
{
    goRoom("east");
}

void MainWindow::on_pushButton_4_clicked()
{
    goRoom("west");
}

void MainWindow::on_pushButton_5_clicked()
{
    goRoom("teleport");
}

void MainWindow::on_pushButton_6_clicked()
{
    goRoom("take");
}
