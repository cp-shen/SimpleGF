#ifndef MATERIAL_H
#define MATERIAL_H

#include "./MaterialArg.h"
#include "./MaterialMap.h"
#include "./ShaderProgram.h"

namespace SimpleGF {

class Material {
public:
    Material();
    Material(std::shared_ptr<ShaderProgram> shader);
    virtual ~Material();

    Material(const Material& other) = default;
    Material& operator=(const Material& other) = default;

    std::shared_ptr<ShaderProgram> shader;
    std::vector<MaterialArg> args;
    std::vector<std::shared_ptr<MaterialMap>> maps;
};

} // namespace SimpleGF

#endif /* MATERIAL_H */
