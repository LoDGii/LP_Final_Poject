//
// Created by Diogo Cardoso on 30/12/2021.
//

#include "auxilio.h"
#include "menu_admin.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include <time.h>


int exist_model;/*!< Caso exista cliente o seu valor é 1, caso não exista é 0*/
int index_modelencontrado;/*!< Armazena o index do modelo com o numero igual ao pretendido*/
int index_clienteencontrado;/*!< Armazena o index do cliente com o numero igual ao pretendido */

/**
 * Esta Função vai apagar tudo o que se encontrar na tela do utilizador
 */
void limpar_tela(){
    system("cls");
}

/**
 * Verificação de Modelo
 *
 * @param numero numero do modelo que o utilizador deseja procurar
 * @param i vai ajudar a percorrer toda a base de dados dos modelos
 * @param exist_model caso exista modelo a variavel toma como valor o numero 1
 * @param index_modeloencontrado vai armazenar o indice do modelo encontrado
 */
int existe_modelo(){
    int i,numero;
    exist_model = 0;
    printf("Numero de Modelo: ");
    scanf("%d", &numero);
    for(i = 0;i < nmr_modelos;i++){
        if(numero == modelo[i].codigo){
            exist_model = 1;
            index_modelencontrado = i;
        }
    }
}


/**
 * Verificação de Cliente
 *
 * @param numero numero de cliente que o utilizador deseja procurar
 * @param i vai ajudar a percorrer toda a base de dados dos clientes
 * @param exist_client caso exista cliente a variavel toma como valor o numero 1
 * @param index_clienteencontrado vai armazenar o indice do cliente encontrado
 */
int existe_cliente(){
    int i, numero;
    exist_client = 0;
    printf("Numero de Cliente: ");
    scanf("%d", &numero);
    for(i = 0;i < nmr_clientes;i++){
        if(lista[i].codigo_cliente == numero){
            exist_client = 1;
            index_clienteencontrado = i;
        }
    }
    if(exist_client != 1){
        return 1;
    }
}
/**
 * Libertação de Memoria

 * Fazendo uso da função free é posssivel libertar toda a memória dinamica alocada
 */
void libertar_memoria(){
    int i;
    for(i = 0;i < nmr_clientes;i++){
        free(lista[i].pais);
        free(lista[i].nome);
    }
    for(i = 0;i < nmr_encomendas;i++){
        free(encomendas[i].pais);
    }
    for(i = 0;i < nmr_modelos;i++){
        free(modelo[i].nome);
    }
    free(encomendas);
    free(lista);
    free(modelo);
    free(staff);
    free(cliente);
}


/**
 * Paragem de Tempo
 * @param number_of_seconds numero de segundos definidos para esperar
 * @param milli_seconds o numero de segundos é convertido para milissegundos e é passado para este parametro
 */
void delay(int number_of_seconds){
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}
