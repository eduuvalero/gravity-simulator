#include "graphics/LightManager.h"

#include <glm/glm.hpp>

LightManager::LightManager(float cellSize, float softening, float threshold) : grid_(cellSize), softening_(softening), threshold_(threshold) {};

void LightManager::addLight(const Light& light){
    lights_.push_back(light);

    const std::size_t index = lights_.size() - 1;
    grid_.insert(index, light.position);
}

const Light& LightManager::getLight(std::size_t index) const{
    return lights_[index];
}

std::vector<std::size_t> LightManager::queryNearby(const glm::vec3& position, int radius) const {
    return grid_.queryNearby(position, radius);
}

float LightManager::calculateIntensity(const Light& light, const glm::vec3& position) const{
    const glm::vec3 delta = position - light.position;

    const float distanceSquared = glm::dot(delta, delta);

    return light.intensity / (distanceSquared + softening_ * softening_ * Config::lightning.intensityScale);
}

std::vector<std::size_t> LightManager::getRelevantLights(const glm::vec3& position, int radius) const {
    std::vector<std::size_t> relevantLights;

    for (std::size_t index : queryNearby(position, radius)) {
        if (calculateIntensity(getLight(index), position) >= threshold_) {
            relevantLights.push_back(index);
        }
    }
    return relevantLights;
}

void LightManager::clear() { 
    lights_.clear();
    grid_.clear();
}