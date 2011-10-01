#ifndef Texture__hpp
#define Texture__hpp

#include <GL/gl.h>

class Texture
{
public:
  Texture(GLuint texture)
    : texture(texture)
  {
  }

  GLuint const texture;
};

#endif // Texture

