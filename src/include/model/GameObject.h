//
// Created by symbolic on 23-6-1.
//

#ifndef REFLECTIVESHADOWMAPSREMAKE_GAMEOBJECT_H
#define REFLECTIVESHADOWMAPSREMAKE_GAMEOBJECT_H

#include <glm/gtc/quaternion.hpp>

#include "glm/glm.hpp"

using glm::qua;
using glm::vec3;
namespace renderer {
class GameObject {
    glm::vec3 position_ = {0, 0, 0};
    glm::qua<float> rotation_;

   public:
    void MoveTo(vec3 pos) { position_ = pos; }
    vec3 GetPosition() { return position_; }
    void Move(vec3 pos) { position_ += pos; }

    void Rotate(vec3 rot) { rotation_ *= qua<float>(glm::radians(rot)); }
    qua<float> GetRotation() { return rotation_; };
    void RotateTo(vec3 rot) { rotation_ = qua<float>(glm::radians(rot)); }
};
}  // namespace renderer

#endif  // REFLECTIVESHADOWMAPSREMAKE_GAMEOBJECT_H
