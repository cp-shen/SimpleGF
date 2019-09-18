#include <vector>
#include <memory> // shared_ptr
#include <catch2/catch.hpp>

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


TEST_CASE("Draw") {
    REQUIRE_NOTHROW( Application::init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE) );

    SECTION("Draw_Section") {
        std::vector<std::shared_ptr<Shader>> shaders;
        std::shared_ptr<ShaderProgram> shaderProgram;
        std::shared_ptr<Window> window;
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;
        std::shared_ptr<Renderer> renderer;
        std::shared_ptr<Image> img;
        std::shared_ptr<Texture2D> tex;

        REQUIRE_NOTHROW( shaders.push_back(Shader::shaderFromFile(vShaderPath, GL_VERTEX_SHADER)) );
        REQUIRE_NOTHROW( shaders.push_back(Shader::shaderFromFile(fShaderPath, GL_FRAGMENT_SHADER)) );
        REQUIRE_NOTHROW( shaderProgram = std::make_shared<ShaderProgram>(shaders) );
        REQUIRE_NOTHROW( window = Application::getWindow() );
        REQUIRE_NOTHROW( material = std::make_shared<Material>(shaderProgram) );
        REQUIRE_NOTHROW( renderer = std::make_shared<Renderer>() );

        SECTION("Cube") {
            REQUIRE_NOTHROW( mesh = std::make_shared<Mesh>(cubeVertPosData, cubeIdxData) );
            Camera camera;
            camera.setAspectByWindow(*window);

            Transform modelTransform;
            modelTransform.translation = {0.0f, 0.0f, 5.0f};

            while(!window->shouldClose()) {
                REQUIRE_NOTHROW( Input::pollEvents() );
                REQUIRE_NOTHROW( renderer->drawMesh(*mesh, *material, camera, modelTransform) );
                REQUIRE_NOTHROW( window->swapBuffers() );
            }
        }

        SECTION("Textured_triangle") {
            REQUIRE_NOTHROW( mesh = std::make_shared<Mesh>(cubeVertPosData, cubeIdxData) );
            REQUIRE_NOTHROW( img = Image::imageFromFile(testImagePath) );
            REQUIRE_NOTHROW( tex = std::shared_ptr<Texture2D> (new Texture2D(*img))) ;
            REQUIRE_NOTHROW( img->flipVertically() );

            VertexAttribData<GLfloat> triPosAttribData(
                    "pos", GL_FLOAT, 3, triVertPosData.data(), 3);
            VertexAttribData<GLfloat> triUvAttribData(
                    "texcoord", GL_FLOAT, 2, triVertPosData.data(), 3);

        }
    }

    REQUIRE_NOTHROW( Application::terminate() );
}

