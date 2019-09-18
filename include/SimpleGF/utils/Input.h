#ifndef INPUT_H
#define INPUT_H

#include "./Window.h"

namespace SimpleGF {

class Input {
public:
    virtual ~Input();
    static bool getKeyDown(const Window& window, int key);
    static void pollEvents();

private:
    Input();
};

} // namespace SimpleGF

#endif /* INPUT_H */
