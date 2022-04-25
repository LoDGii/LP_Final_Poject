#include <stdio.h>
#include "structs.h"
#include "menu_admin.h"
#include <locale.h>
#include "cliente.h"
#include "principal.h"
#include "ficheiros.h"
#include "auxilio.h"



int main() {
    setlocale(LC_ALL, "");
    menu_principal();
    delay(10);
    return 0;
}
