#include "free.h"
/* free all list*/
void freeALL() {

        free_code();

        free_label();

        freeAsSymbol();

        freeData();

}
