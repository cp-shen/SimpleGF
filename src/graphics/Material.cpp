#include "./GraphicsCommon.h"

using namespace SimpleGF;

Material::Material(std::shared_ptr<ShaderProgram> shader)
    : shader(shader)
{ }

Material::Material()
    : shader(nullptr)
{ }

Material::~Material() { }

