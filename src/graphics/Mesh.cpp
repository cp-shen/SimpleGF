#include <stdexcept> // runtime_error
#include <cstring> // memcpy
#include <vector>

#include "./GraphicsCommon.h"

using namespace SimpleGF;

Mesh::Mesh()
    : _vertexCount(0)
    , _indexCount(0)
    , _vertexData(nullptr)
    , _indexData(nullptr)
    , _vao(0)
    , _vbo(0)
    , _ebo(0)
{ }

Mesh::Mesh(std::vector<GLfloat>& vertData)
    : Mesh()
{
    setVertexData(vertData.data(), vertData.size());
}

Mesh::Mesh(std::vector<GLfloat>& vertData, std::vector<GLuint>& idxData)
    : Mesh(vertData)
{
    setIndexData(idxData.data(), idxData.size());
}

Mesh::~Mesh() {
    if(_vertexData)
        delete[] _vertexData;
    if(_indexData)
        delete[] _indexData;

    unload();
}

void Mesh::setVertexData(const GLfloat* data, unsigned count) {
    if(!data || count <= 0)
        throw std::runtime_error("No vertex data");

    if(_vertexData)
        delete[] _vertexData;

    _vertexCount = count;
    _vertexData = new GLfloat[count];
    memcpy(_vertexData, data, count * sizeof(GLfloat));
}

void Mesh::setIndexData(const GLuint* data, unsigned count) {
    if(!data || count <= 0)
        throw std::runtime_error("No index data");

    if(_indexData)
        delete[] _indexData;

    _indexCount = count;
    _indexData = new GLuint[count];
    memcpy(_indexData, data, count * sizeof(GLuint));
}

void Mesh::getVertexData(GLfloat* buf) {
    memcpy(buf, _vertexData, _vertexCount * sizeof(GLfloat));
}

void Mesh::getIndexData(GLuint* buf) {
    memcpy(buf, _vertexData, _vertexCount * sizeof(GLuint));
}


unsigned Mesh::getVertexCount() {
    return _vertexCount;
}

unsigned Mesh::getIndexCount() {
    return _indexCount;
}

GLuint Mesh::vao() {
    return _vao;
}

GLuint Mesh::vbo() {
    return _vbo;
}

GLuint Mesh::ebo() {
    return _ebo;
}

void Mesh::load() {
    if(!_vertexData)
        throw std::runtime_error("no vertex data in mesh to load");

    unload();

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertexCount * sizeof(GLfloat), _vertexData, GL_STATIC_DRAW);

    if(!_indexData) {
        glGenBuffers(1, &_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount * sizeof(GLuint), _indexData, GL_STATIC_DRAW);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::unload() {
    if(_vao) {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
    }
    if(_vbo) {
        glDeleteBuffers(1, &_vbo);
        _vbo = 0;
    }
    if(_ebo) {
        glDeleteBuffers(1, &_ebo);
        _ebo = 0;
    }
}
