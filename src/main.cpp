//
// Created by symbolic on 23-6-1.
//

#include <glad/glad.h>

#include <iostream>

#include "GLFW/glfw3.h"
#include "controller/ResourceManager.h"
#include "model/GameObject.h"
#include "model/Mesh.h"
const unsigned int kScrWidth = 512;
const unsigned int kScrHeight = 512;
using namespace renderer;
int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window =
        glfwCreateWindow(kScrWidth, kScrHeight, "LearnOpenGL", NULL, NULL);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    GameObject camera;

    Mesh mesh(ResourceManager::GetMeshVao("dir"));
    Material material = {ResourceManager::GetTexture("Albedo"),
                         ResourceManager::GetTexture("Normal"),
                         ResourceManager::GetTexture("metallic"),
                         ResourceManager::GetShaderProgram("fs", "vs")};
    mesh.SetMaterial(material);


    while (!glfwWindowShouldClose(window)) {
        // 1. 几何处理阶段
        GLuint g_buffer;
        glGenFramebuffers(1, &g_buffer);
        glBindFramebuffer(GL_FRAMEBUFFER, g_buffer);
        GLuint g_position;
        GLuint g_normal;
        GLuint g_albedo_spec;
        // 位置颜色缓冲
        glGenTextures(1, &g_position);
        glBindTexture(GL_TEXTURE_2D, g_position);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, kScrWidth, kScrHeight, 0,
                     GL_RGB, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, g_position, 0);
        // 法线颜色缓冲
        glGenTextures(1, &g_normal);
        glBindTexture(GL_TEXTURE_2D, g_normal);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, kScrWidth, kScrHeight, 0,
                     GL_RGB, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,
                               GL_TEXTURE_2D, g_normal, 0);
        // 颜色+镜面颜色缓冲
        glGenTextures(1, &g_albedo_spec);
        glBindTexture(GL_TEXTURE_2D, g_normal);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, kScrWidth, kScrHeight, 0,
                     GL_RGBA, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2,
                               GL_TEXTURE_2D, g_albedo_spec, 0);

        GLuint attachments[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
                                GL_COLOR_ATTACHMENT2};
        glDrawBuffers(3, attachments);

        glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);
        // TODO: Use the first pass shader;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, g_position);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, g_normal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, g_albedo_spec);
        // TODO: Send light data to shader;
        auto camera_position = camera.GetPosition();
        const unsigned int shader_lighting_pass_program = 0;
        glUniform3fv(
            glGetUniformLocation(shader_lighting_pass_program, "view_pos"), 1,
            &camera_position[0]);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}