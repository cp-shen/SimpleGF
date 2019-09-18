#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "./GraphicsAbstraction.h"
#include "./Image.h"

namespace SimpleGF {

class Texture2D {
public:
    Texture2D();
    Texture2D(const Image& img, GLint minMagFiler = GL_LINEAR, GLint wrapMode = GL_CLAMP_TO_EDGE);
    virtual ~Texture2D();
    GLuint objectId() const;
    unsigned width() const;
    unsigned height() const;

private:
    GLuint _objectId;
    unsigned _width;
    unsigned _height;
    // int _mipmapLevel; // default to 1
    // int _format;

    Texture2D(const Texture2D& other) = default;
    Texture2D& operator=(const Texture2D& other) = default;
};

} // namespace SimpleGF

#endif /* TEXTURE2D_H */
