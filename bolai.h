#ifndef BOLAI_H
#define BOLAI_H

#include "constants.h"


class BolAI
{
public:
    BolAI();
    virtual ~BolAI();

    virtual void compute() = 0;

    virtual void linkRotation(cqreal_rptr rotation) = 0;
    virtual void linkVelocity(cqreal_rptr velocity_x, cqreal_rptr velocity_y) = 0;

    virtual cqreal_ptr getTorqueLink() const = 0;
    virtual cqreal_ptr getThrustLink() const = 0;
};

#endif // BOLAI_H
