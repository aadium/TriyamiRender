# TriyamiRender
TriyamiRender is designed to render 3D objects using OpenGL. It supports basic functionalities such as loading shaders, creating and rendering meshes and handling camera movements. The engine is built using C++ and leverages libraries such as GLFW for window management and input handling, GLEW for OpenGL extension loading, and GLM for mathematical operations.
<br/>
<img src="https://github.com/user-attachments/assets/3a257278-1984-4bc0-9c4f-48eafb364f75" width=500/>
## Features
<li><b>Shader Management</b>: Load and compile vertex and fragment shaders.</li>
<li><b>Mesh Management</b>: Create and render 3D meshes.</li>
<li><b>Camera Control</b>: Handle camera movements and perspectives.</li>

## Dependencies
<li><b>GLFW</b>: For window management and input handling.</li>
<li><b>GLEW</b>: For loading OpenGL extensions.</li>
<li><b>GLM</b>: For mathematical operations.</li>
<li><b>OpenGL</b>: For rendering.</li>

## Getting Started
### Building the Project
<li>Clone this repository</li>

```
git clone https://github.com/yourusername/3d-rendering-engine.git
cd 3d-rendering-engine
```
<li>Create a build directory and navigate to it</li>

```
mkdir build
cd build
```
<li>Generate the build files using CMake</li>

```
cmake ..
```
<li>Build the project</li>

```
make
```
## Using the Rendering Engine API
Below is an example of how to set up and use the Rendering Engine API:
```
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
```
### Detailed steps
<li>Initialize the renderer</li>

```
#include "Renderer/Renderer.h"
Renderer renderer(1600, 1200, "3D Rendering Engine");
```
<li>Setup the camera</li>

```
#include "Camera/Camera.h"
Camera camera;
camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
camera.setPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
```
<li>Load shaders</li>

```
#include "Shader/Shader.h"
Shader shader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
renderer.setShader(&shader);
```
<li>Create a mesh</li>

```
#include "Mesh/Mesh.h"
std::vector<float> sphereVertices = generateSphereVertices(0.4f, 216, 108);
std::vector<unsigned int> sphereIndices = generateSphereIndices(216, 108);
Mesh sphere(sphereVertices, sphereIndices);
renderer.addMesh(&sphere);
```
<li>Render loop</li>

```
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
```
