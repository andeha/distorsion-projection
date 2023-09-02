/*  satur-calculat.c | third row mathematical functions. */

#include "Twinbeam.h"

extern void sincos(simd_tᵦ x, simd_tᵦ * s, simd_tᵦ * c) ⓣ;
extern void sincos(Sequenta x, Sequenta * s, Sequenta * c) ⓣ;
extern simd_tᵦ tan(simd_tᵦ,int) ⓣ;
extern Sequenta tan(Sequenta,int) ⓣ;
extern simd_tᵦ sqrt(simd_tᵦ,int) ⓣ;
extern Sequenta sqrt(Sequenta,int) ⓣ;
extern simd_tᵦ nroot(simd_tᵦ,simd_tᵦ) ⓣ;
extern Sequenta nroot(Sequenta,Sequenta) ⓣ;
extern simd_tᵦ power(simd_tᵦ,simd_tᵦ) ⓣ;
extern Sequenta power(Sequenta,Sequenta) ⓣ;
extern simd_tᵦ exponential(simd_tᵦ) ⓣ;
extern Sequenta exponential(Sequenta) ⓣ;
extern simd_tᵦ logₑ(simd_tᵦ) ⓣ;
extern Sequenta logₑ(Sequenta) ⓣ;

inexorable simd_tᵦ arctan(simd_tᵦ x) ⓣ { return tan(x,1); }
inexorable struct sequent arctan(Sequenta x) ⓣ { return tan(x,1); }
inexorable simd_tᵦ tan(simd_tᵦ x) ⓣ { return tan(x,0); }
inexorable struct sequent tan(Sequenta x) ⓣ { return tan(x,0); }

#pragma recto arccos x = π/2 - arcsin x

simd_tᵦ sin(simd_tᵦ x, int arc) ⓣ
{ simd_tᵦ c,s,one,two,x²,𝟷₋x²,₍𝟷₋x²₎⁰⁵,den,arg,atan;
   if (arc) {
     one=simd_initᵦ(1.0),two=simd_initᵦ(2.0);
     x² = __builtin_simd_mulᵦ(x,x);
     𝟷₋x² = __builtin_simd_subᵦ(one,x²);
     ₍𝟷₋x²₎⁰⁵ = sqrt(𝟷₋x²,0);
     den = __builtin_simd_addᵦ(one,₍𝟷₋x²₎⁰⁵);
     arg = __builtin_simd_divᵦ(x,den);
     atan = arctan(arg);
     return __builtin_simd_mulᵦ(two,atan);
   }
   else { sincos(x,&s,&c); return s; }
}

struct sequent sin(Sequenta x, int arc) ⓣ
{ Sequenta c,s,one,two,x²,𝟷₋x²,₍𝟷₋x²₎⁰⁵,den,arg,atan;
   if (arc) {
     one=product₋abelian(),two=redundant₋many();
     x² = __builtin_fixpoint_mul(x,x);
     𝟷₋x² = __builtin_fixpoint_sub(one,x²);
     ₍𝟷₋x²₎⁰⁵ = sqrt(𝟷₋x²,0);
     den = __builtin_fixpoint_add(one,₍𝟷₋x²₎⁰⁵);
     arg = __builtin_fixpoint_div(x,den);
     atan = arctan(arg);
     return __builtin_fixpoint_mul(two,atan);
   } /* y = 2*arctan(x/(1+sqrt(1-x^2))). */
   else { sincos(x,&s,&c); return s; }
}

simd_tᵦ cos(simd_tᵦ x, int arc) ⓣ
{ simd_tᵦ c,s,asin,pidivtwo;
   if (arc) {
     pidivtwo = simd_initᵦ(1.5707963267948966192313216916397514420985846996875529104874722961);
     asin = sin(x,1);
     return __builtin_simd_subᵦ(pidivtwo,asin);
   }
   else { sincos(x,&s,&c); return c; }
}

