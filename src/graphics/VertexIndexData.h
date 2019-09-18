#ifndef VERTEXINDEXDATA_H
#define VERTEXINDEXDATA_H

#include "./GraphicsAbstraction.h"

namespace SimpleGF {

class VertexIndexData {
    friend class Mesh; //_load
    public:
        VertexIndexData(const GLuint* data, unsigned vertexCount);
        virtual ~VertexIndexData();
        unsigned vertexCount() const;
    private:
        void _load();
        void _set(const GLuint* data, unsigned vertexCount);
        GLuint* _data;
        GLuint _ibo;
        unsigned _vertexCount;
};

}

#endif /* VERTEXINDEXDATA_H */
