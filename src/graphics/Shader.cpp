#include <fstream> // ifstream
#include <sstream> // stringstream
#include <cstring> // strlen
#include <stdexcept> // runtime_error

#include "./GraphicsCommon.h"

using namespace SimpleGF;

Shader::Shader(const char* shaderCode, GLenum shaderType) {
    // create shader object
    _objectId = glCreateShader(shaderType);
    if(_objectId == 0)
        throw std::runtime_error("glCreateShader failed");

    // set shader code
    GLint length = strlen(shaderCode);
    const GLchar* code = shaderCode;
    glShaderSource(_objectId, 1, &code, &length);

    // compile shader
    glCompileShader(_objectId);

    // check compile failure
    GLint status;
    glGetShaderiv(_objectId, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) {
        std::string msg = "failed to compile shader: " + std::to_string(_objectId);

        GLint infoLogLength;
        glGetShaderiv(_objectId, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar infoLog[infoLogLength + 1];
        glGetShaderInfoLog(_objectId, infoLogLength, nullptr, infoLog);

        glDeleteShader(_objectId);

        msg += "\n";
        msg += infoLog;
        throw std::runtime_error(msg);
    }
}

Shader::~Shader(){
    glDeleteShader(_objectId);
}

std::shared_ptr<Shader> Shader::shaderFromFile(const char* filePath, GLenum shaderType){
    std::ifstream f;
    f.open(filePath, std::ios::in | std::ios::binary);
    if(!f.is_open())
        throw std::runtime_error(std::string("failed to open file: ") + filePath);

    std::stringstream buffer;
    buffer << f.rdbuf();

    return std::make_shared<Shader>(buffer.str().c_str(), shaderType);
}

GLuint Shader::getObjectId() {
    return _objectId;
}
