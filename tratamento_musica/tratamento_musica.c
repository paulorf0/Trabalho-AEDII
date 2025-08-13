/*
    Sobre wchar e derivados

    https://learn.microsoft.com/pt-br/cpp/c-runtime-library/reference/mbstowcs-mbstowcs-l?view=msvc-170 - conversão entre tipos char e wchar
    https://pubs.opengroup.org/onlinepubs/7908799/xsh/wchar.h.html - biblioteca wchar.h
    https://pubs.opengroup.org/onlinepubs/009696699/basedefs/wctype.h.html - biblioteca wctype.h
*/

#include "tratamento_musica.h"

char **ler_arquivo(const char *nome_arquivo, int *num_linhas)
{
    FILE *arq = fopen(nome_arquivo, "r");
    if (arq == NULL)
    {
        perror("Erro ao abrir arquivo");
        return NULL;
    }

    char buffer[1024];
    char **texto = NULL;
    *num_linhas = 0;

    while (fgets(buffer, sizeof(buffer), arq))
    {
        if (strlen(buffer) < 2)
            continue;

        char **temp = realloc(texto, (*num_linhas + 1) * sizeof(char *));
        if (temp == NULL)
        {
            perror("Erro ao realocar memoria para o array de linhas");
            for (int i = 0; i < *num_linhas; i++)
                free(texto[i]);
            free(texto);
            fclose(arq);
            return NULL;
        }
        texto = temp;

        buffer[strcspn(buffer, "\n")] = '\0';

        texto[*num_linhas] = malloc(strlen(buffer) + 1);
        if (texto[*num_linhas] == NULL)
        {
            perror("Erro ao alocar memoria para a linha");
            for (int i = 0; i < *num_linhas; i++)
                free(texto[i]);
            free(texto);
            fclose(arq);
            return NULL;
        }

        strcpy(texto[*num_linhas], buffer);
        (*num_linhas)++;
    }

    fclose(arq);
    return texto;
}

// Complexidade O(n*47)
void retirar_acento(wchar_t *str)
{
    // Note o L antes das strings para indicar que são literais "wide"
    wchar_t com_acento[] = L"áàâãäéèêëíìîïóòôõöúùûüçÁÀÂÃÄÉÈÊËÍÌÎÏÓÒÔÕÖÚÙÛÜÇ";
    wchar_t sem_acento[] = L"aaaaaeeeeiiiiooooouuuucAAAAAEEEEIIIIOOOOOUUUUC";

    // A lógica do loop permanece a mesma, mas agora opera em caracteres completos
    for (int i = 0; str[i] != L'\0'; i++)
    {
        for (int j = 0; com_acento[j] != L'\0'; j++)
        {
            if (str[i] == com_acento[j])
            {
                str[i] = sem_acento[j];
                break; // Encontrou, pode parar o loop interno
            }
        }
    }
}

// Complexidade O(n)
void to_lower(wchar_t *str)
{

    for (int i = 0; str[i] != L'\0'; i++)
    {
        str[i] = towlower((unsigned char)str[i]);
    }
}

// Complexidade \approx O(47*n)
void normalizar_linha(char *str)
{
    if (str == NULL)
        return;

    const size_t len = strlen(str) + 1; // Caracter nulo contado
    wchar_t wStr[len];
    mbstowcs(wStr, str, len);
    retirar_acento(wStr);
    to_lower(wStr);
    wcstombs(str, wStr, len);
}

char **obter_musica(char *nome_arquivo)
{
    int num_linhas = 0;
    char **texto = ler_arquivo(nome_arquivo, &num_linhas);
    if (texto)
    {
        for (int i = 0; i < num_linhas; i++)
            normalizar_linha(texto[i]);
    }

    return texto;
}