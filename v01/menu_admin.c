//
// Created by Diogo Cardoso on 30/12/2021.
//

#include "menu_admin.h"
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "auxilio.h"
#include <locale.h>
#include "principal.h"
#include "ficheiros.h"


int nmr_modelos;/*!< Numero de modelos de calçado existentes*/
int index_clienteencontrado;/*!< Index do cliente com o mesmo numero do procurado */

int exist_client;/*!< Caso seja 1 é porque encontrou um numero de cliente igual */

int nmr_clientes;/*!< Numero de clientes existentes*/
int nmr_formstaff;/*!< Numero de Formulários preenchidos pela staff*/
int nmr_formclientes;/*!< Numero de Formulários preenchidos pelos clientes*/

form_cliente *cliente;/*!< Estrutura usada para armazenar os formulários dos clientes */
formulario_staff *staff;/*!< Estrutura usada para armazenar os formulários do staff */
Cliente *lista;/*!< Armazenamento de lista de clientes*/
modelos *modelo;/*!< Armazenamento de todos os modelos  de calçado*/
Calcado custos[3];/*!< Armazenamento da tabela de custos*/



/*
 * Menu de Gestão de cliente
 */
int gestao_clientecriar();
int gestao_clienteeditar();
void gestao_clienteremover();
void gestao_clientemostrar();
/*
 * Menu de Gestão de Artigos
 */
int gestao_artigoscriar();
void gestao_artigoseditar();
void gestao_artigosremover();
void mostrar_modelos();
/*
 * Menu de Relatórios
 */
void relatorio_encomendas();
void relatorio_cliente();
void relatorio_geoloc();
void relatorio_vendas();
void relatorio_staff();

/**Inquerito ao Staff
 * @brief Questionário para avaliar o contentamento do staff
 *
 *Este inquerito pretende ficar a conhecer um pouco mais a empresa em si,faz perguntas sobre o ambiente de trabalho
 * e formas de melhorar os indices de confiança e contentamento
 */
void menu_inquerito(){
    staff = (formulario_staff *)realloc(staff,(nmr_formstaff + 1) * sizeof(formulario_staff));
    printf("Ira agora responder a um questionario de forma anonima");
    delay(5);
    do {
        limpar_tela();
        printf("Como classifica o Ambiente no seu local de trabalho (0-20): ");
        scanf("%d", &staff[nmr_formstaff].um);
    }while(staff[nmr_formstaff].um < 0 || staff[nmr_formstaff].um > 20);
    do {
        limpar_tela();
        printf("Como Classifica o seu horário de trabalho (0-20): ");
        scanf("%d", &staff[nmr_formstaff].dois);
    }while(staff[nmr_formstaff].dois < 0 || staff[nmr_formstaff].dois > 20);
    do {
        limpar_tela();
        printf("SE PUDESSE QUAL DAS SEGUINTES OPÇÕES ESCOLHERIA\n");
        printf("1 - Melhoria Salarial\n2 - Melhoria do Horário de Trabalho\n3 - Atividades recreativas extra-trabalho\n");
        printf("Escolha: ");
        scanf("%d", &staff[nmr_formstaff].tres);
    }while(staff[nmr_formstaff].tres < 1 || staff[nmr_formstaff].tres > 3);
    do {
        limpar_tela();
        printf("Classificação geral da empresa (0-20): ");
        scanf("%d", &staff[nmr_formstaff].quatro);
    }while(staff[nmr_formstaff].quatro < 0 || staff[nmr_formstaff].quatro > 20);
    nmr_formstaff++;
    menu_admin();
}

/**Menu Relatórios
 * @brief cinco relatórios diferentes que tencionam ajudar no desenvolvimento
 *
 * Estes 5 relatórios têm como objetivo dar a conhecer um pouco melhor a realidade da empresa.
 *
 */
