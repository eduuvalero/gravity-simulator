#include "graphics/LightGrid.h"

#include <cmath>

CellCoord LightGrid::worldToCell(const glm::vec3& position) const {
    return {static_cast<int>(std::floor(position.x / cellSize_)), 
            static_cast<int>(std::floor(position.y / cellSize_)), 
            static_cast<int>(std::floor(position.z / cellSize_))};
}

void LightGrid::insert(std::size_t lightIndex, const glm::vec3& position) {
    const CellCoord cell = worldToCell(position);
    cells_[cell].push_back(lightIndex);
}