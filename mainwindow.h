#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCursor>
#include "canvas.h"
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QCursor mouse_cursor;
private slots:
    void on_pushButton_clear_clicked();
    void addNewPointCoords();
    void on_pushButton_calculate_clicked();

private:
    Ui::MainWindow *ui;
    void loadData();

};
#endif // MAINWINDOW_H
