#include "./UtilsCommon.h"

using namespace SimpleGF;

Application::Application() { }

Application::~Application() { }

std::shared_ptr<Window> Application::_window = nullptr ;

void Application::init(int wWidth, int wHeight, const char* title) {
    _window = std::shared_ptr<Window>(new Window(wWidth, wHeight, title));
}

void Application::terminate() {
    _window = nullptr;
    glfwTerminate();
}

std::shared_ptr<Window> Application::getWindow() {
    return _window;
}
