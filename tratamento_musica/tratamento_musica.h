
#include <wctype.h> 
#include <wchar.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

char **ler_arquivo(const char *nome_arquivo, int *num_linhas);
// Complexidade O(n*47)
void retirar_acento(wchar_t *str);

// Complexidade O(n)
void to_lower(wchar_t *str);