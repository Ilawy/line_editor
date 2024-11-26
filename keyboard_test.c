#include "conio.h"
#include "keyboard.c"
#include "stdio.h"


int main(){
    while(1){
        printf("%d\n", captureKeyboardInput());
    }
    
    return 0;
}