#include "Turtle.h"

/* https://stackoverflow.com/questions/9695329/c-how-to-round-a-double-to-an-int */
#define double_to_int(x) ceil(x - 0.5)



Turtle::Turtle(Canvas *canvas) {
    // Set pointers to rendering surfaces
    this->canvas = canvas;

    // Initialize variables to default value
    x = 0;
    y = 0;
    heading = 0;
    r = 0;
    g = 0;
    b = 0;
    a = 255;
    pen_down = true;
    pen_cache_alpha = 255;

    // Give pointer to display turtle to canvas
    canvas->AddDisplayTurtle(&display_turtle);

    // Initialize display turtle
    display_turtle = DisplayTurtle {x, y, true, heading, r, g, b, a};
}

void Turtle::UpdateDisplayTurtle() {
    display_turtle.x = x;
    display_turtle.y = y;
    display_turtle.heading = heading;
    display_turtle.r = r;
    display_turtle.g = g;
    display_turtle.b = b;
    display_turtle.a = a;
}



void Turtle::SetColor(int r, int g, int b, int a) {
    // Turtle variables
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;

    // Update display turtle
    Turtle::UpdateDisplayTurtle();
}

void Turtle::SetVisible(bool visible) {
    // Set turtle visibility
    display_turtle.visible = visible;
}

void Turtle::SetPen(bool pen_down) {
    // Set pen visibility. If pen is already at requested visibility, don't do anything.
    // If it isn't, change visibility boolean, and cache the alpha value or load it to the
    // turtle colour, depending on visibility change
    if (this->pen_down != pen_down) {
        this->pen_down = pen_down;
        
        if (pen_down) {
            a = pen_cache_alpha;
        } else {
            pen_cache_alpha = a;
            a = 0;
        }
    }
}





void Turtle::Goto(int x, int y) {
    // Draw line indicating path
    canvas->DrawLine(this->x, this->y, x, y, r, g, b, a);

    // Set the turtle's new coordinates
    this->x = x;
    this->y = y;

    // Update display turtle
    Turtle::UpdateDisplayTurtle();
}

void Turtle::GetPosition(int &x, int &y) {
    // YKTD
    x = this->x;
    y = this->y;
}




void Turtle::Forward(int distance) {
    // Convert degrees to radians (sin() and cos() only accept radians)
    double heading_in_radians = double(heading) * (PI/180.0);

    // Draw line to new position
    canvas->DrawLine(x, y, x + double_to_int(distance * cos(heading_in_radians)), y + double_to_int(distance * sin(heading_in_radians)), r, g, b, a);

    // Update turtle position
    x += double_to_int(distance * cos(heading_in_radians));
    y += double_to_int(distance * sin(heading_in_radians));

    // Update display turtle
    Turtle::UpdateDisplayTurtle();
}

void Turtle::Backward(int distance) {
    // Convert degrees to radians (sin() and cos() only accept radians)
    double heading_in_radians = double(heading) * (PI/180.0);

    // Draw line to new position
    canvas->DrawLine(x, y, x - double_to_int(distance * cos(heading_in_radians)), y - double_to_int(distance * sin(heading_in_radians)), r, g, b, a);

    // Update turtle position
    x -= double_to_int(distance * cos(heading_in_radians));
    y -= double_to_int(distance * sin(heading_in_radians));

    // Update display turtle
    Turtle::UpdateDisplayTurtle();
}




void Turtle::Left(int degrees) {
    // Adjust heading
    heading -= degrees;

    // Update display turtle
    Turtle::UpdateDisplayTurtle();
}

void Turtle::Right(int degrees) {
    // Adjust heading
    heading += degrees;

    // Update display turtle
    Turtle::UpdateDisplayTurtle();
}




void Turtle::DisplayRectangle(int w, int h) {
    // Add a new rectangle to the canvas drawing stack
    canvas->DrawRectangle(
        x + (w/2),
        y + (h/2),
        x - (w/2),
        y - (h/2),
        r, g, b, a);
}

void Turtle::DisplayCircle(int radius) {
    // Add a new circle to the canvas drawing stack
    canvas->DrawCircle(
        x, y,
        radius,
        r, g, b, a);
}



void Turtle::Wait(int milliseconds) {
    Sleep(milliseconds);
}