#include"Window.h"

int main()
{

 
    //Initialize window object
    Window window;

    //window loop
    while (window.running())
    {
        if (!window.isPaused()) 
            window.update();

        if (window.isPaused())
            window.pollEvents();

        if (window.isRestarted())
        {
            window.~Window();
            main();
        }

        else 
            window.render();
        
    }
    
    return 0;
}