#include <SimpleGF/graphics/Color.h>

using namespace SimpleGF;

Color::Color()
{
    // default white color
    r = 1.0f;
    g = 1.0f;
    b = 1.0f;
    a = 1.0f;
}

Color::Color(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}
