#ifndef MATERIALMAP_H
#define MATERIALMAP_H

#include "./Color.h"
#include "./Texture2D.h"

namespace SimpleGF {

class MaterialMap {
private:
    std::shared_ptr<Texture2D> texture;
    Color color;
    float value;

public:
    MaterialMap();
    virtual ~MaterialMap();
};

} // namespace SimpleGF

#endif /* MATERIALMAP_H */
