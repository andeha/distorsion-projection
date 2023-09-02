/*  circula-convers.c | the hyperbola and the inverted hyperbola. */

#include "Twinbeam.h"

simd_tᵦ tanh(simd_tᵦ x, int arc) ⓣ
{ simd_tᵦ acc=simd_initᵦ(0.0),two=simd_initᵦ(2.0),
 one=simd_initᵦ(1.0);
  double idx[]={ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
   if (arc)
   { simd_tᵦ k,A,B,den,zero=simd_initᵦ(0.0);
      for (int i=14; i>=1; i = i - 1)
      {
         k = simd_initᵦ(idx[i]);
         A = __builtin_simd_mulᵦ(__builtin_simd_mulᵦ(k,k),__builtin_simd_mulᵦ(x,x));
         B = __builtin_simd_addᵦ(__builtin_simd_mulᵦ(two,k),one);
         acc = __builtin_simd_divᵦ(__builtin_simd_subᵦ(zero,A),__builtin_simd_addᵦ(B,acc));
      }
      den = __builtin_simd_addᵦ(one,acc);
      return __builtin_simd_divᵦ(x,den);
   } /* when xϵ[-1,1] a․𝘬․a tanh⁻¹(z) = z (1 + 𝐊(-k²z², 2k+1))⁻¹ where kϵ[1,∞). */
   else
   { simd_tᵦ I,twoI,odd,z,sum;
      for (int i=8; i>=0; i = i - 1)
      {
         I = simd_initᵦ(idx[i]);
         twoI = __builtin_simd_mulᵦ(two,I);
         odd = __builtin_simd_addᵦ(twoI,one);
         z = __builtin_simd_divᵦ(odd,x);
         sum = __builtin_simd_addᵦ(z,acc);
         acc = __builtin_simd_divᵦ(one,sum);
      }
      return acc;
   } /* xϵ[-π,π] and 1/z,3/z,5/z,7/z,9/z,... */
}

struct sequent tanh(Sequenta x, int arc) ⓣ
{ Sequenta acc=accumulative₋zero(), two=redundant₋many(), 
 one=product₋abelian();
   int64_t idx[]= { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
   if (arc)
   { Sequenta k,A,B,den,zero=accumulative₋zero();
       for (int i=14; i>=1; i = i - 1)
       {
         int₋to₋sequent(idx[i],&k);
         A = __builtin_fixpoint_mul(__builtin_fixpoint_mul(k,k),__builtin_fixpoint_mul(x,x));
         B = __builtin_fixpoint_add(__builtin_fixpoint_mul(k,two),one);
         acc = __builtin_fixpoint_div(__builtin_fixpoint_sub(zero,A),__builtin_fixpoint_add(B,acc));
       }
       den = __builtin_fixpoint_add(one,acc);
       return __builtin_fixpoint_div(x,den);
   }
   else
   { Sequenta I,twoI,odd,z,sum;
      for (int i=8; i>=0; i = i - 1)
      {
        int₋to₋sequent(idx[i],&I);
        twoI = __builtin_fixpoint_mul(two,I);
        odd = __builtin_fixpoint_add(twoI,one);
        z = __builtin_fixpoint_div(odd,x);
        sum = __builtin_fixpoint_add(z,acc);
        acc = __builtin_fixpoint_div(one,sum);
      }
      return acc;
   }
}

