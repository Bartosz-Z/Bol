#ifndef UTILITY_H
#define UTILITY_H

#include <QLineF>
#include <QPointF>


qreal sqrDistance(const QPointF& a, const QPointF& b);
qreal sqrMagnitude(const QPointF& a);
qreal magnitude(const QPointF& a);
qreal distance_to_segment(const QPointF& pl1, const QPointF& pl2, const QPointF& p);
qreal distance_to_segment(const QLineF& segment, const QPointF& p);

qreal sigmoid(qreal value);
qreal fast_sigmoid(qreal value);

#endif // UTILITY_H
