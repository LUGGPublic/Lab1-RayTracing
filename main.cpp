/*
 *  main.cpp
 *  swTracer
 *
 *  Created by Michael Doggett on 2021-09-23.
 *  Copyright (c) 2021 Michael Doggett
 */
#define _USE_MATH_DEFINES
#include <cfloat>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "swCamera.h"
#include "swIntersection.h"
#include "swMaterial.h"
#include "swRay.h"
#include "swScene.h"
#include "swSphere.h"
#include "swVec3.h"

inline float clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

float uniform() {
    // Will be used to obtain a seed for the random number engine
    static std::random_device rd;
    // Standard mersenne_twister_engine seeded with rd()
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    return dis(gen);
}

void writeColor(int index, swVec3 p, uint8_t *pixels) {
    // gamma correct for gamma=2.2, x^(1/gamma), more see :
    // https://www.geeks3d.com/20101001/tutorial-gamma-correction-a-story-of-linearity/
    for (int n = 0; n < 3; n++) {
        p.m[n] = pow(p.m[n], 1.0f / 2.2f);
        pixels[index + n] = (uint8_t)(256 * clamp(p.m[n], 0.0f, 0.999f));
    }
}

Color traceRay(const swRay &r, swScene scene, int depth) {
    Color c, directColor;
    if (depth < 0) return c;

    swIntersection hp, si;
    if (!scene.intersect(r, hp)) return Color(0, 0, 0); // Background color

    const swVec3 lightPos(0.0f, 30.0f, -5.0f);
    swVec3 lightDir = lightPos - hp.mPosition;
    lightDir.normalize();

    c = Color(1, 1, 1);

    return c;
}

int main() {
    int imageWidth = 512;
    int imageHeight = imageWidth;
    const int numChannels = 3;
    uint8_t *pixels = new uint8_t[imageWidth * imageHeight * numChannels];

    // Define materials
    // swMaterial(swVec3 color, reflectivity, refractivity, refractiveIndex)
    swMaterial whiteDiffuse = swMaterial(Color(0.9f, 0.9f, 0.9f), 0.0f, 0.0f, 1.0f);
    swMaterial greenDiffuse = swMaterial(Color(0.1f, 0.6f, 0.1f), 0.0f, 0.0f, 1.0f);
    swMaterial redDiffuse = swMaterial(Color(1.0f, 0.1f, 0.1f), 0.0f, 0.0f, 1.0f);
    swMaterial blueDiffuse = swMaterial(Color(0.0f, 0.2f, 0.9f), 0.0f, 0.0f, 1.0f);
    swMaterial yellowReflective = swMaterial(Color(1.0f, 0.6f, 0.1f), 0.2f, 0.0f, 1.0f);
    swMaterial redTransparent = swMaterial(Color(1.0f, 0.1f, 0.2f), 0.2f, 0.8f, 1.3f);

    // Setup scene
    swScene scene;

    scene.push(swSphere(swVec3(-7.0f, 3.0f, -20.0f), 3.0f, greenDiffuse));
    scene.push(swSphere(swVec3(0.0f, 3.0f, -20.0f), 3.0f, blueDiffuse));
    scene.push(swSphere(swVec3(7.0f, 3.0f, -20.0f), 3.0f, redDiffuse));

    // TODO: Uncomment to render Cornell box
    // scene.push(swSphere(swVec3(0.0f, -5000.0f, 0.0f), 5000, whiteDiffuse)); // A big sphere for the ground
    // scene.push(swSphere(swVec3(0.0f, 0.0f, -5050.0f), 5000, whiteDiffuse)); // Back wall
    // scene.push(swSphere(swVec3(0.0f, 5040.0f, 0.0f), 5000, whiteDiffuse));  // Ceiling
    // scene.push(swSphere(swVec3(5020.0f, 20.0f, 0.0f), 5000, greenDiffuse)); // Green wall
    // scene.push(swSphere(swVec3(-5020.0f, 20.0f, 0.0f), 5000, redDiffuse));  // Red wall

    // TODO: Uncomment to render reflective spheres
    // scene.push(swSphere(swVec3(7.0f, 3.0f, 0.0f), 3.0f, yellowReflective));
    // scene.push(swSphere(swVec3(9.0f, 10.0f, 0.0f), 3.0f, yellowReflective));

    // TODO: Uncomment to render refractive spheres
    // scene.push(swSphere(swVec3(-7.0f, 3.0f, 0.0f), 3.0f, redTransparent));
    // scene.push(swSphere(swVec3(-9.0f, 10.0f, 0.0f), 3.0f, redTransparent));

    // Setup camera
    swVec3 eye(0.0f, 10.0f, 30.0f);
    swVec3 lookAt(0.0f, 10.0f, -5.0f);
    swVec3 up(0.0f, 1.0f, 0.0f);
    swCamera camera(eye, lookAt, up, 52.0f,
                    (float)imageWidth / (float)imageHeight);
    camera.setup(imageWidth, imageHeight);

    // Ray trace pixels
    int depth = 3;
    std::cout << "Rendering...\n";
    for (int j = 0; j < imageHeight; ++j) {
        for (int i = 0; i < imageWidth; ++i) {
            Color pixel;
            // Get center of pixel coordinate
            float cx = ((float)i) + 0.5f;
            float cy = ((float)j) + 0.5f;

            // Get a ray and trace it
            swRay r = camera.getRay(cx, cy);
            pixel = traceRay(r, scene, depth);

            // Write pixel value to image
            writeColor((j * imageWidth + i) * numChannels, pixel, pixels);
        }
    }

    // Save image to file
    stbi_write_png("out.png", imageWidth, imageHeight, numChannels, pixels,
                   imageWidth * numChannels);
    
    // Free allocated memory
    delete[] pixels;

    std::cout << "Done\n";
}
