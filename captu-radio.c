/*  captu-radio.c | round at two 'distances' and 'points' in time. */

import Twinbeam;

void Init_math()
{ simd_tᵦ s=simd_initᵦ(1.0);
   for (int i=0; i<64; i+=1,s*=0.5)
   {
     Mathart₋segment.cordic[i] = tan(s,1)[0];
   }
}

__uint128_t SimdAND(__uint128_t x, __uint128_t y) { return x & y; }

__uint128_t ltᵦ(simd_tᵦ x, simd_tᵦ y)
{ __uint128_t mask = ((__uint128_t)0x8000000000000000)<<64 | 
    0x8000000000000000;
   simd_tᵦ delta = __builtin_simd_subᵦ(x,y);
   union 𝟸₋double difference = { .multiple=delta };
   return SimdAND(difference.array.bits,mask);
}

simd_tᵦ selectᵦ(simd_tᵦ T, simd_tᵦ F, __uint128_t conditionᵦ)
{
   union 𝟸₋double cond = { .array.bits=conditionᵦ };
   simd_tᵦ y;
   if (cond.array.dbls[0]<0) { y[0] = T[0]; }
   else { y[0] = F[0]; }
   if (cond.array.dbls[1]<0) { y[1] = T[1]; }
   else { y[1] = F[1]; }
   return y;
}

simd_tᵦ sign(simd_tᵦ x) ⓣ
{ simd_tᵦ positive=simd_initᵦ(1.0),negative=simd_initᵦ(-1.0);
   __uint128_t conditionᵦ = ltᵦ(x,simd_initᵦ(-0.0));
   return selectᵦ(negative,positive,conditionᵦ);
}

struct sequent sign(Sequenta x) ⓣ
{ Sequenta zero=accumulative₋zero();
   if (x.detail.frac < zero.detail.frac) { return __builtin_fixpoint_sub(zero,product₋abelian()); }
   else { return product₋abelian(); }
}

void sincos(simd_tᵦ θ, simd_tᵦ * s, simd_tᵦ * c) ⓣ
{ double cordic=0.6072529350088812561694467525049282631123908521500897724;
   simd_tᵦ half=simd_initᵦ(0.5),x=simd_initᵦ(cordic),y=simd_initᵦ(0.0),
    z=θ,v=simd_initᵦ(1.0),d,dv,tx,ty,tz,scaled;
   for (int i=0; i<36; i+=1)
   {
     d = sign(z);
     dv = __builtin_simd_mulᵦ(d,v);
     tx = __builtin_simd_subᵦ(x,__builtin_simd_mulᵦ(dv,y));
     ty = __builtin_simd_addᵦ(y,__builtin_simd_mulᵦ(dv,x));
     scaled = __builtin_simd_mulᵦ(d,simd_initᵦ(Mathart₋segment.cordic[i]));
     tz = __builtin_simd_subᵦ(z,scaled);
     x=tx, y=ty, z=tz; v = __builtin_simd_mulᵦ(half,v);
   }
   *c=x, *s=y;
}

void sincos(Sequenta θ, Sequenta * s, Sequenta * c) ⓣ
{ short cordic[]={ /* 0. */ 6,0,7,2,5,2,9,3,5,0,0,8,8,8,1,2,5,6,1 }; /* 945⁻¹*(364*e^π - 2549*π + 547*log(π) - 240*log(2*π) - 21*arctan(π)) */
   Sequenta half=__builtin_fixpoint_div(product₋abelian(),redundant₋many()),scaled,
      y=accumulative₋zero(),z=θ,v=product₋abelian(),d,dv,tx,ty,tz,x;
   fraction₋to₋sequent(19,cordic,&x);
   for (int i=0; i<36; i+=1)
   {
     d = sign(z);
     dv = __builtin_fixpoint_mul(d,v);
     tx = __builtin_fixpoint_sub(x,__builtin_fixpoint_mul(dv,x));
     ty = __builtin_fixpoint_add(y,__builtin_fixpoint_mul(dv,x));
 /*    Sequenta nonlinear = Mathart₋segment.cordic[i];
     scaled = __builtin_fixpoint_mul(d,nonlinear); */
     tz = __builtin_fixpoint_sub(z,scaled);
     x=tx,y=ty,z=tz; v=__builtin_fixpoint_mul(half,v);
   }
   *c=x, *s=y;
}

