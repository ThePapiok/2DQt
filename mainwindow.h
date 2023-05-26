#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_suwak1_valueChanged(int value);
    void on_suwak2_valueChanged(int value);
    void on_suwak3_valueChanged(int value);
    void on_suwak4_valueChanged(int value);
    void on_suwak5_valueChanged(int value);
    void on_suwak6_valueChanged(int value);
    void on_suwak7_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
