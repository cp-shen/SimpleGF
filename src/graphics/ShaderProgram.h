#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <memory> // shared_ptr
#include <vector>

#include "./GraphicsAbstraction.h"
#include "./Shader.h"

namespace SimpleGF {

class ShaderProgram {
    public:
        ShaderProgram(const std::vector<std::shared_ptr<Shader> >& shaders);
        virtual ~ShaderProgram();

        GLuint objectId() const;
        GLint getAttribLocation(const GLchar* attribName) const;
        GLint getUniformLocation(const GLchar* uniformName) const;

    private:
        GLuint _objectId;
        std::vector<std::shared_ptr<Shader> > _shaders;

        ShaderProgram(const ShaderProgram& other) = default;
        ShaderProgram& operator=(const ShaderProgram& other) = default;

        void _attachShaders();
};

}

#endif /* SHADERPROGRAM_H */
