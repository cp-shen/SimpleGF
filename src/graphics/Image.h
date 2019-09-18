#ifndef IMAGE_H
#define IMAGE_H

#include <memory> //shared_ptr

namespace SimpleGF {

enum class ImageFormat {
    Format_Grayscale = 1, /**< one channel: grayscale */
    Format_GrayscaleAlpha = 2, /**< two channels: grayscale and alpha */
    Format_RGB = 3, /**< three channels: red, green, blue */
    Format_RGBA = 4 /**< four channels: red, green, blue, alpha */
};

class Image {
    public:
        Image(unsigned width, unsigned height, ImageFormat format,
                const unsigned char* pixels);
        virtual ~Image();
        static std::shared_ptr<Image> imageFromFile(const char* filePath);
        void flipVertically();
        unsigned width() const;
        unsigned height() const;
        ImageFormat format() const;
        unsigned char* pixelBuffer() const;
    private:
        unsigned _width;
        unsigned _height;
        ImageFormat _format;
        unsigned char* _pixels;

        Image(const Image& other) = default;
        Image& operator=(const Image& other) = default;

        void _set(unsigned width, unsigned height, ImageFormat format,
                const unsigned char* pixels);
};

}

#endif /* IMAGE_H */
