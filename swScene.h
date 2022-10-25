#pragma once

#include <memory>
#include <vector>

#include "swIntersection.h"
#include "swPrimitive.h"
#include "swSphere.h"
#include "swTriangle.h"

namespace sw {

class Scene {
  public:
    void pushSphere(const Sphere &s) { primitives.push_back(std::make_shared<Sphere>(s)); }
    void pushTriangle(const Triangle &t) { primitives.push_back(std::make_shared<Triangle>(t)); }
    bool intersect(const Ray &r, Intersection &isect, bool any = false);

  private:
    std::vector<std::shared_ptr<Primitive>> primitives;
};

} // namespace sw
