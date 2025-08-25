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
    if (arq == NULL) {
        perror("Erro ao abrir arquivo");
        return NULL;
    }

    char buffer[1024];
    char **texto = NULL;
    *num_linhas = 0;

    while (fgets(buffer, sizeof(buffer), arq)) {
        if (strlen(buffer) < 2)
            continue;

        char **temp = realloc(texto, (*num_linhas + 1) * sizeof(char *));
        if (temp == NULL) {
            perror("Erro ao realocar memoria");
            for (int i = 0; i < *num_linhas; i++) free(texto[i]);
            free(texto);
            fclose(arq);
            return NULL;
        }
        texto = temp;

        buffer[strcspn(buffer, "\n")] = '\0';

        texto[*num_linhas] = malloc(strlen(buffer) + 1);
        if (texto[*num_linhas] == NULL) {
            perror("Erro ao alocar memoria");
            for (int i = 0; i < *num_linhas; i++) free(texto[i]);
            free(texto);
            fclose(arq);
            return NULL;
        }

        strcpy(texto[*num_linhas], buffer);
        (*num_linhas)++;
    }

    char **temp = realloc(texto, (*num_linhas + 1) * sizeof(char *));
    if (temp == NULL) {
        perror("Erro ao realocar memoria para terminador");
        for (int i = 0; i < *num_linhas; i++) free(texto[i]);
        free(texto);
        fclose(arq);
        return NULL;
    }
    texto = temp;
    texto[*num_linhas] = NULL;

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

void normalizar_linhaV2(char *str) {
    unsigned char *src = (unsigned char*)str;
    char *dst = str;

    while (*src) {
        unsigned char c = *src;

        if (c < 0x80) {
            char ch = (char)c;
            if (ch >= 'A' && ch <= 'Z') ch = (char)(ch - 'A' + 'a');
            *dst++ = ch;
            src++;
            continue;
        }

        if (c == 0xC3 && src[1]) {
            
            unsigned char d = src[1];
            char repl = 0;

            // A / a
            if (d==0x80||d==0x81||d==0x82||d==0x83||d==0x84||  // À Á Â Ã Ä
                d==0xA0||d==0xA1||d==0xA2||d==0xA3||d==0xA4)   // à á â ã ä
                repl = 'a';
            // E / e
            else if (d==0x88||d==0x89||d==0x8A||d==0x8B||      // È É Ê Ë
                     d==0xA8||d==0xA9||d==0xAA||d==0xAB)       // è é ê ë
                repl = 'e';
            // I / i
            else if (d==0x8C||d==0x8D||d==0x8E||d==0x8F||      // Ì Í Î Ï
                     d==0xAC||d==0xAD||d==0xAE||d==0xAF)       // ì í î ï
                repl = 'i';
            // O / o
            else if (d==0x92||d==0x93||d==0x94||d==0x95||d==0x96|| // Ò Ó Ô Õ Ö
                     d==0xB2||d==0xB3||d==0xB4||d==0xB5||d==0xB6)   // ò ó ô õ ö
                repl = 'o';
            // U / u
            else if (d==0x99||d==0x9A||d==0x9B||d==0x9C||      // Ù Ú Û Ü
                     d==0xB9||d==0xBA||d==0xBB||d==0xBC)       // ù ú û ü
                repl = 'u';
            // Ç / ç
            else if (d==0x87 || d==0xA7)
                repl = 'c';
            
            else if (d==0x91 || d==0xB1)
                repl = 'n';

            if (repl) *dst++ = repl;

            // Pula os dois bytes do caractere UTF-8
            src += 2;
            continue;
        }

        // Outros caracteres multi-byte: pula eles (3 ou 4 bytes)
        if ((c & 0xE0) == 0xC0) { 
            src += (src[1] ? 2 : 1);
        } else if ((c & 0xF0) == 0xE0) { // 3 bytes
            src += (src[1] ? (src[2] ? 3 : 2) : 1);
        } else if ((c & 0xF8) == 0xF0) { // 4 bytes
            src += (src[1] ? (src[2] ? (src[3] ? 4 : 3) : 2) : 1);
        } else {
            // byte de continuação perdido: descarta
            src++;
        }
    }

    *dst = '\0';
}

char **obter_musica(char *nome_arquivo)
{
    int num_linhas = 0;
    char **texto = ler_arquivo(nome_arquivo, &num_linhas);
    if (texto)
    {
        for (int i = 0; i < num_linhas; i++)
            normalizar_linhaV2(texto[i]);
    }

    return texto;
}