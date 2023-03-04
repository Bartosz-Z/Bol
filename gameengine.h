#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "bol.h"
#include <QMutex>


class GameEngine
{
public:
    GameEngine(qreal step_size);

    void step();
    void draw(QPainter *painter) const;

    void addBol(const std::shared_ptr<Bol>& bol) { bols.emplaceBack(bol); }
    void setBounds(const QRectF& rect);
private:
    QMutex mutex;
    qreal step_size;
    QVector<std::shared_ptr<Bol>> bols;
    QVector<QLineF> bounds;
};

#endif // GAMEENGINE_H
