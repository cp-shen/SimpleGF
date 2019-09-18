#include <SimpleGF/graphics/Image.h>

// uses stb_image to try load files
#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace SimpleGF;

static inline unsigned GetPixelOffset(unsigned col, unsigned row, unsigned width, unsigned height, ImageFormat format)
{
    return (row * width + col) * static_cast<int>(format);
}

Image::Image(unsigned width, unsigned height, ImageFormat format, const unsigned char* pixels)
    : _pixels(nullptr)
{
    _set(width, height, format, pixels);
}

Image::~Image()
{
    if (_pixels)
        delete[] _pixels;
}

void Image::_set(unsigned width, unsigned height, ImageFormat format, const unsigned char* pixels)
{
    if (width == 0)
        throw std::runtime_error("Zero width bitmap");
    if (height == 0)
        throw std::runtime_error("Zero height bitmap");

    _width = width;
    _height = height;
    _format = format;

    size_t newSize = _width * _height * static_cast<int>(_format);

    if (_pixels)
        delete[] _pixels;

    _pixels = new unsigned char[newSize];
    memcpy(_pixels, pixels, newSize);
}

std::shared_ptr<Image> Image::imageFromFile(const char* filePath)
{
    int width, height, channels;
    unsigned char* pixels = stbi_load(filePath, &width, &height, &channels, 0);

    if (!pixels)
        throw std::runtime_error(stbi_failure_reason());

    if (channels < 1 || channels > 4)
        throw std::runtime_error("invalid channel count");

    auto img = std::make_shared<Image>(
        width, height, static_cast<ImageFormat>(channels), pixels);

    stbi_image_free(pixels);

    return img;
}

void Image::flipVertically()
{
    unsigned long rowWidth = static_cast<int>(_format) * _width;
    unsigned char rowBuffer[rowWidth];
    unsigned halfHeight = _height / 2;

    for (unsigned idx = 0; idx < halfHeight; idx++) {
        unsigned char* row = _pixels + GetPixelOffset(0, idx, _width, _height, _format);
        unsigned char* oppositeRow =
            _pixels + GetPixelOffset(0, _height - idx - 1, _width, _height, _format);

        memcpy(rowBuffer, row, rowWidth);
        memcpy(row, oppositeRow, rowWidth);
        memcpy(oppositeRow, rowBuffer, rowWidth);
    }
}

unsigned Image::width() const
{
    return _width;
}

unsigned Image::height() const
{
    return _height;
}

ImageFormat Image::format() const
{
    return _format;
}

unsigned char* Image::pixelBuffer() const
{
    return _pixels;
}
