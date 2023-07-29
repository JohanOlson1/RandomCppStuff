
#ifndef COMPLEX_COMPLEX
#define COMPLEX_COMPLEX

#include <complex>

namespace sip {

template<typename T>
class complex {
 public:
  T real{0};
  T imag{0};

  complex() = default;
  complex(const T real, const T imag) : real(real), imag(imag) {};

  ~complex() = default;

  complex operator+(const complex& value) const {
    return complex<T>{value.real + real, value.imag + imag};
  };

  complex operator-(const complex& value) const {
    return complex<T>{real - value.real, imag - value.imag};
  };

  complex operator*(const complex& value) const {
    return complex<T>{real * value.real - imag * value.imag, real * value.imag + imag * value.real};
  };
};

}
#endif // COMPLEX_COMPLEX