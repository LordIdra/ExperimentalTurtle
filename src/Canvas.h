#pragma once



#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>

#include "Geometry.h"

using std::vector;



constexpr double PI = 3.14159265359;

class Canvas
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    int r, g, b;
    int window_width, window_height;
    int yc, xc;   // Window centre

    vector<DisplayLine> lines;
    vector<DisplayRectangle> rectangles;
    vector<DisplayCircle> circles;
    vector<DisplayTurtle*> display_turtles;



public:
    Canvas();

    void SetColor(int r, int g, int b);
    void GetColor(int &r, int &g, int &b);

    void SetSize(int x, int y);
    void GetSize(int &x, int &y);

    void SetFullscreen(bool fullscreen);

    void Update();


    void AddDisplayTurtle(DisplayTurtle *display_turtle);
    void DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a);
    void DrawRectangle(int x1, int y1, int x2, int y2, int r, int g, int b, int a);
    void DrawCircle(int x, int y, int radius, int r, int g, int b, int a);
    void DrawPolygon(int x, int y, int radius, int sides, int r, int g, int b, int a);
};