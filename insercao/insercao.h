#ifndef INSERCAO_H
#define INSERCAO_H

#include "../avl/AVL.h"
#include "../binary_tree/BinaryTree.h"
#include "../estrutura_freq/AVLFreq.h"
#include "../estrutura_freq/BinaryTreeFreq.h"
#include "../general.h"
#include "../vetor_ordenado/vetor_ordenado.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

void inserir_estruturas(nodeAVL **nodeavl, nodeAVLFreq **nodeAvlFreq,
                        node **nodeBT, nodeFreq **nodeBTFreq,
                        VetorOrdenado **vec, float *tAVL, float *tBT,
                        float *tVec, char **musica);
inf *buscar_informacao(nodeAVL **nodeavl, nodeAVLFreq **nodeAvlFreq,
                       node **nodeBT, nodeFreq **nodeBTFreq,
                       VetorOrdenado **vec, float *tAVL, float *tBT,
                       float *tVec, char *palavra, int *freq);

#endif
