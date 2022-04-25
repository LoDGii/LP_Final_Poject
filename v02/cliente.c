//
// Created by Diogo Cardoso on 01/01/2022.
//

#include "principal.h"
#include "cliente.h"
#include "menu_admin.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "auxilio.h"
#include "ficheiros.h"
#include "windows.h"



int nmr_modelos;/*!< numero de modelos de calçado existentes*/
int index_clienteencontrado;/*!< index do cliente com o mesmo numero de cliente ao procurado*/
int exist_client;/*!< É igual a 1 se existir cliente*/
int nmr_clientes;/*!< Numero de Clientes Existentes*/
int nmr_formstaff;/*!< Numero de formulários preenchidos pela Staff*/
int index_clienteencontrado;/*!< Numero de formulários preenchidos pelos clientes*/
int nmr_encomendas;/*!< Numero de encomendas existentes*/


formulario_staff *staff;/*!< Armazenamento de formulários de staff*/
Cliente *lista;/*!< Armazenamento de lista de clientes*/
modelos *modelo;/*!< Armazenamento de lista de modelos de calçado*/
Calcado custos[3];/*!< Armazenamento de Tabela de Custos*/
form_cliente *cliente;/*!< Armazenamento de formulários preenchidos pelos clientes*/

int nmr_formclientes;/*!< Numero de formulários preenchidos pelos clientes*/



float preco_final = 0;/*!< Preço final a pagar pelo cliente */
int *quantidade;/*!< Vai armazenar as diferentes quantidades de pares de sapato pretendidas */
int *indice_calcadosver;/*!< Indice com todos os sapatos visiveis no menu*/
int *indicemodelos_escolhidos;/*!< Vai armazenar os indices dos modelos escolhidos pelo cliente*/
int tamanho_carrinho = 0;/*!< Indica o tamanho do carrinho de compras */
int *indice_tamanhos;/*!< Indice de tamanhos para os diferentes pares de calçado*/

int atualizar_vendas();


int menu_finalizar();

void listar_encomendas();


void cliente_inquerito();
void novo_cliente();
int cliente_registado();

void mostrar_carrinhocomprar();

void menu_compra();

void menu_calcado();

int clientecriar();


/**
 * Menu Cliente
 *
 * @param escolha consoante a escolha o cliente é levado para o menu de criação de conta ou para um onde é pedido o seu numero de cliente
 *
 *
 * dá a opção ao utilizador de criar uma conta cliente nova ou de "logar" com uma já existente
 *
 * @pre a variavel "escolha" tem que estar entre 0 e 2
 */
