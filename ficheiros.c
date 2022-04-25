//
// Created by Diogo Cardoso on 03/01/2022.
//

#include "ficheiros.h"
#include "cliente.h"
#include "menu_admin.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "auxilio.h"
#include <windows.h>


FILE *fp;/*!< Variavel do tipo FILE necessária para  a manipulação de ficheiros */

Cliente *lista;/*!< Estrutura para armazenar os clientes */
modelos *modelo;/*!< Estrutura para armazenar os modelos de calçado*/
Calcado custos[3];/*!< Estrutura para armazenar a tabela de custos*/

float preco_final;
int index_clienteencontrado;
int *quantidade;
int *indice_calcadosver;
int *indicemodelos_escolhidos;
int tamanho_carrinho;
int *indice_tamanhos;
int nmr_clientes;
int nmr_modelos;/*!< Numero de modelos de sapatos existentes */


/**
 * @file ficheiros.c
 //! Para ler os valores contidos nos ficheiros primeiro temos que criar um apontador do tipo FILE
 //! Usamos a função fgets para obter a primeira linha porque essa não interessa
 //! Depois usamos um ciclo while que faz o programa ler linha a linha o ficheiro
 //! depois usamos o strtok para partir a linha com o delimitador (que no csv é ";")
 //! a informação vem em formato string por defeito por isso é necessario usar funções como atof e atoi para transformar em float e inteiro respetivamente
*
 */




/**Ler Encomendas
 *
 * @param lerCodeUser é onde vai ser armazenada a linha do ficheiro que estamos a ler
 * @param encomendas é a struct que armazena a lista de encomendas
 * @param nmr_encomendas apresenta o numero total de encomendas
 */
int ler_encomendas(){
    int i = 0, t;
    fp = fopen("lista_encomendas.csv", "r");
    char lerCodeUser[15000];
    char *tok;
    fgets (lerCodeUser, 15000, fp);
    while(fgets (lerCodeUser, 15000, fp)!= NULL){
        encomendas = (encomenda *)realloc(encomendas, (i + 1) * sizeof(encomenda));
        tok = strtok(lerCodeUser, ";");
        encomendas[i].codigo_cliente = atoi(tok);
        tok = strtok(NULL, ";");
        encomendas[i].dia = atoi(tok);
        tok = strtok(NULL, ";");
        encomendas[i].mes = atoi(tok);
        tok = strtok(NULL, ";");
        encomendas[i].ano = atoi(tok);
        tok = strtok(NULL, ";");
        encomendas[i].preco_final = atof(tok);
        tok = strtok(NULL, ";");
        encomendas[i].pais = strdup(tok);
        i++;
    }
    nmr_encomendas = i;
    fclose(fp);
}

/**Ler Tabela de Custos
 *@brief leitura dos valores da tabela de custos
 *
 */
int ler_tabelacustos(){
    int i = 0, t;
    fp = fopen("tabela_custos.csv", "r");
    char lerCodeUser[15000];
    char *tok;
    fgets (lerCodeUser, 15000, fp);
    while(fgets (lerCodeUser, 15000, fp)!= NULL){
        tok = strtok(lerCodeUser, ";");
        tok = strtok(NULL, ";");
        custos[i].obra = atoi(tok);
        tok = strtok(NULL, ";");
        custos[i].fixo = atoi(tok);
        for(t = 0;t < 15; t++){
            tok = strtok(NULL, ";");
            custos[i].margem_tamanho[t] = atoi(tok);
        }
        tok = strtok(NULL, ";");
        custos[i].margem = atoi(tok);
        i++;
    }
    fclose(fp);
}
/**Ler Lista de Modelos
 *@brief leitura da lista de modelos de calçado
 *
 *
 * @param nmr_modelos guarda o numero total de modelos
 */
