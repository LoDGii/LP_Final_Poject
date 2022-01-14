//
// Created by Diogo Cardoso on 04/01/2022.
//

#include "principal.h"
#include "menu_admin.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "auxilio.h"
#include <locale.h>
#include "cliente.h"
#include "ficheiros.h"
/**
 * @file principal.c
 *
 * Este ficheiro é o que junta todos os outros num só programa
 *
 */


/**Menu Principal
 * @brief Junção de todas as funções em um só programa
 *
 *
 *  Há aqui uma interligação entre todas as funções que nos permitem fornecer um programa funcional
 */
int menu_principal(){
    int escolha;
    do {
        limpar_tela();
        printf("MENU PRINCIPAL\n");
        printf("____________________\n");
        printf("1 - MENU DE ADMIN\n2 - MENU DE CLIENTE\n3 - LER FICHEIROS\n4 - GUARDAR FICHEIROS\n0 - SAIR\n");
        printf("____________________\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
    }while(escolha < 0 || escolha > 4);
    switch(escolha){
        case 1:
            menu_admin();
        case 2:
            menu_cliente();
        case 3:
            ler_tabelacustos();
            ler_clientes();
            ler_formstaff();
            ler_formcliente();
            ler_encomendas();
            ler_modelos();
            printf("FICHEIROS LIDOS COM SUCESSO!");
            delay(2);
            menu_principal();
        case 4:
            guardar_tabela();
            guardar_clientes();
            guardar_modelos();
            guardar_formstaff();
            guardar_formclientes();
            guardar_encomenda();
            printf("FICHEIROS GUARDADOS COM SUCESSO!");
            delay(2);
            menu_principal();
        case 0:
            libertar_memoria();
            return (EXIT_SUCCESS);
    }
}