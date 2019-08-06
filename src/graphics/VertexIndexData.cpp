#include <cstring> // memcpy
#include "./GraphicsCommon.h"

using namespace SimpleGF;

VertexIndexData::VertexIndexData(const GLuint* data, unsigned count) {
    _set(data, count);
}

VertexIndexData::~VertexIndexData() {
    delete[] _data;
}

void VertexIndexData::_set(const GLuint* data, unsigned count) {
    if(!data || count <= 0)
        throw std::runtime_error("No index data");

    if(_data)
        delete[] _data;

    _count = count;
    _data = new GLuint[count];
    memcpy(_data, data, count * sizeof(GLuint));
}