void menu_relatorios(){
    int escolha;
    do {
        limpar_tela();
        printf("MENU DE RELATORIOS\n");
        printf("____________________\n");
        printf("1 - Relatorio Geolocalizacao\n2 - Relatorio de Vendas\n3 - Relatorio de Satisfacao de Staff\n4 - Relatorio de Satisfacao de Cliente\n5 - Relatorio de Encomendas\n0 - Menu Admin\n");
        printf("____________________\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
    }while(escolha < 0 || escolha > 6);
    switch(escolha){
        case 1:
            relatorio_geoloc();
            break;
        case 2:
            relatorio_vendas();
            break;
        case 3:
            relatorio_staff();
        case 4:
            relatorio_cliente();
        case 5:
            relatorio_encomendas();
    }
}

/**Relatorio de encomendas
 * @brief situação das encomendas
 *
 * Permite ao utilizador escolher duas datas á sua escolha e ver que encomendas existem entre essas duas datas
 */
void relatorio_encomendas(){
    int dia_min,mes_min,ano_min;
    int dia_max,mes_max,ano_max;
    int i;
        limpar_tela();
        printf("RELATORIO DE ENCOMENDAS\n");
        printf("____________________\n");
        printf("Insira a data minima da encomenda\n");
        printf("Dia: ");
        scanf("%d", &dia_min);
        printf("Mes: ");
        scanf("%d", &mes_min);
        printf("Ano: ");
        scanf("%d", &ano_min);
        limpar_tela();
        printf("Insira a data maxima da encomenda (dd/mm/yy)\n");
    printf("Dia: ");
    scanf("%d", &dia_max);
    printf("Mes: ");
    scanf("%d", &mes_max);
    printf("Ano: ");
    scanf("%d", &ano_max);
        limpar_tela();
        printf("LISTA DE ENCOMENDAS\n");
        printf("____________________\n");
        for(i = 0;i < nmr_encomendas;i++){
            if(encomendas[i].dia >= dia_min && encomendas[i].dia <= dia_max && encomendas[i].mes >= mes_min && encomendas[i].mes <= mes_max && encomendas[i].ano >= ano_min && encomendas[i].ano <= ano_max){
                printf("Numero de Cliente: %d Pais de Entrega: %s Preco Final: %.2f \n", encomendas[i].codigo_cliente, encomendas[i].pais, encomendas[i].preco_final);
            }
        }
        printf("____________________\n");
        delay(10);

        menu_admin();


}
/**Gestão da Tabela de Custos
 * @brief aqui o admin poderá alterar todos os valores da tabela
 *
 *
 */
void gestao_tabelacusto(){
    int mudanca,escolha, i;
    do {
        limpar_tela();
        printf("GESTAO DE TABELA DE CUSTOS\n");
        printf("____________________\n");
        printf("1 - Sapatos\n2 - Sandalias\n3 - Botas\n0 - Menu de Admin\n");
        printf("____________________\n");
        printf("Escolha: ");
        scanf("%d", &mudanca);
    }while(mudanca < 0 || mudanca > 3);
    do {
        limpar_tela();
        printf("MUDANCAS DISPONIVEIS\n");
        printf("____________________\n");
        printf("1 - Mão de Obra\n2 - Custo Fixo\n3 - Margem por Tamanhos\n4 - Margem\n0 - Menu Admin\n");
        printf("____________________\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
    }while(escolha < 0 || escolha > 4);
    switch(escolha){
        case 1:

            printf("Novo valor: ");
            scanf("%f", &custos[mudanca - 1].obra);
            break;
        case 2:
            printf("Novo Valor: ");
            scanf("%f", &custos[mudanca - 1].fixo);
            break;
        case 3:
            do {
                limpar_tela();
                printf("Tamanho cujo valor deseja alterar: ");
                scanf("%d", &escolha);
            }while(escolha < 34 || escolha > 48);
            printf("Novo Valor: ");
            scanf("%f", &custos[mudanca - 1].margem_tamanho[-(34 - escolha)]);
            break;

        case 4:
            printf("Novo Valor: ");
            scanf("%f", &custos[mudanca - 1].margem);
            break;
    }
    menu_admin();
}
/**Gestão de Clientes
 * @brief Função CRUD para fazer a gestão dos clientes
 *
 */
void gestao_clientes(){
    int escolha;
    do {
        limpar_tela();
        printf("GESTAO DE CLIENTES\n");
        printf("____________________\n");
        printf("1 - Criar\n2 - Editar\n3 - Remover\n4 - Ver Lista de Clientes\n0 - Voltar ao Menu de Administrador\n");
        printf("____________________\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
    }while(escolha < 0 || escolha > 4);
    limpar_tela();
    switch(escolha){
        case 0:
            menu_admin();
        case 1:
            gestao_clientecriar();
        case 2:
            gestao_clienteeditar();
        case 3:
            gestao_clienteremover();
        case 4:
            gestao_clientemostrar();
    }
}

/**Gestão de Artigos
 * @brief Alteração, edição, remoção e criação de artigos
 *
 *
 */
void gestao_artigos(){
    int escolha;
    do{
        limpar_tela();
        printf("MENU GESTAO DE ARTIGOS\n");
        printf("____________________\n");
        printf("1 - Criar\n2 - Editar\n3 - Remover\n4 - Mostrar Modelos\n0 - Menu de Administrador\n");
        printf("____________________\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
    }while(escolha < 0 || escolha > 4);
    switch(escolha){
        case 0:
            menu_admin();
        case 1:
            gestao_artigoscriar();
        case 2:
            gestao_artigoseditar();
        case 3:
            gestao_artigosremover();
        case 4:
            mostrar_modelos();

    }
}


/**Menu de Administrador
 * @brief Onde o administrador tem todo o seu controlo
 */

void menu_admin(){
    int escolha;
        do {
            limpar_tela();
            printf("MENU ADMIN\n");
            printf("____________________\n");
            printf("1 - Gestao de Clientes\n2 - Gestao de Artigos\n3 - Gestao de Tabelas de Custo\n4 - Relatorios\n5 - Preencher Questionario\n0 - Voltar ao Menu Principal\n");
            printf("____________________\n");
            printf("Escolha: ");
            scanf("%d", &escolha);
        } while (escolha < 0 || escolha > 5);
        limpar_tela();
        switch (escolha) {
            case 0:
                menu_principal();
            case 1:
                gestao_clientes();
            case 2:
                gestao_artigos();
            case 3:
                gestao_tabelacusto();
            case 4:
                menu_relatorios();
            case 5:
                menu_inquerito();

        }


}

/**Criar Cliente
 * @brief criação de um perfil de cliente
 *
 *  Atravês da memória dinamica é possivel alocar espaço para mais um (ou até mais) clientes
 */
int gestao_clientecriar(){
    int i, existente = 0;
    limpar_tela();
    lista = (Cliente *)realloc(lista, (nmr_clientes + 1) * sizeof(Cliente));
    printf("Nome: ");
    lista[nmr_clientes].nome = (char *)malloc(841 * sizeof(char));
    scanf("%s", lista[nmr_clientes].nome);
    lista[nmr_clientes].nome = (char *)realloc(lista[nmr_clientes].nome,(1 + strlen(lista[nmr_clientes].nome)) * sizeof(char));
    do {
        limpar_tela();
        existente = 0;
        printf("Numero de Cliente: ");
        scanf("%d", &lista[nmr_clientes].codigo_cliente);
        for (i = 0; i < (nmr_clientes - 1); i++) {
            if (lista[i].codigo_cliente == lista[nmr_clientes].codigo_cliente) {
                existente = 1;
            }
        }
    }while(existente == 1);
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
    printf("%s", lista[nmr_clientes].nome);
    nmr_clientes++;
    guardar_clientes();
    menu_admin();
}
/**Editar Clientes
 * @brief editar dados de cliente
 *
 *
 * É possivel editar qualquer dado armazenado na memoria
 */
int gestao_clienteeditar(){
    int escolha, i, existe;
    existe_cliente();
    if(exist_client != 1){
        printf("Cliente Não Encontrado!\n");
        delay(10);
        limpar_tela();
        menu_admin();
    }
    do {
        limpar_tela();
        printf("EDITAR CLIENTE\n");
        printf("____________________\n");
        printf("1 - Nome\n2 - NIF\n3 - Numero de Cliente\n4 - Pais\n0 - Menu de Administrador\n");
        printf("____________________\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
    }while(escolha < 0 || escolha > 4);
    limpar_tela();
    switch(escolha){
        case 1:
            printf("Novo Nome: ");
            lista[index_clienteencontrado].nome = (char *) realloc(lista[index_clienteencontrado].nome,891 * sizeof(char));
            scanf("%s", lista[index_clienteencontrado].nome);
            lista[index_clienteencontrado].nome = (char *)realloc(lista[index_clienteencontrado].nome, (strlen(lista[index_clienteencontrado].nome) + 1) * sizeof(char));
            break;
        case 2:
            do {
                limpar_tela();
                printf("Novo NIF: ");
                scanf("%d", &lista[index_clienteencontrado].nif);
            }while(lista[nmr_clientes].nif < 100000000 || lista[nmr_clientes].nif >= 1000000000);
            break;
        case 3:
            do{
            limpar_tela();
            existe = 0;
            printf("Novo Numero de Cliente: ");
            scanf("%d", &lista[index_clienteencontrado].codigo_cliente);
            for(i = 0;i < nmr_clientes;i++){
                if(i == index_clienteencontrado){
                    existe = existe;
                }else {
                    if (lista[i].codigo_cliente == lista[index_clienteencontrado].codigo_cliente) {
                        existe = 1;
                    }

                }
            }
            }while(existe == 1);

            break;
        case 4:
            printf("Novo Pais: ");
            lista[index_clienteencontrado].pais = (char *)realloc(lista[index_clienteencontrado].pais,891 * sizeof(char));
            scanf("%s", &lista[index_clienteencontrado].pais);
            lista[index_clienteencontrado].pais = (char *)realloc(lista[index_clienteencontrado].pais, (strlen(lista[index_clienteencontrado].pais) + 1) * sizeof(char));
            break;

    }
}

/**Remover Cliente
 * @brief remoção do cliente segundo o enunciado
 *
 * A remoção do cliente neste caso apenas passa por alterar o campo do "removido" de "nao" para "sim"
 */
void gestao_clienteremover(){
    existe_cliente();
    if(exist_client != 1){
            printf("Cliente Não Encontrado!\n");
            delay(10);
            limpar_tela();
            menu_admin();
    }
    strcpy(lista[index_clienteencontrado].removido, "sim");
    menu_admin();

}


/**Mostrar Cliente
 * @brief vizualizar clientes
 *
 * Com esta função é possivel ver o numero e nome de todos os clientes, estejam eles ou nao removidos
 */
void gestao_clientemostrar(){
    int i;
    char enter = 0;
    for(i = 0;i < nmr_clientes;i++){
        printf("Numero: %d Nome: %s\n", lista[i].codigo_cliente, lista[i].nome);
    }
    delay(10);
    menu_admin();
}
/**Criar Artigos
 * @brief possibilidade de criação de artigos
 *
 */
int gestao_artigoscriar() {
    int escolha,i;
    limpar_tela();
    modelo = (modelos *) realloc(modelo,(nmr_modelos + 1) * sizeof(modelos));
    printf("Nome: ");
    modelo[nmr_modelos].nome = (char *) malloc(891 * sizeof(char));
    scanf("%s", modelo[nmr_modelos].nome);
    modelo[nmr_modelos].nome = (char *) realloc(modelo[nmr_modelos].nome,strlen(modelo[nmr_modelos].nome) * sizeof(char));
    do {
        limpar_tela();
        exist_model = 0;
        printf("Codigo de Modelo: ");
        scanf("%d", &modelo[nmr_modelos].codigo);
        for(i = 0;i < nmr_modelos;i++){
            if(modelo[nmr_modelos].codigo == modelo[i].codigo){
                exist_model = 1;
            }
        }
    }while(exist_model == 1);
    do {
        limpar_tela();
        printf("Menor Tamanho Disponivel: ");
        scanf("%d", &modelo[nmr_modelos].tam_min);
    }while(modelo[nmr_modelos].tam_min < 34);
    do {
        limpar_tela();
        printf("Maior Tamanho Disponivel: ");
        scanf("%d", &modelo[nmr_modelos].tam_max);
    }while(modelo[nmr_modelos].tam_max > 48 || modelo[nmr_modelos].tam_max < modelo[nmr_modelos].tam_min);
    modelo[nmr_modelos].vendas = 0;
    do {
        limpar_tela();
        printf("TIPO DE CALCADO\n");
        printf("____________________\n");
        printf("1 - Sapato\n2 - Sandalia\n3 - Bota\n");
        printf("____________________\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
    }while(escolha < 1 || escolha > 3);
    switch (escolha) {
        case 1:
            strcpy(modelo[nmr_modelos].tipo, "Sap");
            break;
        case 2:
            strcpy(modelo[nmr_modelos].tipo, "San");
            break;
        case 3:
            strcpy(modelo[nmr_modelos].tipo, "Bot");
            break;
    }
    do {
        printf("Valor adicional (para além do referido na tabela de custos): ");
        scanf("%f", &modelo[nmr_modelos].valor_adicional);
    }while(modelo[nmr_modelos].valor_adicional < 0);
    nmr_modelos++;
    menu_admin();
}
/**Editar Artigos
 * @brief Possibilidade de editar artigos
 */
void gestao_artigoseditar(){
    int escolha;
    limpar_tela();
    existe_modelo();
    if(exist_model != 1){
        printf("MODELO NAO ENCONTRADO!");
        delay(10);
        menu_admin();
    }
    do {
        limpar_tela();
        printf("MENU EDICAO DE ARTIGOS\n");
        printf("____________________\n");
        printf("1 - Nome de Artigo\n2 - Tamanho\n3 - Tipo\n0 - Menu de Admin\n");
        printf("____________________\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
    }while(escolha < 0 || escolha > 3);
    switch(escolha){
        case 0:
            menu_admin();
        case 1:
            printf("Novo Nome: ");
            modelo[index_modelencontrado].nome = (char *)realloc(modelo[index_modelencontrado].nome,891 * sizeof(char));
            scanf("%s", modelo[index_clienteencontrado].nome);
            modelo[index_modelencontrado].nome = (char *)realloc(modelo[index_modelencontrado].nome,(strlen(modelo[index_modelencontrado].nome) + 1) * sizeof(char));
            break;
        case 2:
            do {
                limpar_tela();
                printf("MUDANÇA DE TAMANHO\n");
                printf("____________________\n");
                printf("1 - Menor Tamanho\n2 - Maior Tamanho\n");
                printf("____________________\n");
                printf("Escolha: ");
                scanf("%d", &escolha);
            }while(escolha < 1 || escolha > 2);
            do {
                limpar_tela();
                printf("Novo Tamanho: ");
                switch (escolha) {
                    case 1:
                        scanf("%d", &modelo[index_modelencontrado].tam_min);
                        break;
                    case 2:
                        scanf("%d", &modelo[index_modelencontrado].tam_max);
                        break;
                }
            }while(modelo[index_modelencontrado].tam_min < 34 || modelo[index_modelencontrado].tam_max > 48 || modelo[index_modelencontrado].tam_max < modelo[index_modelencontrado].tam_min);
            break;
        case 3:
            do {
                limpar_tela();
                printf("MUDAR TIPO\n");
                printf("____________________\n");
                printf("1 - Sapato\n2 - Sandalia\n3 - Bota\n");
                printf("____________________\n");
                printf("Escolha: ");
                scanf("%d", &escolha);
            }while(escolha < 1 || escolha > 3);
            switch (escolha) {
                case 1:
                    strcpy(modelo[index_modelencontrado].tipo, "Sap");
                    break;
                case 2:
                    strcpy(modelo[index_modelencontrado].tipo, "San");
                    break;
                case 3:
                    strcpy(modelo[index_modelencontrado].tipo, "Bot");
                    break;
            }
            menu_admin();
    }
}
/**Remoção de Artigos
 * @brief remoção de artigos selecionados
 *
 * Ao contrario da remoção de clientes aqui o artigo é mesmo apagado e não há como o recuperar
 *
 */
void gestao_artigosremover(){
    limpar_tela();
    existe_modelo();
    if(exist_model != 1){
        printf("MODELO NÃO EXISTE!");
        delay(10);
        limpar_tela();
        menu_admin();
    }
    modelo[index_modelencontrado].nome = (char *)realloc(modelo[index_modelencontrado].nome, strlen(modelo[nmr_modelos - 1].nome) * sizeof(char));

    modelo[index_modelencontrado].nome = strdup(modelo[nmr_modelos - 1].nome);
    modelo[index_modelencontrado].tam_min = modelo[nmr_modelos - 1].tam_min;
    modelo[index_modelencontrado].tam_max = modelo[nmr_modelos - 1].tam_max;
    modelo[index_modelencontrado].vendas = modelo[nmr_modelos - 1].vendas;
    modelo[index_modelencontrado].codigo = modelo[nmr_modelos - 1].codigo;
    strcpy(modelo[index_modelencontrado].tipo, modelo[nmr_modelos - 1].tipo);
    free(modelo[nmr_modelos - 1].nome);
    nmr_modelos--;
    modelo =(modelos *)realloc(modelo,nmr_modelos * sizeof(modelos));
    menu_admin();
}
/**Mostrar Modelos
 * @brief ver todos os modelos disponiveis
 */
void mostrar_modelos(){
    int i;
    limpar_tela();
    printf("MODELOS\n");
    printf("____________________\n");
    for(i = 0;i < nmr_modelos;i++){
        printf("Codigo: %d Nome: %s\n", modelo[i].codigo, modelo[i].nome);
    }
    printf("____________________\n");
    delay(10);
    menu_admin();
}
/**Relatorio de Geolocalização
 * @brief Relatorio de clientes nacionais e internacionais
 *
 * Este relatório permite ter uma maior visão do mercado da empresa
 *
 */
void relatorio_geoloc(){
    int i,t, cliente_nacional = 0, cliente_internacional = 0;
    for(t = 0;t < nmr_clientes;t++) {
        for (int i = 0; lista[t].pais[i]; i++) {
            lista[t].pais[i] = tolower(lista[t].pais[i]);
        }
    }
    for(i = 0;i < nmr_clientes;i++){
        if(strcmp(lista[i].pais, "portugal") == 0){
            cliente_nacional++;
        }else{
            cliente_internacional++;
        }
    }
    limpar_tela();
    printf("RELATORIO DE GEOLOCALIZACAO\n");
    printf("____________________\n");
    printf("Clientes a Nivel Nacional: %d\n", cliente_nacional);
    printf("Clientes a Nivel Internacional: %d\n", cliente_internacional);
    printf("____________________\n");
    delay(10);

    menu_admin();
}
/**Relatório de Vendas
 *
 */
void relatorio_vendas(){
    int i, vendas_total = 0;
    limpar_tela();
    printf("RELATORIO DE VENDAS\n");
    printf("____________________\n");
    for(i = 0;i < nmr_modelos;i++){
        printf("Codigo: %d Nome:  %s Numero de Vendas: %d\n", modelo[i].codigo, modelo[i].nome, modelo[i].vendas);
        vendas_total = vendas_total + modelo[i].vendas;
    }
    printf("Numero de Vendas total: %d\n", vendas_total);
    printf("____________________\n");
    delay(10);
    menu_admin();
}
/**Relatorio de Satisfação de Staff
 *
 */
void relatorio_staff(){
    limpar_tela();
    int i,opc_um = 0,opc_dois = 0,opc_tres = 0;
    float um = 0, dois = 0, quatro = 0;
    for(i = 0; i < nmr_formstaff;i++){
        um = um + staff[i].um;
        dois = dois + staff[i].dois;
        quatro = quatro + staff[i].quatro;
        switch(staff[i].tres){
            case 1:
                opc_um++;
                break;
            case 2:
                opc_dois++;
                break;
            case 3:
                opc_tres++;
                break;
        }
    }
    um = um / nmr_formstaff;
    dois = dois / nmr_formstaff;
    quatro = quatro / nmr_formstaff;
    printf("RELATORIO DE SATISFACAO DE STAFF\n");
    printf("____________________\n");
    printf("Classificacao do Ambiente no Local de Trabalho (0-20): %.2f\n", um);
    delay(2);
    printf("Classificacao do Horario de trabalho (0-20): %.2f\n", dois);
    printf("____________________\n");
    printf("%d elemento(s) desejam melhorias a nivel salarial\n", opc_um);
    printf("%d elemento(s) desejam melhorias no horario de trabalho\n ",opc_dois);
    printf("%d elemento(s) desejam a implementacao de atividades recreativas extra-trabalho\n", opc_tres);
    printf("____________________\n");
    printf("Classificacao geral da empresa (0-20): %.2f\n", quatro);
    delay(20);
    menu_admin();
}


/**Relatorio de Satisfação de Cliente
 *
 */
void relatorio_cliente(){
    limpar_tela();
    int i;
    float um = 0,dois = 0,tres = 0;
    for(i = 0;i < nmr_formclientes;i++){
        um = um + cliente[i].um;
        dois = dois + cliente[i].dois;
        tres = tres + cliente[i].tres;
    }
    um = um / nmr_formclientes;
    dois = dois / nmr_formclientes;
    tres = tres / nmr_formclientes;
    printf("RELATORIO SATISFACAO DE CLIENTE\n");
    printf("____________________\n");
    printf("Classificacao de variedade de produtos (0-20): %.2f\n", um);
    printf("Classificacao de atendimento prestado (0-20): %.2f\n", dois);
    printf("____________________\n");
    printf("Classificacao Geral da Empresa (0-20): %.2f\n", tres);
    printf("____________________\n");
    delay(20);
    menu_admin();

}