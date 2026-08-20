#include "graphics/SphereMesh.h"

#include <glm/gtc/constants.hpp>

#include "graphics/Vertex.h"

SphereMesh::SphereMesh(unsigned int segments, unsigned int rings){
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indexData;

    const unsigned int verticesPerRow = segments + 1;

    for (unsigned int ring = 0; ring <= rings; ++ring) {
        for (unsigned int segment = 0; segment <= segments; ++segment){

            float theta = (static_cast<float>(segment) / segments) * 2.0f * glm::pi<float>();
            float phi = (static_cast<float>(ring) / rings) * glm::pi<float>();

            float x = std::sin(phi) * std::cos(theta);
            float y = std::cos(phi);
            float z = std::sin(phi) * std::sin(theta);

            Vertex vertex;
            vertex.position = glm::vec3(x, y, z);
            vertex.normal = glm::vec3(x, y, z);
            vertex.color = glm::vec3(1.0f);
            vertices.push_back(vertex);
            
            if (ring < rings && segment < segments) {
                unsigned int A = ring * verticesPerRow + segment;
                unsigned int B = A + 1;
                unsigned int C = A + verticesPerRow;
                unsigned int D = C + 1;

                indexData.push_back(A);
                indexData.push_back(B);
                indexData.push_back(C);
                indexData.push_back(C);
                indexData.push_back(B);
                indexData.push_back(D);
            }

        }
    }

    mesh = std::make_unique<Mesh>(vertices, indexData);
}

const Mesh& SphereMesh::getMesh() const {
    return *mesh;
}