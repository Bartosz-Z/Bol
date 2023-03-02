#include "bolai.h"
#include "constants.h"
#include "mainwindow.h"
#include "nnbolai.h"
#include "staticbolai.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameEngine game_engine(FRAMES_DELTA_TIME);
    Bol bol(10, 200, 200, M_PI_4 + M_PI_2);
    std::shared_ptr<BolAI> bol_ai = std::make_shared<NNBolAI>(20, M_PI_4);
    bol.linkAI(bol_ai);
    game_engine.addBol(&bol);

    MainWindow w;
    game_engine.setBounds(QRectF(0, 0, w.width(), w.height()));
    w.setGameEngine(&game_engine);

    w.show();
    return a.exec();
}
