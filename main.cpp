#define SDL_MAIN_HANDLED



#include "src/Turtle.h"


int main() {
    Canvas canvas = Canvas();
    canvas.SetColor(0, 0, 0);

    vector<Turtle> turtles = {Turtle(&canvas)};

    for (int i = 0; i < 100; i++) {

        for (Turtle &turtle : turtles) {

            turtle.SetColor(0, 0, 255, 255);

            turtle.Forward(i/3);
            turtle.Right(50);
            turtle.Left(i);
        }

        canvas.Update();
    }

    while (true) canvas.Update();

    return 0;
}