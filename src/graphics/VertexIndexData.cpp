#include <cstring> // memcpy
#include "./GraphicsCommon.h"

using namespace SimpleGF;

VertexIndexData::VertexIndexData(const GLuint* data, unsigned vertexCount) {
    _set(data, vertexCount);
}

VertexIndexData::~VertexIndexData() {
    delete[] _data;
    glDeleteBuffers(1, &_ibo);
}

void VertexIndexData::_load() {
    glGenBuffers(1, &_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            _vertexCount * 3 * sizeof(GLuint),
            _data,
            GL_STATIC_DRAW);
}

void VertexIndexData::_set(const GLuint* data, unsigned vertexCount) {
    if(!data || vertexCount <= 0)
        throw std::runtime_error("No index data");

    if(_data)
        delete[] _data;

    _vertexCount = vertexCount;
    _data = new GLuint[vertexCount * 3];
    memcpy(_data, data, 3 * vertexCount * sizeof(GLuint));
}
