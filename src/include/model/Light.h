//
// Created by symbolic on 23-6-1.
//

#ifndef REFLECTIVESHADOWMAPSREMAKE_LIGHT_H
#define REFLECTIVESHADOWMAPSREMAKE_LIGHT_H

#include "GameObject.h"

namespace renderer {

    class Light : public GameObject {
    public:
        glm::vec3 color;
    };

} // renderer

#endif //REFLECTIVESHADOWMAPSREMAKE_LIGHT_H
