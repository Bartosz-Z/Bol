#include "gameengine.h"

GameEngine::GameEngine(qreal step_size)
    : step_size(step_size)
{

}

void GameEngine::step()
{
    foreach (auto* bol, bols)
    {
        if (!bol->isFrozen())
        {
            QPointF bol_pos = bol->getPosition();
            bol->step(step_size);
            foreach(const auto& bound, bounds)
                if (bol->isCollisionWith(bound))
                {
                    bol->setPosition(bol_pos);
                    bol->freeze();
                    break;
                }
        }
    }
}

void GameEngine::draw(QPainter *painter)
{
    foreach (auto* bol, bols)
        bol->draw(painter);
}

void GameEngine::setBounds(const QRectF& rect)
{
    bounds.emplaceBack(rect.topLeft(), rect.topRight());
    bounds.emplaceBack(rect.topRight(), rect.bottomRight());
    bounds.emplaceBack(rect.bottomRight(), rect.bottomLeft());
    bounds.emplaceBack(rect.bottomLeft(), rect.topLeft());
}
