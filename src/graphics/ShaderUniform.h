#ifndef SHADERUNIFORM_H
#define SHADERUNIFORM_H

#include "./GraphicsAbstraction.h"
#include <string>

namespace SimpleGF {

class ShaderUnifrom {
    private:
        std::string name;
        int location;
        GLenum type;
};

}

#endif /* SHADERUNIFORM_H */
