#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdlib>
#include <GL/glew.h>
#include <GL/gl.h>

extern float tiem;

class Texture
{
public:
    Texture();
    void Draw(GLuint*);
    void Update();

private:
    float x, y, z;
};

#endif // TEXTURE_H
