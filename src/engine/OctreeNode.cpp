#include "engine/OctreeNode.h"
#include "config/Config.h"

int OctreeNode::getOctant(const Vector3d& pos) const {
    int oct = 0;
    if (pos.x > center_.x) oct |= 1;
    if (pos.y > center_.y) oct |= 2;
    if (pos.z > center_.z) oct |= 4;
    return oct;
}

void OctreeNode::createChild(int oct){
    double quarter = halfWidth_ * 0.5;

    Vector3d offset{
        (oct & 1) ? quarter : -quarter,
        (oct & 2) ? quarter : -quarter,
        (oct & 4) ? quarter : -quarter
    };

    children_[oct] = std::make_unique<OctreeNode>(
        Vector3d{
            center_.x + offset.x,
            center_.y + offset.y,
            center_.z + offset.z
        },
        quarter
    );
}

void OctreeNode::insert(Body* body){
    const double oldMass = totalMass_;

    totalMass_ += body->mass;

    centerOfMass_ = (centerOfMass_ * oldMass + body->position * body->mass) / totalMass_;

    if(isLeaf()){
        if(bodies_.size() < Config::octree.capacity){
            bodies_.push_back(body);
            return;
        }

        if (halfWidth_ <= Config::octree.minimumHalfWidth)
        {
            bodies_.push_back(body);
            return;
        }
        
        for (Body* b : bodies_){
            int oct = getOctant(b->position);

            if(!children_[oct])
                createChild(oct);

            children_[oct]->insert(b);
        }

        bodies_.clear();
    }

    int oct = getOctant(body->position);

    if(!children_[oct])
        createChild(oct);

    children_[oct]->insert(body);
};

void OctreeNode::print(int depth) const{

    for (int i = 0; i < depth; i++)
        std::cout << "  ";

    std::cout 
        << "Node"
        << " | Mass: " << totalMass_
        << " | COM: ("
        << centerOfMass_.x << ", "
        << centerOfMass_.y << ", "
        << centerOfMass_.z << ")"
        << " | Bodies: " << bodies_.size()
        << "\n";

    
    if (isLeaf()){
        for (Body* b : bodies_)
        {
            for (int i = 0; i < depth + 1; i++)
                std::cout << "  ";

            std::cout 
                << "Body"
                << " | Mass: " << b->mass
                << " | Pos: ("
                << b->position.x << ", "
                << b->position.y << ", "
                << b->position.z << ")"
                << "\n";
        }
    }

    for (const auto& child : children_)
    {
        if (child)
            child->print(depth + 1);
    }
}