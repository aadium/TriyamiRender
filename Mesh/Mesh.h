#ifndef MESH_H
#define MESH_H

#include <GLEW/glew.h>
#include <vector>

class Mesh {
public:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    GLuint VAO, VBO, EBO;

    Mesh(std::vector<float> vertices, std::vector<unsigned int> indices);
    void Draw();

private:
    void setupMesh();
};

#endif