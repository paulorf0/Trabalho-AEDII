#ifndef MENU_H
#define MENU_H

#include "../avl/AVL.h"
#include "../binary_tree/BinaryTree.h"
#include "../estrutura_freq/AVLFreq.h"
#include "../estrutura_freq/BinaryTreeFreq.h"
#include "../insercao/insercao.h"
#include "../tratamento_musica/tratamento_musica.h"
#include "../vetor_ordenado/vetor_ordenado.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

void menu(nodeAVL **nodeavl, node **nodeBT, VetorOrdenado **vec,
          nodeAVLFreq **nodeAvlF, nodeFreq **nodeF);

#endif
