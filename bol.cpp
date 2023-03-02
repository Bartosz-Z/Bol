#include "bol.h"
#include "constants.h"
#include "qdebug.h"
#include "utility.h"
#include <QtMath>

Bol::Bol(qreal size, const QPointF& pos, qreal rotation)
    : position(pos), rotation(rotation), size(size)
{
    linkAI(std::make_shared<StaticBolAI>());
}

Bol::Bol(qreal size, qreal x_pos, qreal y_pos, qreal rotation)
    : Bol(size, QPointF(x_pos, y_pos), rotation) {}

void Bol::step(qreal step_size)
{
    if (frozen)
        return;
    ai->compute();
    QPointF acceleration = -velocity * magnitude(velocity) * SPHERE_DRAG_CONSTANT * size * size;
    acceleration.rx() -= *thrust * qCos(rotation);
    acceleration.ry() -= *thrust * qSin(rotation) - GRAVITY;
    acceleration.rx() /= mass;
    acceleration.ry() /= mass;
    position.rx() += velocity.x() * step_size;
    position.ry() += velocity.y() * step_size;
    velocity.rx() += acceleration.x() * step_size;
    velocity.ry() += acceleration.y() * step_size;
    rotation += *torque * step_size;
    while (rotation >= M_TWO_PI)
        rotation -= M_TWO_PI;
    while (rotation < 0)
        rotation += M_TWO_PI;
}

void Bol::draw(QPainter *painter) const
{
    painter->setPen(QPen(Qt::blue, 10));
    painter->setPen(Qt::black);
    painter->drawEllipse(position, size, size);
    painter->setPen(QPen(Qt::red, 4));
    painter->drawPoint(position.x() + size * qCos(rotation), position.y() + size * qSin(rotation));
}

void Bol::linkAI(const std::shared_ptr<BolAI>& ai)
{
    this->ai = ai;
    torque = ai->getTorqueLink();
    thrust = ai->getThrustLink();
    ai->linkRotation(getRotationLink());
}

bool Bol::isCollisionWith(const QLineF& segment) const
{
    return distance_to_segment(segment, position) < size * size;
}
