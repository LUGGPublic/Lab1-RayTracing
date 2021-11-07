#pragma once
#include "swVec3.h"

class swRay {
  public:
    swRay() = default;
    swRay(const swVec3 &o, const swVec3 &d, float t = 0, float nt = 0,
          float xt = FLT_MAX)
      : orig(o), dir(d), tm(t), minT(nt), maxT(xt) {}

    swVec3 origin() const { return orig; }
    swVec3 direction() const { return dir; }
    float time() const { return tm; }

  public:
    swVec3 orig;
    swVec3 dir;
    float tm{0.0f}, minT{0.0f}, maxT{FLT_MAX};
};
