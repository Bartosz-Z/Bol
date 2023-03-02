#ifndef NNBOLAI_H
#define NNBOLAI_H

#include "bolai.h"
#include "utility.h"

#define INPUTS 1
#define HIDDEN 2
#define OUTPUTS 2

class NNBolAI : public BolAI
{
public:
    NNBolAI(qreal max_thrust, qreal max_torque, qreal (*activation_function)(qreal) = &fast_sigmoid);
    ~NNBolAI();

    void compute() override;

    void mutate();

    void setActivationFunction(qreal (*activation_function)(qreal)) { this->activation_function = activation_function; }
    void linkRotation(const qreal* rotation) override { inputs[0] = rotation; }

    const qreal* getTorqueLink() const override { return outputs; }
    const qreal* getThrustLink() const override { return outputs + 1; }
private:
    qreal max_torque, max_thrust;

    const qreal *inputs[INPUTS];
    qreal outputs[OUTPUTS];

    qreal weights_ih[INPUTS][HIDDEN], weights_ho[HIDDEN][OUTPUTS];

    qreal (*activation_function)(qreal);
};

#endif // NNBOLAI_H
