#include "Gammatron.h"
#include <cstring>

int main(int argc, char *argv[]) {
    Gammatron b;
    b.read_program();
    b.run_program();
    return 0;
}
