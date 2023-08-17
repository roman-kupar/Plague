#include"Window.h"

int main()
{

    //Initialize window object
    Window window;

    //window loop
    while (window.running())
    {
        window.update();
        window.render();
    }
    return 0;
}