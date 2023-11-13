#include "window.h"
#include "linear_interpolator.h"
#include <iostream>


int main(int argc, char** argv) {
    LinearInterpolator interpolator(0.0f, 50.0f, -1.0f, 1.0f);

    for(int i = 0; i <= 50; i += 1) {
        std::cout << i << " => " << interpolator.map(i) << "\n";

    }
    //Window window;
    //window.run();
    return 0;
}