void menu_cliente(){
    int escolha;
    limpar_tela();
    do{
        printf("MENU DE CLIENTE\n");
        printf("____________________\n");
        printf("1 - Cliente Registrado\n2 - Novo Cliente\n0 - Menu Principal\n");
        printf("____________________\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
    }while(escolha < 0 || escolha > 2);
    switch(escolha){
        case 0:
            menu_principal();
        case 1:
            cliente_registado();
        case 2:
            novo_cliente();
    }
}

/**
 * Menu de Compra
 * @param escolha irá guardar a opção do cliente
 * @param tipo o seu valor irá variar entre "Sap", "San" e "Bot" consoante a escolha do utilizador tenha sido 1, 2 ou 3
 *
 *
 * Funciona no fundo como um hub, a partir daqui o cliente consegue aceder aos menus de compras e eliminar itens do carrinho
 *
 *
 * @pre a variavel "escolha" tem que estar entre 0 e 5
 */
void menu_compra(){
    int escolha;
    char *tipo;
    do{
        limpar_tela();
        printf("MENU DE COMPRA\n");
        printf("____________________\n");
        printf("1 - Sapatos\n2 - Sandalias\n3 - Botas\n4 - Remover produtos do carrinho\n5 - Finalizar Compra\n0 - Menu Principal\n");
        printf("____________________\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
    }while(escolha < 0 || escolha > 5);
    switch(escolha){
        case 0:
            menu_principal();
        case 1:
            tipo = strdup("Sap");
            menu_calcado(tipo);
        case 2:
            tipo = strdup("San");
            menu_calcado(tipo);
        case 3:
            tipo = strdup("Bot");
            menu_calcado(tipo);
        case 4:
            mostrar_carrinhocomprar();
        case 5:
            menu_finalizar();
    }
}


/**
 *Adicionar itens ao carrinho
 *
 * @param tipo é recebido atravês do menu de compra
 * @param escolha armazena a opção do utilizador
 * @param i vai ajudar a percorrer a base de dados dos modelos
 * @param d vai ajudar na atribuição da numeração do menu
 * @param indice_tamanhos vai armazenar o tamanho que o utilizador escolheu para cada par de calçado
 * @param quantidade vai armazenar a quantidade de pares que o utilizador escolheu para cada modelo
 *
 *
 * consoante o valor da variavel tipo irão aparecer no menu calçado do tipo botas, sandalias ou sapatos,
 * tal é possivel graças á função strcmp que compara a string tipo com o tipo de calçado de todos os modelos e
 * apresenta apenas aqueles que são iguais.
 *
 * @pre a variavel "escolha" tem que estar compreendida entre 0 e d-1
 */
void menu_calcado(char *tipo){
    int escolha,i, d = 1;
    do {
        limpar_tela();
        printf("MENU CALCADO\n");
        printf("____________________\n");
        for (i = 0; i < nmr_modelos; i++) {
            if (strcmp(tipo, modelo[i].tipo) == 0) {
                printf("%d - %s\n", d, modelo[i].nome);
                indice_calcadosver = (int *) realloc(indice_calcadosver, d * sizeof(int));
                indice_calcadosver[d - 1] = i;
                d++;
            }
        }
        printf("0 - Menu de Compra\n");
        printf("____________________\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
    }while(escolha< 0 || escolha > d - 1);
    switch(escolha){
        case 0:
            menu_compra();
        default:
            indicemodelos_escolhidos = (int *)realloc(indicemodelos_escolhidos, (tamanho_carrinho + 1) * sizeof(int));
            indicemodelos_escolhidos[tamanho_carrinho] = indice_calcadosver[escolha - 1];
            indice_tamanhos = (int *)realloc(indice_tamanhos, (tamanho_carrinho + 1) * sizeof(int));
            do{
                limpar_tela();
                printf("Tamanho: ");
                scanf("%d", &indice_tamanhos[tamanho_carrinho]);
            }while(indice_tamanhos[tamanho_carrinho] < modelo[indicemodelos_escolhidos[tamanho_carrinho]].tam_min || indice_tamanhos[tamanho_carrinho] > modelo[indicemodelos_escolhidos[tamanho_carrinho]].tam_max);
            quantidade = (int *)realloc(quantidade, (tamanho_carrinho + 1) * sizeof(int));
                limpar_tela();
                printf("Quantidade: ");
                scanf("%d", &quantidade[tamanho_carrinho]);
                tamanho_carrinho++;
                menu_compra();

    }
}
/**
 * Vizualizar e eliminar carrinho de compras
 *
 * @param i vai ajudar a percorrer todos os modelos no carrinho de compras
 * @param d vai ajudar na numeração do menu
 * @param escolha vai armazenar a escolha do utilizador
 * @param indicemodelos_escolhidos vai apresentar o indice de todos os modelos no carrinho de compras do cliente
 * @param quantidade vai apresentar o numero de pares que o cliente selecionou para cada par de calçado no seu carrinho
 *@param tamanho_carrinho apresenta o numero de produtos no carrinho
 *
 *
 */
void mostrar_carrinhocomprar(){
    int i, d = 1, escolha;
    do{
        limpar_tela();
        printf("CARRINHO DE COMPRAS\n");
        printf("____________________\n");
        for(i = 0;i < tamanho_carrinho;i++){
            printf("%d - %s QNTD: %d\n", d, modelo[indicemodelos_escolhidos[i]].nome, quantidade[i]);
            d++;
        }
        printf("0 - Menu de Compra\n");
        printf("____________________\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
    }while(escolha < 0 || escolha > d - 1);
    switch(escolha){
        case 0:
            menu_compra();
        default:
            indicemodelos_escolhidos[escolha - 1] = indicemodelos_escolhidos[tamanho_carrinho - 1];
            indice_tamanhos[escolha - 1] = indice_tamanhos[tamanho_carrinho - 1];
            quantidade[escolha - 1] = quantidade[tamanho_carrinho - 1];
            indicemodelos_escolhidos = (int *)realloc(indicemodelos_escolhidos, (tamanho_carrinho - 1) * sizeof(int));
            indice_tamanhos = (int *)realloc(indice_tamanhos, (tamanho_carrinho - 1) * sizeof(int));
            quantidade = (int *)realloc(quantidade, (tamanho_carrinho - 1) * sizeof(int));
            tamanho_carrinho--;

            menu_compra();
    }
}
/**Finalização de Compra
 *
 * @param i vai ajudar a percorrer todos os items do carrinho
 * @param t ajuda a identificar o tipo de sapato
 *  @param preco_final após o fim do ciclo for o mesmo será igual ao preço a pagar pelo cliente
 *  @param tamanho_carrinho numero de itens no carrinho
 *
 *  Cada vez que o ciclo for é realizado é verificadoo tipo de calçado e é atribuido um valor a t consoante
 *  Após a atribuição do valor é feita a soma do preço da peça ao preço final.
 */
int menu_finalizar(){
    int i, t;
    if(tamanho_carrinho == 0){
      menu_compra();
    }
    for(i = 0;i < tamanho_carrinho;i++){
        if(strcmp(modelo[indicemodelos_escolhidos[i]].tipo, "Sap") == 0){
            t = 0;
        }else if(strcmp(modelo[indicemodelos_escolhidos[i]].tipo, "San") == 0){
            t = 1;
        }else if(strcmp(modelo[indicemodelos_escolhidos[i]].tipo, "Bot") == 0){
            t = 2;
        }
        preco_final = preco_final + quantidade[i] * (((((2 *custos[t].obra) + custos[t].fixo + custos[t].margem_tamanho[-(34 - indice_tamanhos[i])]) * custos[t].margem) + ((2 *custos[t].obra) + custos[t].fixo + custos[t].margem_tamanho[-(34 - indice_tamanhos[i])])) + modelo[indicemodelos_escolhidos[i]].valor_adicional);
    }
    listar_encomendas();
    cliente_inquerito();
    atualizar_vendas();
    libertar_memoria();
    free(indicemodelos_escolhidos);
    free(indice_tamanhos);
    free(indice_calcadosver);
    menu_principal();
}

/**Guardar Encomenda
 *@brief adiciona a encomenda realizada á lista de encomendas
 *
 *
 *usando o fopen em modo "a+" o ponteiro irá ficar a apontar para o fim do ficheiro, dessa maneira é apenas necessário
 * imprimir as informações da nova encomenda.
 */
int guardar_encomenda(){
    FILE *fp;
    SYSTEMTIME t;
    GetLocalTime(&t);
    fp = fopen("lista_encomendas.csv", "a+");
    fprintf(fp, "%d;%d;%d;%d;%f;%s\n", lista[index_clienteencontrado].codigo_cliente, t.wDay, t.wMonth, t.wYear,preco_final, lista[index_clienteencontrado].pais);
    fclose(fp);
}
/**Recibo de Cliente
 *@brief gera um txt chamado recibo com informações da compra
 *
 *
 * A criação do recibo é feita atravês de varios fprintf's, no recibo é apresentado o numero de cliente, NIF,
 * País de envio, produtos vendidos e quantidade dos mesmos e o preço final.
 */
int gerar_recibo(){
    FILE *fp;
    int i;
    fp = fopen("recibo.txt", "w");
    fprintf(fp, "LOJA DO COLAS!\n");
    fprintf(fp, "________________________________________\n");
    fprintf(fp, "Numero de Cliente: %d            NIF: %d\n", lista[index_clienteencontrado].codigo_cliente, lista[index_clienteencontrado].nif);
    fprintf(fp, "Pais de envio: %s\n", lista[index_clienteencontrado].pais);
    fprintf(fp,"________________________________________\n");
    for(i = 0;i < tamanho_carrinho;i++){
        fprintf(fp, "%d - %s - QNTD: %d\n", modelo[indicemodelos_escolhidos[i]].codigo, modelo[indicemodelos_escolhidos[i]].nome, quantidade[i]);
    }
    fprintf(fp, "________________________________________\n");
    fprintf(fp,"Preco Final: %.2f €\n", preco_final);
    fprintf(fp,"_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
    fprintf(fp,"OBRIGADO POR COMPRAR CONNOSCO!\n");
    fclose(fp);

}
/**Listar Encomendas
 * @brief junção de duas funções
 */
void listar_encomendas(){
   // guardar_encomenda();
    gerar_recibo();
}
/**
 *
 * Atualizar numero de vendas
 *
 * Atravês da variavel do tipo inteiro indicemodelos_escolhidos e quantidade consigo somar o numero de vendas do
 * modelo com as que o cliente acabou de comprar
 */
int atualizar_vendas(){
    int i;
    for(i = 0;i < tamanho_carrinho;i++){
        modelo[indicemodelos_escolhidos[i]].vendas += quantidade[i];
    }
}

/**
 * Cliente Registado

 *Aqui vai ser perguntado ao utilizador qual o seu numero de cliente e caso o mesmo não exista o utilizador
 *  é redirecionado para trás
 */
int cliente_registado(){
    existe_cliente();
    if(exist_client != 1){
        menu_cliente();
    }else if(strcmp(lista[index_clienteencontrado].removido, "nao") == 0){
        menu_compra();
    }else if(strcmp(lista[index_clienteencontrado].removido, "nao") != 0){
        menu_cliente();
    }
}
/**
 * Inquerito ao Cliente
 *
 * Irão ser feitas diversas perguntas ao cliente de forma a onter dados para o relatório de satisfação de clientes
 */
void cliente_inquerito(){
    int escolha;
    do {
        limpar_tela();
        printf("Deseja Responder a um Inquerito?\n");
        printf("____________________\n");
        printf("1 - SIM\n2 - NAO\n");
        printf("____________________\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
    }while(escolha < 1 || escolha > 2);
    switch(escolha){
        case 1:
            limpar_tela();
            printf("Ira agora responder a um questionario anonimo");
            cliente = (form_cliente *)realloc(cliente, (nmr_formclientes + 1) * sizeof(form_cliente));
            delay(10);
            do {
                limpar_tela();
                printf("Como classifica a variedade de produtos (0-20): ");
                scanf("%d", &cliente[nmr_formclientes].um);
            }while(cliente[nmr_formclientes].um < 0 || cliente[nmr_formclientes].um > 20);
            do{
                limpar_tela();
                printf("Como classifica o atendimento prestado (0-20): ");
                scanf("%d", &cliente[nmr_formclientes].dois);
            }while(cliente[nmr_formclientes].dois < 0 || cliente[nmr_formclientes].dois > 20);
            do{
                limpar_tela();
                printf("Como classifica a empresa em geral (0-20): ");
                scanf("%d", &cliente[nmr_formclientes].tres);
            }while(cliente[nmr_formclientes].tres < 0 || cliente[nmr_formclientes].tres > 20);
            nmr_formclientes++;
            guardar_formclientes();
            break;
        case 2:
            break;
    }
}



/**
 * Menu para novos clientes
 */
void novo_cliente(){
    limpar_tela();
    printf("Ficha de Cliente\n");
    printf("____________________\n");
    clientecriar();
    index_clienteencontrado = nmr_clientes - 1;
}

/**Criar Cliente
 * @brief criar conta de cliente
 * Caso o utilizador não tenha uma conta de cliente é redirecionado para cá onde pode criar uma
 */
int clientecriar(){
    int i;
    limpar_tela();

    lista = (Cliente *)realloc(lista, (nmr_clientes + 1) * sizeof(Cliente));

    printf("Nome: ");
    lista[nmr_clientes].nome = (char *)malloc(841 * sizeof(char));
    scanf("%s", lista[nmr_clientes].nome);
    lista[nmr_clientes].nome = (char *)realloc(lista[nmr_clientes].nome,(1 + strlen(lista[nmr_clientes].nome)) * sizeof(char));
    do {
        limpar_tela();
        printf("NIF: ");
        scanf("%d", &lista[nmr_clientes].nif);
    }while(lista[nmr_clientes].nif < 100000000 || lista[nmr_clientes].nif >= 1000000000);
    lista[nmr_clientes].pais = (char *)malloc(841 * sizeof(char));
    printf("País: ");
    scanf("%s", lista[nmr_clientes].pais);
    lista[nmr_clientes].pais = (char *)realloc(lista[nmr_clientes].pais,(strlen(lista[nmr_clientes].pais) + 1) * sizeof(char));
    strcpy(lista[nmr_clientes].removido, "nao");
    do {
        limpar_tela();
        exist_client = 0;
        printf("Numero de cliente: ");
        scanf("%d", &lista[nmr_clientes].codigo_cliente);
        for(i = 0;i < nmr_clientes;i++){
            if(lista[i].codigo_cliente == lista[nmr_clientes].codigo_cliente){
                exist_client = 1;
            }
        }
    }while(exist_client == 1);
    nmr_clientes++;
    menu_cliente();
}
