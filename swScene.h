#pragma once
#include "swIntersection.h"
#include "swSphere.h"
#include <vector>

class swScene {
  public:
    void push(const swSphere &s) { mSpheres.push_back(s); }
    bool intersect(const swRay &r, swIntersection &isect, bool any = false);

  private:
    std::vector<swSphere> mSpheres;
};
