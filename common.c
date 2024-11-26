#include "stdio.h"
#include "stdarg.h"


//fake any
typedef void* anyptr;


typedef enum CursorMode{
    Block = 1,
    SteadyBlock = 2,
    Underline = 3,
    SteadyUnderline = 4,
    IBeam,
    SteadyIBeam
} CursorMode;

void setCursor(CursorMode mode){
    printf("\e[%d q", mode);
}