#pragma once

#include <cstddef>
#include <unordered_map>
#include <vector>
#include <glm/vec3.hpp>

struct CellCoord {
    int x, y, z;

    bool operator==(const CellCoord& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct CellCoordHash{
    std::size_t operator()(const CellCoord& coord) const {
        std::size_t h1 = std::hash<int>{}(coord.x);
        std::size_t h2 = std::hash<int>{}(coord.y);
        std::size_t h3 = std::hash<int>{}(coord.z);

        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

class LightGrid {
    private:
        float cellSize_;
        std::unordered_map<CellCoord, std::vector<std::size_t>,CellCoordHash> cells_;
        CellCoord worldToCell(const glm::vec3& position) const;
        void insert(std::size_t lightIndex, const glm::vec3& position);
};