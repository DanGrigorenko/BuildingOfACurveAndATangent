#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include <QtMath>

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
    void TimerSlot();
    void index1_clicked();
    void index2_clicked();
    void index3_clicked();
    void index4_clicked();
    void index5_clicked();

    void on_comboBox_activated(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    double xBegin, xEnd, h, X;
    int N, current_index = 0;
    QVector<double> x, y;
    QTimer *timer;
    int time;


    void ChangeFunc();
};
#endif // MAINWINDOW_H
