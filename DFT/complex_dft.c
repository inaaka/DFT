/*
set of functions for complex number
*/

#include "math.h"
#include "complex_dft.h"

/* make new complex number */
dftComplex newComplex(double a, double b)
{
  dftComplex result;

  result.real = a;
  result.imag = b;

  return result;
}

/* addition of complex numbers */
dftComplex addComplex(dftComplex a, dftComplex b)
{
  dftComplex result;

  result.real = a.real + b.real;
  result.imag = a.imag + b.imag;

  return result;
}

/* multiplication of complex numbers */
dftComplex mulComplex(dftComplex a, dftComplex b)
{
  dftComplex result;

  result.real = a.real * b.real - a.imag * b.imag;
  result.imag = a.real * b.imag + a.imag * b.real;

  return result;
}

/* absolute value of complex numbers */
double absComplex(dftComplex a)
{
  double result;

  result = sqrt(a.real * a.real + a.imag * a.imag);

  return result;
}

/* complex number to the power of exp  */
dftComplex expComplex(dftComplex x)
{
  double e_r;
  dftComplex result;

  e_r = exp(x.real);

  result.real = e_r * cos(x.imag);
  result.imag = e_r * sin(x.imag);

  return result;
}