//
// Created by Symbolic on 2023/6/1.
//
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "controller/ResourceManager.h"
#include "stb_image.h"
namespace renderer {
unsigned int ResourceManager::GetShaderProgram(
    const std::string& vertex_shader_dir,
    const std::string& fragment_shader_dir) {
    // 创建Fragment shader
    std::string fragment_shader_source = GetStringFromFile(fragment_shader_dir);
    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* data = fragment_shader_source.c_str();
    glShaderSource(fragment_shader, 1, &data, nullptr);
    // 创建Vertex shader
    std::string vertex_shader_source = GetStringFromFile(vertex_shader_dir);
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertex_data = vertex_shader_source.c_str();
    glShaderSource(vertex_shader, 1, &vertex_data, nullptr);
    // 创建Shader program
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return shader_program;
}
std::string ResourceManager::GetStringFromFile(const std::string& dir) {
    std::ifstream file_stream;
    file_stream.open(dir);
    std::stringstream string_stream;
    string_stream << file_stream.rdbuf();
    std::string source = string_stream.str();
    return source;
}
unsigned int ResourceManager::GetTexture(const std::string& texture_dir) {
    unsigned int texture;
    int width;
    int height;
    int nr_channel;
    unsigned char* data = nullptr;
    const char* directory_str = texture_dir.c_str();
    data = stbi_load(directory_str, &width, &height, &nr_channel, 0);
    assert(data != nullptr);
    if (data == nullptr) {
        std::cout << "The texture failed ot load!\n";
    } else {
        std::cout << "Loaded texture." << std::endl;
    }
    glGenTextures(1, &texture);
    std::cout << "Texture id" << texture << std::endl;
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);

    // glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    return texture;
}
}  // namespace renderer