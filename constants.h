#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "qglobal.h"
#include <memory>

#define FRAMES_PER_SECOND 20
#define FRAMES_DELTA_TIME 0.05

#define M_TWO_PI 6.28318530717958647693
#define GRAVITY 9.75
#define SPHERE_DRAG_COEF 0.47
//#define AIR_DENSITY 1.205
#define AIR_DENSITY 0.0001205
// SPHERE_DRAG_CONSTANT = 0.5 * AIR_DENSITY * SPHERE_DRAG_COEF * PI
//#define SPHERE_DRAG_CONSTANT 0.8896204996802897003
#define SPHERE_DRAG_CONSTANT 0.000088962049968029


#define MUTATION_WEIGHT_CHANCE 0.3
#define MUTATION_WEIGHT_STRENGTH 0.05

typedef const std::shared_ptr<const qreal>& cqreal_rptr;
typedef std::shared_ptr<const qreal> cqreal_ptr;
typedef std::shared_ptr<qreal> qreal_ptr;

#endif // CONSTANTS_H
