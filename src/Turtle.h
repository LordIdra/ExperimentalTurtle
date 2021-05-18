#pragma once



#include <SDL2/SDL.h>
#include <math.h>
#include <windows.h>

#include "Canvas.h"



class Turtle
{
private:
    Canvas *canvas;
    DisplayTurtle display_turtle;
    int x;
    int y;
    int heading;
    int r, g, b, a;
    bool pen_down;
    int pen_cache_alpha;

    

public:
    Turtle(Canvas *canvas);

    void UpdateDisplayTurtle();

    void SetColor(int r, int g, int b, int a);
    void SetVisible(bool visible);
    void SetPen(bool pen_down);

    void Goto(int x, int y);
    void GetPosition(int &x, int &y);

    void Forward(int distance);
    void Backward(int distance);
    void Left(int degrees);
    void Right(int degrees);

    void DisplayRectangle(int w, int h);
    void DisplayCircle(int radius);

    void Wait(int milliseconds);
};