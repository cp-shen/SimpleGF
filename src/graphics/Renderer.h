#ifndef RENDERER_H
#define RENDERER_H

#include "../math/MathCommom.h"
#include "./Camera.h"
#include "./Color.h"
#include "./Material.h"
#include "./Mesh.h"

namespace SimpleGF {

class Renderer {
public:
    Renderer();
    virtual ~Renderer();

    Color clearColor;

    void drawMesh(const Mesh& mesh,
                  const Material& material,
                  const Camera& camera,
                  const Transform& modelTransform);

private:
    void loadMesh(const Mesh& mesh, const Material& material);
    // disable copying
    Renderer(const Renderer& other) = default;
    Renderer& operator=(const Renderer& other) = default;
};

} // namespace SimpleGF

#endif /* RENDERER_H */
