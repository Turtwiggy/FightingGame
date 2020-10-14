
//header
#include "texture.hpp"

//c++ standard library headers
#include <iostream>

//other library headers
#include <GL/glew.h>

namespace fightingengine {

Texture2D::Texture2D()
    : Texture2D::Texture2D("defaultconstructor")
{
    printf("!! texture created using default constructor !! ");
}

Texture2D::Texture2D(std::string path)
    : width(0)
    , height(0)
    , Internal_Format(GL_RGB)
    , Image_Format(GL_RGB)
    , Wrap_S(GL_REPEAT)
    , Wrap_T(GL_REPEAT)
    , Filter_Min(GL_LINEAR)
    , Filter_Max(GL_LINEAR)
    , path(path)
{
    glGenTextures(1, &this->id);
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->width = width;
    this->width = height;
    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}

} //namespace fightingengine
