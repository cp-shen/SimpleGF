#include <stdexcept> // runtime_error
#include <cstring> // memcpy
#include <vector>

#include "./Mesh.h"

using namespace SimpleGF;

Mesh::Mesh()
    //: _vertexCount(0)
    //, _indexCount(0)
    //, _vertexData(nullptr)
    //, _indexData(nullptr)
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

Mesh::~Mesh() { }

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

void Mesh::load() {
    if(_attribData.size() == 0)
        throw std::runtime_error("no vertex attrib data in mesh to load");

    unload();

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    if(_indexData) {
        _indexData->_load();
    }

    for(const auto& attribData : _attribData){
        attribData->_load();
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

