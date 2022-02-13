#include "img.h"
#include "firework.h"
#include "background.h"

int main(void){
    int i;
    for(i = 1; i <= 100; ++i){
        img_clear();
        background(i);
        firework(i);
        img_write();
    }
    return 0;
}
