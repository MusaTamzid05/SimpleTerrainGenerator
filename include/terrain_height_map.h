#ifndef TERRAIN_HEIGHT_MAP_H
#define TERRAIN_HEIGHT_MAP_H

#include "terrain.h"
#include <string>

struct TerrainHeightMap : Terrain {
    TerrainHeightMap(const std::string& path);
    virtual ~TerrainHeightMap();

    void init_height();


    int m_channels;
    unsigned char* m_image_data;


};


#endif
