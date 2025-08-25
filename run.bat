@echo off

:: Compila os arquivos
gcc -Wall -Wextra -std=c99 -g -c main.c -o main.o
gcc -Wall -Wextra -std=c99 -g -c tratamento_musica\tratamento_musica.c -o tratamento_musica\tratamento_musica.o
gcc -Wall -Wextra -std=c99 -g -c vetor_ordenado\vetor_ordenado.c -o vetor_ordenado\vetor_ordenado.o

:: Linka tudo
gcc -Wall -Wextra -std=c99 -g -o programa_musicas.exe main.o tratamento_musica\tratamento_musica.o vetor_ordenado\vetor_ordenado.o -lm

:: Executa se compilou com sucesso
if exist programa_musicas.exe (
    echo.
    cls
    echo Aguarde executando programa_musicas
    programa_musicas.exe
) else (
    echo.
    echo ERRO na compilacao!
)

pause