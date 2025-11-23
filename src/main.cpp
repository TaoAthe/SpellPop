#include "engine/Core.h"

int main() {
    Core engine;
    if (engine.Initialize()) {
        engine.Run();
    }
    return 0;
}
