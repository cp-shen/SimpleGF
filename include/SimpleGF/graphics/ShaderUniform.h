#ifndef SHADERUNIFORM_H
#define SHADERUNIFORM_H

#include "./GL.h"
#include <string>

namespace SimpleGF {

class ShaderUnifrom {
private:
    std::string name;
    int location;
    GLenum type;
};

} // namespace SimpleGF

#endif /* SHADERUNIFORM_H */
