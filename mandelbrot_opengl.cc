#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

// Vertex shader source code
const char* vertexShaderSrc = R"glsl(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    void main() {
        gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    }
)glsl";

// Fragment shader source code
const char* fragmentShaderSrc = R"glsl(
    #version 330 core
    out vec4 FragColor;
    uniform vec2 u_resolution;
    uniform int u_maxIterations;

    vec2 complexSquare(vec2 z) {
        return vec2(z.x*z.x - z.y*z.y, 2.0*z.x*z.y);
    }

    void main() {
        vec2 c = (gl_FragCoord.xy / u_resolution - 0.5) * 2.0 - vec2(1.0, 0.0);
        c.x *= u_resolution.x / u_resolution.y;
        vec2 z = vec2(0.0, 0.0);
        int i;
        for(i = 0; i < u_maxIterations; i++) {
            z = complexSquare(z) + c;
            if(dot(z, z) > 4.0) break;
        }
        float t = float(i) / float(u_maxIterations);
        FragColor = vec4(t, 0.0, 1.0 - t, 1.0);
    }
)glsl";

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Mandelbrot Set", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Vertex Array Object (VAO)
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Vertex Buffer Object (VBO)
    GLfloat vertices[] = {
        -1.0f,  1.0f, // Top-left
         1.0f,  1.0f, // Top-right
         1.0f, -1.0f, // Bottom-right
        -1.0f, -1.0f  // Bottom-left
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Element Buffer Object (EBO)
    GLuint indices[] = {
        0, 1, 2, // First Triangle
        2, 3, 0  // Second Triangle
    };

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    // Create shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Set up vertex data interpretation
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Use the shader program
    glUseProgram(shaderProgram);

    // Set uniform values
    GLint resolutionLoc = glGetUniformLocation(shaderProgram, "u_resolution");
    glUniform2f(resolutionLoc, width, height);
    GLint maxIterationsLoc = glGetUniformLocation(shaderProgram, "u_maxIterations");
    glUniform1i(maxIterationsLoc, 100);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the Mandelbrot set
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap the screen buffers
        glfwSwapBuffers(window);

        // Poll for window events
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);

    glfwTerminate();
    return 0;
}