#include <vector>
#include <math.h>
#include "Shader/Shader.h"
#include "Mesh/Mesh.h"
#include "Camera/Camera.h"
#include "Renderer/Renderer.h"
#include <iostream>
#include <chrono>

// Function to generate sphere vertices with normals
std::vector<float> generateSphereVertices(float radius, int sectorCount, int stackCount) {
    std::vector<float> vertices;
    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / radius;
    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i) {
        stackAngle = M_PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
        }
    }
    return vertices;
}

// Function to generate sphere indices
std::vector<unsigned int> generateSphereIndices(int sectorCount, int stackCount) {
    std::vector<unsigned int> indices;
    int k1, k2;
    for (int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stackCount - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
    return indices;
}

int main() {
    Renderer renderer(1600, 1200, "3D Rendering Engine");

    Shader shader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
    renderer.setShader(&shader);

    std::vector<float> sphereVertices = generateSphereVertices(0.4f, 216, 108);
    std::vector<unsigned int> sphereIndices = generateSphereIndices(216, 108);
    Mesh sphere(sphereVertices, sphereIndices);
    renderer.addMesh(&sphere);

    // FPS calculation
    auto lastTime = std::chrono::high_resolution_clock::now();
    int nbFrames = 0;

    while (!glfwWindowShouldClose(renderer.window)) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastTime).count();
        nbFrames++;
        if (deltaTime >= 1.0f) {
            std::cout << 1000.0f / float(nbFrames) << " ms/frame" << std::endl;
            nbFrames = 0;
            lastTime = currentTime;
        }

        renderer.processInput();
        renderer.renderLoop();
    }

    return 0;
}