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
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
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
    game_engine->step();
}
