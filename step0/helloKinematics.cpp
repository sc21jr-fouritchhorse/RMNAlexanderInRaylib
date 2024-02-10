#include <raylib.h>
#include <raymath.h>
#include <cstdio>
#include <vector>


const int resolutions[][2] = {
    {320, 240},
    {640, 480},
    {800, 600},
    {1024, 768},
    {1280, 720},
    {1280, 1024},
    {1600, 900},
    {1920, 1080},
    {2560, 1440}
};


int currW, currH;
float userX, userY;
float myTime;
Vector2 lastVel = {0.0f, 0.0f};
int frameCount;
const float userSpeed = 10.0f;
const float inverseUS = 1.0f / userSpeed;
int boneCount = 100;
float inverseBC = (1.0f / boneCount) + 1E-32f;



typedef struct bone {
    struct bone *parent;
    Vector2 startCoord;
    Vector2 endCoord;
    float length;
    float angle;
    float damping;
    float drawThickness;
    void Init(Vector2 origin, float l, float theta, float t) 
    {
        startCoord = origin;
        length = l;
        angle = theta;
        parent = nullptr;
        damping = 0.f;
        drawThickness = t;
        Update();
    }
    void Update() 
    {
        if(parent != nullptr)  {
            angle = (parent->angle + (angle - parent->angle) * damping) + ((angle > 0.0f)? 1E-32f : -1E-32f);
            startCoord = parent->endCoord;
            printf("\nChild bone damping: %f\tChild bone angle: %f\n", damping, angle);
        }
        endCoord = Vector2{startCoord.x + length * cosf(angle), startCoord.y + length * sinf(angle)}; 
        
    }
    void Draw() 
    {
        DrawCircle(startCoord.x, startCoord.y, drawThickness, RED);
        DrawCircle(endCoord.x, endCoord.y, drawThickness, RED);
    }


} Bone;


std::vector<Bone*> bones;
Bone firstBone;


void Init()
{
    userX = currW / 2.0f;
    userY = currH / 2.0f;
    firstBone.Init(Vector2{currW * 0.5f, currH * 0.5f}, currW * inverseBC * 0.5f, 1.0f, currH * inverseBC * 2.5f);
    bones.push_back(&firstBone);
    myTime = 1E-32f;
    frameCount = 0;
    Bone *parentBone = &firstBone;
    for (int i = 0; i < boneCount; i++)
    {
        Bone *childBone = new Bone();
        childBone->Init(parentBone->endCoord, parentBone->length, parentBone->angle, parentBone->drawThickness * 0.99f);
        childBone->damping = (i * inverseBC) * ((boneCount - i) * inverseBC);
        childBone->parent = parentBone;
        parentBone = childBone;
        bones.push_back(childBone);                                                   
    }
    
}


void Update()
{
    float velY = firstBone.startCoord.y - userY;
    float velX = firstBone.startCoord.x - userX;
    firstBone.startCoord.x = userX;
    firstBone.startCoord.y = userY;
    firstBone.Update();
    
    if((lastVel.x != 0 || lastVel.y != 0) && (velX != 0.0f || velY != 0.0f)) {
        firstBone.angle = atan2f((velY+1E-32),(velX+1E-32));
        printf("\nRoot angle: %f\n", firstBone.angle);
    }
    
    float tailLen = 0.0f;
    for (bone *i : bones)
    {
        i->Update();
        if(velX != 0 || velY != 0) {
            i->angle += sinf(myTime) * cosf(inverseBC - tailLen) * inverseBC;
        }
        tailLen += inverseBC;
    }
    
    myTime += GetFrameTime();
    lastVel = {velX, velY};
    frameCount += 1;

}


void Draw()
{
    ClearBackground(RAYWHITE);
    DrawText("I'm controlling this with a joystick\n\n\n\n; the dodgy turning is due to atan2f (I think)", 0,  0, currW / 25, BLACK);
    for (bone *i : bones)
    {
        i->Draw();
    }
}

void Exit()
{
    bones.clear();
}


void Input()
{
    //Resolution control
    int resInd = (GetKeyPressed() - (KEY_ZERO) - 1);
    if(resInd >= 0 && resInd <= 8)
        if(resolutions[resInd][0] && resolutions[resInd][1])  {
            SetWindowSize(resolutions[resInd][0], resolutions[resInd][1]);
            currW = resolutions[resInd][0];
            currH = resolutions[resInd][1];
            Exit();
            Init();
        }
    if(IsGamepadAvailable(0)) {
        userX += GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) * userSpeed;
        userY += GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) * userSpeed;
    }
    
    if(IsKeyDown(KEY_W))
        userY -= userSpeed;
    if(IsKeyDown(KEY_S))
        userY += userSpeed;
    if(IsKeyDown(KEY_A))
        userX -= userSpeed;
    if(IsKeyDown(KEY_D))
        userX += userSpeed;
    if(GetMouseDelta().x != 0.0f)
        userX = GetMousePosition().x;
    if(GetMouseDelta().y != 0.0f)
        userY = GetMousePosition().y;
    
}

int main()
{
    InitWindow(800, 600, "Hello Raylib");
    SetTargetFPS(60);

    currH = 600;
    currW = 800;
    Init();
    while(!WindowShouldClose())
    {
        BeginDrawing();
        Input();
        Update();
        Draw();
        EndDrawing();
    }
    Exit();
    CloseWindow();

    return 0;
}