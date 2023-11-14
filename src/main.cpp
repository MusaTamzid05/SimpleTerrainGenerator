#include "window.h"
#include <cstdlib>
#include <ctime>


int main(int argc, char** argv) {
    srand(time(nullptr));
    Window window;
    window.run();
    return 0;
}
