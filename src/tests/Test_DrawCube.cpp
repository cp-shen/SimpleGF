#include <vector>
#include <memory> // shared_ptr
#include <catch.hpp>

#include "../graphics/GraphicsCommon.h"
#include "../utils/UtilsCommon.h"

using namespace SimpleGF;

static const char* vShaderPath = "./resource/shaders/default.vert";
static const char* fShaderPath = "./Resource/shaders/default.frag";
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

static std::vector<GLfloat> vertexData {
// a cube
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
};

static std::vector<GLuint> indexData {
// cube index
    7, 3, 2,
    7, 2, 6,
    6, 2, 5,
    5, 2, 1,
    4, 5, 1,
    4, 1, 0,
    7, 4, 3,
    3, 4, 0,
    4, 7, 6,
    4, 6, 5,
    3, 0, 2,
    2, 0, 1,
};

TEST_CASE("Mesh_bad_alloc") {
    REQUIRE_THROWS_AS(
        std::make_shared<Mesh>(indexData),
        std::bad_alloc
    );
    REQUIRE_THROWS_AS(
        std::make_shared<Mesh>(indexData, vertexData),
        std::bad_alloc
    );
}


TEST_CASE("Mesh_alloc") {
    std::shared_ptr<Mesh> mesh;
    REQUIRE_NOTHROW(
        mesh = std::make_shared<Mesh>(vertexData, indexData)
    );
    REQUIRE_NOTHROW(
            mesh->load()
    );
    REQUIRE_NOTHROW(
            mesh->unload()
    );
    REQUIRE_NOTHROW(
            mesh = nullptr
    );
}

TEST_CASE("Window_alloc") {
    std::shared_ptr<Window> window;
    REQUIRE_NOTHROW(
            window = std::make_shared<Window>(
                WINDOW_WIDTH, WINDOW_HEIGHT, "Testing: DrawCube")
    );
    REQUIRE_NOTHROW(window = nullptr);
}

TEST_CASE("Shader_loading") {
    std::shared_ptr<Shader> vShader;
    std::shared_ptr<Shader> fShader;
    std::shared_ptr<ShaderProgram> shaderProgram;

    REQUIRE_NOTHROW(vShader = Shader::shaderFromFile(vShaderPath, GL_VERTEX_SHADER));
    REQUIRE_NOTHROW(fShader = Shader::shaderFromFile(fShaderPath, GL_FRAGMENT_SHADER));
    REQUIRE_NOTHROW(shaderProgram = std::shared_ptr<ShaderProgram>(
            new ShaderProgram(std::vector<std::shared_ptr<Shader> >{fShader, vShader})));

    REQUIRE_NOTHROW(vShader = nullptr);
    REQUIRE_NOTHROW(fShader = nullptr);
    REQUIRE_NOTHROW(shaderProgram = nullptr);
}

TEST_CASE("Rendering") {
    auto vShader = Shader::shaderFromFile(vShaderPath, GL_VERTEX_SHADER);
    auto fShader = Shader::shaderFromFile(fShaderPath, GL_FRAGMENT_SHADER);
    auto shaders = std::vector<std::shared_ptr<Shader> > {fShader, vShader};
    auto shaderProgram = std::shared_ptr<ShaderProgram> (new ShaderProgram(shaders));
    auto mesh = std::make_shared<Mesh> (vertexData, indexData);
    auto material = std::shared_ptr<Material> (new Material(shaderProgram));
    auto renderer = std::shared_ptr<Renderer> (new Renderer());
    auto window = std::shared_ptr<Window> (new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Rendering"));
    auto camera = std::shared_ptr<Camera> (new Camera());

    Transform modelTransform;

    while(!window->shouldClose()) {
        Input::pollEvents();
        renderer->drawMesh(mesh, material, camera, modelTransform);
        window->swapBuffers();
    }
}
