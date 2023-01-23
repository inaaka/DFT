/*
set of functions for complex number
*/

/* complex number */
typedef struct _dftComplex
{
  double real;
  double imag;
} dftComplex;

/* make new complex number */
dftComplex newComplex(double a, double b);
/* addition of complex numbers */
dftComplex addComplex(dftComplex a, dftComplex b);
/* subtraction of complex numbers */
dftComplex subComplex(dftComplex a, dftComplex b);
/* multiplication of complex numbers */
dftComplex mulComplex(dftComplex a, dftComplex b);
/* absolute value of complex numbers */
double absComplex(dftComplex a);
/* complex number to the power of exp  */
dftComplex expComplex(dftComplex x);