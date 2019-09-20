#ifndef GRAPHICS_COMMOH_H
#define GRAPHICS_COMMOH_H

#include <cstring>   // memcpy
#include <memory>    // shared_ptr
#include <stdexcept> // runtime_error
#include <utility>   // pair
#include <vector>

#include "../math/MathCommom.h"
#include "../utils/UtilsCommon.h"
#include "./GL.h"

namespace SimpleGF {

// class Shader {
// public:
// Shader(const char* shaderCode, GLenum shaderType);
// virtual ~Shader();

// static std::shared_ptr<Shader> shaderFromFile(const char* filePath, GLenum
// shaderType); GLuint objectId() const;

// private:
// GLuint _objectId;

// Shader(const Shader& other) = default;
// Shader& operator=(const Shader& other) = default;
//};

// class ShaderUnifrom {
// private:
// std::string name;
// int location;
// GLenum type;
//};

// class ShaderProgram {
// public:
// ShaderProgram(const std::vector<std::shared_ptr<Shader> >& shaders);
// virtual ~ShaderProgram();

// GLuint objectId() const;
// GLint getAttribLocation(const GLchar* attribName) const;
// GLint getUniformLocation(const GLchar* uniformName) const;

// private:
// GLuint _objectId;
// std::vector<std::shared_ptr<Shader> > _shaders;

// ShaderProgram(const ShaderProgram& other) = default;
// ShaderProgram& operator=(const ShaderProgram& other) = default;

// void _attachShaders();
//};

// class BaseVertexAttribData {
// public:
// BaseVertexAttribData() = default;
// virtual ~BaseVertexAttribData() = default;
// unsigned vertexCount() const { return _vertexCount; };
// protected:
// virtual void _load() = 0;
// std::string _attribName;
// unsigned _attribSize;
// GLenum _type;
// unsigned _vertexCount;
// GLuint _vbo;
//};

// template<typename T>
// class VertexAttribData : BaseVertexAttribData {
// public:
// VertexAttribData(const char* name,
// GLenum type,
// unsigned attribSize,
// const T* data,
// unsigned vertexCount);
// virtual ~VertexAttribData();
// protected:
// void _load();
// private:
// T* _data;
//};
//#include "./VertexAttribData_Impl.h"

// class VertexIndexData {
// public:
// VertexIndexData(const GLuint* data, unsigned vertexCount);
// virtual ~VertexIndexData();
// unsigned vertexCount() const;
// private:
// void _load();
// void _set(const GLuint* data, unsigned vertexCount);
// GLuint* _data;
// GLuint _ibo;
// unsigned _vertexCount;
//};

// class Mesh {
// public:
// Mesh();
////Mesh(std::vector<GLfloat>& vertData);
////Mesh(std::vector<GLfloat>& vertData, std::vector<GLuint>& idxData);
// virtual ~Mesh();

////void setVertexData(const GLfloat* data, unsigned count);
// void setIndexData(std::shared_ptr<VertexIndexData> idxData);
// void addAttribData(std::shared_ptr<BaseVertexAttribData> attribData);
////void getVertexData(GLfloat* buf) const;
////void getIndexData(GLuint* buf) const;
////unsigned getVertexCount() const;
////unsigned getIndexCount() const;
// GLuint vao() const;
// GLuint vbo() const;
// GLuint ebo() const;
// void load();
// void unload();

// private:
// std::vector<std::shared_ptr<BaseVertexAttribData>> _attribData;
// std::shared_ptr<VertexIndexData> _indexData;

////unsigned _vertexCount;
////unsigned _indexCount;
// GLfloat* _vertexData;
////GLuint* _indexData;
// GLuint _vao;
// GLuint _vbo;
// GLuint _ebo;

// Mesh& operator=(const Mesh& other) = default;
// Mesh(const Mesh& other) = default;
//};

// class Color {
// public:
// float r;
// float g;
// float b;
// float a;
// Color();
// Color(float r, float g, float b);
// Color(float r, float g, float b, float a);
//};

// enum class ImageFormat {
// Format_Grayscale = 1, [>*< one channel: grayscale <]
// Format_GrayscaleAlpha = 2, [>*< two channels: grayscale and alpha <]
// Format_RGB = 3, [>*< three channels: red, green, blue <]
// Format_RGBA = 4 [>*< four channels: red, green, blue, alpha <]
//};

// class Image {
// public:
// Image(unsigned width, unsigned height, ImageFormat format,
// const unsigned char* pixels);
// virtual ~Image();
// static std::shared_ptr<Image> imageFromFile(const char* filePath);
// void flipVertically();
// unsigned width() const;
// unsigned height() const;
// ImageFormat format() const;
// unsigned char* pixelBuffer() const;
// private:
// unsigned _width;
// unsigned _height;
// ImageFormat _format;
// unsigned char* _pixels;

// Image(const Image& other) = default;
// Image& operator=(const Image& other) = default;

// void _set(unsigned width, unsigned height, ImageFormat format,
// const unsigned char* pixels);
//};

// class Texture2D {
// public:
// Texture2D();
// Texture2D(const Image& img,
// GLint minMagFiler = GL_LINEAR,
// GLint wrapMode = GL_CLAMP_TO_EDGE);
// virtual ~Texture2D();
// GLuint objectId() const;
// unsigned width() const;
// unsigned height() const;
// private:
// GLuint _objectId;
// unsigned _width;
// unsigned _height;
////int _mipmapLevel; // default to 1
////int _format;

// Texture2D(const Texture2D& other) = default;
// Texture2D& operator=(const Texture2D& other) = default;
//};

// class MaterialMap {
// private:
// std::shared_ptr<Texture2D> texture;
// Color color;
// float value;
//};

// class MaterialArg {

//};

// class Material {
// public:
// Material();
// Material(std::shared_ptr<ShaderProgram> shader);
// virtual ~Material();

// Material(const Material& other) = default;
// Material& operator=(const Material& other) = default;

// std::shared_ptr<ShaderProgram> shader;
// std::vector<MaterialArg> args;
// std::vector<std::shared_ptr<MaterialMap> > maps;
//};

class Model {
public:
    Model();
    virtual ~Model();

    Model(const Model& other) = default;
    Model& operator=(const Model& other) = default;

    Transform transform;

private:
    std::vector<std::pair<std::shared_ptr<Mesh>, std::shared_ptr<Material>>> _meshMatPairs;
};

// class Camera {
// public:
// Camera();
// virtual ~Camera();

// Matrix projectionMatrix() const;
// Matrix viewMatrix() const;
// void setAspectByWindow(const Window& window);

// float fov; // field of view, in radians
// float aspect; // width / height;
// float near;
// float far;

// Vector3 position;
// Quaternion rotation;
//};

// class Renderer {
// public:
// Renderer();
// virtual ~Renderer();

// Color clearColor;

// void drawMesh(const Mesh& mesh, const Material& material,
// const Camera& camera, const Transform& modelTransform);

// private:
// void loadMesh(const Mesh& mesh, const Material& material);
//// disable copying
// Renderer(const Renderer& other) = default;
// Renderer& operator=(const Renderer& other) = default;
//};

} // namespace SimpleGF

#endif // GRAPHICS_COMMOH_H
