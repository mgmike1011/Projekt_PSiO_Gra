#include "game.h"
#include <time.h>
Game Gra;
int main() {
    srand(time(NULL));
    Gra.run();
    return 0;
}
