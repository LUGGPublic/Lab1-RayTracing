#pragma once
#include "swRay.h"

class swCamera {
  public:
    swCamera() = default;
    swCamera(const swVec3 &o, const swVec3 &at, const swVec3 &u, const float &v,
             const float &a)
      : origin(o), lookAt(at), up(u), vFOV(v), aspectRatio(a) {}
    void setup(int w, int h);
    swRay getRay(float x, float y);

  public:
    swVec3 origin;
    swVec3 lookAt;
    swVec3 up;
    float vFOV{0.0f};
    float aspectRatio{1.0f};
    float mImageExtentX{0.0f}, mImageExtentY{0.0f};
    int mImageWidth{0}, mImageHeight{0};
    swVec3 mForward, mRight, mUp;
};
