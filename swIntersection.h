#pragma once
#include "swMaterial.h"
#include "swRay.h"

class swIntersection {
  public:
    swRay getShadowRay(const swVec3 &lightPos);
    swRay getReflectedRay(void);
    swRay getRefractedRay(void);

  public:
    float mHitTime{FLT_MAX};
    swVec3 mPosition;
    swVec3 mNormal;
    bool mFrontFacing{true};
    swMaterial mMaterial;
    swRay mRay; // incoming ray that creates intersection
};
