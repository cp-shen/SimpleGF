#include "./Texture2D.h"

using namespace SimpleGF;

static GLenum getTextureFormat(ImageFormat format) {
    switch (format) {
        case ImageFormat::Format_Grayscale: return GL_LUMINANCE;
        case ImageFormat::Format_GrayscaleAlpha: return GL_LUMINANCE_ALPHA;
        case ImageFormat::Format_RGB: return GL_RGB;
        case ImageFormat::Format_RGBA: return GL_RGBA;
        default: throw std::runtime_error("Unrecognised ImageFormat");
    }
}

Texture2D::Texture2D(const Image& img, GLint minMagFiler, GLint wrapMode)
    : _width(img.width())
    , _height(img.height())
{
    glGenTextures(1, &_objectId);
    glBindTexture(GL_TEXTURE_2D, _objectId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 getTextureFormat(img.format()),
                 (GLsizei)img.width(),
                 (GLsizei)img.height(),
                 0,
                 getTextureFormat(img.format()),
                 GL_UNSIGNED_BYTE,
                 img.pixelBuffer());
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &_objectId);
}

GLuint Texture2D::objectId() const {
    return _objectId;
}

unsigned Texture2D::width() const {
    return _width;
}

unsigned Texture2D::height() const {
    return _height;
}
