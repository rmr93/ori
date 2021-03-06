#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreB.h"

arvoreB criar_arvoreB(void) {
    arvoreB b;

    b = calloc(4, sizeof(struct NO_B));
    b->folha = 1;
    b->nkeys = 0;

    return b;
}

void remover_arvoreB(arvoreB b) {
	int i;

    if(!b->folha) {
		
        for(i = 0; i < b->nkeys + 1; i++) {
            remover_arvoreB(b->filhos[i]);
        }
    }

    free(b);
}

int searchKey(int n, int *b, int key) {
    int lo; 
    int hi; 
    int mid; 
	int *a;
	a = malloc(sizeof(int*));
	a = b;	

    lo = -1;
    hi = n;
	
    while(lo + 1 < hi) {
        mid = (lo+hi)/2;
        if(a[mid] == key) {
            return mid;
        } else if(a[mid] < key) {
            lo = mid;
			//hi = mid+1;
        } else {
            hi = mid;
        }
    }
    return hi;
}

int procurar_arvoreB(arvoreB b, int key) {
    int pos;

    // verifica se é vazia
    if(b->nkeys == 0) {
        return 0;
    }

    pos = searchKey(b->nkeys, b->keys, key);

    if(pos < b->nkeys && b->keys[pos] == key) {
        return 1;
    } else {
        return(!b->folha && procurar_arvoreB(b->filhos[pos], key));
    }
}

arvoreB inserir_arvoreBInternal(arvoreB b, int key, int *median) {
    int pos;
    int mid;
    arvoreB b2;

	//printf("b->nkeys = %d\n", b->nkeys);
    pos = searchKey(b->nkeys, b->keys, key);

    if(pos < b->nkeys && b->keys[pos] == key) {
        return 0;
    }

    if(b->folha) {

        // todos acima de pos se movem um espaço pra cima
        memmove(&b->keys[pos+1], &b->keys[pos], sizeof(*(b->keys)) * (b->nkeys - pos));
        b->keys[pos] = key;
        b->nkeys++;

    } else {

        // insere um nó filho
		if(!b->filhos[pos])
			b->filhos[pos] = criar_arvoreB();
        b2 = inserir_arvoreBInternal(b->filhos[pos], key, &mid);
        
        if(b2) {

            memmove(&b->keys[pos+1], &b->keys[pos], sizeof(*(b->keys)) * (b->nkeys - pos));
            // novo nó entra em pos+1
            memmove(&b->filhos[pos+2], &b->filhos[pos+1], sizeof(*(b->keys)) * (b->nkeys - pos));

            b->keys[pos] = mid;
            b->filhos[pos+1] = b2;
            b->nkeys++;
        }
    }

    // é feito a quebra
    if(b->nkeys >= MAX_KEYS) {
        mid = b->nkeys/2;

        *median = b->keys[mid];

        b2 = malloc(sizeof(struct NO_B));

        b2->nkeys = b->nkeys - mid - 1;
        b2->folha = b->folha;

        memmove(b2->keys, &b->keys[mid+1], sizeof(*(b->keys)) * b2->nkeys);
        if(!b->folha) {
            memmove(b2->filhos, &b->filhos[mid+1], sizeof(*(b->filhos)) * (b2->nkeys + 1));
        }

        b->nkeys = mid;
		//puts("=Quebra=");
        return b2;
    } else {
		//puts("+nada+");
        return 0;
    }
}

void inserir_arvoreB(arvoreB b, int key) {
    arvoreB b1;   // novo nó esquerdo
    arvoreB b2;   // novo nó direito
    int median;

    b2 = inserir_arvoreBInternal(b, key, &median);

    if(b2) { //puts("+=QUEBRA+=");

        b1 = malloc(sizeof(*b1));

        memmove(b1, b, sizeof(*b));

        b->nkeys = 1;
        b->folha = 0;
        b->keys[0] = median;
        b->filhos[0] = b1;
        b->filhos[1] = b2;
    }
}

void imprimir_arvoreB (arvoreB b) {
  int i;
	arvoreB B = criar_arvoreB();
	B = b;
  if (B != NULL) {
	//printf("========%d\n", b->nkeys);
    for (i = 0; i < B->nkeys; i++) {
      imprimir_arvoreB (B->filhos[i]);
    }
    imprimir_arvoreB (B->filhos[B->nkeys]);
  }
}


arvoreB *buscar_arvoreB (arvoreB b, int x) {
  int i;
  if (b == NULL) 
	return NULL;
  for (i = 0; i < b->nkeys && b->keys[i] < x; i++);
  if (i == b->nkeys) 
	return buscar_arvoreB(b->filhos[i], x);
  if (b->keys[i] == x) 
	return b;
  return buscar_arvoreB(b->filhos[i], x);
}

