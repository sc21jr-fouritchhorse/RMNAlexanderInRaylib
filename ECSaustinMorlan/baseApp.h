//
// Created by qiaojun on 10/02/24.
//

#ifndef BASEAPP_H
#define BASEAPP_H

#ifndef APP_H
#define APP_H

#include "theECS.h"
#include <raylib.h>
#include <vector>

class App {
public:
    App(int initialWidth, int initialHeight, const char* title);
    ~App();
    void RunLoop();

protected:
    void Init();
    void Exit();
    void Input();
    void Update();
    void Draw();
    std::vector<> entities;
    std::vector<std::pair<int,int>> resolutions;
    const char *title;
    int currW;
    int currH;
    Color bgCol;

private:
    void setResolutions();
};

#endif // APP_H
#endif //BASEAPP_H
