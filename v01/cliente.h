//
// Created by Diogo Cardoso on 01/01/2022.
//

#ifndef LP_REDONE_CLIENTE_H
#define LP_REDONE_CLIENTE_H
void menu_cliente();
extern float preco_final;
extern int *quantidade;
extern int *indice_calcadosver;
extern int *indicemodelos_escolhidos;
extern int tamanho_carrinho;
extern int *quantidade_carrinho;
extern int *indice_tamanhos;

int guardar_encomenda();

void listar_encomenda();

#endif //LP_REDONE_CLIENTE_H
