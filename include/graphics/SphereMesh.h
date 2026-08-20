#pragma once

#include <memory>

#include "Mesh.h"

class SphereMesh {
    public:
        SphereMesh(unsigned int segments = 32, unsigned int rings = 16);

        const Mesh& getMesh() const;

    private:
        std::unique_ptr<Mesh> mesh;
    };