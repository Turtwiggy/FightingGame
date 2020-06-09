#pragma once

#include "graphics/texture.h"
#include <GL/glew.h>

#include <iostream>
#include <string>

using namespace fightinggame;

class opengl_texture2D : public texture2D
{
public:
    opengl_texture2D(uint32_t width, uint32_t height);
    opengl_texture2D(const char* path, const std::string& director);
    virtual ~opengl_texture2D();

    virtual uint32_t get_width() const override { return width; }
    virtual uint32_t get_height() const override { return height; }
    virtual uint32_t get_renderer_id() const override { return renderer_id; }

    virtual void set_type(std::string t) override { type = t; std::cout << "TEXTURE SET TO TYPE: " << type << std::endl; }
    virtual std::string get_type() const override { return type; }

    virtual std::string get_path() const override { return path; }

    virtual void set_data(void* data, uint32_t size) override;

    virtual void bind(uint32_t slot = 0) const override;

    virtual bool operator==(const texture& other) const override
    {
        return renderer_id == ((opengl_texture2D&)other).renderer_id;
    }

private:
    std::string path;  // we store the path of the texture to compare with other textures
    std::string type;  //diffuse, specular, normal, height
    uint32_t width, height;
    uint32_t renderer_id;

    GLenum internal_format, data_format;
};

