#ifndef BOLAI_H
#define BOLAI_H

#include "qglobal.h"


class BolAI
{
public:
    BolAI();
    virtual ~BolAI();

    virtual void compute() = 0;

    virtual void linkRotation(const qreal* rotation) = 0;

    virtual const qreal* getTorqueLink() const = 0;
    virtual const qreal* getThrustLink() const = 0;
};

#endif // BOLAI_H
