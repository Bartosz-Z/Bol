#include "bolai.h"
#include "constants.h"
#include "mainwindow.h"
#include "nnbolai.h"
#include "nnlearner.h"
#include "staticbolai.h"

#include <QApplication>
#include <QRandomGenerator>

#define BOL_SIZE 10

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QRectF windowRect = QRectF(0, 0, w.width(), w.height());

    NNLearner learner = NNLearner(
                FRAMES_DELTA_TIME,
                400 * FRAMES_PER_SECOND,
                50,
                200,
                BOL_SIZE,
                20,
                M_PI_2);
    learner.setBounds(windowRect);
    learner.train();

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

    w.show();
    return a.exec();
}
