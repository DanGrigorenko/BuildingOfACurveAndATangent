#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    h = 0.1;
    xBegin = -3;
    xEnd = 3 + h;

    N = (xEnd - xBegin)/h + 2;

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();

    ui->pushButton->setEnabled(false);
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_5->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ChangeFunc()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
    ui->widget->clearGraphs();
    time = 0;
    timer->start(20);
    X = xBegin;
    x.clear();
    y.clear();
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_comboBox_activated(int index)
{
    if (index == 1) {
        index1_clicked();
        current_index = 1;
    } else  if (index == 2) {
        index2_clicked();
        current_index = 2;
    } else  if (index == 3) {
        index3_clicked();
        current_index = 3;
    } else  if (index == 4) {
        index4_clicked();
        current_index = 4;
    } else  if (index == 5) {
        index5_clicked();
        current_index = 5;
    }
}


void MainWindow::index1_clicked()
{
    xBegin = -3;
    xEnd = 3 + h;

    N = (xEnd - xBegin)/h + 2;

    ui->widget->xAxis->setRange(-4,4);
    ui->widget->yAxis->setRange(0,9);
    ChangeFunc();
}

void MainWindow::index2_clicked()
{
    xBegin = -3;
    xEnd = 3 + h;

    N = (xEnd - xBegin)/h + 2;

    ui->widget->xAxis->setRange(-4,4);
    ui->widget->yAxis->setRange(-2,2);
    ChangeFunc();
}

void MainWindow::index3_clicked()
{
    ui->widget->xAxis->setRange(-4,4);
    ui->widget->yAxis->setRange(-4,5);

    xBegin = -3;
    xEnd = 3 + h;

    N = (xEnd - xBegin)/h + 2;

    ChangeFunc();
}

void MainWindow::index4_clicked()
{
    ui->widget->xAxis->setRange(-4,4);
    ui->widget->yAxis->setRange(-4,5);

    xBegin = -3;
    xEnd = 3 + h;

    N = (xEnd - xBegin)/h + 2;

    ChangeFunc();
}

void MainWindow::index5_clicked()
{
    ui->widget->xAxis->setRange(-4,4);
    ui->widget->yAxis->setRange(-4,5);

    xBegin = -3;
    xEnd = 3 + h;

    N = (xEnd - xBegin)/h + 2;

    ChangeFunc();
}

void MainWindow::TimerSlot()
{
    if (time <= 20*N) {
        if (X <= xEnd) {
            x.push_back(X);
            if (ui->comboBox->currentText() == "Парабола") {
                y.push_back(X*X);
            }
            else if (ui->comboBox->currentText()  == "Синусоида") {
                y.push_back(sin(X));
            }
            else if (ui->comboBox->currentText()  == "Косинусоида") {
                y.push_back(cos(X));
            }
            else if (ui->comboBox->currentText()  == "Гипербола") {
                y.push_back(1/X);
            }
            else if (ui->comboBox->currentText()  == "X^3") {
                y.push_back(pow(X,3));
            }
            X += h;
        }
        time += 20;
    }
    else {
        time = 0;
        timer->stop();
    }


    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();
}

void MainWindow::on_pushButton_clicked()
{
    double f_x, fx, Y1, XX = 0;
    double x, x1, x2;


    x = ui->lineEdit->text().toDouble();
    x1 = ui->lineEdit_2->text().toDouble();
    x2 = ui->lineEdit_4->text().toDouble();

    if (current_index == 1) {
        f_x = 2 * pow(x, 1);
        fx = pow(x, 2);
    } else if (current_index == 2) {
        f_x = cos(x);
        fx = sin(x);
    } else if (current_index == 3) {
        f_x = -sin(x);
        fx = cos(x);
    } else if (current_index == 4) {
        f_x = -(1/pow(x,2));
        fx = 1/x;
    } else {
        f_x = 3 * pow(x, 2);
        fx = pow(x, 3);
    }

    Y1 = fx + f_x * (XX - x);

    ui->lineEdit_3->clear();
    ui->lineEdit_5->clear();

    ui->lineEdit_3->setText(QString::number(f_x,'f',2));
    if (Y1 < 0) {
         ui->lineEdit_5->setText(QString::number(f_x,'f',2)+"x"+"-"+QString::number(Y1,'f',2));
    }
    else {
        ui->lineEdit_5->setText(QString::number(f_x,'f',2)+"x"+"+"+QString::number(Y1,'f',2));
    }

    double aY1 = f_x*x1+Y1;
    double aY2 = f_x*x2+Y1;

    ui->widget->addGraph() ;
    ui->widget->graph(1)->setPen(QPen(Qt::red));
    ui->widget->graph(1)->addData(x1,aY1);
    ui->widget->graph(1)->addData(x2,aY2);

    ui->widget->replot();
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit_3->clear();
    ui->lineEdit_5->clear();
    ui->widget->clearPlottables();
    ui->widget->replot();

    ui->pushButton->setEnabled(false);
}

