#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->widget, &Canvas::newPointCreated, this, &MainWindow::addNewPointCoords);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->pushButton_calculate->setEnabled(true);
    ui->widget->clearImage();
    int t = ui->tableWidget->rowCount()-1;
    for(t; t >= 0; t--)
    {
        ui->tableWidget->removeRow(t);
    }
    ui->widget->points.clear();
    ui->widget->polygonPoints.clear();
    ui->plainTextEdit->clear();
    update();
}

void MainWindow::addNewPointCoords()
{
    loadData();
    ui->tableWidget->viewport()->update();
}

void MainWindow::loadData()
{
    auto curr_point = ui->widget->points.back();
    int maxRow = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(maxRow+1);
    ui->tableWidget->setItem (maxRow,
                             0,
                             new QTableWidgetItem(QString::number(curr_point.x())));
    ui->tableWidget->setItem (maxRow,
                             1,
                             new QTableWidgetItem(QString::number(curr_point.y())));
}

void MainWindow::on_pushButton_calculate_clicked()
{
    ui->widget->drawMyPolygon();
    ui->plainTextEdit->clear();
    if (ui->widget->getArea() == 0.0)
    {
        ui->plainTextEdit->insertPlainText("Make at least 3 points, please! :')");
    } else
    {
        ui->plainTextEdit->insertPlainText(QString::number(ui->widget->getArea()));
    }
    ui->pushButton_calculate->setDisabled(true);
}

