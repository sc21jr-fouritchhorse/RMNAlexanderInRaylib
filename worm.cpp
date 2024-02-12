#include "worm.h"
#include <cmath>
#include <iostream>

void Bone::applyFK(bone *parent, float alpha)
{
    startCoord = parent->endCoord;
    angle = glm::mix(parent->angle, angle, alpha);
    endCoord = vec2{startCoord.x + length * cosf(angle), startCoord.y + length * sinf(angle)};
}




std::ostream &operator<<(std::ostream &os, const bone &b)
{
    os << b.startCoord.x << ", " << b.startCoord.y << " -> " << b.endCoord.x << ", " << b.endCoord.y
       << " Angle: " << b.angle << " Length: " << b.length << " Damping: " << b.damping << " Thickness: " << b.drawThickness;
    return os;
}

Worm::Worm()
{

}

Worm::~Worm() = default;   

void Worm::Init(vec2 origin, float d, float cdf, float a, float l, float theta, float t)
{
    bones.fill(nullptr);
    Bone* root = new Bone();
    root->startCoord = origin;
    root->length = l;
    root->angle = theta;
    root->damping = d;
    root->drawThickness = t;
    cumulativeDampingFactor = cdf;
    angleBlend = a; // Assign a value to angleBlend
    float cumulativeDamping = 1.0f;
    bones[0] = root;
    float inverseBC = 1.f / boneCount;
    for(int i = 1; i < boneCount; i++)
    {
        auto *childBone = new Bone();
        childBone->startCoord = bones[i-1]->endCoord;
        childBone->length = bones[i-1]->length;
        childBone->angle = bones[i-1]->angle;
        childBone->drawThickness = bones[i-1]->drawThickness * 0.99f;
        childBone->damping = root->damping * cumulativeDamping;
        cumulativeDamping *= cumulativeDampingFactor;
        SetParent(childBone, bones[i-1]);
        bones[i] = childBone;
    }
}

void Worm::SetRootPos(vec2 pos, float angle)
{
    bones[0]->applyFK(new Bone{bones[0]->startCoord, {pos.x, pos.y}, 
    bones[0]->length, angle, bones[0]->damping, 0}, angleBlend);
}

vec2 Worm::GetRootPos()
{
    return bones[0]->startCoord;
}

float Worm::GetRootAngle()
{
    return bones[0]->angle;
}

void Worm::Update()
{
    for (auto& b : bones)
    {
        if (parents.count(b) > 0)
        {
            auto parents_b = parents.equal_range(b);
            for (auto iter = parents_b.first; iter != parents_b.second; ++iter)
            {
                std::cout << std::endl;
                std::cout << b->angle;
                Bone * parent_b = iter->second;
                std::cout << " => ";
                b->applyFK(parent_b, angleBlend);
                std::cout << b->angle;
                std::cout << std::endl;
            }
        }
    }
}

void Worm::Draw()
{
    for (auto b : bones)
    {   
        vec2 b_center = 0.5f * (b->endCoord + b->startCoord);
        float triangleAngle = b->angle + PI * 2.125f;
        if (triangleAngle > 2 * PI)
        {
            triangleAngle -= 2 * PI;
        }
        DrawPolyLines({std::abs(b_center.x), std::abs(b_center.y)}, 3, b->drawThickness, triangleAngle, BLACK);
    }
}

void Worm::SetParent(Bone* child, Bone* parent)
{
    parents.insert({child, parent});
}

void Worm::SetChild(Bone* parent, Bone* child)
{
    children.insert({parent, child});
}
