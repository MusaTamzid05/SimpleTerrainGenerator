#ifndef FRACTAL_TERRAIN_GENERATOR_H
#define FRACTAL_TERRAIN_GENERATOR_H

#include "terrain.h"
#include <string>

struct TerrainFractalGenerator: Terrain {
    TerrainFractalGenerator(
            int cols,
            int rows,
            int iterations,
            float min_height,
            float max_height
            );


    virtual ~TerrainFractalGenerator();

    void init_height();
    void update();
    glm::vec3 generate_random_point() const;

    float m_min_height;
    float m_max_height;

    float m_iterations;




};

#endif
