#include <raylib.h>
#include <cstdio>
#include <vector>
#include "worm.h"

class App {
public:
    App(int width, int height, const char* title)
        : currW(width), currH(height), userX(width / 2.0f), userY(height / 2.0f), myTime(1E-32f), frameCount(0), userSpeed(2.5f)
    {
        InitWindow(width, height, title);
        theWorm = Worm();
        SetTargetFPS(60);
        Init();
    }

    ~App()
    {
        Exit();
        CloseWindow();
    }

    void Run()
    {
        while (!WindowShouldClose())
        {
            BeginDrawing();
            Input();
            Update();
            Draw();
            EndDrawing();
        }
    }

    int currW, currH;
    float userX, userY;
    float myTime;
    int frameCount;
    const float userSpeed;

    void Init()
    {
        userX = currW * 0.5f;
        userY = currH * 0.5f;
        theWorm.Init({currW, currH}, 0.9f, 0.5f, 0.9f, (currW * 0.5f) / theWorm.boneCount, 0.0f, (currH * 0.75f) / theWorm.boneCount);
    }

    void Update()
    {
        vec2 userPos = {userX, userY};
        vec2 lastPos = theWorm.GetRootPos();
        vec2 userDisplacement = (userPos - lastPos);

        float newAngle = theWorm.GetRootAngle();

        if (length(userDisplacement) != 0.f)
        {
            if (length(userDisplacement) < 0.f)
                newAngle = atan2f(userDisplacement.y, userDisplacement.x);
            else
                newAngle = atan2f(-userDisplacement.y, -userDisplacement.x);
        }

        if (userY  > currH)
        {
            userY = currH;
            newAngle -= PI;
            newAngle *= -1.f;
            userDisplacement *= -1.f;
        }

        if (userX > currW)
        {
            userX = currW;
            newAngle -= PI;
            newAngle *= -1.f;
            userDisplacement *= -1.f;
        }

        theWorm.SetRootPos({userX, userY}, newAngle);

        theWorm.Update();

        myTime += GetFrameTime();
        frameCount += 1;
    }

    void Draw()
    {
        ClearBackground(RAYWHITE);
        theWorm.Draw();
    }

    void Exit()
    {
    }

    void Input()
    {
        if (IsKeyPressed(KEY_NINE))
        {
            currW -= static_cast<int>(currW * 0.1f);
            currH -= static_cast<int>(currH * 0.1f);
            SetWindowSize(currW, currH);
            Exit();
            Init();
        }
        if (IsKeyPressed(KEY_ZERO))
        {
            currW += static_cast<int>(currW * 0.1f);
            currH += static_cast<int>(currH * 0.1f);
            SetWindowSize(currW, currH);
            Exit();
            Init();
        }
        
        if (IsGamepadAvailable(0))
        {
            userX += GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) * userSpeed;
            userY += GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) * userSpeed;
        }

        if (IsKeyDown(KEY_W))
            userY -= userSpeed;
        if (IsKeyDown(KEY_S))
            userY += userSpeed;
        if (IsKeyDown(KEY_A))
            userX -= userSpeed;
        if (IsKeyDown(KEY_D))
            userX += userSpeed;
        if (GetMouseDelta().x != 0.0f)
            userX = GetMousePosition().x;
        if (GetMouseDelta().y != 0.0f)
            userY = GetMousePosition().y;
    }
    private:
    Worm theWorm;
};
