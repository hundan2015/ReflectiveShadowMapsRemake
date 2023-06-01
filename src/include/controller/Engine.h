//
// Created by Symbolic on 2023/6/1.
//

#ifndef REFLECTIVESHADOWMAPSREMAKE_ENGINE_H
#define REFLECTIVESHADOWMAPSREMAKE_ENGINE_H
#include <string>
#include <vector>

#include "map"
#include "model/GameObject.h"
#include "model/Light.h"
#include "model/Mesh.h"
namespace renderer {

class Engine {
    std::map<std::string, Mesh> mesh_objects_;
    std::vector<Light> lights_;
    GameObject camera_;
    unsigned int g_buffer_shader_;

    const unsigned int kScrWidth_ = 512;
    const unsigned int kScrHeight_ = 512;
    GLuint g_buffer_;
    GLuint g_position_;
    GLuint g_normal_;
    GLuint g_albedo_spec_;
    GLuint rbo_depth_;

    GLFWwindow *window_;
    int InitGL();
    float delta_time_;

   public:
    Engine();
    void RenderTick();
    void SetupGBuffer();
    void Start() {
        while (!glfwWindowShouldClose(window_)) {
            RenderTick();
            glfwSwapBuffers(window_);
            glfwPollEvents();
        }
        glfwTerminate();
    }
    float GetDeltaTime() { return delta_time_; }
};

}  // namespace renderer

#endif  // REFLECTIVESHADOWMAPSREMAKE_ENGINE_H
