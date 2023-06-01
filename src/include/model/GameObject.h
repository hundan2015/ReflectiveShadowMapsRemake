//
// Created by symbolic on 23-6-1.
//

#ifndef REFLECTIVESHADOWMAPSREMAKE_GAMEOBJECT_H
#define REFLECTIVESHADOWMAPSREMAKE_GAMEOBJECT_H

#include <glm/gtc/quaternion.hpp>
#include "glm/glm.hpp"

using glm::vec3;
using glm::qua;
namespace renderer {
    class GameObject {
    public:
        glm::vec3 position = {0, 0, 0};
        glm::qua<float> rotation;

        void MoveTo(vec3 pos) {
            position = pos;
        }

        void Move(vec3 pos) {
            position += pos;
        }

        void Rotate(vec3 rot) {
            rotation *= qua<float>(glm::radians(rot));
        }

        void RotateTo(vec3 rot) {
            rotation = qua<float>(glm::radians(rot));
        }
    };
}


#endif //REFLECTIVESHADOWMAPSREMAKE_GAMEOBJECT_H
