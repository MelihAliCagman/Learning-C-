#include "cihazlar.h"

#include <iostream>

namespace sensor {
void yaz() { std::cout << "  sensor::yaz() calisti\n"; }
}

namespace motor {
void yaz() { std::cout << "  motor::yaz() calisti, kare(4) = " << telemetri::kare(4) << "\n"; }
}
