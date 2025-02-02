/*  iumoid-twothree.c | the sqrt and nroot and power. */

#include "Twinbeam.h"

extern simd_tᵦ exponential(simd_tᵦ) ⓣ;
extern Sequent exponential(Sequent) ⓣ;
extern simd_tᵦ logₑ(simd_tᵦ) ⓣ;
extern Sequent logₑ(Sequent) ⓣ;

simd_tᵦ nroot(simd_tᵦ r, simd_tᵦ x) ⓣ
{ simd_tᵦ unity=simd_initᵦ(1.0);
   return exponential(__builtin_simd_mulᵦ(logₑ(x),__builtin_simd_divᵦ(unity,r)));
} /* y = x^(1/r) = e^(ln(x)*1/r) */

struct sequent nroot(Sequent r, Sequent x) ⓣ
{ Sequent unity=product₋abelian();
   return exponential(__builtin_fixpoint_mul(logₑ(x),__builtin_fixpoint_div(unity,r)));
}

simd_tᵦ sqrt(simd_tᵦ x, int reciproc) ⓣ
{
   if (reciproc) { return __builtin_simd_rsqrtᵦ(x); }
   else { return __builtin_simd_sqrtᵦ(x); }
}

struct sequent sqrt(Sequent x, int reciproc) ⓣ
{ Sequent two=redundant₋many();
   if (reciproc) { return __builtin_fixpoint_div(product₋abelian(),nroot(two,x)); }
   else { return nroot(two,x); }
}

simd_tᵦ power(simd_tᵦ y, simd_tᵦ r) ⓣ
{
   return exponential(__builtin_simd_mulᵦ(r,logₑ(y)));
} /* y = x^r = e^(r*ln x) */

struct sequent power(Sequent y, Sequent r) ⓣ
{
   return exponential(__builtin_fixpoint_mul(r,logₑ(y)));
}

simd_tᵦ reciproc₋interval(simd_tᵦ x) ⓣ
{
   return __builtin_simd_rcpᵦ(x);
}

struct sequent reciproc_sequent(Sequent x) ⓣ
{
   return __builtin_fixpoint_div(product₋abelian(),x);
}

