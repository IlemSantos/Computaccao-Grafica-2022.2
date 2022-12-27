#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Rasterização de Circunferências, OpenGL3, Qt6, C++");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->widget->set_algorithm(algorithm);
    ui->widget->set_point(ui->spinBox->value(), ui->spinBox_2->value());
    ui->widget->set_radius(ui->spinBox_3->value());
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
    if (ui->radioButton_3->isChecked())
        algorithm = 2;
}
