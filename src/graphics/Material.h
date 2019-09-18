#ifndef MATERIAL_H
#define MATERIAL_H

#include "./MaterialMap.h"
#include "./MaterialArg.h"
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
        std::vector<std::shared_ptr<MaterialMap> > maps;
};

}

#endif /* MATERIAL_H */
