#include <cstdlib>
#include <ctime>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "texture.h"

static const GLchar *vert[] =
{
    "#version 450 core\n"
    "uniform float offset_x, offset_y, offset_z;\n"
    "void main()\n"
    "{ const vec4 verts[] = vec4[]( vec4(-.004, 0, 0, 1), "
    "                                vec4(-.0025, .0025, 0, 1),"
    "                               vec4(.0025, .0025, 0, 1), "
    "                               vec4(.004, 0, 0, 1),"
    "                               vec4(.0025, -.0025, 0, 1),"
    "                               vec4(-.0025, -.0025, 0, 1) ); \n"
    "gl_Position = verts[gl_VertexID] + vec4(offset_x, offset_y, 0, offset_z); "
    "} \n"
};

static const char *frag[] =
{
    "#version 450 core\n"
    "out vec4 color;\n"
    "uniform float offset_z;\n"
    "void main() { \n"
    "color = vec4(offset_z*1.5, 1-offset_z*1.5, 1-offset_z*1.5, (1-offset_z)*1.5);"
    "} \n"
};

GLuint compile_shaders(const GLchar *v[], const GLchar *f[])
{
    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1, v, NULL);
    glCompileShader(vert_shader);

    GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, f, NULL);
    glCompileShader(frag_shader);

    GLuint program = glCreateProgram();

    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);
    glLinkProgram(program);

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    return program;

}

int main()
{
    srand(time(NULL));
    if(!glfwInit()) return 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    GLFWwindow *window = glfwCreateWindow(640, 480, "OpenGL SuperBible", 0, 0);
    glfwMakeContextCurrent(window);
    glfwShowWindow(window);

    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) return 2;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLuint shader = compile_shaders(vert, frag);

    int w, h;
    static float c[] = { 0.0f, 0.0f, 0.05f, 1.0f };

    std::vector<Texture*> stars;
    for(int i=0; i<500; i++) stars.emplace_back(new Texture());

    do
    {
        glViewport(0, 0, w, h);
        glClearBufferfv(GL_COLOR, 0, c);
        glfwGetWindowSize(window, &w, &h);

        for(auto i : stars) { i->Update(); i->Draw(&shader); }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while(!glfwWindowShouldClose(window) &&
          !glfwGetKey(window, GLFW_KEY_ESCAPE));

    while(stars.size() > 0)
        stars.erase(stars.end()-1);

    glfwDestroyWindow(window);

    return 0;
}
