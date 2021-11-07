#pragma once
#include "swIntersection.h"
#include "swMaterial.h"
#include "swRay.h"

class swSphere {
  public:
    swSphere() = default;
    swSphere(const swVec3 &c, const float &r, const swMaterial &m)
      : mCenter(c), mRadius(r), mMaterial(m) {}
    bool intersect(const swRay &r, swIntersection &isect);

  public:
    swVec3 mCenter;
    float mRadius{0.0f};
    swMaterial mMaterial;
};
