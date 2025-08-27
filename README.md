![logo da ufu](https://github.com/paulorf0/Trabalho-AEDII/blob/menu/logoufu.png) <h1 align = center> <em> Projeto de Letras de Músicas </em> </h1>

# Funcionalidades

- Leitura de arquivos de letras de musicas .txt

- Inserção em vetor ordenado

- Inserção em árvore binaria

- Inserção em árvore AVL

- Contagem de palavras

# Compilação
```
gcc -Wall -Wextra -std=c99 -g -c main.c -o main.o
gcc -Wall -Wextra -std=c99 -g -c tratamento_musica\tratamento_musica.c -o tratamento_musica\tratamento_musica.o
gcc -Wall -Wextra -std=c99 -g -c vetor_ordenado\vetor_ordenado.c -o vetor_ordenado\vetor_ordenado.o
gcc -Wall -Wextra -std=c99 -g -o programa_musicas.exe main.o tratamento_musica\tratamento_musica.o vetor_ordenado\vetor_ordenado.o -lm
```
# Como Utilizar

-Primeiro uso: Execute o run.bat

-Uso pleno: Execute apenas programa_musicas.exe

-Uso após novas modificações: Execute o run.bat e então o programa_musicas.exe
