#include <glad/glad.h>

#include <iostream>

#include <shader.hpp>
#include <window.hpp>

int main()
{
    Window window(1280, 720, "Window");
    float aspect = 1280.0/720.0;
    float projection[16] =
    {
        1.0f/aspect, 0, 0, 0,
        0.0, 1.0, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    float vertices[] =
    {
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f
    };
    
    unsigned int indices[] =
    {
        0, 1, 3,
        1, 2, 3
    };

    Shader shader("src/shader/vertex.vs", "src/shader/fragment.fs");

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // Only once as well

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    shader.use(); // Won't change for now
    shader.setmatrix4fv("projection", projection);


    while (!window.shouldClose())
    {
        glClearColor(0.0, 0.0, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.pollEvents();
        window.swapBuffer();
    }

    return 0;
}