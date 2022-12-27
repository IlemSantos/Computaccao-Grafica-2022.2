#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Preenchimento, OpenGL3, Qt6, C++");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->widget->set_algorithm(algorithm);
}

void MainWindow::on_radioButton_1_clicked()
{
    if (ui->radioButton_1->isChecked())
        algorithm = 0;
}

void MainWindow::on_radioButton_2_clicked()
{
    if (ui->radioButton_2->isChecked())
        algorithm = 1;
}

void MainWindow::on_radioButton_3_clicked()
{
    shape = 0;
    if (ui->radioButton_3->isChecked())
    {
        ui->widget->set_shapes(shape);
        ui->widget->set_algorithm(-1);
    }
}

void MainWindow::on_radioButton_4_clicked()
{
    shape = 1;
    if (ui->radioButton_4->isChecked())
    {
        ui->widget->set_shapes(shape);
        ui->widget->set_algorithm(-1);
    }
}

void MainWindow::on_radioButton_5_clicked()
{
    shape = 2;
    if (ui->radioButton_5->isChecked())
    {
        ui->widget->set_shapes(shape);
        ui->widget->set_algorithm(-1);
    }
}

void MainWindow::on_radioButton_6_clicked()
{
    shape = 3;
    if (ui->radioButton_6->isChecked())
    {
        ui->widget->set_shapes(shape);
        ui->widget->set_algorithm(-1);
    }
}
