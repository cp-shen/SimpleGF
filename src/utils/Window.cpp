#include <stdexcept> // runtime_error
#include <iostream> // std::cout
#include <cassert> // std::cout

#include "../graphics/GraphicsAbstraction.h"
#include "./Window.h"

using namespace SimpleGF;

static void glfwOnError(int errorCode, const char* msg) {
    throw std::runtime_error(msg);
}

Window::Window(int wWidth, int wHeight, const char* title) {
    _init(wWidth, wHeight, title);
}

Window::~Window() {
    assert(_glfwWindow);
    glfwDestroyWindow(_glfwWindow);
    std::cout << "Window Closed" << std::endl;
}

void Window::swapBuffers() const {
    glfwSwapBuffers(_glfwWindow);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(_glfwWindow);
}

void Window::_init(int wWidth, int wHeight, const char* title) {

    // init glfw
    glfwSetErrorCallback(glfwOnError);
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");

    // configure glfw window before creating
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // create glfw window
    _glfwWindow = glfwCreateWindow(wWidth, wHeight, title, nullptr, nullptr);
    if(!_glfwWindow) {
        throw std::runtime_error("glfwCreateWindow failed");
    }

    // setup OpenGL context
    glfwMakeContextCurrent(_glfwWindow);

    // init glew
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    if(!GLEW_VERSION_3_3)
        throw std::runtime_error("OpenGL 3.3 API is not avaliable.");

    // enable depth testing
    // default: choose fragment having smaller depth
    glEnable(GL_DEPTH_TEST);
    // enable face culling
    // default: remain front face, which is counter-clockwise
    glEnable(GL_CULL_FACE);

    // setup viewport
    int bufWidth, bufHeight;
    glfwGetFramebufferSize(_glfwWindow, &bufWidth, &bufHeight);
    glViewport(0, 0, bufWidth, bufHeight);

    // print OpenGL info
    _printGLInfo();
}

void Window::_printGLInfo() {
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
}

unsigned Window::width() const {
    int w = 0;
    int h = 0;
    glfwGetFramebufferSize(_glfwWindow, &w, &h);
    return (unsigned) w;
}

unsigned Window::height() const {
    int w = 0;
    int h = 0;
    glfwGetFramebufferSize(_glfwWindow, &w, &h);
    return (unsigned) h;
}
