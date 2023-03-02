#include "utility.h"
#include "qmath.h"

qreal sqrDistance(const QPointF& a, const QPointF& b)
{
    qreal dx = b.x() - a.x();
    qreal dy = b.y() - a.y();
    return dx * dx + dy * dy;
}

qreal sqrMagnitude(const QPointF& a)
{
    return a.x() * a.x() + a.y() * a.y();
}

qreal sqrMagnitude(qreal x, qreal y)
{
    return x * x + y * y;
}

qreal magnitude(const QPointF& a)
{
    return qSqrt(a.x() * a.x() + a.y() * a.y());
}

qreal magnitude(qreal x, qreal y)
{
    return qSqrt(x * x + y * y);
}

qreal distance_to_segment(const QPointF& pl1, const QPointF& pl2, const QPointF& p)
{
    qreal diff_pl1_p_x = pl1.x() - p.x();
    qreal diff_pl1_p_y = pl1.y() - p.y();
    qreal diff_pl2_p_x = pl2.x() - p.x();
    qreal diff_pl2_p_y = pl2.y() - p.y();
    qreal a = diff_pl1_p_x * diff_pl1_p_x + diff_pl1_p_y * diff_pl1_p_y;
    qreal b = diff_pl2_p_x * diff_pl2_p_x + diff_pl2_p_y * diff_pl2_p_y;

    qreal pl_dx = pl2.x() - pl1.x();
    qreal pl_dy = pl2.y() - pl1.y();
    qreal pl_length = pl_dx * pl_dx + pl_dy * pl_dy;

    qreal nominator = pl_dx * diff_pl1_p_y - diff_pl1_p_x * pl_dy;
    qreal h = nominator * nominator / pl_length;

    qreal condition = h + pl_length;
    if (a < condition && b < condition)
        return h;
    return qMin(a, b);
}

qreal distance_to_segment(const QLineF& segment, const QPointF& p)
{
    qreal diff_pl1_p_x = segment.p1().x() - p.x();
    qreal diff_pl1_p_y = segment.p1().y() - p.y();
    qreal diff_pl2_p_x = segment.p2().x() - p.x();
    qreal diff_pl2_p_y = segment.p2().y() - p.y();
    qreal a = diff_pl1_p_x * diff_pl1_p_x + diff_pl1_p_y * diff_pl1_p_y;
    qreal b = diff_pl2_p_x * diff_pl2_p_x + diff_pl2_p_y * diff_pl2_p_y;

    qreal pl_dx = segment.p2().x() - segment.p1().x();
    qreal pl_dy = segment.p2().y() - segment.p1().y();
    qreal pl_length = pl_dx * pl_dx + pl_dy * pl_dy;

    qreal nominator = pl_dx * diff_pl1_p_y - diff_pl1_p_x * pl_dy;
    qreal h = nominator * nominator / pl_length;

    qreal condition = h + pl_length;
    if (a < condition && b < condition)
        return h;
    return qMin(a, b);
}

qreal sigmoid(qreal value)
{
    return 1 / (1 + qExp(-value));
}

qreal fast_sigmoid(qreal value)
{
    return 0.5 * value / (1 + qAbs(value)) + 0.5;
}
