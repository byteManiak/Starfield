#include "texture.h"

Texture::Texture()
{
    x = (rand()%2048-1024) / 1024.0f;
    y = (rand()%1536-768) / 768.0f;
    z  = (rand()%100-50) / 100.0f;
}

void Texture::Update()
{
    z -= 0.015f;
    if(z < -.5) z = .6;
}

void Texture::Draw(GLuint *shader)
{
    glUseProgram(*shader);

    glUniform1f(glGetUniformLocation(*shader, "offset_x"), x);
    glUniform1f(glGetUniformLocation(*shader, "offset_y"), y);
    glUniform1f(glGetUniformLocation(*shader, "offset_z"), z);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
}