struct sequent cos(Sequenta x, int arc) ⓣ
{ Sequenta c,s,asin,pidivtwo;
   if (arc) {
     int₋to₋sequent(1,&pidivtwo);
     short zero_to_nine[] = { 5,7,0,7,9,6,3,2,6,7,9,4,8,9,6,6,1,9,2,3,1,3,2,1,6,9,1,6,3,9,7,5,1,4,4,2,0,9,8,5,8,4,6,9,9,6,8,7,5,5,2,9,1,0,4,8,7,4,7,2,2,9,6,1 };
     fraction₋to₋sequent(50,zero_to_nine,&pidivtwo);
     asin = sin(x,1);
     return __builtin_fixpoint_sub(pidivtwo,asin);
   } /* alternatively '2*arctan(sqrt(1-x^2)/(1+x))'. */
   else { sincos(x,&s,&c); return c; }
}

simd_tᵦ tan(simd_tᵦ x, int arc) ⓣ
{
   if (arc) { return arctan(x); }
   else { return tan(x); }
}

struct sequent tan(Sequenta x, int arc) ⓣ
{
   if (arc) { return arctan(x); }
   else { return tan(x); }
}

#pragma recto damping 𝘦․𝘨 de-ci-be-l and sq-u-are

simd_tᵦ sqrt(simd_tᵦ x, int invert, simd_tᵦ * NoNthRootOrΨΛΩ) ⓣ
{ simd_tᵦ zero=simd_initᵦ(0.0);
   if (invert) { return __builtin_simd_mulᵦ(x,x); }
   else {
      if (NoNthRootOrΨΛΩ == ΨΛΩ) { return sqrt(x,0); }
      else return nroot(x,*NoNthRootOrΨΛΩ);
   }
}

struct sequent sqrt(Sequenta x, int invert, Sequenta * NoNthRootOrΨΛΩ) ⓣ
{ Sequenta zero=accumulative₋zero();
   if (invert) { return __builtin_fixpoint_mul(x,x); }
   else {
     if (NoNthRootOrΨΛΩ == ΨΛΩ) { return sqrt(x,0); }
     else return nroot(x,*NoNthRootOrΨΛΩ);
   }
}

simd_tᵦ power(simd_tᵦ x, int y₋equals₋10, int and₋inverted, simd_tᵦ y) ⓣ
{ simd_tᵦ onedivln10=simd_initᵦ(0.4342944819032518276511289189166050822943970058036665661144537831);
   if (y₋equals₋10) {
     if (and₋inverted) { return __builtin_simd_mulᵦ(onedivln10,logₑ(x)); }
     else { simd_tᵦ ten=simd_initᵦ(10.0);
       return power(ten,x); }
   } else { return power(y,x); }
}

struct sequent power(Sequenta x, int y₋equals₋10, int and₋inverted, struct sequent y) ⓣ
{
   if (y₋equals₋10) {
    if (and₋inverted) { Sequenta onedivln10=accumulative₋zero();
       short zero_to_nine[] = {4,3,4,2,9,4,4,8,1,9,0,3,2,5,1,8,2,7,6,5,1,1,2,8,9,1,8,9,1,6,6,0,5,0,8,2,2,9,4,3,9,7,0,0,5,8,0,3,6,6,6,5,6,6,1,1,4,4,5,3,7,8,3,1 };
       fraction₋to₋sequent(15,zero_to_nine,&onedivln10);
      return __builtin_fixpoint_mul(onedivln10,logₑ(x)); }
    else { Sequenta ten; int₋to₋sequent(10,&ten);
      return power(ten,x); }
   } else { return power(y,x); }
}

simd_tᵦ reciproc(simd_tᵦ x, int no₋exponential, int and₋again₋inverted) ⓣ
{
   simd_tᵦ one=simd_initᵦ(1.0);
   if (no₋exponential) {
     if (and₋again₋inverted) { return logₑ(x); }
     else return exponential(x);
   } else return __builtin_simd_divᵦ(one,x);
}

struct sequent reciproc(Sequenta x, int no₋exponential, int and₋again₋inverted) ⓣ
{ Sequenta one=product₋abelian();
   if (no₋exponential) {
    if (and₋again₋inverted) { return logₑ(x); }
    else return exponential(x);
   } else return __builtin_fixpoint_div(one,x);
}

