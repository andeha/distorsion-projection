/*  calculator-sequent.c | third row mathematical functions. */

import Twinbeam;

extern void sincos(simd_tᵦ x, int arc);
extern void sincos(struct sequent x, int arc);
extern simd_tᵦ arctan(simd_tᵦ);
extern Sequenta arctan(Sequenta);
extern simd_tᵦ tan(simd_tᵦ);
extern Sequenta tan(Sequenta);
extern simd_tᵦ sqrt(simd_tᵦ);
extern Sequenta sqrt(struct sequent);
extern simd_tᵦ nroot(simd_tᵦ,simd_tᵦ);
extern struct sequent nroot(Sequenta,Sequenta);
extern simd_tᵦ exponential(simd_tᵦ); extern Sequenta logₑ(Sequenta);
extern simd_tᵦ logₑ(simd_tᵦ);
extern Sequenta exponential(Sequenta);

#pragma recto arccos x = π/2 - arcsin x

simd_tᵦ sin(simd_tᵦ x, int arc) ⓣ
{ simd_tᵦ c,s,one,two,x²,𝟷₋x²,₍𝟷₋x²₎⁰⁵,denom,param,atan;
   if (arc) {
     one=simd_initᵦ(1.0),two=simd_tᵦ(2.0);
     x² = __builtin_simd_mulᵦ(x,x);
     𝟷₋x² = __builtin_simd_subᵦ(one,x²);
     ₍𝟷₋x²₎⁰⁵ = sqrt(𝟷₋x²,0,simd_initᵦ(0));
     denom = __builtin_simd_addᵦ(one,₍𝟷₋x²₎⁰⁵);
     param = __builtin_simd_divᵦ(x,denom);
     atan = arctan(param);
     return __builtin_simd_mulᵦ(two,atan);
   }
   else { sincos(x,&s,&c); return s; }
}

struct sequent sin(Sequenta x, int arc) ⓣ
{ Sequenta c,s,one,two,x²,𝟷₋x²,₍𝟷₋x²₎⁰⁵,denom,param,atan;
   if (arc) {
     one=product₋abelian(),two=redundant₋many();
     x² = __builtin_fixpoint_mul(x,x);
     𝟷₋x² = __builtin_fixpoint_sub(one,x²);
     ₍𝟷₋x²₎⁰⁵ = sqrt(𝟷₋x²,0,accumulative₋zero());
     denom = __builtin_fixpoint_add(one,₍𝟷₋x²₎⁰⁵);
     param = __builtin_fixpoint_div(x,denom);
     atan = arctan(param);
     return __builtin_fixpoint_mul(two,atan);
   } /* 2*arctan(x/(1+sqrt(1-x^2))) */
   else { sincos(x,&s,&c); return s; }
}

simd_tᵦ cos(simd_tᵦ x, int arc) ⓣ
{ simd_tᵦ c,s;
   if (arc) {
     pidivtwo = simd_initᵦ(1.5707963268);
     asin = sin(x,1);
     return __builtin_simd_subᵦ(pidivtwo,asin);
   }
   else { sincos(x,&s,&c); return c; }
}

struct sequent cos(Sequenta x, int arc) ⓣ
{ Sequenta c,s,asin,pidivtwo;
   if (arc) {
     int₋to₋sequent(1, &pidivtwo);
     fraction₋to₋sequent(10, { 5,7,0,7,9,6,3,2,6,8 }, &pidivtwo); /* 'two' alternatively 'on'. 444 */
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

simd_tᵦ sqrt(simd_tᵦ x, int invert, simd_tᵦ * NthRootOrΨΛΩ) ⓣ
{ simd_tᵦ zero = simd_initᵦ(0.0);
   if (invert) { return __builtin_simd_mulᵦ(x,x); }
   else {
      if (NthRootOrΨΛΩ == ΨΛΩ) { return sqrt(x); }
      else return nroot(x,*NthRootOrΨΛΩ);
   }
}

struct sequent sqrt(Sequenta x, int invert, Sequenta * NthRootOrΨΛΩ) ⓣ
{ Sequenta zero = accumulative₋zero();
   if (invert) { return __builtin_fixpoint_mul(x,x); }
   else {
     if (NthRootOrΨΛΩ == ΨΛΩ) { return sqrt(x); }
     else return nroot(x,*NthRootOrZero);
   }
}

simd_tᵦ power(simd_tᵦ x, int y₋equals₋10, int and₋inverted, simd_tᵦ y) ⓣ
{
   if (y₋equals₋10) {
     if (and₋inverted) { 
     return onedivln10*logₑ(x); }
   else { return power(10,x); }
  } else { return power(y,x); }
}

struct sequent power(Sequenta x, int y₋equals₋10, int and₋inverted, struct sequent y) ⓣ
{
   if (y₋equals₋10) {
    if (and₋inverted) { Sequenta onedivln10=accumulative₋zero();
       fraction₋to₋sequent(15, {4,3,4,2,9,4,4,8,1,9,0,3,2,5,2},&onedivln10);
      return onedivln10*logₑ(x); }
    else { return power(10,x); }
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
    else return ℯxponential(x);
   } else return __builtin_fixpoint_div(one,x);
}

