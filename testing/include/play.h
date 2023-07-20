#ifndef TESTING_PLAY
#define TESTING_PLAY

class MutableTest {
  public:
    int GetValue() const {
        counter++;
        return value;
    }

    int GetCounter() const {
        return counter;
    }

  private:
    int value{5};
    mutable int counter{0};
};

#endif // TESTING_PLAY