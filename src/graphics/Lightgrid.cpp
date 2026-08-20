#include "graphics/LightGrid.h"

#include <cmath>

LightGrid::LightGrid(float cellSize) : cellSize_(cellSize) {}

CellCoord LightGrid::worldToCell(const glm::vec3& position) const {
    return {static_cast<int>(std::floor(position.x / cellSize_)), 
            static_cast<int>(std::floor(position.y / cellSize_)), 
            static_cast<int>(std::floor(position.z / cellSize_))};
}

void LightGrid::insert(std::size_t lightIndex, const glm::vec3& position) {
    const CellCoord cell = worldToCell(position);
    cells_[cell].push_back(lightIndex);
}

const std::vector<std::size_t>* LightGrid::find(const glm::vec3& position) const{
    const CellCoord cell = worldToCell(position);
    const auto it = cells_.find(cell);

    if(it == cells_.end()){
        return nullptr;
    }

    return &it->second;
}

std::vector<std::size_t> LightGrid::queryNearby(const glm::vec3& position, int radius) const{
    const CellCoord center = worldToCell(position);
    std::vector<std::size_t> cells;

    for (int x = center.x - radius; x <= center.x + radius; ++x){
        for (int y = center.y - radius; y <= center.y + radius; ++y){
            for (int z = center.z - radius; z <= center.z + radius; ++z){

                CellCoord cell{x, y, z};
                auto it = cells_.find(cell);

                if (it != cells_.end()) {
                    cells.insert(cells.end(), it->second.begin(), it->second.end());
                }
            }
        }
    }

    return cells;
}

void LightGrid::clear(){
    cells_.clear();
}