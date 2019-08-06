#ifndef VERTEX_ATTRIB_DATA_IMPL_H
#define VERTEX_ATTRIB_DATA_IMPL_H

//#include <cstring> // memcpy
#include "./GraphicsCommon.h"

using namespace SimpleGF;

template <typename T>
VertexAttribData<T>::VertexAttribData(const char* name,
        GLenum type, unsigned attribSize, const T* data, unsigned count)
{
    if(attribSize < 1 || attribSize > 4)
        throw std::runtime_error("size of VertexAttribData must be 1,2,3,4");

    _attribName = name;
    _attribSize = attribSize;
    _type = type;
    _data = new T[count];
    _count = count;
    memcpy(_data, data, count * sizeof(T));
}

template <typename T>
VertexAttribData<T>::~VertexAttribData() {
    delete[] _data;
}

#endif // VERTEX_ATTRIB_DATA_IMPL_H
