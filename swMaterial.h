#pragma once
#include "swVec3.h"

class swMaterial {
  public:
    swMaterial() = default;
    swMaterial(const swVec3 &c, float r = 0, float t = 0, float i = 1)
      : mColor{c}, reflectivity(r), transparency(t), refractiveIndex(i) {}

  public:
    swVec3 mColor;
    float reflectivity{0.0f};
    float transparency{0.0f};
    float refractiveIndex{1.0f};
};
