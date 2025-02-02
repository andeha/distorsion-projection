/*  napier-exponen.c | simple and easy. */

#include "Twinbeam.h"

extern simd_tᵦ tanh(simd_tᵦ,int) ⓣ;
extern Sequent tanh(Sequent,int) ⓣ;

simd_tᵦ exponential(simd_tᵦ x) ⓣ
{ simd_tᵦ one=simd_initᵦ(1.0),two=simd_initᵦ(2.0),param,eval,y,num,den;
   param = __builtin_simd_divᵦ(x,two);
   eval = tanh(param,0);
   num = __builtin_simd_addᵦ(one,eval);
   den = __builtin_simd_subᵦ(one,eval);
   y = __builtin_simd_divᵦ(num,den);
   return y;
} /* (1+tanh(x/2))/(1-tanh(x/2)) */

struct sequent exponential(Sequent x) ⓣ
{ Sequent one=product₋abelian(),two=redundant₋many(),param,eval,y,num,den;
   param = __builtin_fixpoint_div(x,two);
   eval = tanh(param,0);
   num = __builtin_fixpoint_add(one,eval);
   den = __builtin_fixpoint_sub(one,eval);
   y = __builtin_fixpoint_div(num,den);
   return y;
}

