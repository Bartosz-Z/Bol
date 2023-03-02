#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "bol.h"


class GameEngine
{
public:
    GameEngine(qreal step_size);

    void step();
    void draw(QPainter *painter);

    void addBol(const std::shared_ptr<Bol>& bol) { bols.emplaceBack(bol); }
    void setBounds(const QRectF& rect);
private:
    qreal step_size;
    QVector<std::shared_ptr<Bol>> bols;
    QVector<QLineF> bounds;
};

#endif // GAMEENGINE_H
