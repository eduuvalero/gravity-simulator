#ifndef OCTREE_H
#define OCTREE_H

#include <memory>
#include <vector>
#include <array>
#include <iostream>

#include "Body.h"
#include "Config.h"

class OctreeNode {
    private:
        const double halfWidth_;
        const Vector3d center_;

        Vector3d centerOfMass_{0, 0, 0};
        double totalMass_ = 0.0;
        std::vector<Body*> bodies_;
        std::array<std::unique_ptr<OctreeNode>, 8> children_;

        int getOctant(const Vector3d& pos) const;

        void createChild(int oct);
    public:
        OctreeNode(Vector3d center, double halfWidth) : center_(center), halfWidth_(halfWidth) {};

        void insert(Body* body);
        void print(int depth = 0) const;

        // GETTERS
        const std::vector<Body*>& getBodies() const {
            return bodies_;
        }

        double getTotalMass() const {
            return totalMass_;
        }

        double getHalfWidth() const {
            return halfWidth_;
        }

        Vector3d getCenterOfMass() const {
            return centerOfMass_;
        }

        const auto& getChildren() const {
            return children_;
        }

        bool isLeaf() const {
            for (auto& c : children_)
                if (c) return false;
            return true;
        }
};

#endif