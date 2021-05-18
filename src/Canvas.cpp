#include "Canvas.h"



Canvas::Canvas() {
    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create window and renderer
    window = SDL_CreateWindow("Turtle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    // Initialize variables to default value
    r = 0;
    g = 0;
    b = 0;

    window_width = 800;
    window_height = 800;

    xc = window_width/2;
    yc = window_height/2;
}


void Canvas::SetColor(int r, int g, int b) {
    // Set the canvas' R, G and B parameters
    // These will then be used in updates when the screen is cleared
    this->r = r;
    this->g = g;
    this->b = b;
}


void Canvas::GetColor(int &r, int &b, int &g) {
    // Set the supplied variables to the canvas' R, G and B paramaters
    r = this->r;
    g = this->g;
    b = this->b;
}


void Canvas::SetSize(int w, int h) {
    // Just set the window size using SDL's provided function
    SDL_SetWindowSize(window, w, h);
}


void Canvas::GetSize(int &w, int &h) {
    // Set given variables to Canvas object's stored size
    w = window_width;
    h = window_height;
}


void Canvas::SetFullscreen(bool fullscreen) {
    // Set window to fullscreen
    if (fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    else            SDL_SetWindowFullscreen(window, 0);
}


void Canvas::Update() {
    // Clear the window
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);

    // Render geometry
    // TURTLES
    for (DisplayTurtle *e : display_turtles) {
        if (e->visible) {

            double heading_in_radians = double(e->heading) * (PI/180.0);

            vector<Sint16> vx;
            vector<Sint16> vy;

            vx.push_back(xc + e->x - cos(heading_in_radians-0.5) * 10);
            vy.push_back(yc + e->y - sin(heading_in_radians-0.5) * 10);

            vx.push_back(xc + e->x + cos(heading_in_radians) * 5);
            vy.push_back(yc + e->y + sin(heading_in_radians) * 5);

            vx.push_back(xc + e->x - cos(heading_in_radians+0.5) * 10);
            vy.push_back(yc + e->y - sin(heading_in_radians+0.5) * 10);

            vx.push_back(xc + e->x - cos(heading_in_radians) * 5);
            vy.push_back(yc + e->y - sin(heading_in_radians) * 5);

            filledPolygonRGBA(renderer, &vx[0], &vy[0], 4, e->r, e->g, e->b, e->a);
        }
    }

    // LINES
    for (DisplayLine e : lines) {
        aalineRGBA(renderer, 
            xc + e.x1, 
            yc + e.y1, 
            xc + e.x2, 
            yc + e.y2,
            e.r, e.g, e.b, e.a);
    }

    // RECTANGLES
    for (DisplayRectangle e : rectangles) {
        rectangleRGBA(renderer, 
            xc + e.x1, 
            yc + e.y1, 
            xc + e.x2, 
            yc + e.y2, 
            e.r, e.g, e.b, e.a);
    }

    // CIRCLES
    for (DisplayCircle e : circles) {
        aacircleRGBA(renderer, 
            xc + e.x, 
            yc + e.y, 
            e.radius, 
            e.r, e.g, e.b, e.a);
    }


    // Update window size variables
    SDL_GetWindowSize(window, &window_width, &window_height);
    xc = window_width/2;
    yc = window_height/2;

    // Handle events
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        switch (event.type) {

        case SDL_QUIT:
            // Window should quit
            delete this; // am I doing this right?
            break;

        case SDL_KEYDOWN:
            // Key down
            if (event.key.keysym.sym == SDLK_ESCAPE) delete this;   // Escape
            break;
        }
    }

    // Tell SDL to update the window
    SDL_RenderPresent(renderer);
}





void Canvas::AddDisplayTurtle(DisplayTurtle *display_turtle) {
    display_turtles.push_back(display_turtle);
}

void Canvas::DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a) {
    DisplayLine new_line = {x1, y1, x2, y2, r, g, b, a};
    Canvas::lines.push_back(new_line);
}

void Canvas::DrawRectangle(int x1, int y1, int x2, int y2, int r, int g, int b, int a) {
    DisplayRectangle new_rectangle = {x1, y1, x2, y2, r, g, b, a};
    Canvas::rectangles.push_back(new_rectangle);
}

void Canvas::DrawCircle(int x, int y, int radius, int r, int g, int b, int a) {
    DisplayCircle new_circle = {x, y, radius, r, g, b, a};
    Canvas::circles.push_back(new_circle);
}