#pragma once

#include <vector>

#include "Light.h"
#include "LightGrid.h"
#include "config/Config.h"

class LightManager{
    private:
        std::vector<Light> lights_;
        LightGrid grid_;
        float softening_;
        float threshold_;
        std::vector<std::size_t> queryNearby(const glm::vec3& position, int radius) const;
        float calculateIntensity(const Light& light, const glm::vec3& position) const;
    public:
        LightManager(float cellSize = Config::lightning.cellSize, float softening = Config::lightning.softening, float threshold = Config::lightning.threshold);
        void addLight(const Light& light);
        const Light& getLight(std::size_t index) const;
        std::vector<std::size_t> getRelevantLights( const glm::vec3& position, int radius) const;
        void clear();
};