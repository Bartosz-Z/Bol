#include "nnbolai.h"
#include <QRandomGenerator>

NNBolAI::NNBolAI(qreal max_thrust, qreal max_torque, qreal (*activation_function)(qreal))
    : max_torque(max_torque), max_thrust(max_thrust), activation_function(activation_function)
{
    inputs[0] = std::make_shared<const qreal>(1);
    for (quint32 i = 0; i < INPUTS; i++)
        for (quint32 j = 0; j < HIDDEN; j++)
            weights_ih[i][j] = 2 * QRandomGenerator::global()->generateDouble() - 1;
    for (quint32 i = 0; i < HIDDEN; i++)
        for (quint32 j = 0; j < OUTPUTS; j++)
            weights_ho[i][j] = 2 * QRandomGenerator::global()->generateDouble() - 1;
    for (quint32 i = 0; i < OUTPUTS; i++)
        outputs[i] = std::make_shared<qreal>();
}

NNBolAI::~NNBolAI() {}

void NNBolAI::compute()
{
    qreal hidden_values[HIDDEN];
    for (quint32 i = 0; i < HIDDEN; i++)
    {
        hidden_values[i] = 0;
        for (quint32 j = 0; j < INPUTS; j++)
            hidden_values[i] += *(inputs[j]) * weights_ih[j][i];
        hidden_values[i] = activation_function(hidden_values[i]);
    }
    for (quint32 i = 0; i < OUTPUTS; i++)
    {
        *(outputs[i]) = 0;
        for (quint32 j = 0; j < HIDDEN; j++)
            *(outputs[i]) += hidden_values[j] * weights_ho[j][i];
        *(outputs[i]) = activation_function(*(outputs[i]));
    }

    *(outputs[0]) = (*(outputs[0]) - 0.5) * max_torque;
    *(outputs[1]) *= max_thrust;
}

void NNBolAI::mutate()
{
    for (quint32 i = 0; i < INPUTS; i++)
        for (quint32 j = 0; j < HIDDEN; j++)
            if (QRandomGenerator::global()->generateDouble() < MUTATION_WEIGHT_CHANCE)
                weights_ih[i][j] += 2 * MUTATION_WEIGHT_STRENGTH * QRandomGenerator::global()->generateDouble() - MUTATION_WEIGHT_STRENGTH;
    for (quint32 i = 0; i < HIDDEN; i++)
        for (quint32 j = 0; j < OUTPUTS; j++)
            if (QRandomGenerator::global()->generateDouble() < MUTATION_WEIGHT_CHANCE)
                weights_ho[i][j] += 2 * MUTATION_WEIGHT_STRENGTH * QRandomGenerator::global()->generateDouble() - MUTATION_WEIGHT_STRENGTH;
}
