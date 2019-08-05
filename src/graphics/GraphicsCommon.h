#ifndef GRAPHICS_COMMOH_H
#define GRAPHICS_COMMOH_H

#include <vector>
#include <memory> // shared_ptr
#include <utility> // pair

#include "./GraphicsAbstraction.h"
#include "../math/MathCommom.h"

namespace SimpleGF {

class Shader {
    public:
        Shader(const char* shaderCode, GLenum shaderType);
        ~Shader();

        static std::shared_ptr<Shader> shaderFromFile(const char* filePath, GLenum shaderType);
        GLuint getObjectId();

    private:
        GLuint _objectId;

        Shader(const Shader& other);
        Shader& operator=(const Shader& other);
};

class ShaderVertAttrib {
    private:
        std::string name;
        int location;
        GLenum type;
};

class ShaderUnifrom {
    private:
        std::string name;
        int location;
        GLenum type;
};

class ShaderProgram {
    public:
        ShaderProgram(const std::vector<std::shared_ptr<Shader> >& shaders);
        ~ShaderProgram();

        GLuint getObjectId();
        GLint getAttribLocation(const GLchar* attribName) const;
        GLint getUniformLocation(const GLchar* uniformName) const;

    private:
        GLuint _objectId;
        std::vector<std::shared_ptr<Shader> > _shaders;

        ShaderProgram(const ShaderProgram& other);
        ShaderProgram& operator=(const ShaderProgram& other);

        void _attachShaders();
};

class Mesh {
    public:
        Mesh();
        Mesh(std::vector<GLfloat>& vertData);
        Mesh(std::vector<GLfloat>& vertData, std::vector<GLuint>& idxData);
        virtual ~Mesh();

        void setVertexData(const GLfloat* data, unsigned count);
        void setIndexData(const GLuint* data, unsigned count);
        void getVertexData(GLfloat* buf);
        void getIndexData(GLuint* buf);
        unsigned getVertexCount();
        unsigned getIndexCount();
        GLuint vao();
        GLuint vbo();
        GLuint ebo();
        void load();
        void unload();

    private:
        unsigned _vertexCount;
        unsigned _indexCount;
        GLfloat* _vertexData;
        GLuint* _indexData;
        GLuint _vao;
        GLuint _vbo;
        GLuint _ebo;

        Mesh& operator=(const Mesh& other);
        Mesh(const Mesh& other);
};

// TODO: each of r, g, b, a should be clamped between 0.0f and 1.0f
// TODO: adding operator *, +
struct Color {
    public:
        float r;
        float g;
        float b;
        float a;
        Color() {
            // default white color
            r = 1.0f;
            g = 1.0f;
            b = 1.0f;
            a = 1.0f;
        }
        Color(float r, float g, float b) {
            this->r = r;
            this->g = g;
            this->b = b;
        }
        Color(float r, float g, float b, float a) {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }
};

class Texture2D {
    public:
        Texture2D();
        ~Texture2D();

    private:
        GLuint _objectId;
        int width;
        int height;
        int mipmapLevel;
        int format;

        Texture2D(const Texture2D& other);
        Texture2D& operator=(const Texture2D& other);
};

class MaterialMap {
    private:
        std::shared_ptr<Texture2D> texture;
        Color color;
        float value;
};

class MaterialArg {

};

struct Material {
    public:
        Material();
        Material(std::shared_ptr<ShaderProgram> shader);
        ~Material();

        Material(const Material& other) = default;
        Material& operator=(const Material& other) = default;

        std::shared_ptr<ShaderProgram> shader;
        std::vector<MaterialArg> args;
        std::vector<std::shared_ptr<MaterialMap> > maps;
};

class Model {
    public:
        Model();
        ~Model();

        Model(const Model& other) = default;
        Model& operator=(const Model& other) = default;

        Transform transform;

    private:
        std::vector<std::pair<std::shared_ptr<Mesh>, std::shared_ptr<Material>>> _meshMatPairs;
};

struct Camera {
    public:
        Camera();
        ~Camera();

        Matrix projectionMatrix();
        Matrix viewMatrix();

        float fov; // field of view, in radians
        float aspect; // width / height;
        float near;
        float far;

        Vector3 position;
        Quaternion rotation;
};

class Renderer {
    public:
        Renderer();
        ~Renderer();

        Color clearColor;

        void drawMesh(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material,
                std::shared_ptr<Camera> camera, Transform modelTransform);

    private:
        void loadMesh(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
        // disable copying
        Renderer(const Renderer& other) = default;
        Renderer& operator=(const Renderer& other) = default;
};

} // namespace SimpleGF

#endif // GRAPHICS_COMMOH_H
