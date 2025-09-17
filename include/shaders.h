#pragma once

typedef struct shader_program
{
    unsigned int ID;
} shader_program;

shader_program create_shader_program(const char *vertexShaderPath, const char *fragmentShaderPath);

void use_shader_program(shader_program shader);

void set_shader_uniform_int(shader_program shader, const char *name, int value);

void set_shader_uniform_float(shader_program shader, const char *name, float value);
