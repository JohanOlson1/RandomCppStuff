
#ifndef COMPLEX_COMPLEX
#define COMPLEX_COMPLEX

#include <complex>

namespace app {

template<typename T>
class complex {
 public:
  complex() = default;
  complex(const T real, const T imag) : real_(real), imag_(imag) {};

  ~complex() = default;

  complex operator+(const complex& c) const {
    return complex<T>{c.real_ + real_, c.imag_ + imag_};
  };

  complex operator-(const complex& c) const {
    return complex<T>{real_ - c.real_, imag_ - c.imag_};
  };

  complex operator*(const complex& c) const {
    return complex<T>{real_ * c.real_ - imag_ * c.imag_, real_ * c.imag_ + imag_ * c.real_};
  };

  complex operator/(const complex& c) const {
    const T divisor{c.real_ * c.real_ + c.imag_ * c.imag_};
    return complex<T>{(real_ * c.real_ + imag_ * c.imag_) / divisor, (imag_ * c.real_ - real_ * c.imag_) / divisor};
  }

  T real_{0};
  T imag_{0};
};

}
#endif // COMPLEX_COMPLEX