//
// Created by Diogo Cardoso on 30/12/2021.
//

#ifndef LP_REDONE_STRUCTS_H
#define LP_REDONE_STRUCTS_H

/**@struct Formularios Clientes
 * @brief esta estrutura armazena os formularios dos clientes
 *
 *
 */
typedef struct{
    int um,dois,tres;
}form_cliente;

/**@struct Listagem de Encomendas
 * @brief esta estrutura armazena a lista de encomendas realizadas
 */
typedef struct{
    int codigo_cliente;
    float preco_final;
    int dia,mes,ano;
    char *pais;
}encomenda;
/**@struct Tabela de Custos
 * @brief Nesta estrutura fica armazenado a tabela de custos
 *
 */
typedef struct{
    float obra,fixo,margem;
    float margem_tamanho[15];
}Calcado;
/**@struct Lista Clientes
 * @brief nesta estrutura fica armazenado a lista de clientes
 */
typedef struct{
    char removido[3],*nome,*pais;
    int nif,codigo_cliente;
}Cliente;
/**@struct Modelos
 * @brief nesta estrutura irão ficar armazenados os varios tipos de modelos
 */
typedef struct{
    char *nome,tipo[3];
    int codigo,tam_min,tam_max,vendas;
    float valor_adicional;
}modelos;
/**@struct Formulario Staff
 * @brief Nesta estrutura ficara armazenado os formularios do staff
 */
typedef struct{
    int um,dois,tres,quatro;
}formulario_staff;

extern int nmr_clientes;
extern int nmr_modelos;
extern int nmr_formstaff;
extern int nmr_formclientes;
extern int nmr_encomendas;

formulario_staff *staff;
form_cliente *cliente;
Cliente *lista;
modelos *modelo;
Calcado custos[3];
encomenda *encomendas;


#endif //LP_REDONE_STRUCTS_H
