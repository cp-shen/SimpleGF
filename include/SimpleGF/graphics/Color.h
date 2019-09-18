#ifndef COLOR_H
#define COLOR_H

namespace SimpleGF {

class Color {
public:
    float r;
    float g;
    float b;
    float a;
    Color();
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);
};

} // namespace SimpleGF

#endif /* COLOR_H */
