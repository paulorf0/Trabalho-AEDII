#include "vetor_ordenado.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

VetorOrdenado* vetor_criar(int capacidade_inicial) {
    VetorOrdenado *vetor = malloc(sizeof(VetorOrdenado));
    
    if (!vetor) 
        return NULL;
    
    vetor->dados = malloc(capacidade_inicial * sizeof(Entrada));
    
    if (!vetor->dados) {

        free(vetor);
        return NULL;

    }
    
    vetor->tamanho = 0;
    vetor->capacidade = capacidade_inicial;
    return vetor;

}

void vetor_redimensionar(VetorOrdenado *vetor, int nova_capacidade) {
    Entrada *novos_dados = realloc(vetor->dados, nova_capacidade * sizeof(Entrada));
    
    if (!novos_dados) return;
    
    vetor->dados = novos_dados;
    vetor->capacidade = nova_capacidade;
}

void vetor_inserir(VetorOrdenado *vetor, Entrada entrada) {
    if (vetor->tamanho >= vetor->capacidade) {

        vetor_redimensionar(vetor, vetor->capacidade * 2);

    }

    int inicio = 0, fim = vetor->tamanho - 1;
   
    int pos = vetor->tamanho; 

    while (inicio <= fim) {
    
        int meio = (inicio + fim) / 2;
    
        int cmp = strcmp(entrada.palavra, vetor->dados[meio].palavra);
        
        if (cmp < 0) {
    
            fim = meio - 1;
            pos = meio;
    
        } else if (cmp > 0) {
    
            inicio = meio + 1;
            pos = meio + 1;
    
        } else {
    
            if (entrada.freq_na_musica > vetor->dados[meio].freq_na_musica) {
    
                free(vetor->dados[meio].palavra);
                free(vetor->dados[meio].nome_musica);
                free(vetor->dados[meio].nome_cantor);
                free(vetor->dados[meio].estrofe);
                
                vetor->dados[meio] = entrada;
    
            }
    
            vetor->dados[meio].freq_total_repo += entrada.freq_na_musica;
    
            return;
        }
    }

    for (int i = vetor->tamanho; i > pos; i--) {
    
        vetor->dados[i] = vetor->dados[i - 1];
    
    }

    vetor->dados[pos] = entrada;
    vetor->tamanho++;

}

Entrada* vetor_buscar(const VetorOrdenado *vetor, const char *palavra) {

    int inicio = 0, fim = vetor->tamanho - 1;
    
    while (inicio <= fim) {

        int meio = (inicio + fim) / 2;

        int cmp = strcmp(palavra, vetor->dados[meio].palavra);
        
        if (cmp < 0) {

            fim = meio - 1;

        } else if (cmp > 0) {

            inicio = meio + 1;

        } else {

            return &vetor->dados[meio];

        }
    }

    return NULL;

}

void vetor_liberar(VetorOrdenado *vetor) {

    if (!vetor)
        return;
    
    for (int i = 0; i < vetor->tamanho; i++) {
    
        free(vetor->dados[i].palavra);
        free(vetor->dados[i].nome_musica);
        free(vetor->dados[i].nome_cantor);
        free(vetor->dados[i].estrofe);
    
    }
    
    free(vetor->dados);
    free(vetor);

}

void vetor_imprimir(const VetorOrdenado *vetor) {

    printf("Vetor Ordenado (%d/%d):\n", vetor->tamanho, vetor->capacidade);

    for (int i = 0; i < vetor->tamanho; i++) {

        printf("[%d] %s (Música: %s, Freq: %d/%d)\n", i, vetor->dados[i].palavra,
                                                         vetor->dados[i].nome_musica,
                                                         vetor->dados[i].freq_na_musica, 
                                                         vetor->dados[i].freq_total_repo);
    
    }
}
