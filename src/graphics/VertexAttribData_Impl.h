#ifndef VERTEX_ATTRIB_DATA_IMPL_H
#define VERTEX_ATTRIB_DATA_IMPL_H

#include "./VertexAttribData.h"

template <typename T>
SimpleGF::VertexAttribData<T>::VertexAttribData(
    const char* name, GLenum type, unsigned attribSize, const T* data, unsigned vertexCount)
{
    if (attribSize < 1 || attribSize > 4)
        throw std::runtime_error("size of VertexAttribData must be 1,2,3,4");

    _attribName = name;
    _type = type;
    _attribSize = attribSize;
    _vertexCount = vertexCount;
    _data = new T[vertexCount * attribSize];
    memcpy(_data, data, vertexCount * attribSize * sizeof(T));
}

template <typename T>
SimpleGF::VertexAttribData<T>::~VertexAttribData()
{
    delete[] _data;
    glDeleteBuffers(1, &_vbo);
}

template <typename T>
void SimpleGF::VertexAttribData<T>::_load()
{
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertexCount * _attribSize * sizeof(T), _data, GL_STATIC_DRAW);
}

#endif // VERTEX_ATTRIB_DATA_IMPL_H
