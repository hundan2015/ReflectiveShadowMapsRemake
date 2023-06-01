//
// Created by symbolic on 23-6-1.
//

#include <glad/glad.h>

#include <iostream>

#include "GLFW/glfw3.h"
#include "controller/Engine.h"
#include "controller/ResourceManager.h"
#include "model/GameObject.h"
#include "model/Mesh.h"
const unsigned int kScrWidth = 512;
const unsigned int kScrHeight = 512;
using namespace renderer;
int main() {
    GameObject camera;
    Engine engine;

    Mesh mesh(ResourceManager::GetMeshVao("dir"));
    Material material = {ResourceManager::GetTexture("Albedo"),
                         ResourceManager::GetTexture("Normal"),
                         ResourceManager::GetTexture("metallic"),
                         ResourceManager::GetShaderProgram("fs", "vs")};
    mesh.SetMaterial(material);

    engine.Start();
    return 0;
}