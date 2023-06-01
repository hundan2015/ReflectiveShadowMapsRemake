//
// Created by Symbolic on 2023/6/1.
//

#ifndef REFLECTIVESHADOWMAPSREMAKE_MATERIAL_H
#define REFLECTIVESHADOWMAPSREMAKE_MATERIAL_H
#include <glad/glad.h>

#include <iostream>

#include "GLFW/glfw3.h"
namespace renderer {
class Material {
   public:
    unsigned int albedo;
    unsigned int normal;
    unsigned int metallic;
    unsigned int shader_program;
    void Use() { glUseProgram(shader_program); }
};
}  // namespace renderer

#endif  // REFLECTIVESHADOWMAPSREMAKE_MATERIAL_H
