#include "bolai.h"
#include "constants.h"
#include "mainwindow.h"
#include "nnbolai.h"
#include "nnlearner.h"
#include "staticbolai.h"

#include <QApplication>
#include <QRandomGenerator>

#define BOL_SIZE 10
#define BOL_MAX_THRUST 35

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QRectF windowRect = QRectF(0, 0, w.width(), w.height());

    NNLearner learner = NNLearner(
                FRAMES_DELTA_TIME,
                100,
                BOL_SIZE,
                BOL_MAX_THRUST,
                M_PI,
                &sigmoid);
    learner.setBounds(windowRect);
    learner.train(100, 400 * FRAMES_PER_SECOND);

    auto ai = learner.getBestNN();
    auto bol = std::make_shared<Bol>(
                BOL_SIZE,
                0.5 * (windowRect.bottomRight() - windowRect.topLeft()),
                QRandomGenerator::global()->bounded(M_TWO_PI));
    bol->linkAI(ai);

    GameEngine game_engine(FRAMES_DELTA_TIME);
    game_engine.addBol(bol);

    game_engine.setBounds(windowRect);
    w.setGameEngine(&game_engine);
    w.linkBol(bol, BOL_MAX_THRUST);

    w.show();
    return a.exec();
}
