#include "game.h"
#include <time.h>
Game Gra("Space war");
int main() {
    srand(time(NULL));
    Gra.run();
    return 0;
}
