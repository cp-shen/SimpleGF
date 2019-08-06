#ifndef UTILS_COMMON_H
#define UTILS_COMMON_H

#include <GLFW/glfw3.h> // should be included after including glew
#include <memory> // shared_ptr

namespace SimpleGF {

class Window {
    friend class Application;

    public:
        virtual ~Window();

        void swapBuffers() const;
        bool shouldClose() const;
    private:
        Window(int wWidth, int wHeight, const char* title);

        // disable copying
        Window(const Window& other) = default;
        Window& operator=(const Window& other) = default;

        void _init(int wWidth, int wHeight, const char* title);
        void _printGLInfo();

        GLFWwindow* _glfwWindow;
};

class Application {
    public:
        virtual ~Application();
        static void init(int wWidth, int wHeight, const char* title);
        static void terminate();
        static std::shared_ptr<Window> getWindow();
    private:
        Application();
        static std::shared_ptr<Window> _window;

        // disable copying
        Application(const Application& other) = default;
        Application& operator=(const Application& other) = default;
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

