#ifndef BOL_H
#define BOL_H

#include "constants.h"
#include "staticbolai.h"

#include <QPainter>
#include <QPointF>


class Bol
{
public:
    Bol(qreal size, const QPointF& pos, qreal rotation = 0);
    Bol(qreal size, qreal x_pos = 0, qreal y_pos = 0, qreal rotation = 0);

    void step(qreal step_size);
    void draw(QPainter *painter) const;

    bool collideWith(const QLineF& segment) const;

    void setMass(qreal m) { mass = m; }
    void setPosition(const QPointF& pos) { position = pos; }
    void setVelocity(const QPointF& v) { *velocity_x = v.x(); *velocity_y = v.y(); }
    void setVelocity(qreal vx, qreal vy) { *velocity_x = vx; *velocity_y = vy; }
    void setRotation(qreal r) { *rotation = r; }

    void linkTorque(cqreal_rptr t) { torque = t; }
    void linkThrust(cqreal_rptr t) { thrust = t; }
    void linkAI(const std::shared_ptr<BolAI>& ai);

    cqreal_ptr getRotationLink() const { return rotation; }
    cqreal_ptr getVelocityXLink() const { return velocity_x; }
    cqreal_ptr getVelocityYLink() const { return velocity_y; }

    qreal getTorque() const { return *torque; }
    qreal getThrust() const { return *thrust; }

    void freeze() { frozen = true; }
    void unfreeze() { frozen = false; }
    bool isFrozen() const { return frozen; }
    QPointF getPosition() const { return position; }
private:
    cqreal_ptr torque, thrust;
    QPointF position;
    const qreal_ptr
        velocity_x = std::make_shared<qreal>(0),
        velocity_y = std::make_shared<qreal>(0),
        rotation;
    qreal size, mass = 1;
    bool frozen = false;

    std::shared_ptr<BolAI> ai;
};

#endif // BOL_H
