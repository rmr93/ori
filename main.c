#include <arquivo.h>
#include <arvore.h>
#include <locale.h>

int main(void)
{
    srand(time(NULL));

    // Define a língua portuguesa como local
    setlocale(LC_ALL, "Portuguese");

    /*// Teste de gerador randômico
    for(i = 0; i < 10; i++) {
        printf("%d\n", gerador_nome_rand());
    }*/

    // Teste de inserção e busca
    no *arv = NULL;
    no *ab = NULL;

    int i, rand;
    for (i = 0; i < 5; i++) {
        rand = gerador_nome_rand();
        arv = inserir(arv, rand);
    }

    imprimir(arv);

    ab = busca(arv, rand);
    printf("\n\nBusca: %d\n\n", ab->nome);

    return 0;
}
