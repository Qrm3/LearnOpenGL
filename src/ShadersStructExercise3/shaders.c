#include <stdio.h>
#include <stdlib.h>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <shaders.h>

// TODO : Add a bunch of checking and validation for file IO.
long int get_file_size(FILE *file)
{
    long int size;
    fseek(file, 0L, SEEK_END);

    size = ftell(file);

    rewind(file);
    
    return size;
}

char *read_file_contents(FILE *file)
{
    long int fileSize = get_file_size(file);

    char *result = malloc(sizeof(char) * (fileSize + 1));

    fread(result, sizeof(char), fileSize, file);
    result[fileSize] = '\0';

    return result;
}


shader_program create_shader_program(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    shader_program shader;

    FILE *vertexShaderFile = fopen(vertexShaderPath, "rb");

    FILE *fragmentShaderFile = fopen(fragmentShaderPath, "rb");

    const char *vertexShaderSource = read_file_contents(vertexShaderFile);
    const char *fragmentShaderSource = read_file_contents(fragmentShaderFile);
    
    fclose(vertexShaderFile);
    fclose(fragmentShaderFile);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, 0, infoLog);

        printf("vertexShader failed to compile: %s\n", infoLog);
    }

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, 0, infoLog);

        printf("fragment shader failed to compile: %s\n", infoLog);
    }

    shader.ID = glCreateProgram();

    glAttachShader(shader.ID, vertexShader);
    glAttachShader(shader.ID, fragmentShader);
    glLinkProgram(shader.ID);

    glGetProgramiv(shader.ID, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shader.ID, 512, 0, infoLog);

        printf("Shader program failed to link: %s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader;
}

void use_shader_program(shader_program shader)
{
    glUseProgram(shader.ID);
}

void set_shader_uniform_int(shader_program shader, const char *name, int value)
{
    glUniform1i(glGetUniformLocation(shader.ID, name), value);
}

void set_shader_uniform_float(shader_program shader, const char *name, float value)
{
    glUniform1f(glGetUniformLocation(shader.ID, name), value);
}
