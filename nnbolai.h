#ifndef NNBOLAI_H
#define NNBOLAI_H

#include "bolai.h"
#include "utility.h"

#define INPUTS 4
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
    void linkRotation(cqreal_rptr rotation) override { inputs[1] = rotation; }
    void linkVelocity(cqreal_rptr velocity_x, cqreal_rptr velocity_y) override
    { inputs[2] = velocity_x; inputs[3] = velocity_y; }

    cqreal_ptr getTorqueLink() const override { return outputs[0]; }
    cqreal_ptr getThrustLink() const override { return outputs[1]; }
private:
    qreal max_torque, max_thrust;

    cqreal_ptr inputs[INPUTS];
    qreal_ptr outputs[OUTPUTS];

    qreal weights_ih[INPUTS][HIDDEN], weights_ho[HIDDEN][OUTPUTS];

    qreal (*activation_function)(qreal);
};

#endif // NNBOLAI_H
