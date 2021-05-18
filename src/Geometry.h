#pragma once





struct DisplayLine {
    int x1;
    int y1;
    int x2;
    int y2;
    
    int r;
    int g; 
    int b;
    int a;
};


struct DisplayRectangle {
    int x1;
    int y1;
    int x2;
    int y2;
    
    int r;
    int g; 
    int b;
    int a;
};


struct DisplayCircle {
    int x;
    int y;

    int radius;
    
    int r;
    int g; 
    int b;
    int a;
};


struct DisplayTurtle {
    int x;
    int y;

    bool visible;
    int heading;

    int r;
    int g;
    int b;
    int a;
};