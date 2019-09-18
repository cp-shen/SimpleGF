#ifndef MESH_H
#define MESH_H

#include <memory>
#include <vector>
#include "./GraphicsAbstraction.h"
#include "./BaseVertexAttribData.h"
#include "./VertexIndexData.h"

namespace SimpleGF {

class Mesh {
    public:
        Mesh();
        //Mesh(std::vector<GLfloat>& vertData);
        //Mesh(std::vector<GLfloat>& vertData, std::vector<GLuint>& idxData);
        virtual ~Mesh();

        //void setVertexData(const GLfloat* data, unsigned count);
        void setIndexData(std::shared_ptr<VertexIndexData> idxData);
        void addAttribData(std::shared_ptr<BaseVertexAttribData> attribData);
        //void getVertexData(GLfloat* buf) const;
        //void getIndexData(GLuint* buf) const;
        //unsigned getVertexCount() const;
        //unsigned getIndexCount() const;
        GLuint vao() const;
        void load();

    private:
        std::vector<std::shared_ptr<BaseVertexAttribData>> _attribData;
        std::shared_ptr<VertexIndexData> _indexData;

        //unsigned _vertexCount;
        //unsigned _indexCount;
        GLfloat* _vertexData;
        //GLuint* _indexData;
        GLuint _vao;

        Mesh& operator=(const Mesh& other) = default;
        Mesh(const Mesh& other) = default;
};

}

#endif /* MESH_H */
