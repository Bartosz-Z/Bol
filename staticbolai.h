#ifndef STATICBOLAI_H
#define STATICBOLAI_H

#include "bolai.h"


class StaticBolAI : public BolAI
{
public:
    StaticBolAI(qreal thrust = 0, qreal torque = 0);
    ~StaticBolAI();

    void compute() override {};

    void linkRotation(const qreal* rotation) override {};

    const qreal* getTorqueLink() const override { return &torque; };
    const qreal* getThrustLink() const override { return &thrust; };
private:
    qreal torque, thrust;
};

#endif // STATICBOLAI_H
