//
// Created by symbolic on 23-6-1.
//

#ifndef REFLECTIVESHADOWMAPSREMAKE_MESH_H
#define REFLECTIVESHADOWMAPSREMAKE_MESH_H


#include "GameObject.h"

namespace renderer {
    class Mesh : public GameObject {
    private:
        unsigned int vao_;
    public:
        Mesh(unsigned int vao) : vao_(vao) {}

        unsigned int GetVao() const {
            return vao_;
        }
    };
}

#endif //REFLECTIVESHADOWMAPSREMAKE_MESH_H
