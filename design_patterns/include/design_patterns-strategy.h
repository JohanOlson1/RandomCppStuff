
#ifndef DESIGN_PATTERNS_STRATEGY
#define DESIGN_PATTERNS_STRATEGY

#include <iostream>
#include <memory>

namespace pat {

class Strategy {
 public:
  ~Strategy() = default;

  virtual void DoAlgorithm() = 0;   
};

class StrategyA : public Strategy {
 public:
  void DoAlgorithm() override {
    std::cout << "StrategyA \n";
  }
};

class StrategyB : public Strategy {
 public:
  void DoAlgorithm() override {
    std::cout << "StrategyB \n";
  }
};

class StrategyContext {
 public:
  explicit StrategyContext(std::unique_ptr<pat::Strategy>&& strategy = {}) : strategy_(std::move(strategy)) {};

  void SetStrategy(std::unique_ptr<pat::Strategy>&& strategy = {}) {
    strategy_ = std::move(strategy);
  }

  void Process() {
    if(strategy_) {
      strategy_->DoAlgorithm();
    } else {
      std::cout << "Strategy not set \n";
    }
  }

 private:
  std::unique_ptr<pat::Strategy> strategy_;
};

}

#endif // DESIGN_PATTERNS_STRATEGY