#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include "triangle.h"
#include "tiny_obj_loader.h"

#include <vector>
#include <string>
#include <iostream>
std::vector<triangle> loadOBJ(const std::string& filename, const color& albedo) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str())) {
        std::cerr << warn << err << std::endl;
        return {};
    }

    std::vector<triangle> tris;
    
    // Track bounds
    double min_x = 1e10, max_x = -1e10;
    double min_y = 1e10, max_y = -1e10;
    double min_z = 1e10, max_z = -1e10;

    for (const auto& shape : shapes) {
        size_t index_offset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
            int fv = shape.mesh.num_face_vertices[f];
            if (fv != 3) {
                index_offset += fv;
                continue;
            }

            point3 v[3];
            for (int vtx = 0; vtx < 3; vtx++) {
                tinyobj::index_t idx = shape.mesh.indices[index_offset + vtx];
                v[vtx] = point3(
                    attrib.vertices[3 * idx.vertex_index + 0],
                    attrib.vertices[3 * idx.vertex_index + 1] - 0.7,
                    attrib.vertices[3 * idx.vertex_index + 2] - 1
                );
                
                // Track bounds
                min_x = std::min(min_x, v[vtx].x());
                max_x = std::max(max_x, v[vtx].x());
                min_y = std::min(min_y, v[vtx].y());
                max_y = std::max(max_y, v[vtx].y());
                min_z = std::min(min_z, v[vtx].z());
                max_z = std::max(max_z, v[vtx].z());
            }
            tris.emplace_back(v[0], v[1], v[2], albedo);
            index_offset += fv;
        }
    }
    
    std::cerr << "Loaded " << tris.size() << " triangles\n";
    std::cerr << "Bounds: X[" << min_x << ", " << max_x << "] "
              << "Y[" << min_y << ", " << max_y << "] "
              << "Z[" << min_z << ", " << max_z << "]\n";
    
    return tris;
}
#endif
