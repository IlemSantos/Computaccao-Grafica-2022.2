#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Recorte, OpenGL3, Qt6, C++");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_1_clicked()
{
    polygons = 0;
    if (ui->radioButton_1->isChecked())
        ui->widget->set_polygon(polygons);
}

void MainWindow::on_radioButton_2_clicked()
{
    polygons = 1;
    if (ui->radioButton_2->isChecked())
        ui->widget->set_polygon(polygons);
}

void MainWindow::on_radioButton_3_clicked()
{
    polygons = 2;
    if (ui->radioButton_3->isChecked())
        ui->widget->set_polygon(polygons);
}

void MainWindow::on_radioButton_4_clicked()
{
    polygons = 3;
    if (ui->radioButton_4->isChecked())
        ui->widget->set_polygon(polygons);
}

void MainWindow::on_pushButton_clicked()
{
    ui->widget->set_clipping();
}