/*  sequent-sinuativ.c | the words /sin/ and /cos/ and one is postponed. */

#include "Twinbeam.h"

simd_tᵦ tan(simd_tᵦ x, int arc) ⓣ
{ simd_tᵦ 𝟸⁻¹=simd_initᵦ(0.5),one=simd_initᵦ(1.0),b=simd_initᵦ(1.0),
    x²=__builtin_simd_mulᵦ(x,x),x²p₁=__builtin_simd_addᵦ(x²,one);
   if (arc)
   {
     simd_tᵦ a=__builtin_simd_rsqrtᵦ(x²p₁),a₊b,𝟸⁻¹₍a₊b₎,ab,sqrt₍ab₎;
     for (int i=0; i<25; i+=1)
     {
       a₊b = __builtin_simd_addᵦ(a,b);
       𝟸⁻¹₍a₊b₎ = __builtin_simd_mulᵦ(𝟸⁻¹,a₊b);
       a = 𝟸⁻¹₍a₊b₎;
       ab = __builtin_simd_mulᵦ(a,b);
       sqrt₍ab₎ = __builtin_simd_sqrtᵦ(ab);
       b = sqrt₍ab₎;
     }
     simd_tᵦ y,r,m;
     r = __builtin_simd_sqrtᵦ(x²p₁);
     m = __builtin_simd_mulᵦ(a,r);
     y = __builtin_simd_divᵦ(x,m);
     return y;
   } /* arctan(x) = x / (a √(x²+1)) where a = √(x²+1), ... */
   else
   { simd_tᵦ zero=simd_initᵦ(0.0),₋1=simd_initᵦ(-1.0),𝟸=simd_initᵦ(2.0), 
      acc=simd_initᵦ(0.0),even,odd,ing,den;
     for (int i=0; i<14; i+=1)
     {
       even = simd_initᵦ(2*i);
       odd = __builtin_simd_addᵦ(even,₋1);
       ing = __builtin_simd_divᵦ(odd,x);
       den = __builtin_simd_addᵦ(ing,acc);
       acc = __builtin_simd_divᵦ(₋1,den);
     }
     return __builtin_simd_subᵦ(zero,acc);
   } /* acc = -1.0/((2*i - 1)/z + acc) */
}

struct sequent tan(Sequenta x, int arc) ⓣ
{ Sequenta 𝟸⁻¹=accumulative₋zero(),one=product₋abelian(),
   b=product₋abelian(),x²=__builtin_fixpoint_mul(x,x),
   x²p₁=__builtin_fixpoint_add(x²,one);
   short zeroToNines[] = { /* 0. */ 5, 0 };
   fraction₋to₋sequent(1,zeroToNines,&𝟸⁻¹);
   if (arc)
   {
      Sequenta a = __builtin_fixpoint_rsqrt(x²p₁),a₊b,𝟸⁻¹₍a₊b₎,ab,sqrt₍ab₎;
      for (int i=0; i<25; i+=1)
      {
        a₊b = __builtin_fixpoint_add(a,b);
        𝟸⁻¹₍a₊b₎ = __builtin_fixpoint_mul(𝟸⁻¹,a₊b);
        a = 𝟸⁻¹₍a₊b₎;
        ab = __builtin_fixpoint_mul(a,b);
        sqrt₍ab₎ = __builtin_fixpoint_sqrt(ab);
        b = sqrt₍ab₎;
      }
      Sequenta y,r,m;
      r = __builtin_fixpoint_sqrt(x²p₁);
      m = __builtin_fixpoint_mul(a,r);
      y = __builtin_fixpoint_div(x,m);
      return y;
   }
   else
   { Sequenta zero=accumulative₋zero(),
       ₋1=__builtin_fixpoint_sub(zero,product₋abelian()),
       acc=accumulative₋zero(),even,odd,ing,den;
      for (int i=0; i<14; i+=1)
      {
        int₋to₋sequent(2*i,&even);
        odd = __builtin_fixpoint_add(even,₋1);
        ing = __builtin_fixpoint_div(odd,x);
        den = __builtin_fixpoint_add(ing,acc);
        acc = __builtin_fixpoint_div(₋1,den);
      }
      return __builtin_fixpoint_sub(zero,acc);
   }
}

