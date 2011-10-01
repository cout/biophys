#ifndef Texture_Loader__hpp
#define Texture_Loader__hpp

#include "Texture.hpp"

#include <map>
#include <string>

class Texture_Loader
{
public:
  Texture_Loader();

  Texture texture(std::string const & filename);

private:
  typedef std::map<std::string, Texture> Textures;
  Textures textures_;
};

#endif // Texture_Loader__hpp
