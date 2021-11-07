#include "swCamera.h"

void swCamera::setup(int w, int h) {
    mImageWidth = w;
    mImageHeight = h;

    mForward = lookAt - origin;
    mForward.normalize();
    mRight = mForward % up;
    mRight.normalize();
    mUp = mRight % mForward;

    mImageExtentX = std::tan(0.5f * vFOV * static_cast<float>(M_PI) / 180.0f);
    mImageExtentY =
      std::tan(0.5f * vFOV / aspectRatio * static_cast<float>(M_PI) / 180.0f);
}

swRay swCamera::getRay(float x, float y) {
    swVec3 xIncr = 2.0f / ((float)mImageWidth) * mImageExtentX * mRight;
    swVec3 yIncr = -2.0f / ((float)mImageHeight) * mImageExtentY * mUp;
    swVec3 view = mForward - mImageExtentX * mRight + mImageExtentY * mUp;

    return swRay(origin, view + x * xIncr + y * yIncr, 0, 0, FLT_MAX);
}
