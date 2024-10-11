#ifndef RENDERER_H
#define RENDERER_H

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include "../Mesh/Mesh.h"

class Renderer {
public:
    GLFWwindow* window;
    Shader* shader;
    Camera* camera;
    std::vector<Mesh*> meshes;

    Renderer(int width, int height, const char* title);
    void setShader(Shader* shader);
    void addMesh(Mesh* mesh);
    void renderLoop();
    void processInput();

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif