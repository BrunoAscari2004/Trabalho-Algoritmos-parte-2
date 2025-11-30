#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINHA 1024

//Este programa serve somente para criar os arquivos binarios quando não estão presentes

typedef struct prod
{
    long long id;
    char categoria[20];
    float preco;
} Produto;

typedef struct ped{
    long long id;
    long long id_produto;
    char data[11];
} Pedido;


#define DELIMITADOR ","

Produto processar_linha(char *linha) {
    Produto p = {0}; // Inicializa toda a struct com zero
    char *token;
    int indice_coluna = 0;

    // Remove o '\n' se presente
    //linha[strcspn(linha, "\n")] = 0; 

    token = strtok(linha, DELIMITADOR);
    //printf("\n%s\n",token);

    while (token != NULL) {
        
        // Se a string tem tamanho zero (ou seja, é um campo vazio)
        int is_empty = (token[0] == '\0');
        
        switch (indice_coluna) {
            case 0: // ID (long long) - Geralmente obrigatório, mas tratado aqui
                if (is_empty) {
                    p.id = 0; // Atribui 0 se estiver vazio
                } else {
                    p.id = strtoll(token, NULL, 10);
                }
                break;

            case 1: // Categoria (char[20])
                if (is_empty) {
                    strcpy(p.categoria, " "); 
                } else {
                    // O campo não está vazio, copia normalmente
                    strncpy(p.categoria, token, sizeof(p.categoria) - 1);
                    p.categoria[sizeof(p.categoria) - 1] = '\0'; 
                }
                break;

            case 2: // Preço (float)
                if (is_empty) {
                    p.preco = 0.0f; 
                } else {
                    // O campo não está vazio, converte o float
                    p.preco = (float)strtod(token, NULL);
                }
                break;
            
            default:
                break;
        }

        token = strtok(NULL, DELIMITADOR);
        indice_coluna++;
    }

    return p;
}

Pedido processar_linha_pedido(char *linha) {
    Pedido p = {0}; // Inicializa toda a struct com zero
    char *token;
    int indice_coluna = 0;

    // Remove o '\n' se presente
    //linha[strcspn(linha, "\n")] = 0; 

    token = strtok(linha, DELIMITADOR);


    while (token != NULL) {
         //printf("\n%s\n",token);
        
        // Se a string tem tamanho zero (ou seja, é um campo vazio)
        int is_empty = (token[0] == '\0');
        
        switch (indice_coluna) {
            case 0: // ID (long long)
                if (is_empty) {
                    p.id = 0; // Atribui 0 se estiver vazio
                } else {
                    p.id = strtoll(token, NULL, 10);
                }
                break;

            case 1: // ID Produto (long long)
                if (is_empty) {
                    p.id_produto = 0; // Atribui 0 se estiver vazio
                } else {
                    p.id_produto = strtoll(token, NULL, 10);
                }
                break;

            case 2: // Data (char[11])
                if (is_empty) {
                    strcpy(p.data, " "); 
                } else {
                    // O campo não está vazio, copia normalmente
                    strncpy(p.data, token, sizeof(p.data) - 1);
                    p.data[sizeof(p.data) - 1] = '\0'; 
                }
                break;
            
            default:
                break;
        }

        token = strtok(NULL, DELIMITADOR);
        indice_coluna++;
    }

    return p;
}

void salvar_pedido(FILE * arquivo, const Pedido *pedido) {

    size_t itens_escritos;

    itens_escritos = fwrite(pedido, sizeof(Pedido), 1, arquivo);

    if (itens_escritos != 1) {
        fprintf(stderr, "Erro na escrita: Apenas %zu de 1 item foram escritos.\n", itens_escritos);
    } else {
        //printf("Pedido ID %lld salvo com sucesso no arquivo binário.\n", pedido->id);
    }

}


void salvar_produto(FILE * arquivo, const Produto *produto) {

    size_t itens_escritos;


    // Usar fwrite para escrever a struct inteira
    // Escreve 1 item do tamanho de 'Produto', começando no endereço de 'produto'
    itens_escritos = fwrite(produto, sizeof(Produto), 1, arquivo);

    if (itens_escritos != 1) {
        fprintf(stderr, "Erro na escrita: Apenas %zu de 1 item foram escritos.\n", itens_escritos);
    } else {
        printf("Produto ID %lld salvo com sucesso no arquivo binário.\n", produto->id);
    }

}

Produto ler_produto(FILE *arquivo, int quant){

    Produto produto;
    for (int i = 0; i < quant; i++)
    {
        fread(&produto, sizeof(Produto),1, arquivo);
        printf("\n%lld - %s - %.2f", produto.id, produto.categoria, produto.preco);
    }
    
}

Pedido ler_pedido(FILE *arquivo, int quant){



    Pedido pedido;
    for (int i = 0; i < quant; i++)
    {
        fread(&pedido, sizeof(Pedido),1, arquivo);
        //printf("\n%lld - %lld - %s", pedido.id, pedido.id_produto, pedido.data);
    }
    

}



int main(){

    /*

    FILE *produtoscsv = fopen("produtos.csv","r");
    FILE *produtosbin = fopen("produtos.bin","wb");

    char buffer[MAX_LINHA];
    int count = 0;

    //utilizando o fgets para ler até o \n
    while(fgets(buffer, MAX_LINHA, produtoscsv) != NULL){
        Produto prod = processar_linha(buffer);
        salvar_produto(produtosbin, &prod);
        count++;
        if(count == 50)
            break;
    }


    fclose(produtosbin);


    produtosbin = fopen("produtos.bin", "rb");

    ler_produto(produtosbin, 50);
    */
    FILE *pedidoscsv = fopen("pedidos.csv","r");
    FILE *pedidosbin = fopen("pedidos.bin","wb");

        char buffer[MAX_LINHA];
    int count = 0;

    //utilizando o fgets para ler até o \n
    while(fgets(buffer, MAX_LINHA, pedidoscsv) != NULL){
        Pedido ped = processar_linha_pedido(buffer);

        //printf("\n%lld - %lld - %s\n", ped.id, ped.id_produto, ped.data);
        salvar_pedido(pedidosbin, &ped);
    }

    fclose(pedidosbin);
    fclose(pedidoscsv);

    return 0;
}