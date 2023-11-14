#include "terrain.h"
#include "shader.h"
#include "linear_interpolator.h"
#include "headers.h"
#include "camera.h"
#include <iostream>

Vertex::Vertex(const glm::vec3& position) {
    m_position = position;
}


Terrain::Terrain(int cols, int rows):
    m_cols(cols),
    m_rows(rows) {

    m_shader = new Shader("../shaders/terrain.vs", "../shaders/terrain.fs");

    }



Terrain::~Terrain() {

}

void Terrain::init() {
    init_vertices();
    init_height();
    init_mesh();

    m_shader->use();
    glm::mat4 projection = Camera::get_instance()->get_projection();
    m_shader->set_mat4("projection", projection);

}

void Terrain::init_vertices() {
    if(m_cols == -1 || m_rows == -1) {
        std::cerr << "cols and rows are not set\n";
        exit(4);
    }


    m_vertices.resize(m_rows * m_cols);

    LinearInterpolator col_interpolator(0.0f, m_cols, -1.0f, 1.0f);
    LinearInterpolator row_interpolator(0.0f, m_rows, -1.0f, 1.0f);

    int vertex_index = 0;

    for(int z = 0; z < m_rows; z += 1) {
        for(int x = 0; x < m_cols; x += 1 ) {

            float x_pos = (float)x;
            float z_pos = (float)z;

            x_pos = col_interpolator.map(x_pos);
            z_pos = row_interpolator.map(z_pos);

            m_vertices[vertex_index] = Vertex(glm::vec3(x_pos, 0.0f, z_pos));

            vertex_index += 1;

        }
    }

    m_indices.resize((m_cols - 1) * (m_rows - 1) * 6);

    int indices_index = 0;

    for(int z = 0; z < m_rows - 1; z += 1) {
        for(int x = 0; x < m_cols -1; x += 1) {

            unsigned int index_bottom_left = z * m_cols + x;
            unsigned int index_top_left = (z + 1) * m_cols + x;
            unsigned int index_top_right = (z + 1)  * m_cols + x + 1;
            unsigned int index_bottom_right = z  * m_cols + x + 1;

            // top triangle
            m_indices[indices_index++] = index_bottom_left;
            m_indices[indices_index++] = index_top_left;
            m_indices[indices_index++] = index_top_right;


            // bottom triangle
            m_indices[indices_index++] = index_bottom_left;
            m_indices[indices_index++] = index_top_right;
            m_indices[indices_index++] = index_bottom_right;



        }
    }



}

void Terrain::init_height() {

}


void Terrain::init_mesh() {
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER,
            m_vertices.size() * sizeof(Vertex),
            m_vertices.data(),
            GL_STATIC_DRAW
            );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            m_indices.size() * sizeof(unsigned int),
            m_indices.data(),
            GL_STATIC_DRAW
            );

    glBindVertexArray(0);


}


void Terrain::render() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (m_rows - 1) * (m_cols - 1) * 6, GL_UNSIGNED_INT, 0);

}


void Terrain::update() {
    m_shader->use();

    glm::mat4 view = Camera::get_instance()->get_view();
    m_shader->set_mat4("view", view);

    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(0.0f, -0.5, 0.0f));
    m_shader->set_mat4("model", model);


}

void Terrain::set_vertex(int col, int row, const Vertex& vertex) {
    m_vertices[(row * m_cols) + col] = vertex;

}


Vertex Terrain::get_vertex(int col, int row) const {
    return m_vertices[(row * m_cols) + col];

}
