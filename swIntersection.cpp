#include "swIntersection.h"

swRay swIntersection::getShadowRay(const swVec3 &lightPos) {
    swVec3 L = lightPos - mPosition;
    return swRay(mPosition, L.normalize(), 0.0f, 0.01f, sqrt(L * L));
}

swRay swIntersection::getReflectedRay(void) {
    swVec3 N = mNormal;
    const swVec3 D = mRay.dir;

    // TODO: Implement reflection.
    // -------------------
    swVec3 R = D;
    // -------------------
    swRay rray = swRay(mPosition, R, 0.0f, 0.01f, FLT_MAX);
    return rray;
}

swRay swIntersection::getRefractedRay(void) {
    const swVec3 &D = mRay.dir;
    swVec3 N = mNormal;
    swVec3 O; // O : outgoing refracted vector
    float eta = 1.0f / mMaterial.refractiveIndex;
    if (!mFrontFacing) eta = 1.0f / eta; // Inside material.

    // TODO: Implement refraction.
    // -------------------
    swVec3 R = D;
    // -------------------

    return swRay(mPosition, O, 0.0f, 0.01f, FLT_MAX);
}
