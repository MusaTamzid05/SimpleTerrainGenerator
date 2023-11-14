#include "fractal_terrain_generator.h"
#include "linear_interpolator.h"
#include "shader.h"
#include "camera.h"


TerrainFractalGenerator::TerrainFractalGenerator(
        int cols,
        int rows,
        int iterations,
        float min_height,
        float max_height
        ):Terrain(cols, rows),
    m_iterations(iterations),
    m_min_height(min_height),
    m_max_height(max_height) {
        m_shader = new Shader("../shaders/fractal.vs", "../shaders/fractal.fs");
    }

TerrainFractalGenerator::~TerrainFractalGenerator() {

}


void TerrainFractalGenerator::init_height() {
    float delta_height = m_max_height - m_min_height;

    for(int i = 0; i < m_iterations; i += 1) {
        glm::vec3 point1 = generate_random_point();
        glm::vec3 point2;

        bool different_points = false;

        while(!different_points) {
            point2 = generate_random_point();

            if(point1 != point2)
                different_points = true;
        }


        float iteration_ration = (float) i / (float) m_iterations;
        float height = m_max_height - iteration_ration * delta_height;

        glm::vec3 main_dir = point2 - point1;

        for(int z = 0; z < m_rows; z += 1) {
            for(int x = 0; x < m_cols; x += 1) {

                glm::vec3 current_dir = glm::vec3(
                        x - point1.x,
                        0.0f,
                        z - point1.z
                        );

                // x1 * z2- z1 * x2
                float cross_product = (current_dir.x * main_dir.z) - (current_dir.z * main_dir.x);


                if(cross_product > 0.0f) {
                    Vertex vertex = get_vertex(x, z);
                    vertex.m_position.y += height;
                    set_vertex(x, z, vertex);

                }


            }
        }
    }

    float filter = 0.9;

    // left to right
    for(int z = 0; z < m_rows; z += 1) {
        float prev_filter = get_vertex(0, z).m_position.y;

        for(int x = 1; x < m_cols; x += 1) {
            Vertex vertex = get_vertex(x, z);
            float current_value = vertex.m_position.y;
            float new_value  = filter * prev_filter + (1 - filter) * current_value;
            vertex.m_position.y = new_value;
            prev_filter = new_value;
            set_vertex(x, z, vertex);

        }
    }


    // right to left
    for(int z = 0; z < m_rows; z += 1) {
        float prev_filter = get_vertex(0, z).m_position.y;

        for(int x = m_cols - 2; x >= 0; x -= 1) {
            Vertex vertex = get_vertex(x, z);
            float current_value = vertex.m_position.y;
            float new_value  = filter * prev_filter + (1 - filter) * current_value;
            vertex.m_position.y = new_value;
            prev_filter = new_value;
            set_vertex(x, z, vertex);

        }
    }


    // top to bottom
    for(int x = 0; x < m_cols; x += 1) {
        float prev_filter = get_vertex(0, x).m_position.y;

        for(int z = m_rows- 2; z >= 0; z -= 1) {
            Vertex vertex = get_vertex(x, z);
            float current_value = vertex.m_position.y;
            float new_value  = filter * prev_filter + (1 - filter) * current_value;
            vertex.m_position.y = new_value;
            prev_filter = new_value;
            set_vertex(x, z, vertex);

        }
    }


    // bottom to top
    for(int x = 0; x < m_cols; x += 1) {
        float prev_filter = get_vertex(0, x).m_position.y;

        for(int z = 1 ; z < m_rows; z += 1) {
            Vertex vertex = get_vertex(x, z);
            float current_value = vertex.m_position.y;
            float new_value  = filter * prev_filter + (1 - filter) * current_value;
            vertex.m_position.y = new_value;
            prev_filter = new_value;
            set_vertex(x, z, vertex);

        }
    }



    float max = -1.0f;
    float min = 10000000.0f;


    for(int i = 0; i < m_vertices.size(); i += 1) {
        float value = m_vertices[i].m_position.y;

        if(value > max )
            max = value;

        else if(value < min)
            min = value;



    }

    LinearInterpolator interpolator(min, max, 0.0f, 0.3f);

    for(int i = 0 ; i < m_vertices.size(); i += 1) {
        float y = m_vertices[i].m_position.y;
        m_vertices[i].m_position.y = interpolator.map(y);
    }

}


void TerrainFractalGenerator::update() {
    m_shader->use();

    glm::mat4 view = Camera::get_instance()->get_view();
    m_shader->set_mat4("view", view);

    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(0.0f, -0.5, 0.0f));
    //model = glm::translate(model, glm::vec3(0.0f, -5.0, -10.0f));
    //model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
    m_shader->set_mat4("model", model);


}


glm::vec3 TerrainFractalGenerator::generate_random_point() const {
    return glm::vec3(rand() % m_cols, 0.0f, rand() % m_rows);
}
