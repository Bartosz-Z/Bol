#include "body.h"

Body::Body(QPointF pos, qreal rotation)
    : position(pos), rotation(rotation) {}

Body::Body(qreal x_pos, qreal y_pos, qreal rotation)
    : position(x_pos, y_pos), rotation(rotation) {}
