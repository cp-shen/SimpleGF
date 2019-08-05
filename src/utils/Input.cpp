#include "./UtilsCommon.h"

using namespace SimpleGF;

bool Input::getKeyDown(const Window& window, int key) {
    if (glfwGetKey(window.getGLFWwindow(), key) == GLFW_PRESS)
        return true;
    return false;
}

void Input::pollEvents() {
    glfwPollEvents();
}
