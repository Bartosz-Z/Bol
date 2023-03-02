#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gameengine.h"
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

    void setGameEngine(GameEngine *engine) { game_engine = engine; }

private:
    Ui::MainWindow *ui;
    GameEngine *game_engine = nullptr;

protected:
    void paintEvent(QPaintEvent *event);
};
#endif // MAINWINDOW_H
