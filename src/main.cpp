#include "graphics/Window.h"

#include <glad/glad.h>


int main()
{
    Window window(
        1280,
        720,
        "Gravity Simulator"
    );


    while (!window.shouldClose())
    {
        // Color de fondo
        glClearColor(
            0.05f,
            0.05f,
            0.08f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);


        window.update();
    }


    return 0;
}