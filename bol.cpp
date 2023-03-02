#include "bol.h"
#include "constants.h"
#include "qdebug.h"
#include "utility.h"
#include <QtMath>

Bol::Bol(qreal size, const QPointF& pos, qreal rotation)
    : position(pos), rotation(std::make_shared<qreal>(rotation)), size(size)
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
    qreal mag_const = magnitude(*velocity_x, *velocity_y) * SPHERE_DRAG_CONSTANT * size * size;
    qreal
            acceleration_x = -*thrust * qCos(*rotation) - *velocity_x * mag_const,
            acceleration_y = -*thrust * qSin(*rotation) - *velocity_y * mag_const;
    acceleration_x /= mass;
    acceleration_y /= mass;
    acceleration_y += GRAVITY;
    *velocity_x += acceleration_x * step_size;
    *velocity_y += acceleration_y * step_size;
    position.rx() += *velocity_x * step_size;
    position.ry() += *velocity_y * step_size;
    *rotation += *torque * step_size;
    while (*rotation >= M_TWO_PI)
        *rotation -= M_TWO_PI;
    while (*rotation < 0)
        *rotation += M_TWO_PI;
}

void Bol::draw(QPainter *painter) const
{
    painter->setPen(Qt::black);
    painter->drawEllipse(position, size, size);
    painter->setPen(QPen(Qt::red, 4));
    painter->drawPoint(position.x() + size * qCos(*rotation), position.y() + size * qSin(*rotation));
}

void Bol::linkAI(const std::shared_ptr<BolAI>& ai)
{
    this->ai = ai;
    linkTorque(ai->getTorqueLink());
    linkThrust(ai->getThrustLink());
    ai->linkRotation(getRotationLink());
    ai->linkVelocity(getVelocityXLink(), getVelocityYLink());
}

bool Bol::collideWith(const QLineF& segment) const
{
    return distance_to_segment(segment, position) < size * size;
}
