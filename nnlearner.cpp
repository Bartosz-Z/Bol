#include "nnlearner.h"
#include "constants.h"
#include "qdebug.h"
#include "utility.h"
#include <QRandomGenerator>

NNLearner::NNLearner(
        qreal step_size,
        quint32 generation_duration,
        quint32 generations_count,
        quint32 population,
        qreal bol_size,
        qreal max_thrust,
        qreal max_torque)
    : step_size(step_size), generation_duration(generation_duration), generations_count(generations_count)
{
    bols.reserve(population);
    for (quint32 i = 0; i < population; i++)
    {
        bols.emplace_back(bol_size);
        nns.emplaceBack(std::make_shared<NNBolAI>(max_thrust, max_torque));
        bols.back().linkAI(nns.last());
    }
    fittings.resize(population);
}

void NNLearner::train()
{
    for (quint32 gen_i = 0; gen_i < generations_count; gen_i++)
    {
        reset();
        for (quint32 step_i = 0; step_i < generation_duration; step_i++)
            step();
        for (quint32 i = 0; i < bols.size(); i++)
            if (fittings[i] == 0)
                fittings[i] = 2 * generation_duration;
        qDebug().nospace() << "Generation " << gen_i << ":";
        mutate();
    }
    qDebug().nospace() << "Generation " << generations_count << ":";
    reset();
    for (quint32 step_i = 0; step_i < generation_duration; step_i++)
        step();
    for (quint32 i = 0; i < bols.size(); i++)
        if (fittings[i] == 0)
            fittings[i] = 2 * generation_duration;
    qDebug() << "best fitting:" << fittings[getBestNNindex()];
}

void NNLearner::step()
{
    for (quint32 i = 0; i < bols.size(); i++)
    {
        if (!bols[i].isFrozen())
        {
            for (const auto& bound : bounds)
                if (bols[i].collideWith(bound))
                {
                    bols[i].freeze();
                    fittings[i] = steps_taken;
                    break;
                }
            if (!bols[i].isFrozen())
                bols[i].step(step_size);
        }
    }
    steps_taken++;
}

void NNLearner::reset()
{
    for (quint32 i = 0; i < bols.size(); i++)
    {
        bols[i].unfreeze();
        bols[i].setPosition(center);
        bols[i].setRotation(QRandomGenerator::global()->bounded(M_TWO_PI));
        bols[i].setVelocity(0, 0);
        fittings[i] = 0;
    }
    steps_taken = 0;
}

void NNLearner::mutate()
{
    quint32 indecies[bols.size()];
    for (quint32 i = 0; i < bols.size(); i++)
        indecies[i] = i;
    std::sort(indecies, indecies + bols.size(), sort_indices<qreal>(fittings.data()));

    quint32 half_bols_size = bols.size() / 2 + bols.size() % 2;
    for (quint32 i = half_bols_size; i < bols.size(); i++)
    {
        nns[indecies[i]] = std::make_shared<NNBolAI>(*nns[indecies[i - half_bols_size]].get());
        bols[indecies[i]].linkAI(nns[indecies[i]]);
    }
    for (auto& nn : nns)
        nn->mutate();
    qDebug() << "best fitting:" << fittings[indecies[0]];
}

quint32 NNLearner::getBestNNindex() const
{
    quint32 best_index = 0;
    for (quint32 i = 1; i < bols.size(); i++)
        if (fittings[i] > fittings[best_index])
            best_index = i;
    return best_index;
}

std::shared_ptr<NNBolAI> NNLearner::getBestNN() const
{
    return nns[getBestNNindex()];
}

void NNLearner::setBounds(const QRectF& rect)
{
    bounds.emplaceBack(rect.topLeft(), rect.topRight());
    bounds.emplaceBack(rect.topRight(), rect.bottomRight());
    bounds.emplaceBack(rect.bottomRight(), rect.bottomLeft());
    bounds.emplaceBack(rect.bottomLeft(), rect.topLeft());
    center = 0.5 * (rect.bottomRight() - rect.topLeft());
}
