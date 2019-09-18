#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h> // should be included after including glew

namespace SimpleGF {

class Window {
    friend class Application; // constructor
    friend class Input; // _glfwWindow

    public:
        virtual ~Window();

        void swapBuffers() const;
        bool shouldClose() const;
        unsigned width() const;
        unsigned height() const;
    private:
        Window(int wWidth, int wHeight, const char* title);

        // disable copying
        Window(const Window& other) = default;
        Window& operator=(const Window& other) = default;

        void _init(int wWidth, int wHeight, const char* title);
        void _printGLInfo();

        GLFWwindow* _glfwWindow;
};

}

#endif /* WINDOW_H */
