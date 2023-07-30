
#include <memory>

#include "design_patterns-strategy.h"

void StrategyClient() {
  pat::StrategyContext strategy_context{std::make_unique<pat::StrategyA>()};
  strategy_context.Process();

  strategy_context.SetStrategy(std::make_unique<pat::StrategyB>());
  strategy_context.Process();

  strategy_context.SetStrategy();
  strategy_context.Process();
}

int main() {
  StrategyClient();

  return 1;
}