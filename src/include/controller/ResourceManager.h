//
// Created by Symbolic on 2023/6/1.
//

#ifndef REFLECTIVESHADOWMAPSREMAKE_RESOURCEMANAGER_H
#define REFLECTIVESHADOWMAPSREMAKE_RESOURCEMANAGER_H
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <sstream>

#include "fstream"
#include "model/GameObject.h"
#include "model/Material.h"
namespace renderer {
class ResourceManager {
   public:
    static unsigned int GetShaderProgram(
        const std::string& vertex_shader_dir,
        const std::string& fragment_shader_dir);
    static std::string GetStringFromFile(const std::string& dir);
    static unsigned int GetTexture(const std::string& texture_dir);
    static unsigned int GetMeshVao(const std::string mesh_dir) {
        // TODO: use assimp to load something.
        return 0;
    }
};

}  // namespace renderer

#endif  // REFLECTIVESHADOWMAPSREMAKE_RESOURCEMANAGER_H
