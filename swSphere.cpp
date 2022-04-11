#include "swSphere.h"

bool solveQuadratic(float A, float B, float C, float &t0, float &t1) {
    float d = B * B - 4.0f * A * C;
    if (d < 0.0f) return false;
    d = std::sqrt(d);
    t0 = (-B - d) / (2.0f * A);
    t1 = (-B + d) / (2.0f * A);
    return true;
}

bool swSphere::intersect(const swRay &r, swIntersection &isect) {
    swVec3 o = r.orig - mCenter;
    swVec3 d = r.dir; // - sphere.mCenter;

    // Compute polynom coefficients.
    float A = d * d;
    float B = 2.0f * d * o;
    float C = o * o - mRadius * mRadius;

    // Solve quadratic equation for ray enter/exit point t0, t1 respectively.
    float t0, t1;
    if (!solveQuadratic(A, B, C, t0, t1))
        return false; // no real solutions -> ray missed

    if (t0 > r.maxT || t1 < r.minT) {
        return false; // sphere before/after ray
    }
    if (t0 < r.minT && t1 > r.maxT) return false; // ray inside sphere

    isect.mHitTime = t0 < r.minT ? t1 : t0;
    isect.mNormal = (o + (isect.mHitTime) * d) * (1.0f / mRadius);
    isect.mNormal.normalize();
    isect.mFrontFacing = (-d * isect.mNormal) > 0.0f;
    if (!isect.mFrontFacing) isect.mNormal = -isect.mNormal;
    isect.mPosition = o + (isect.mHitTime) * d + mCenter;
    isect.mMaterial = mMaterial;
    isect.mRay = r;
    return true;
}
