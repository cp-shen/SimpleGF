#ifndef SHADER_H
#define SHADER_H

#include <memory> // shared_ptr

#include "./GL.h"

namespace SimpleGF {

class Shader {
public:
    Shader(const char* shaderCode, GLenum shaderType);
    virtual ~Shader();

    static std::shared_ptr<Shader> shaderFromFile(const char* filePath, GLenum shaderType);
    GLuint objectId() const;

private:
    GLuint _objectId;

    Shader(const Shader& other) = default;
    Shader& operator=(const Shader& other) = default;
};

} // namespace SimpleGF
#endif /* SHADER_H */
