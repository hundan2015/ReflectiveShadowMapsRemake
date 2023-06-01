//
// Created by symbolic on 23-6-1.
//

#ifndef REFLECTIVESHADOWMAPSREMAKE_MESH_H
#define REFLECTIVESHADOWMAPSREMAKE_MESH_H

#include <memory>

#include "GameObject.h"
#include "Material.h"

namespace renderer {
class Mesh : public GameObject {
   private:
    unsigned int vao_;
    Material material_;

   public:
    Mesh() = default;
    Mesh(unsigned int vao) : vao_(vao) {}

    unsigned int GetVao() const { return vao_; }
    void SetMaterial(Material material) { material_ = material; }
    void SetShaderProgram(unsigned int shader_program) {
        material_.shader_program = shader_program;
    }
};
}  // namespace renderer

#endif  // REFLECTIVESHADOWMAPSREMAKE_MESH_H
