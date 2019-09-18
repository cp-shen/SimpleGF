#ifndef APPLICATION_H
#define APPLICATION_H

#include "./Window.h"
#include <memory>

namespace SimpleGF {

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

} // namespace SimpleGF

#endif /* APPLICATION_H */
