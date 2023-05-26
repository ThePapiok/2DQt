#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_suwak1_valueChanged(int value)
{
    ui->widget->setTranslajcax(value);
}

void MainWindow::on_suwak2_valueChanged(int value)
{
    ui->widget->setTranslajcay(value);
}
void MainWindow::on_suwak3_valueChanged(int value)
{
    if(value<=0)
    {
        ui->widget->setSkalax(1/(float)(2+(-value)));
    }
    else
    {
        ui->widget->setSkalax(value);
    }
}
void MainWindow::on_suwak4_valueChanged(int value)
{
    if(value<=0)
    {
        ui->widget->setSkalay(1/(float)(2+(-value)));
    }
    else
    {
        ui->widget->setSkalay(value);
    }
}
void MainWindow::on_suwak5_valueChanged(int value)
{
    ui->widget->setObrotalfa(value);
}
void MainWindow::on_suwak6_valueChanged(int value)
{
    ui->widget->setPochyleniea(value);
}
void MainWindow::on_suwak7_valueChanged(int value)
{
    ui->widget->setPochylenieb(value);
}


