#include "swScene.h"

bool swScene::intersect(const swRay &r, swIntersection &isect, bool any) {
    bool hit = false;
    swIntersection curIsect;
    for (auto &object : mSpheres) {
        if (object.intersect(r, curIsect)) {
            hit = true;
            if (any) return hit;
            if (curIsect.mHitTime < isect.mHitTime) {
                isect = curIsect;
            }
        }
    }
    return hit;
}
