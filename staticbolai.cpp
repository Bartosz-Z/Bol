#include "staticbolai.h"

StaticBolAI::StaticBolAI(qreal thrust, qreal torque)
    : torque(std::make_shared<const qreal>(torque)), thrust(std::make_shared<const qreal>(thrust)) {}
StaticBolAI::~StaticBolAI() {}
