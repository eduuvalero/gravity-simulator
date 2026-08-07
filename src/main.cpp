#include <vector>

#include "graphics/Window.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include "graphics/Shader.h"
#include "graphics/Vertex.h"


int main(){
    Window window(800, 600, "Gravity Simulator");

    std::vector<Vertex> vertices ={
        {{-0.5f, -0.5f, 0.0f}},
        {{ 0.5f, -0.5f, 0.0f}},
        {{ 0.0f,  0.5f, 0.0f}}
    };

    VertexArray vao;
    VertexBuffer vbo(vertices, GL_STATIC_DRAW);

    vao.bind();
    vbo.bind();
    vao.addAttribute(0, 3, GL_FLOAT, sizeof(Vertex), nullptr);

    Shader shader("shaders/default.vert", "shaders/default.frag");

    while (!window.shouldClose()){
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.update();
    }


    return 0;
}