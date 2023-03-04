#ifndef NNLEARNER_H
#define NNLEARNER_H

#include "bol.h"
#include "nnbolai.h"

class NNLearner
{
public:
    NNLearner(qreal step_size, quint32 population,
              qreal bol_size, qreal max_thrust, qreal max_torque, qreal (*activation_function)(qreal) = &fast_sigmoid);

    void train(quint32 generations_count, quint32 generation_duration);
    std::shared_ptr<NNBolAI> getBestNN() const;

    void setBounds(const QRectF& rect);
private:
    void step();
    void reset();
    void mutate();

    quint32 getBestNNindex() const;

    qreal step_size;
    quint32 steps_taken;
    std::vector<Bol> bols;
    QVector<std::shared_ptr<NNBolAI>> nns;
    QVector<qreal> fittings;
    QVector<QLineF> bounds;
    QPointF center;
};

#endif // NNLEARNER_H
