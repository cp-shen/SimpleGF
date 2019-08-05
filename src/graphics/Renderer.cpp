#include <stdexcept>

#include "./GraphicsCommon.h"

using namespace SimpleGF;

Renderer::Renderer()
    : clearColor(0.9f, 0.9f, 0.9f)
{ }

Renderer::~Renderer() { }

void Renderer::loadMesh(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) {
    std::shared_ptr<ShaderProgram> shader = material->shader;
    static const char* VERT_SHADER_POS_ATTRIB_NAME = "pos";

    if (!mesh) {
        throw std::runtime_error("no mesh data in Renderer");
    }
    if (!shader) {
        throw std::runtime_error("no shader program in Renderer");
    }
    if (!mesh->vao() || !mesh->vbo()) {
        mesh->load();
    }

    glBindVertexArray(mesh->vao());
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo());

    glEnableVertexAttribArray(
        shader->getAttribLocation(VERT_SHADER_POS_ATTRIB_NAME));
    glVertexAttribPointer(
        shader->getAttribLocation(VERT_SHADER_POS_ATTRIB_NAME), 3,
        GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::drawMesh(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material,
        std::shared_ptr<Camera> camera, Transform modelTransform)
{
    std::shared_ptr<ShaderProgram> shader = material->shader;

    // set up mvp matrix
    Matrix modelMatrix = modelTransform.toMatrix();
    Matrix viewMatrix = MatrixIdentity();
    Matrix projectionMatrix = MatrixIdentity();

    if(camera) {
        viewMatrix = camera->viewMatrix();
        projectionMatrix = camera->projectionMatrix();
    }

    Matrix mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    GLint mvpLoc = shader->getUniformLocation("mvp");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, MatrixToFloatV(mvpMatrix).v);

    loadMesh(mesh, material);

    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    // clear color and depth info since last draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // setup defore drawing
    glUseProgram(shader->getObjectId());
    glBindVertexArray(mesh->vao());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo());

    // draw some primitives
    if(mesh->ebo())
        glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, mesh->getVertexCount());

    // reset bindings after drawing
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

