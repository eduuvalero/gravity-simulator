#pragma once

#include <memory>
#include <vector>
#include <array>
#include <iostream>

#include "Body.h"
#include "math/Vector3.h"

class OctreeNode {
    private:
        const double halfWidth_;
        const Vec3d center_;

        Vec3d centerOfMass_{0, 0, 0};
        double totalMass_ = 0.0;
        std::vector<Body*> bodies_;
        std::array<std::unique_ptr<OctreeNode>, 8> children_;

        int getOctant(const Vec3d& pos) const;
        void createChild(int oct);
        bool intersectsSphere(const Vec3d& center, double radius) const;

    public:
        OctreeNode(Vec3d center, double halfWidth) : center_(center), halfWidth_(halfWidth) {};
        void insert(Body* body);
        void print(int depth = 0) const;
        void querySphere(const Vec3d& center, double radius, std::vector<Body*>& results) const;

        // GETTERS
        const std::vector<Body*>& getBodies() const { return bodies_; }

        double getTotalMass() const { return totalMass_; }

        double getHalfWidth() const { return halfWidth_; }

        Vec3d getCenterOfMass() const { return centerOfMass_; }

        const auto& getChildren() const { return children_; }

        bool isLeaf() const {
            for (auto& c : children_)
                if (c) return false;
            return true;
        }
};