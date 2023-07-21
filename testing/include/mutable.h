#ifndef TESTING_MUTABLE
#define TESTING_MUTABLE

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

void TestMutable();

#endif // TESTING_MUTABLE