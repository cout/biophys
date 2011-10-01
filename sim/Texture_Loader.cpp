#include "Texture_Loader.hpp"

#include <SOIL/SOIL.h>

#include <sstream>
#include <stdexcept>

Texture_Loader::
Texture_Loader()
  : textures_()
{
}

Texture
Texture_Loader::
texture(std::string const & filename)
{
  Textures::const_iterator it(textures_.find(filename));
  if (it != textures_.end())
  {
    return it->second;
  }

  Texture texture(
      SOIL_load_OGL_texture(
          filename.c_str(),
          SOIL_LOAD_RGBA,
          SOIL_CREATE_NEW_ID,
          SOIL_FLAG_MIPMAPS | SOIL_FLAG_POWER_OF_TWO));

  if (texture.texture == 0)
  {
    std::stringstream strm;
    strm << "Unable to load texture file: " << filename;
    throw std::runtime_error(strm.str());
  }

  textures_.insert(std::make_pair(filename, texture));
  return texture;
}

