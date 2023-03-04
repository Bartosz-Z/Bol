#include "mainwindow.h"
#include "constants.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=] () {
        game_engine->step();
        if (bol)
        {
            ui->thrust_bar->setValue(qRound(bol->getThrust()));
            ui->thrust_value->setText(QString::number(bol->getThrust(), 'f', 1));
        }
        update();
    });
    timer->start(FRAMES_PER_SECOND);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    game_engine->draw(&painter);
}

void MainWindow::linkBol(const std::shared_ptr<const Bol> bol, qreal max_thrust)
{
    this->bol = bol;
    ui->thrust_bar->setRange(0, qRound(max_thrust));
    ui->bol_status->setEnabled(true);
}
