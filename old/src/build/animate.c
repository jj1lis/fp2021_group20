#include "../img.h"
#include "../util.h"
#include "../background.h"
#include "../firework.h"


int main(void){
    for(int time = 0; time < 100; time++){
        img_clear();
        background(time);
        firework(time);
        img_write();
    }

    return 0;
}
