#ifndef BODY_H
#define BODY_H

#include <QPainter>


class Body
{
public:
    Body(QPointF pos = QPointF(), qreal rotation = 0);
    Body(qreal x_pos = 0, qreal y_pos = 0, qreal rotation = 0);

    void step(qreal step_size);
    virtual void draw(QPainter *painter) = 0;

    void setMass(qreal m) { mass = m; }
    void linkTorque(const std::shared_ptr<const qreal>& t) { torque = t; }
    void setTorque(qreal t) { torque = std::make_shared<const qreal>(t); }
    void linkThrust(const std::shared_ptr<const qreal>& t) { thrust = t; }
    void setThrust(qreal t) { thrust = std::make_shared<const qreal>(t); }
private:
    std::shared_ptr<const qreal>
        torque = std::make_shared<const qreal>(0),
        thrust = std::make_shared<const qreal>(0);
    QPointF position, velocity = QPointF();
    qreal rotation, mass = 1;
};

#endif // BODY_H
