#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Curvas de Bézier, OpenGL3, Qt6, C++");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_1_clicked()
{
    if (ui->radioButton_1->isChecked())
    {
        algorithm = 0;
        ui->widget->set_algorithm(algorithm);
    }
}

void MainWindow::on_radioButton_2_clicked()
{
    if (ui->radioButton_2->isChecked())
    {
        algorithm = 1;
        ui->widget->set_algorithm(algorithm);
    }
}
