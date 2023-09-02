/*  abundan-invert.c | natural logarithm. */

#include "Twinbeam.h"

extern simd_tᵦ tanh(simd_tᵦ,int) ⓣ;
extern Sequenta tanh(Sequenta,int) ⓣ;

simd_tᵦ logₑ(simd_tᵦ x) ⓣ
{ simd_tᵦ two=simd_initᵦ(2.0),one=simd_initᵦ(1.0), 
   x₋1,x₊1,param,eval,y;
   x₋1 = __builtin_simd_subᵦ(x,one);
   x₊1 = __builtin_simd_addᵦ(x,one);
   param = __builtin_simd_divᵦ(x₋1,x₊1);
   eval = tanh(param,1);
   y = __builtin_simd_mulᵦ(two,eval);
   return y;
} /* logₑ x = 2 tanh⁻¹((x-1)/(x+1)) */

struct sequent logₑ(Sequenta x) ⓣ
{ Sequenta two=redundant₋many(),one=product₋abelian(), 
   x₋1,x₊1,param,eval,y;
   x₋1 = __builtin_fixpoint_sub(x,one);
   x₊1 = __builtin_fixpoint_add(x,one);
   param = __builtin_fixpoint_div(x₋1,x₊1);
   eval = tanh(param,1);
   y = __builtin_fixpoint_mul(two,eval);
   return y;
}

