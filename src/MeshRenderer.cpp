#include "common.h"
#include <stdexcept>

using namespace GLPractice;

MeshRenderer::MeshRenderer(Mesh* mesh, GLProgram* program):
    _mesh(mesh),
    _shaderProgram(program),
    clearColor(0.9f, 0.9f, 0.9f)
{
    if(!_mesh)
        throw std::runtime_error("mesh is null in MeshRenderer constructor");

    if(!_shaderProgram)
        throw std::runtime_error("shaderProgram is null in MeshRenderer constructor");

    load();
}

MeshRenderer::~MeshRenderer() {
    unload();
}

void MeshRenderer::load() {
    if(!_mesh) {
        throw std::runtime_error("no mesh data in MeshRenderer");
    }
    if(!_shaderProgram) {
        throw std::runtime_error("no shader program in MeshRenderer");
    }

    if(!_mesh->vao() || !_mesh->vbo() || !_mesh->ebo()) {
        _mesh->load();
    }

    glBindVertexArray(_mesh->vao());
    glBindBuffer(GL_ARRAY_BUFFER, _mesh->vbo());

    glEnableVertexAttribArray(_shaderProgram->GetAttribLocation(VERT_SHADER_POS_ATTRIB_NAME));
    glVertexAttribPointer(_shaderProgram->GetAttribLocation(VERT_SHADER_POS_ATTRIB_NAME), 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshRenderer::unload() {

}

void MeshRenderer::render() {
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    // clear color and depth info since last draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // setup defore drawing
    glUseProgram(_shaderProgram->getObjectId());
    glBindVertexArray(_mesh->vao());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh->ebo());

    // draw some primitives
    //glDrawArrays(GL_TRIANGLES, 0, _mesh->getVertexCount());
    glDrawElements(GL_TRIANGLES, _mesh->getIndexCount(), GL_UNSIGNED_INT, 0);

    // reset bindings after drawing
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
}
