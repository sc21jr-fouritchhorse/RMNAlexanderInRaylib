#include <glm/glm.hpp>
#include <raylib.h>
#include <cmath>
#include <math.h>
#include <array>
#include <iostream>
#include <map>
#include <ostream>
using namespace glm;

#define MAX_SEGMENTS 25

//The bone component (the component that handles the kinematics of the bone entity) 
typedef struct bone 
{
    vec2 startCoord;
    vec2 endCoord;
    float length;
    float angle;
    float damping;
    float drawThickness;
    void applyFK(bone *parent, float alpha);
    //void applyIK(bone *child, float alpha);

} Bone;




class Worm
{
    public:
        Worm();
        ~Worm();
        void Init(vec2 origin, float d, float cdf, float a, float l, float theta, float t);
        void Update();
        void Draw();
        const static int boneCount = MAX_SEGMENTS;
        void SetRootPos(vec2 pos, float angle);
        vec2 GetRootPos();
        float GetRootAngle();
    private:
        void SetParent(Bone* child, Bone* parent);
        void SetChild(Bone* parent, Bone* child);
        std::array<Bone*, MAX_SEGMENTS> bones;
        std::multimap<Bone*, Bone*> parents;
        std::multimap<Bone*, Bone*> children;
        float initialDamping;
        float angleBlend;
        float cumulativeDampingFactor;
};
