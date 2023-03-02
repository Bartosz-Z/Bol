#ifndef UTILITY_H
#define UTILITY_H

#include <QLineF>
#include <QPointF>


qreal sqrDistance(const QPointF& a, const QPointF& b);
qreal sqrMagnitude(const QPointF& a);
qreal sqrMagnitude(qreal x, qreal y);
qreal magnitude(const QPointF& a);
qreal magnitude(qreal x, qreal y);
qreal distance_to_segment(const QPointF& pl1, const QPointF& pl2, const QPointF& p);
qreal distance_to_segment(const QLineF& segment, const QPointF& p);

qreal sigmoid(qreal value);
qreal fast_sigmoid(qreal value);

template < typename T >
class sort_indices
{
   private:
     const T* mparr;
   public:
     sort_indices(const T* parr) : mparr(parr) {}
     bool operator()(quint32 i, quint32 j) const { return mparr[i] > mparr[j]; }
};

#endif // UTILITY_H
