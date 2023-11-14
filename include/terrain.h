#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 m_position;

    Vertex(const glm::vec3& position = glm::vec3(0.0f));

};


struct Shader;

struct Terrain {
    Terrain(int cols = -1, int rows = -1);
    virtual ~Terrain();

    void init();

    void init_vertices();
    virtual void init_height();
    void init_mesh();


    void render();
    void update();

    void set_vertex(int col, int row, const Vertex& vertex);
    Vertex get_vertex(int col, int row) const;

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    int m_cols;
    int m_rows;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    Shader* m_shader;






};

#endif