int ler_modelos(){
    int i = 0;
    fp = fopen("lista_modelos.csv", "r");
    char lerCodeUser[15000];
    char *tok;
    fgets (lerCodeUser, 15000, fp);
    while(fgets (lerCodeUser, 15000, fp)!= NULL){
       modelo = (modelos *)realloc(modelo, (i + 1) * sizeof(modelos));
        tok = strtok(lerCodeUser, ";");
        modelo[i].nome = strdup(tok);
        tok = strtok(NULL, ";");
        modelo[i].tam_min = atoi(tok);
        tok = strtok(NULL, ";");
        modelo[i].tam_max = atoi(tok);
        tok = strtok(NULL, ";");
        modelo[i].codigo = atoi(tok);
        tok = strtok(NULL, ";");
        modelo[i].valor_adicional = atof(tok);
        tok = strtok(NULL, ";");
        if(strcmp(tok, "Sap") == 0){
            strcpy(modelo[i].tipo, "Sap");
        }else if(strcmp(tok, "San") == 0){
            strcpy(modelo[i].tipo, "San");
        }else if(strcmp(tok, "Bot") == 0){
            strcpy(modelo[i].tipo, "Bot");
        }

        tok = strtok(NULL, ";");
        modelo[i].vendas = atoi(tok);
        i++;
    }
    nmr_modelos = i;
    fclose(fp);
}
/**Ler Formulários de Clientes
 * @brief Leitura dos formulários dos clientes
 *
 * @var nmr_formclientes
 *
 * representa o numero de formulários preenchidos por clientes
 */
int ler_formcliente(){
    int i = 0;
    fp = fopen("lista_formclientes.csv", "r");
    char lerCodeUser[15000];
    char *tok;
    fgets (lerCodeUser, 15000, fp);
    while(fgets (lerCodeUser, 15000, fp)!= NULL){
        cliente = (form_cliente *)realloc(cliente, (i + 1) * sizeof(form_cliente));
        tok = strtok(lerCodeUser, ";");
        cliente[i].um = atoi(tok);
        tok = strtok(lerCodeUser, ";");
        cliente[i].dois = atoi(tok);
        tok = strtok(lerCodeUser, ";");
        cliente[i].tres = atoi(tok);
        i++;
    }
    nmr_formclientes = i;
    fclose(fp);
}
/**Ler Formulário de Staff
 * @brief Guarda todos os formulários de staff preenchidos
 *
 *@var nmr_formstaff
 * indica o numero de formulários de staff preenchidos
 */
int ler_formstaff(){
    int i = 0;
    fp = fopen("lista_formstaff.csv", "r");
    char lerCodeUser[15000];
    char *tok;
    fgets (lerCodeUser, 15000, fp);
    while(fgets (lerCodeUser, 15000, fp)!= NULL){
        staff = (formulario_staff *)realloc(staff, (i + 1) * sizeof(formulario_staff));
        tok = strtok(lerCodeUser, ";");
        staff[i].um = atoi(tok);
        tok = strtok(NULL, ";");
        staff[i].dois = atoi(tok);
        tok = strtok(NULL, ";");
        staff[i].tres = atoi(tok);
        tok = strtok(NULL, ";");
        staff[i].quatro = atoi(tok);
        i++;
    }
    nmr_formstaff = i;
    fclose(fp);
}
/**Ler Lista de Clientes
 * @brief Leitura da lista dos clientes
 *
 * @var nmr_clientes
 *
 * O valor nmr_clientes indica quantos clientes tem a loja, este valor é muito util para a recolha e ordenamento de informação
 *
 */
