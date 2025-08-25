#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tratamento_musica/tratamento_musica.h"
#include "vetor_ordenado/vetor_ordenado.h"

#define NUM_MUSICAS 16
#define TAM_LINHA 256
#define PASTA_MUSICAS "LetrasMusicas/"

void exibir_menu_principal() {
    printf("\n=== REPOSITORIO DE LETRAS DE MUSICAS ===\n");
    printf("1 - Carregar musicas\n");
    printf("2 - Buscar palavra nas musicas carregadas\n");
    printf("3 - Buscar palavra por frequencia em AVL\n");
    printf("0 - Sair\n");
    printf("\nEscolha uma opcao: ");
}

void exibir_lista_musicas() {
    printf("\n=== LISTA DE MUSICAS DISPONIVEIS ===\n");
    
    for (int i = 1; i <= NUM_MUSICAS; i++) {
        char caminho_arquivo[50];
        snprintf(caminho_arquivo, sizeof(caminho_arquivo), "%s%d.txt", PASTA_MUSICAS, i);
        
        int num_linhas;
        char **conteudo = ler_arquivo(caminho_arquivo, &num_linhas);
        
        if (conteudo != NULL && num_linhas >= 2) {
            normalizar_linhaV2(conteudo[0]);  // Nome da música
            normalizar_linhaV2(conteudo[1]);  // Artista
            
            printf("%2d - %-30s | %s\n", i, conteudo[0], conteudo[1]);
            
            // Libera a memória
            for (int j = 0; j < num_linhas; j++) {
                free(conteudo[j]);
            }
            free(conteudo);
        } else {
            printf("%2d - arquivo %s nao carregou\n", i, caminho_arquivo);
            if (conteudo) {
                for (int j = 0; j < num_linhas; j++) free(conteudo[j]);
                free(conteudo);
            }
        }
    }
    printf("\n0 - Voltar ao menu principal\n");
}

int carregar_musicas(VetorOrdenado *vetor) {
    int escolha_arquivo;
    char buffer[TAM_LINHA];
    int musicas_carregadas = 0;
    double tempo_total_processamento = 0.0;
    
    do {
        exibir_lista_musicas();
        printf("\nDigite o numero da musica para carregar: ");
        
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Erro de leitura\n");
            continue;
        }
        
        if (sscanf(buffer, "%d", &escolha_arquivo) != 1) {
            printf("Entrada invalida\n");
            continue;
        }
        
        if (escolha_arquivo == 0) {
            printf("Voltando ao menu principal\n");
            break;
        }
        
        if (escolha_arquivo < 1 || escolha_arquivo > NUM_MUSICAS) {
            printf("Numero invalido escolha entre 1 e %d\n", NUM_MUSICAS);
            continue;
        }
        
        char caminho_arquivo[50];
        snprintf(caminho_arquivo, sizeof(caminho_arquivo), "%s%d.txt", PASTA_MUSICAS, escolha_arquivo);
        
        printf("\n=== Carregando: %s ===\n", caminho_arquivo);
        
        // Mede tempo REAL de processamento
        double inicio_processamento = get_real_time();
        
        char **letra = obter_musica(caminho_arquivo);
        
        if (!letra) {
            printf("Erro ao carregar a musica\n");
            continue;
        }
        
        // Obtém nome da música e cantor
        char *nome_musica = letra[0] ? strdup(letra[0]) : strdup("Desconhecido");
        char *nome_cantor = letra[1] ? strdup(letra[1]) : strdup("Desconhecido");
        
        // Processa as palavras da música
        processar_palavras_musica(vetor, letra, nome_musica, nome_cantor);
        
        double fim_processamento = get_real_time();
        double tempo_musica = elapsed_time(inicio_processamento, fim_processamento);
        
        tempo_total_processamento += tempo_musica;
        
        printf("Musica: %-30s | Artista: %s\n", nome_musica, nome_cantor);
        printf("Tempo total: %.6f segundos\n", tempo_musica);
        
        musicas_carregadas++;
        
        free(nome_musica);
        free(nome_cantor);

        int num_linhas = 0;

        while (letra[num_linhas] != NULL) 
            num_linhas++;

        for (int i = 0; i < num_linhas; i++)
            free(letra[i]);
        
        free(letra);
        
    } while (1);
    
    printf("\n=== RESULTADOS ===\n");
    //printf("Total de musicas carregadas: %d\n", musicas_carregadas);
    printf("Tempo total de processamento: %.6f segundos\n", tempo_total_processamento);
    
    return musicas_carregadas;
}

void buscar_palavra_vetor(VetorOrdenado *vetor, int musicas_carregadas) {
    if (vetor == NULL || musicas_carregadas == 0) {
        printf("\nNenhuma musica foi carregada ainda\n");
        return;
    }
    
    char palavra[TAM_LINHA];
    printf("\n=== BUSCAR PALAVRA NAS MUSICAS ===\n");
    printf("Digite a palavra a ser buscada: ");
    
    if (!fgets(palavra, sizeof(palavra), stdin)) {
        printf("Erro de leitura\n");
        return;
    }
    
    palavra[strcspn(palavra, "\n")] = 0;
    
    if (strlen(palavra) == 0) {
        printf("Palavra invalida\n");
        return;
    }
    
    normalizar_linhaV2(palavra);
    
    printf("\nBuscando a palavra '%s' no vetor\n", palavra);

    //implementar a busca
}

void buscar_palavra_avl(int musicas_carregadas) {
    if (musicas_carregadas == 0) {
        printf("\nNenhuma musica foi carregada ainda. Use a opcao 1 primeiro.\n");
        return;
    }
    
    char palavra[TAM_LINHA];
    printf("\n=== BUSCAR PALAVRA POR FREQUENCIA NA AVL ===\n");
    printf("Digite a palavra a ser buscada: ");
    
    if (!fgets(palavra, sizeof(palavra), stdin)) {
        printf("Erro de leitura\n");
        return;
    }
    
    palavra[strcspn(palavra, "\n")] = 0;
    
    if (strlen(palavra) == 0) {
        printf("Palavra invalida\n");
        return;
    }
    
    normalizar_linhaV2(palavra);
    
    printf("\nBuscando a palavra '%s' na AVL por frequencia\n", palavra);
    
    //implementar busca avl
}

int main() {
    int escolha;
    char buffer[TAM_LINHA];

    VetorOrdenado *vetor = vetor_criar(100);
    int musicas_carregadas = 0;
    
    printf("=== SISTEMA DE PROCESSAMENTO DE LETRAS DE MUSICA ===\n");
    
    do {
        exibir_menu_principal();
        
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Erro de leitura\n");
            continue;
        }
        
        if (sscanf(buffer, "%d", &escolha) != 1) {
            printf("Entrada invalida\n");
            continue;
        }
        
        switch (escolha) {
            case 0:
                printf("Saindo...\n");
                break;
                
            case 1:
                {
                    int novas_musicas = carregar_musicas(vetor);
                    musicas_carregadas += novas_musicas;
                    //printf("\nTotal de %d musicas carregadas\n", musicas_carregadas);
                }
                break;
                
            case 2:
                buscar_palavra_vetor(vetor, musicas_carregadas);
                break;
                
            case 3:
                buscar_palavra_avl(musicas_carregadas);
                break;
                
            default:
                printf("Opcao invalida!\n");
                break;
        }
        
        if (escolha != 0) {
            printf("\nPressione Enter para continuar...");
            fgets(buffer, sizeof(buffer), stdin);
        }
        
    } while (escolha != 0);

    if (vetor != NULL) {
        vetor_liberar(vetor);
    }
    
    return 0;
}