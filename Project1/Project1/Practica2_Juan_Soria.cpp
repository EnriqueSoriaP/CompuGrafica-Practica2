// Practica 2 
// Soria Palos Juan Enrique
// Fecha de entrega: 23/08/2025
// 422015639
//

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;

// 0 = blanco, 1 = negro, 2 = rojo
int deadpool[30][30] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,2,2,2,2,2,2,2,1,0,0,0,0,0,0},
    {0,0,0,0,1,2,1,1,1,2,1,1,1,2,1,0,0,0,0,0},
    {0,0,0,1,2,1,1,1,1,2,1,1,1,1,2,1,0,0,0,0},
    {0,0,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,0,0,0},
    {0,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,0,0},
    {0,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,0,0},
    {0,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,0,0},
    {0,1,2,1,1,0,1,1,1,2,1,1,1,0,1,1,2,1,0,0},
    {0,1,2,1,1,0,0,1,1,2,1,1,0,0,1,1,2,1,0,0},
    {0,1,2,1,1,1,0,0,1,2,1,0,0,1,1,1,2,1,0,0},   // 0 = blanco, 1 = negro, 2 = rojo
    {0,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,0,0},
    {0,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,0,0},
    {0,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,0,0},
    {0,0,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,0,0,0},
    {0,0,0,1,2,1,1,1,1,2,1,1,1,1,2,1,0,0,0,0},
    {0,0,0,0,1,2,1,1,1,2,1,1,1,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,2,2,2,2,2,2,2,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int main() {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2 Enrique Soria", NULL, NULL);
    glfwSetFramebufferSizeCallback(window, resize);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Fondo blanco
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.Use();

        float pixelSize = 0.08f; // tamaño de cada cuadrado 

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                int color = deadpool[i][j];
                float r = 1.0f, g = 1.0f, b = 1.0f; // blanco por defecto

                if (color == 1) { r = 0.0f; g = 0.0f; b = 0.0f; } // negro
                if (color == 2) { r = 1.0f; g = 0.0f; b = 0.0f; } // rojo

                float x = -1.0f + j * pixelSize;
                float y = 1.0f - i * pixelSize;

                float vertices[] = {
                    x, y, 0.0f,   r,g,b,
                    x + pixelSize, y, 0.0f,   r,g,b,
                    x + pixelSize, y - pixelSize, 0.0f,   r,g,b,
                    x, y - pixelSize, 0.0f,   r,g,b
                };

                unsigned int indices[] = { 0,1,2, 0,2,3 };

                GLuint VBO, VAO, EBO;
                glGenVertexArrays(1, &VAO);
                glGenBuffers(1, &VBO);
                glGenBuffers(1, &EBO);

                glBindVertexArray(VAO);

                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
                glEnableVertexAttribArray(0);

                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
                glEnableVertexAttribArray(1);

                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                glBindVertexArray(0);

                glDeleteVertexArrays(1, &VAO);
                glDeleteBuffers(1, &VBO);
                glDeleteBuffers(1, &EBO);
            }
        }

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
