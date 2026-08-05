#ifndef OCTREE_H
#define OCTREE_H

#include <memory>
#include <array>
#include <iostream>

#include "body.h"

class OctreeNode {
    public:
        OctreeNode(Vector3d center, double halfWidth) : center_(center), halfWidth_(halfWidth) {};

        void insert(Body* body);
        void print(int depth = 0) const;

        Vector3d centerOfMass_{0, 0, 0};
        double totalMass_ = 0.0;

    private:
        Vector3d center_;
        double halfWidth_;
        Body* body_ = nullptr;
        std::array<std::unique_ptr<OctreeNode>, 8> children_;
        static constexpr double MIN_HALFWIDTH = 1e-6;

        bool isLeaf() const {
            for (auto& c : children_) if (c) return false;
            return true;
        }

        int getOctant(const Vector3d& pos) const {
            int oct = 0;
            if (pos.x > center_.x) oct |= 1;
            if (pos.y > center_.y) oct |= 2;
            if (pos.z > center_.z) oct |= 4;
            return oct;
        }

        void subdivide() {
            double quarter = halfWidth_ / 2.0;
            for (int i = 0; i < 8; ++i) {
                Vector3d offset{
                    (i & 1) ? quarter : -quarter,
                    (i & 2) ? quarter : -quarter,
                    (i & 4) ? quarter : -quarter
                };
                children_[i] = std::make_unique<OctreeNode>(
                    Vector3d{center_.x + offset.x, center_.y + offset.y, center_.z + offset.z},
                    quarter
                );
            }
        }
};

#endif