#include <vector>
#include <memory> // shared_ptr
#include <catch.hpp>

#include "../graphics/GraphicsCommon.h"
#include "../utils/UtilsCommon.h"

using namespace SimpleGF;

static const char* vShaderPath = "./resources/shaders/default.vert";
static const char* fShaderPath = "./resources/shaders/default.frag";
static const char* testImagePath = "./resources/images/hazard.png";
static const char* WINDOW_TITLE = "SimpleGF - Testing";
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

static std::vector<GLfloat> cubeVertPosData {
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
};

static std::vector<GLuint> cubeIdxData {
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

static std::vector<GLfloat> triVertPosData {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
};

static std::vector<GLfloat> triVertUvData {
     0.5f, 1.0f,
     0.0f, 0.0f,
     1.0f, 0.0f,
};

static std::vector<GLuint> triIdxData {
    0, 1, 2
};

TEST_CASE("Window_alloc") {
    std::shared_ptr<Window> window;
    REQUIRE_NOTHROW(window = std::make_shared<Window>(
                WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE));
}

TEST_CASE("Mesh_alloc") {
    auto window = std::make_shared<Window>( WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    std::shared_ptr<Mesh> mesh;
    REQUIRE_NOTHROW(mesh = std::make_shared<Mesh>(cubeVertPosData, cubeIdxData));
    REQUIRE_NOTHROW(mesh->load());
    REQUIRE_NOTHROW(mesh->unload());
}

TEST_CASE("Shader_loading") {
    auto window = std::make_shared<Window>(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    std::shared_ptr<Shader> vShader;
    std::shared_ptr<Shader> fShader;
    std::shared_ptr<ShaderProgram> shaderProgram;

    REQUIRE_NOTHROW(vShader = Shader::shaderFromFile(vShaderPath, GL_VERTEX_SHADER));
    REQUIRE_NOTHROW(fShader = Shader::shaderFromFile(fShaderPath, GL_FRAGMENT_SHADER));
    REQUIRE_NOTHROW(shaderProgram = std::shared_ptr<ShaderProgram>(
            new ShaderProgram(std::vector<std::shared_ptr<Shader>>{fShader, vShader})));
}

TEST_CASE("Rendering") {
    auto window = std::make_shared<Window>( WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    auto vShader = Shader::shaderFromFile(vShaderPath, GL_VERTEX_SHADER);
    auto fShader = Shader::shaderFromFile(fShaderPath, GL_FRAGMENT_SHADER);
    auto shaders = std::vector<std::shared_ptr<Shader> > {fShader, vShader};
    auto shaderProgram = std::shared_ptr<ShaderProgram> (new ShaderProgram(shaders));
    auto mesh = std::make_shared<Mesh> (cubeVertPosData, cubeIdxData);
    auto material = std::shared_ptr<Material> (new Material(shaderProgram));
    auto renderer = std::shared_ptr<Renderer> (new Renderer());

    Camera camera;
    camera.setAspectByWindow(*window);

    Transform modelTransform;
    modelTransform.translation = {0.0f, 0.0f, 5.0f};

    while(!window->shouldClose()) {
        Input::pollEvents();
        REQUIRE_NOTHROW(renderer->drawMesh(*mesh, *material, camera, modelTransform));
        window->swapBuffers();
    }
}

TEST_CASE("Texture_loading") {
    std::shared_ptr<Window> window;
    std::shared_ptr<Image> img;
    std::shared_ptr<Texture2D> tex;

    REQUIRE_NOTHROW(window =
            std::make_shared<Window>( WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE));
    REQUIRE_NOTHROW(img =
            Image::imageFromFile(testImagePath));
    REQUIRE_NOTHROW(tex =
            std::shared_ptr<Texture2D> (new Texture2D(*img)));
    REQUIRE_NOTHROW(img->flipVertically());
}

TEST_CASE("Texture_triangle") {
    std::shared_ptr<Window> window;
    std::shared_ptr<Image> img;
    std::shared_ptr<Texture2D> tex;

    REQUIRE_NOTHROW(window =
            std::make_shared<Window>( WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE));
    REQUIRE_NOTHROW(img =
            Image::imageFromFile(testImagePath));
    REQUIRE_NOTHROW(tex =
            std::shared_ptr<Texture2D> (new Texture2D(*img)));
    REQUIRE_NOTHROW(img->flipVertically());

    auto vShader = Shader::shaderFromFile(vShaderPath, GL_VERTEX_SHADER);
    auto fShader = Shader::shaderFromFile(fShaderPath, GL_FRAGMENT_SHADER);
    auto shaders = std::vector<std::shared_ptr<Shader> > {fShader, vShader};
    auto shaderProgram = std::shared_ptr<ShaderProgram> (new ShaderProgram(shaders));
    auto mesh = std::make_shared<Mesh> (triVertPosData, triIdxData);
    auto material = std::shared_ptr<Material> (new Material(shaderProgram));
    auto renderer = std::shared_ptr<Renderer> (new Renderer());

    Camera camera;
    camera.setAspectByWindow(*window);

    Transform modelTransform;
    modelTransform.translation = {-1.0f, 0.0f, 5.0f};

    while(!window->shouldClose()) {
        Input::pollEvents();
        renderer->drawMesh(*mesh, *material, camera, modelTransform);
        window->swapBuffers();
    }
}

