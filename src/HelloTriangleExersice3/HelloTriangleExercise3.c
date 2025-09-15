// Exercise 1 :
// Try to draw 2 triangles next to each other using `glDrawArrays` by adding 
// more vertices to your data.

#include <stdio.h>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

// Source Vertex Shader written in GLSL. 
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Source Fragment Shader written in GLSL.
const char *orangeShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char *yellowShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";


int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle", 0, 0);

    if (!window)
    {
        printf("GLFW Window Creation Failed!\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("GLAD failed to initialize!\n");
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, 800, 600);

    // Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, 0 , infoLog);

        printf("vertex shader failed to compile: %s\n", infoLog);
        return -1;
    }

    // Fragment Shader
    // Orange
    unsigned int orangeFragmentShader;
    orangeFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(orangeFragmentShader, 1, &orangeShaderSource, 0);
    glCompileShader(orangeFragmentShader);

    glGetShaderiv(orangeFragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(orangeFragmentShader, 512, 0, infoLog);

        printf("fragment shader failed to compile: %s\n", infoLog);
        return -1;
    }

    // Yellow
    unsigned int yellowFragmentShader;
    yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(yellowFragmentShader, 1, &yellowShaderSource, 0);
    glCompileShader(yellowFragmentShader);

    glGetShaderiv(yellowFragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(yellowFragmentShader, 512, 0, infoLog);

        printf("fragment shader failed to compile: %s\n", infoLog);
        return -1;
    }

    // Shader program
    // Orange
    unsigned int orangeShaderProgram = glCreateProgram();

    glAttachShader(orangeShaderProgram, vertexShader);
    glAttachShader(orangeShaderProgram, orangeFragmentShader);
    glLinkProgram(orangeShaderProgram);

    glGetProgramiv(orangeShaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(orangeShaderProgram, 512, 0, infoLog);

        printf("Shader program failed to link: %s\n", infoLog);
        return -1;
    }


    unsigned int yellowShaderProgram = glCreateProgram();

    glAttachShader(yellowShaderProgram, vertexShader);
    glAttachShader(yellowShaderProgram, yellowFragmentShader);
    glLinkProgram(yellowShaderProgram);

    glGetProgramiv(yellowShaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(yellowShaderProgram, 512, 0, infoLog);

        printf("Shader program failed to link: %s\n", infoLog);
        return -1;
    }

    // Delete vertex and fragment shader objects as they are no longer needed.
    glDeleteShader(vertexShader);
    glDeleteShader(orangeFragmentShader);
    glDeleteShader(yellowFragmentShader);
   
    // triangle vertices
    float triangle1Vertices[] = {
        // Triangle 1
        -1.0f, -0.5f, 0.0f, // Left
        0.0f, -0.5f, 0.0f,  // Right 
        -0.5f, 0.5f, 0.0f   // Top
    };

    float triangle2Vertices[] = {
        // Triangle 2
        -0.0f, -0.5f, 0.0f, // Left
        1.0f, -0.5f, 0.0f,  // Right
        0.5f, 0.5f, 0.0f    // Top
    };

    // Vertex Buffer Object and Vertex Array Object
    unsigned int triangle1VAO;
    unsigned int triangle1VBO;

    glGenVertexArrays(1, &triangle1VAO);
    glGenBuffers(1, &triangle1VBO);

    glBindVertexArray(triangle1VAO);

    glBindBuffer(GL_ARRAY_BUFFER, triangle1VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1Vertices), triangle1Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int triangle2VAO;
    unsigned int triangle2VBO;

    glGenVertexArrays(1, &triangle2VAO);
    glGenBuffers(1, &triangle2VBO);

    glBindVertexArray(triangle2VAO);

    glBindBuffer(GL_ARRAY_BUFFER, triangle2VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2Vertices), triangle2Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Triangle 1
        glUseProgram(orangeShaderProgram);
        glBindVertexArray(triangle1VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Triangle 2
        glUseProgram(yellowShaderProgram);
        glBindVertexArray(triangle2VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
