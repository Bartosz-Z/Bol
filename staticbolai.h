#ifndef STATICBOLAI_H
#define STATICBOLAI_H

#include "bolai.h"


class StaticBolAI : public BolAI
{
public:
    StaticBolAI(qreal thrust = 0, qreal torque = 0);
    ~StaticBolAI();

    void compute() override {};

    void linkRotation(cqreal_rptr rotation) override {};
    void linkVelocity(cqreal_rptr velocity_x, cqreal_rptr velocity_y) override {}

    cqreal_ptr getTorqueLink() const override { return torque; };
    cqreal_ptr getThrustLink() const override { return thrust; };
private:
    const cqreal_ptr torque, thrust;
};

#endif // STATICBOLAI_H
