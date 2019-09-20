#ifndef MESH_H
#define MESH_H

#include "./BaseVertexAttribData.h"
#include "./GL.h"
#include "./VertexIndexData.h"
#include <memory>
#include <vector>

namespace SimpleGF {

class Mesh {
public:
    Mesh();
    // Mesh(std::vector<GLfloat>& vertData);
    // Mesh(std::vector<GLfloat>& vertData, std::vector<GLuint>& idxData);
    virtual ~Mesh();

    // void setVertexData(const GLfloat* data, unsigned count);
    void setIndexData(std::shared_ptr<VertexIndexData> idxData);
    void addAttribData(std::shared_ptr<BaseVertexAttribData> attribData);
    // void getVertexData(GLfloat* buf) const;
    // void getIndexData(GLuint* buf) const;
    // unsigned getVertexCount() const;
    // unsigned getIndexCount() const;
    GLuint vao() const;
    void load();

private:
    std::vector<std::shared_ptr<BaseVertexAttribData>> _attribData;
    std::shared_ptr<VertexIndexData> _indexData;

    // unsigned _vertexCount;
    // unsigned _indexCount;
    GLfloat* _vertexData;
    // GLuint* _indexData;
    GLuint _vao;

    Mesh& operator=(const Mesh& other) = default;
    Mesh(const Mesh& other) = default;
};

} // namespace SimpleGF

#endif /* MESH_H */
