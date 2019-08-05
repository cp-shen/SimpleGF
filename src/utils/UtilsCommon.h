#ifndef UTILS_COMMON_H
#define UTILS_COMMON_H

#include <GLFW/glfw3.h>

#include "../graphics/GraphicsCommon.h"

namespace SimpleGF {

class Window {
    public:
        Window(int wWidth, int wHeight, const char* title);
        virtual ~Window();

        GLFWwindow* getGLFWwindow() const;
        void swapBuffers() const;
        bool shouldClose() const;
    private:
        // disable copying
        Window(const Window& other) = default;
        Window& operator=(const Window& other) = default;

        void _init(int wWidth, int wHeight, const char* title);
        void _printGLInfo();

        GLFWwindow* _glfwWindow;
};

class Input {
    public:
        virtual ~Input();
        static bool getKeyDown(const Window& window, int key);
        static void pollEvents();

    private:
        Input();
};

} // namespace

#endif /* UTILS_COMMON_H */

