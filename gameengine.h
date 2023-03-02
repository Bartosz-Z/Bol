#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "bol.h"


class GameEngine
{
public:
    GameEngine(qreal step_size);

    void step();
    void draw(QPainter *painter);

    void addBol(Bol *bol) { bols.emplaceBack(bol); }
    void setBounds(const QRectF& rect);
private:
    qreal step_size;
    QVector<Bol*> bols;
    QVector<QLineF> bounds;
};

#endif // GAMEENGINE_H
