#include <glad/glad.h>

#include <iostream>

#include <shader.hpp>
#include <window.hpp>
#include "stb/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

int main()
{
    Window window(1280, 720, "Window");
    Input& input = window.getInput();

    // float vertices[] =
    // {
    //     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    //     0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
    //     -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
    //     -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f
    // };

    
    // unsigned int indices[] =
    // {
    //     0, 1, 3,
    //     1, 2, 3
    // };
    float vertices[] =
    {
        // Back face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f, 1.0f,
        // Left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f, 0.0f,
        // Right face
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,  0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,  0.0f, 0.0f,
        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,   0.0f, -1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
        // Top face
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f, 0.0f
    };

    Shader shader("src/shader/vertex.vs", "src/shader/fragment.fs");
    Shader outlineShader("src/shader/outline.vs", "src/shader/outline.fs");

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // unsigned int EBO;
    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load("assets/test.png", &width, &height, &channels, 4);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture\n";
    }
    stbi_image_free(data);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5*sizeof(float)));
    glEnableVertexAttribArray(2);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // view = glm::rotate(view, glm::radians(-45.0f), glm::vec3(1.0, 0.0, 0.0));

    glm::mat4 projection = glm::mat4(1.0f);
    
    window.setResizeCallback([&projection](int width, int height)
    {
        projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
    });
    projection = glm::perspective(glm::radians(45.0f), window.getWidth()/window.getHeight(), 0.1f, 100.0f);

    
    window.showFPSInTitle(true);

    shader.use();
    shader.setmatrix4fv("projection", projection);

    outlineShader.use();
    outlineShader.setmatrix4fv("projection", projection);
    bool vsync = true;

    while (!window.shouldClose())
    {
        window.pollEvents();
        glClearColor(0.0, 0.0, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (input.isKeyPressed(GLFW_KEY_F11))
        {
            window.toggleFullScreen();
        }

        if (input.isKeyPressed(GLFW_KEY_F1))
        {
            vsync = !vsync;
            window.setVSync(vsync);
        }

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5, 0.0, 1.0));
        
        shader.use();
        shader.setmatrix4fv("model", model);
        shader.setmatrix4fv("view", view);
        shader.setmatrix4fv("projection", projection);

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);

        outlineShader.use();
        model = glm::scale(model, glm::vec3(1.05f));
        outlineShader.setmatrix4fv("model", model);
        outlineShader.setmatrix4fv("view", view);
        outlineShader.setmatrix4fv("projection", projection);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);

        window.updateFPS();
        // window.pollEvents();
        window.swapBuffer();

        input.endFrame();
    }

    // without one more pollevent, it gives me segfault on wayland
    glfwPollEvents();
    glfwTerminate();

    return 0;
}