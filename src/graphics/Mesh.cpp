#include <stdexcept> // runtime_error
#include <cstring> // memcpy
#include <vector>

#include "./GraphicsCommon.h"

using namespace SimpleGF;

Mesh::Mesh()
    //: _vertexCount(0)
    //, _indexCount(0)
    //, _vertexData(nullptr)
    //, _indexData(nullptr)
    //, _vao(0)
    //, _vbo(0)
    //, _ebo(0)
{ }

//Mesh::Mesh(std::vector<GLfloat>& vertData)
    //: Mesh()
//{
    //setVertexData(vertData.data(), vertData.size());
    //load();
//}

//Mesh::Mesh(std::vector<GLfloat>& vertData, std::vector<GLuint>& idxData)
    //: Mesh()
//{
    //setVertexData(vertData.data(), vertData.size());
    //setIndexData(idxData.data(), idxData.size());
    //load();
//}

Mesh::~Mesh() {
    //if(_vertexData)
        //delete[] _vertexData;
    //if(_indexData)
        //delete[] _indexData;

    unload();
}

//void Mesh::setVertexData(const GLfloat* data, unsigned count) {
    //if(!data || count <= 0)
        //throw std::runtime_error("No vertex data");

    //if(_vertexData)
        //delete[] _vertexData;

    //_vertexCount = count;
    //_vertexData = new GLfloat[count];
    //memcpy(_vertexData, data, count * sizeof(GLfloat));
//}

void Mesh::setIndexData(std::shared_ptr<VertexIndexData> idxData) {
    _indexData = idxData;
}

void Mesh::addAttribData(std::shared_ptr<BaseVertexAttribData> attribData) {
    if(attribData == nullptr)
        throw std::runtime_error("nullptr detected in addAttribData");
    _attribData.push_back(attribData);
}

//void Mesh::getVertexData(GLfloat* buf) const {
    //memcpy(buf, _vertexData, _vertexCount * sizeof(GLfloat));
//}

//void Mesh::getIndexData(GLuint* buf) const {
    //memcpy(buf, _vertexData, _vertexCount * sizeof(GLuint));
//}


//unsigned Mesh::getVertexCount() const {
    //return _vertexCount;
//}

//unsigned Mesh::getIndexCount() const {
    //return _indexCount;
//}

GLuint Mesh::vao() const {
    return _vao;
}

GLuint Mesh::vbo() const {
    return _vbo;
}

GLuint Mesh::ebo() const {
    return _ebo;
}

void Mesh::load() {
    if(_attribData.size() == 0)
        throw std::runtime_error("no vertex attrib data in mesh to load");

    unload();

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    if(_indexData) {
        _indexData->_load();
    }

    for(auto attribData : _attribData){
        attribData->_load();
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
