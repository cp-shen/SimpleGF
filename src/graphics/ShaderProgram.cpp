#include <stdexcept> // runtime_error
#include <cassert>

#include "./GraphicsCommon.h"

using namespace SimpleGF;

ShaderProgram::ShaderProgram(const std::vector<std::shared_ptr<Shader> >& shaders) {
    if(shaders.size() == 0)
        throw std::runtime_error("no shader provided to create the program");
    for(auto shader_ptr : shaders) {
        if(!shader_ptr)
            throw std::runtime_error("shader is null in ShaderProgram ctor");
    }

    _objectId = glCreateProgram();

    if(_objectId == 0)
        throw std::runtime_error("glCreateProgram failed");

     _shaders = shaders;
    _attachShaders();
}

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(_objectId);
}

GLuint ShaderProgram::objectId() const{
    return _objectId;
}

GLint ShaderProgram::getAttribLocation(const GLchar* attribName) const {
    if(!attribName)
        throw std::runtime_error("attribName is null");

    GLint location = glGetAttribLocation(_objectId, attribName);

    if(location < 0)
        throw std::runtime_error("Attrib " + std::string(attribName) +
                " not found in shaders");

    return location;
}

GLint ShaderProgram::getUniformLocation(const GLchar* uniformName) const {
    if(!uniformName)
        throw std::runtime_error("uniformName is null");

    GLint location = glGetUniformLocation(_objectId, uniformName);

    if(location < 0)
        throw std::runtime_error("Uniform " + std::string(uniformName) +
                " not found in shaders");

    return location;
}

void ShaderProgram::_attachShaders() {
    assert(_shaders.size() > 0 );

    for(auto shader_ptr : _shaders){
        assert(shader_ptr != nullptr);
        glAttachShader(_objectId, shader_ptr->objectId());
    }

    glLinkProgram(_objectId);
    glValidateProgram(_objectId);

    for(auto shader_ptr : _shaders){
        assert(shader_ptr != nullptr);
        glDetachShader(_objectId, shader_ptr->objectId());
    }

    // check link error
    GLint status;
    glGetProgramiv(_objectId, GL_LINK_STATUS, &status);
    if(status == GL_FALSE){
        std::string msg = "failed to link program: " + std::to_string(_objectId);

        GLint infoLogLength;
        glGetProgramiv(_objectId, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar infoLog[infoLogLength + 1];
        glGetProgramInfoLog(_objectId, infoLogLength, nullptr, infoLog);

        glDeleteProgram(_objectId);

        msg += "\n";
        msg += infoLog;
        throw std::runtime_error(msg);
    }
    // check validate error
    glGetProgramiv(_objectId, GL_VALIDATE_STATUS, &status);
    if(status == GL_FALSE){
        std::string msg = "failed to validate program: " + std::to_string(_objectId);

        GLint infoLogLength;
        glGetProgramiv(_objectId, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar infoLog[infoLogLength + 1];
        glGetProgramInfoLog(_objectId, infoLogLength, nullptr, infoLog);

        glDeleteProgram(_objectId);

        msg += "\n";
        msg += infoLog;
        throw std::runtime_error(msg);
    }
}
