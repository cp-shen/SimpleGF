#ifndef BASEVERTEXATTRIBDATA_H
#define BASEVERTEXATTRIBDATA_H

#include <string>

#include "./GraphicsAbstraction.h"

namespace SimpleGF {

class BaseVertexAttribData {
        friend class Mesh; //_load
    public:
        BaseVertexAttribData() = default;
        virtual ~BaseVertexAttribData() = default;
        unsigned vertexCount() const { return _vertexCount; };
    protected:
        virtual void _load() = 0;
        std::string _attribName;
        unsigned _attribSize;
        GLenum _type;
        unsigned _vertexCount;
        GLuint _vbo;
};

}

#endif /* BASEVERTEXATTRIBDATA_H */
