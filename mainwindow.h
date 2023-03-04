#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gameengine.h"
#include <QMainWindow>
#include <QProgressBar>

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
    void linkBol(const std::shared_ptr<const Bol> bol, qreal max_thrust);

private:
    Ui::MainWindow *ui;

    GameEngine *game_engine = nullptr;
    std::shared_ptr<const Bol> bol;

protected:
    void paintEvent(QPaintEvent *event);
};
#endif // MAINWINDOW_H