int ler_clientes(){
    int i = 0;
    fp = fopen("lista_clientes.csv", "r");
    char lerCodeUser[15000];
    char *tok;
    fgets (lerCodeUser, 15000, fp);
    while(fgets (lerCodeUser, 15000, fp)!= NULL){
        lista = (Cliente *)realloc(lista ,(i + 1) * sizeof(Cliente));
        tok = strtok(lerCodeUser, ";");
        lista[i].nome = strdup(tok);
        tok = strtok(NULL, ";");
        lista[i].pais = strdup(tok);
        tok = strtok(NULL, ";");
        if(strcmp(tok, "nao") == 0){
            strcpy(lista[i].removido, "nao");
        }else{
            strcpy(lista[i].removido, "sim");
        }
        tok = strtok(NULL, ";");
        lista[i].codigo_cliente = atoi(tok);
        tok = strtok(NULL, ";");
        lista[i].nif = atoi(tok);
        i++;
    }
    nmr_clientes = i;
    fclose(fp);
}


/**Guardar Clientes
 * @brief Guardar a lista toda de clientes
 *
 */
int guardar_clientes(){
    int i;
    fp = fopen("lista_clientes.csv", "w");
    fprintf(fp,"Nome;Pais;Removido;Codigo;NIF\n");
    for(i = 0;i < nmr_clientes;i++){
        fprintf(fp,"%s;%s;%s;%d;%d\n", lista[i].nome, lista[i].pais, lista[i].removido, lista[i].codigo_cliente, lista[i].nif);
    }
    fclose(fp);
}

/**Guarda Tabela de Custos
 * @brief Guardar todos os valores alterados pelo admin relativamente á tabela de custos
 */
void guardar_tabela(){
    int i,t;
    fp = fopen("tabela_custos.csv", "w");
    fprintf(fp,";Mao Obra (peça);Custos Fixos(par);34;35;36;37;38;39;40;41;42;43;44;45;46;47;48;Margem\n");
    for(i = 0;i < 3; i++) {
        if(i == 0){
            fprintf(fp, "Sapatos;");
        }else if(i == 1){
            fprintf(fp, "Sandalias;");
        }else if(i == 2){
            fprintf(fp, "Botas;");
        }
        fprintf(fp, "%f;%f;", custos[i].obra, custos[i].fixo);
        for (t = 0; t < 15; t++) {
           fprintf(fp, "%f;", custos[i].margem_tamanho[t]);
        }
        fprintf(fp, "%f\n", custos[i].margem);
    }
    fclose(fp);
}


/**Guardar Lista de Modelos
 * @brief Armazena os valores dos artigos
 *
 * São percorridos todos os modelos e guardados atravês do fprintf
 */
void guardar_modelos(){
    int i;
    fp = fopen("lista_modelos.csv", "w");
    fprintf(fp, "Nome;Minimo;Maximo;Codigo;Adicional;Tipo;Vendas\n");
    for(i = 0;i < nmr_modelos;i++){
        fprintf(fp, "%s;%d;%d;%d;%f;%s;%d\n", modelo[i].nome, modelo[i].tam_min, modelo[i].tam_max, modelo[i].codigo, modelo[i].valor_adicional, modelo[i].tipo, modelo[i].vendas);
    }
    fclose(fp);
}
/**Guarda Formularios Staff
 * @brief Guarda todos os formularios de staff
 *
 *
 *
 */
void guardar_formstaff(){
    int i;
    fp = fopen("lista_formstaff.csv", "w");
    fprintf(fp, "Um;Dois;Tres;Quatro\n");
    for(i = 0; i < nmr_formstaff;i++){
        fprintf(fp, "%d;%d;%d;%d\n", staff[i].um, staff[i].dois, staff[i].tres, staff[i].quatro);
    }
    fclose(fp);
}
/**Formulários de Clientes
 * @brief Guarda todos os formulários de clientes
 *
 */
void guardar_formclientes(){
    int i;
    fp = fopen("lista_formclientes.csv", "w");
    fprintf(fp, "Um;Dois;Tres\n");
    for(i = 0;i < nmr_formclientes;i++){
        fprintf(fp, "%d;%d;%d\n", cliente[i].um, cliente[i].dois, cliente[i].tres);
    }
    fclose(fp);
}