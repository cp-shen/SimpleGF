#include <stdexcept>

#include "./GraphicsAbstraction.h"
#include "./Renderer.h"

using namespace SimpleGF;

Renderer::Renderer()
    : clearColor(0.9f, 0.9f, 0.9f)
{ }

Renderer::~Renderer() { }

void Renderer::loadMesh(const Mesh& mesh, const Material& material) {

    if(!material.shader)
        throw std::runtime_error("no shader provided in the material");
    const ShaderProgram& shader = *material.shader;

    static const char* VERT_SHADER_POS_ATTRIB_NAME = "pos";

    //if (!mesh) {
        //throw std::runtime_error("no mesh data in Renderer");
    //}
    //if (!shader) {
        //throw std::runtime_error("no shader program in Renderer");
    //}
    if (!mesh.vao() || !mesh.vbo()) {
        throw std::runtime_error("vao or vbo is not loaded in the mesh");
    }

    glBindVertexArray(mesh.vao());
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo());

    glEnableVertexAttribArray(
        shader.getAttribLocation(VERT_SHADER_POS_ATTRIB_NAME));
    glVertexAttribPointer(
        shader.getAttribLocation(VERT_SHADER_POS_ATTRIB_NAME), 3,
        GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::drawMesh(const Mesh& mesh, const Material& material,
        const Camera& camera, const Transform& modelTransform)
{
    static const char* VERT_SHADER_MVP_UNIFORM_NAME = "mvp";

    // get shader program
    if(!material.shader)
        throw std::runtime_error("no shader provided in the material");
    const ShaderProgram& shader = *material.shader;

    // load mesh attrib
    loadMesh(mesh, material);

    // set up mvp matrix
    Matrix modelMatrix = modelTransform.toMatrix();
    Matrix viewMatrix = MatrixIdentity();
    Matrix projectionMatrix = MatrixIdentity();
    //if(camera) {
        viewMatrix = camera.viewMatrix();
        projectionMatrix = camera.projectionMatrix();
    //}
    Matrix mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

    // clear color and depth info since last draw
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // setup defore drawing
    glUseProgram(shader.objectId());
    glBindVertexArray(mesh.vao());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo());

    // setup uniform value
    GLint mvpLoc = shader.getUniformLocation(VERT_SHADER_MVP_UNIFORM_NAME);
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, MatrixToFloatV(mvpMatrix).v);

    // draw some primitives
    if(mesh.jindexData)
        glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());

    // reset bindings after drawing
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

