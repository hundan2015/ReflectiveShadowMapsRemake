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
    Engine() {}
    void RenderTick() {
        // First pass.
        for (auto &i : mesh_objects_) {
            auto &mesh_object = i.second;
            mesh_object.SetShaderProgram(g_buffer_shader_);
            FirstPass();
        }
        // Second pass.
        for (auto &i : mesh_objects_) {
        }
    }
    void FirstPass() const {
        // TODO: make first pass.
        //  1. 几何处理阶段
        GLuint g_buffer;
        glGenFramebuffers(1, &g_buffer);
        glBindFramebuffer(GL_FRAMEBUFFER, g_buffer);
        GLuint g_position;
        GLuint g_normal;
        GLuint g_albedo_spec;
        // 位置颜色缓冲
        glGenTextures(1, &g_position);
        glBindTexture(GL_TEXTURE_2D, g_position);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, kScrWidth_, kScrHeight_, 0,
                     GL_RGB, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, g_position, 0);
        // 法线颜色缓冲
        glGenTextures(1, &g_normal);
        glBindTexture(GL_TEXTURE_2D, g_normal);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, kScrWidth_, kScrHeight_, 0,
                     GL_RGB, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,
                               GL_TEXTURE_2D, g_normal, 0);
        // 颜色+镜面颜色缓冲
        glGenTextures(1, &g_albedo_spec);
        glBindTexture(GL_TEXTURE_2D, g_normal);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, kScrWidth_, kScrHeight_, 0,
                     GL_RGBA, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2,
                               GL_TEXTURE_2D, g_albedo_spec, 0);

        GLuint attachments[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
                                GL_COLOR_ATTACHMENT2};
        glDrawBuffers(3, attachments);
    }
};

}  // namespace renderer

#endif  // REFLECTIVESHADOWMAPSREMAKE_ENGINE_H
