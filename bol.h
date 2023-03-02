#ifndef BOL_H
#define BOL_H

#include "staticbolai.h"

#include <QPainter>
#include <QPointF>


class Bol
{
public:
    Bol(qreal size, const QPointF& pos = QPointF(), qreal rotation = 0);
    Bol(qreal size, qreal x_pos = 0, qreal y_pos = 0, qreal rotation = 0);

    void step(qreal step_size);
    void draw(QPainter *painter) const;

    bool isCollisionWith(const QLineF& segment) const;

    void setMass(qreal m) { mass = m; }
    void setPosition(const QPointF& pos) { position = pos; }
    void linkTorque(const qreal* t) { torque = t; }
    void linkThrust(const qreal* t) { thrust = t; }
    void linkAI(const std::shared_ptr<BolAI>& ai);

    const qreal* getRotationLink() const { return &rotation; }

    void freeze() { frozen = true; }
    void unfreeze() { frozen = false; }
    bool isFrozen() const { return frozen; }
    QPointF getPosition() const { return position; }
private:
    const qreal *torque = nullptr, *thrust = nullptr;
    QPointF position, velocity = QPointF();
    qreal rotation, size, mass = 1;
    bool frozen = false;

    std::shared_ptr<BolAI> ai;
};

#endif // BOL_H
