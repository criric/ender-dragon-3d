#include <iostream>
#include "sculptor.hpp"
using namespace std;

int main()
{
    Sculptor enderDragon(150,150,150);
    enderDragon.setColor(0.01, 0.01, 0.01, 1.0);

    //Cabeça
    enderDragon.putBox(59, 89, 59, 89, 59, 89);

    //Focinho
    enderDragon.putBox(89, 109, 61, 76, 63, 85);
    enderDragon.cutBox(89,109, 70,71, 59, 89);
    enderDragon.cutBox(89,107, 69,70, 64, 84);
    enderDragon.cutBox(89,107, 71,72, 64, 84);

    enderDragon.setColor(169.1, 169.1, 169.1, 1.0);
    enderDragon.putBox(101, 107, 76, 79, 66, 69);
    enderDragon.putBox(101, 107, 76, 79, 79, 82);

    //Olhos
    enderDragon.setColor(128.1, 0.01, 128.1, 1.0);
    enderDragon.putBox(89, 90, 81, 84, 78, 82);
    enderDragon.putVoxel(89, 81, 77);

    enderDragon.putBox(89, 90, 81, 84, 66, 70);
    enderDragon.putVoxel(89, 81, 70);

    //Chifres
    enderDragon.setColor(128.1, 128.1, 128.1, 1.0);
    enderDragon.putBox(67, 81, 89, 94, 64, 67);

    enderDragon.putBox(67, 81, 89, 94, 81, 84);

    //Fogo
    enderDragon.setColor(128.1, 0.01, 128.1, 1.0);
    for(int i = 0; i < 200; i++){
        int x = rand() % 150;
        int y = rand() % 150;
        int z = rand() % 150;
        enderDragon.putVoxel(x, y, z);
    }

    //Trófeu
//    enderDragon.setColor(244.1, 169.01, 0.1, 1.0);
//    enderDragon.putBox(57, 58, 54, 95, 54, 95);
//    enderDragon.cutVoxel(57, 92, 74);

    enderDragon.writeOFF("deathStar.off");


    return 0;
}
