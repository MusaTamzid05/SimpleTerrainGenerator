#include "terrain_height_map.h"
#include "linear_interpolator.h"
#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TerrainHeightMap::TerrainHeightMap(const std::string& path):Terrain() {
    m_rows = 100;
    m_cols = 100;

    m_image_data = stbi_load(path.c_str(), &m_cols, &m_rows, &m_channels, 0);

    if(m_image_data == nullptr) {
        std::cerr << "Could not load " << path << "\n";
        exit(4);
    }

}

TerrainHeightMap::~TerrainHeightMap() {

}


void TerrainHeightMap::init_height() {
    LinearInterpolator interpolator(0.0f, 255.0f, 0.0f, 0.1f);

    for(int z = 0; z < m_rows; z += 1) {;
        for(int x = 0; x < m_cols; x += 1) {

            unsigned char* tex_data = m_image_data + (x + m_cols * z) * m_channels;
            float y = (float)tex_data[0];


            Vertex vertex = get_vertex(x, z);
            vertex.m_position.y = interpolator.map(y);
            set_vertex(x, z, vertex);
        }
    }
}
