/*-----------------------------------------------------
TRABALHO 1 ICSF20-S73 ESTRUTURA DE DADOS
ESTUDANTE: GIOVANNI MIOTO
RA: 2603454
------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 14000000


typedef struct
{
    char *nome;
    int rg;
} Cliente;

typedef struct ListaClientes
{
    Cliente *clientes;
    int quantidade;
} ListaClientes;

//Funcao complementar para devolver posicao na lista sequencial
int calculaPosicaoSeq(ListaClientes *lista, int rg, int *comparacoesSeq, int *copiasRealizadasSeq)
{

    //procura na lista
    for (int i = 0; i < lista->quantidade; i++/*, (*comparacoesSeq)++*/)
    {
        //(*comparacoesSeq)++;
        if (lista->clientes[i].rg == rg)   //se encontrar o mesmo rg passado como parametro, devolve a posicao encontrada
        {
            return i;
        }
    }

    return -1; // RG nao encontrado
}

void insereNoFimDaListaSeq(ListaClientes *lista, char *nome, int rg, int *comparacoesSeq, int *copiasRealizadasSeq)
{
    clock_t inicio = clock();

    int posicao;

    *comparacoesSeq = 0;
    *copiasRealizadasSeq = 0;

    *comparacoesSeq++;
    //caso a lista esteja cheia, n adiciona cliente
    if (lista->quantidade >= MAX_CLIENTES)
    {
        printf("Lista cheia. Não é possível inserir mais elementos.\n");
        return;
    }

    (*copiasRealizadasSeq)++;
    lista->clientes[lista->quantidade].nome = strdup(nome); //adiciona nome
    (*copiasRealizadasSeq)++;
    lista->clientes[lista->quantidade].rg = rg; //adiciona rg
    (*copiasRealizadasSeq)++;

    clock_t fim = clock();
    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;


    //printf("Nome: %s, RG: %d, C(n):%d, M(n): %d, Tempo de execução: %f, P(n): %d\n\n", nome, rg, *comparacoesSeq, *copiasRealizadasSeq, tempoExecucao, lista->quantidade);
    lista->quantidade++;
}

void insereNoInicioDaListaSeq(ListaClientes *lista, char *nome, int rg, int *comparacoesSeq, int *copiasRealizadasSeq)
{
    int posicao;
    clock_t inicio = clock();
    *comparacoesSeq = 0;
    *copiasRealizadasSeq = 0;

    (*comparacoesSeq++);
    //caso a lista esteja cheia, n adiciona cliente
    if (lista->quantidade >= MAX_CLIENTES)
    {
        printf("Lista cheia. Não é possível inserir mais elementos.\n");
        return;
    }

    // Movendo todos os elementos uma posição para frente no vetor
    for (int i = lista->quantidade; i >= 0; i--, (*comparacoesSeq)++)
    {
        lista->clientes[i] = lista->clientes[i - 1];
        (*copiasRealizadasSeq)++;
    }

    // Inserindo o novo elemento no início da lista, nome e rg
    lista->clientes[0].nome = strdup(nome);
    (*copiasRealizadasSeq)++;
    lista->clientes[0].rg = rg;
    (*copiasRealizadasSeq)++;

    posicao = calculaPosicaoSeq(lista, rg, comparacoesSeq, copiasRealizadasSeq);
    clock_t fim = clock();
    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;


    (*copiasRealizadasSeq)++;
    printf("Nome: %s, RG: %d, C(n): %d, M(n): %d, Tempo de execução: %f, P(n): %d\n", nome, rg, *comparacoesSeq, *copiasRealizadasSeq, tempoExecucao, posicao);
    lista->quantidade++;
}

void insereNoNDaListaSeq(ListaClientes *lista, int posicao, char *nome, int rg, int *comparacoesSeq, int *copiasRealizadasSeq)
{

    clock_t inicio = clock();

    *comparacoesSeq = 0;
    *copiasRealizadasSeq = 0;

    (*comparacoesSeq++);
    //caso a lista esteja cheia, n adiciona cliente
    if (lista->quantidade >= MAX_CLIENTES)
    {
        printf("Lista cheia. Não é possível inserir mais elementos.\n");
        return;
    }

    (*comparacoesSeq)++;
    //posicoes menores que 1 ou maiores do que a quantidade atual sao invalidadas
    if (posicao < 0 || posicao > lista->quantidade)
    {
        printf("Posição inválida.\n");
        return;
    }

    //move os elementos depois da posicao inserida para a proxima posicao
    for (int i = lista->quantidade; i >= posicao; i--, (*comparacoesSeq)++)
    {
        (*copiasRealizadasSeq)++;
        lista->clientes[i] = lista->clientes[i - 1];
    }

    (*copiasRealizadasSeq)++;
    lista->clientes[posicao].nome = strdup(nome);
    (*copiasRealizadasSeq)++;
    lista->clientes[posicao].rg = rg;
    (*copiasRealizadasSeq)++;

    clock_t fim = clock();
    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    (*copiasRealizadasSeq)++;
    printf("Nome: %s, RG: %d, C(n):%d, M(n): %d, Tempo de execução: %f, P(n): %d\n", nome, rg, *comparacoesSeq, *copiasRealizadasSeq, tempoExecucao, posicao);
    lista->quantidade++;
}

void retiraNoFimDaListaSeq(ListaClientes *lista, int *comparacoesSeq, int *copiasRealizadasSeq)
{
    int posicao;
    clock_t inicio = clock();

    *comparacoesSeq = 0;
    *copiasRealizadasSeq = 0;

    (*comparacoesSeq)++;
    //caso a lista esteja vazia, n tenta remove nenhum cliente
    if (lista->quantidade == 0)
    {
        printf("Lista vazia. Não há elementos para remover.\n");
        return;
    }

    posicao = calculaPosicaoSeq(lista, lista->clientes[lista->quantidade-1].rg, comparacoesSeq, copiasRealizadasSeq);
    clock_t fim = clock();
    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    (*copiasRealizadasSeq)++;
    //remove cliente do final da lista
    lista->quantidade--;
    printf("Nome: %s, RG: %d, C(n):%d, M(n): %d, Tempo de execução: %f, P(n): %d\n", lista->clientes[lista->quantidade].nome, lista->clientes[lista->quantidade].rg, *comparacoesSeq, *copiasRealizadasSeq, tempoExecucao, posicao);
}

void retiraNoInicioDaListaSeq(ListaClientes *lista, int *comparacoesSeq, int *copiasRealizadasSeq)
{
    int posicao, i;
    clock_t inicio = clock();

    *comparacoesSeq = 0;
    *copiasRealizadasSeq = 0;

    (*comparacoesSeq)++;
    //caso a lista esteja vazia, n tenta remove nenhum cliente
    if (lista->quantidade == 0)
    {
        printf("Lista vazia. Não há elementos para remover.\n");
        return;
    }

    printf("Nome: %s, RG: %d, ", lista->clientes[0].nome, lista->clientes[0].rg);

    //move os elementos depois da posicao inserida para a posicao anterior do mesmo
    for (i = 0; i < lista->quantidade - 1; i++, (*comparacoesSeq)++)
    {
        lista->clientes[i] = lista->clientes[i + 1];
        (*copiasRealizadasSeq)++;
    }

    posicao = calculaPosicaoSeq(lista, lista->clientes[0].rg, comparacoesSeq, copiasRealizadasSeq);

    clock_t fim = clock();
    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    (*copiasRealizadasSeq)++;
    printf("C(n):%d, M(n): %d, Tempo de execução: %f, P(n): %d\n", *comparacoesSeq, *copiasRealizadasSeq, tempoExecucao, posicao);
    lista->quantidade--;
}

void retiraNoNDaListaSeq(ListaClientes *lista, int posicao, int *comparacoesSeq, int *copiasRealizadasSeq)
{
    int i;

    clock_t inicio = clock();

    *comparacoesSeq = 0;
    *copiasRealizadasSeq = 0;

    (*comparacoesSeq)++;
    //caso a lista esteja vazia, n tenta remove nenhum cliente
    if (lista->quantidade == 0)
    {
        printf("Lista vazia. Não há elementos para remover.\n");
        return;
    }
    (*comparacoesSeq)++;
    //posicoes menores que 1 ou maiores do que a quantidade atual sao invalidadas
    if (posicao < 0 || posicao >= lista->quantidade)
    {
        printf("Posição inválida.\n");
        return;
    }

    printf("Nome: %s, RG: %d, ", lista->clientes[posicao].nome, lista->clientes[posicao].rg);

    //move os elementos depois da posicao inserida para a posicao anterior do mesmo
    for ( i = posicao; i < lista->quantidade - 1; i++, (*comparacoesSeq)++)
    {
        (*copiasRealizadasSeq)++;
        lista->clientes[i] = lista->clientes[i + 1];
    }

    (*copiasRealizadasSeq)++;
    clock_t fim = clock();
    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    (*copiasRealizadasSeq)++;
    printf("C(n):%d, M(n): %d, Tempo de execução: %f, P(n): %d\n", *comparacoesSeq, *copiasRealizadasSeq, tempoExecucao, posicao);
    lista->quantidade--;
}

void procurarPorRGSeq(ListaClientes *lista, int rg, int *comparacoesSeq, int *copiasRealizadasSeq)
{
    int posicao, i;
    clock_t inicio = clock();

    *comparacoesSeq = 0;
    *copiasRealizadasSeq = 0;

    int encontrado = 0;

    //percorre a lista
    for (i = 0; i < lista->quantidade; i++, (*comparacoesSeq)++)
    {
        (*comparacoesSeq)++;
        if (lista->clientes[i].rg == rg)  //se o rg é o mesmo passado por parametro, retorna o cliente encontrado
        {
            encontrado = 1;
            break;
        }
    }

    (*comparacoesSeq)++;
    if (!encontrado)  //se nao encontrou
    {
        printf("Cliente com RG %d não encontrado na lista.\n", rg);
    }
    else
    {

        posicao = calculaPosicaoSeq(lista, rg, comparacoesSeq, copiasRealizadasSeq)+1;
        clock_t fim = clock();
        double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        printf("Nome: %s, RG: %d, C(n):%d, M(n): %d, Tempo de execução: %f, P(n): %d\n", lista->clientes[i].nome, lista->clientes[i].rg, *comparacoesSeq, *copiasRealizadasSeq, tempoExecucao, posicao);
    }
}
void procurarPorRGBin(ListaClientes *lista, int rg, int *comparacoesSeq, int *copiasRealizadasSeq){
    clock_t inicio = clock();
    int esquerda = 0;
    int direita = lista->quantidade - 1;
    int meio;
    int posicao;
    *comparacoesSeq = 0;
    *copiasRealizadasSeq = 0;

    (*comparacoesSeq)++;
    while (esquerda <= direita) {
        (*copiasRealizadasSeq)++;
        meio = (esquerda + direita) / 2;
        (*comparacoesSeq)++;
        if (lista->clientes[meio].rg == rg) {
            // Elemento encontrado
            posicao = calculaPosicaoSeq(lista, rg, comparacoesSeq, copiasRealizadasSeq)+1;
            clock_t fim = clock();
            double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

            printf("Nome: %s, RG: %d, C(n):%d, M(n): %d, Tempo de execução: %f, P(n): %d\n", lista->clientes[meio].nome, lista->clientes[meio].rg, *comparacoesSeq, *copiasRealizadasSeq, tempoExecucao, posicao);

            return;
        } else if (lista->clientes[meio].rg < rg) {
            (*comparacoesSeq)++;
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    // Se chegou aqui, o elemento não está presente na lista
    printf("Cliente com RG %d não encontrado.\n", rg);
}

void imprimirListaSeq(ListaClientes *lista, int *comparacoesSeq, int *copiasRealizadasSeq)
{

    *comparacoesSeq = 0;
    *copiasRealizadasSeq = 0;

    (*comparacoesSeq)++;
    if (lista->quantidade == 0)
    {
        printf("Lista vazia.\n");
        return;
    }

    //percorre e imprime a lista
    for (int i = 0; i < lista->quantidade; i++, (*comparacoesSeq)++)
    {
        printf("%s, %d\n", lista->clientes[i].nome, lista->clientes[i].rg);
    }
}


void lerListaDeArquivo( ListaClientes *lista, int* comparacoes, int* copiasRealizadas, const char *nomeArquivo)
{
    clock_t inicio = clock();
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return;
    }

    char linha[100];
    char nome[50];
    int rg;

    while (fscanf(arquivo, "%[^,], %d\n", nome, &rg) != EOF)
    {
        //insereNoFimDaListaSeq(lista, nome, rg,comparacoes, copiasRealizadas);
        insereNoFimDaListaSeq(lista, nome, rg,comparacoes, copiasRealizadas);
    }
    fclose(arquivo);

    clock_t fim = clock();
    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Lista lida do arquivo %s\n", nomeArquivo);
}

void salvarListaSeq(ListaClientes *lista)
{
    FILE *arquivo = fopen("clientes.txt", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve cada cliente no arquivo
    for (int i = 0; i < lista->quantidade; i++)
    {
        fprintf(arquivo, "%s, %d\n", lista->clientes[i].nome, lista->clientes[i].rg);
    }

    fclose(arquivo);

    printf("Lista de clientes salva com sucesso no arquivo 'clientes.txt'.\n");
}

void selectionSort(ListaClientes *lista, int* comparacoes, int* copiasRealizadas)
{
    *comparacoes = 0;
    *copiasRealizadas = 0;
    int i, j, k;
    Cliente temp;

    //Loop externo percorrendo a lista
    for (i = 0; i < lista->quantidade; i++, (*comparacoes)++)
    {
        (*copiasRealizadas)++;
        k = i;

        // Encontra o índice do menor elemento restante
        for (j = i + 1; j < lista->quantidade; j++, (*comparacoes)++)
        {
            //Compara com a posicao atual da lista e guarda a posicao do menor
            (*comparacoes)++;
            if (lista->clientes[j].rg < lista->clientes[k].rg)
            {
                (*copiasRealizadas)++;
                k = j;
            }
        }

        // Troca o menor elemento encontrado com o primeiro não ordenado
        (*comparacoes)++;
        if (k != i)
        {
            (*copiasRealizadas) += 3;
            temp = lista->clientes[i];
            lista->clientes[i] = lista->clientes[k];
            lista->clientes[k] = temp;
        }
    }
}

void insertionSort(ListaClientes *lista, int* comparacoes, int* copiasRealizadas) {
	for (int i = 1; i < lista->quantidade; i++, (*comparacoes)++) {

        (*copiasRealizadas)++;
		int j = i;

		(*comparacoes)++;
		while (j > 0 && lista->clientes[j].rg < lista->clientes[j-1].rg) {
            (*comparacoes)++;
            (*copiasRealizadas)+=3;
			Cliente aux = lista->clientes[j];
			lista->clientes[j] = lista->clientes[j - 1];
			lista->clientes[j - 1] = aux;
			j -= 1;
		}

	}
}

void bubbleSort(ListaClientes *lista, int* comparacoes, int* copiasRealizadas)
{
    *comparacoes = 0;
    *copiasRealizadas = 0;
    Cliente temp;
    int flag = 1, i;

    //Enqunto a lista tiver itens desordenados
    while(flag)
    {
        flag = 0;
        //Loop que percorre a lista completa
        for (i = 0; i < lista->quantidade-1; i++, (*comparacoes)++)
        {
            //Comparacao entre a posicao atual, e a próxima respectiva posição
            (*comparacoes)++;
            if(lista->clientes[i].rg > lista->clientes[i+1].rg)
            {
                (*copiasRealizadas) += 3;
                //Flag indicando que a lista ainda está sendo ordenada, caso essa flag nao seja ativada, indica que nenhum item mais foi ordenado
                flag = 1;
                temp = lista->clientes[i];
                lista->clientes[i] = lista->clientes[i+1];
                lista->clientes[i+1] = temp;
            }
        }
    }

}

void shellSort(ListaClientes *lista, int* comparacoes, int* copiasRealizadas)
{
    *comparacoes = 0;
    *copiasRealizadas = 0;
    Cliente temp;
    int i, j, h = 1;
    // Definindo o intervalo inicial h

    (*comparacoes)++;
    while (h < lista->quantidade / 3){
        (*comparacoes)++;
        (*copiasRealizadas);
        h = 3 * h + 1;
    }

    (*comparacoes)++;
    while (h >= 1)
    {
        (*comparacoes)++;
        // Loop sobre os elementos com intervalo h
        for (i = h; i < lista->quantidade; i++, (*comparacoes)++)
        {
            // Inserção dos elementos com comparação dentro do intervalo
            for (j = i; j >= h && lista->clientes[j - h].rg > lista->clientes[j].rg; j -= h, (*comparacoes)++)
            {
                (*copiasRealizadas) += 3;
                temp = lista->clientes[j];
                lista->clientes[j] = lista->clientes[j - h];
                lista->clientes[j - h] = temp;
            }
        }
        // Atualização do intervalo h
        (*copiasRealizadas)++;
        h /= 2;
    }
}

void quickSort(ListaClientes *lista, int iniVet, int fimVet, int* comparacoes, int* copiasRealizadas)
{
    Cliente temp, pivo;
    int i, j;

    i = iniVet;
    j = fimVet;

    (*copiasRealizadas)++;
    pivo = lista->clientes[(iniVet+fimVet)/2];

    (*comparacoes)++;
    while(i<=j)
    {
        (*comparacoes)++;
        (*comparacoes)++;
        while(lista->clientes[i].rg < pivo.rg)
        {
            (*comparacoes)++;
            (*copiasRealizadas)++;
            i = i + 1;
        }
        (*comparacoes)++;
        while(lista->clientes[j].rg > pivo.rg)
        {
            (*copiasRealizadas)++;
            j = j - 1;
        }
        (*comparacoes)++;
        if(i <= j)
        {
            (*copiasRealizadas) += 5;
            temp = lista->clientes[i];
            lista->clientes[i] = lista->clientes[j];
            lista->clientes[j] = temp;
            i = i + 1;
            j = j - 1;

        }

    }
    (*comparacoes)++;
    if(j > iniVet)
    {
        quickSort(lista, iniVet, j, comparacoes, copiasRealizadas);
    }
    (*comparacoes)++;
    if(i < fimVet)
    {
        quickSort(lista, i, fimVet, comparacoes, copiasRealizadas);
    }
}

void merge(ListaClientes *lista, int esquerda, int meio, int direita, int* comparacoes, int* copiasRealizadas)
{
    ListaClientes *helper = (ListaClientes*)malloc(sizeof(ListaClientes));
    helper->quantidade = direita - esquerda + 1;
    helper->clientes = (Cliente*)malloc(helper->quantidade * sizeof(Cliente));

    //Fazendo uma cópia do vetor original para helper
    for (int i = 0; i < helper->quantidade; i++, (*comparacoes)++)
    {
        (*copiasRealizadas)++;
        helper->clientes[i] = lista->clientes[esquerda + i];
    }

    (*copiasRealizadas)+=3;
    int i = 0, j = meio - esquerda + 1, k = esquerda;

    (*comparacoes)++;
    //Comparacao enquanto o índice i nao chega até o meio e j no chega até o fim da lista analisada
    while (i <= meio - esquerda && j <= direita - esquerda)
    {
        (*comparacoes)++;
        (*comparacoes)++;
        if (helper->clientes[i].rg <= helper->clientes[j].rg) //comparacao de qual posicao tem o menor elemento
        {
            (*copiasRealizadas)++;
            lista->clientes[k] = helper->clientes[i]; //faz a troca no vetor original
            i++; //anda posicao
        }
        else
        {
            (*copiasRealizadas)++;
            lista->clientes[k] = helper->clientes[j]; //faz a troca no vetor original
            j++; //anda posicao
        }
        k++; //anda posicao no vetor original
    }

    (*comparacoes)++;
    //Caso o vetor de posicoes j já tenha sido todo realocado na ordenação, preenche os restantes indices i
    while (i <= meio - esquerda)
    {
        (*comparacoes)++;
        (*copiasRealizadas)++;
        lista->clientes[k] = helper->clientes[i];
        i++;
        k++;
    }
    //Caso o vetor de posicoes i já tenha sido todo realocado na ordenação, preenche os restantes indices j
    (*comparacoes)++;
    while (j <= direita - esquerda)
    {
        (*comparacoes)++;
        (*copiasRealizadas)++;
        lista->clientes[k] = helper->clientes[j];
        j++;
        k++;
    }

    //desalocacao do vetor copia
    free(helper->clientes);
    free(helper);
}

void mergeSort(ListaClientes *lista, int esquerda, int direita, int* comparacoes, int* copiasRealizadas)
{
    (*comparacoes)++;
    if (esquerda >= direita)
        return;

    (*copiasRealizadas)++;
    int meio = (esquerda + direita) / 2;

    mergeSort(lista, esquerda, meio, comparacoes, copiasRealizadas);
    mergeSort(lista, meio + 1, direita, comparacoes, copiasRealizadas);

    merge(lista, esquerda, meio, direita, comparacoes, copiasRealizadas);
}


int main()
{
    FILE *arquivo;
    ListaClientes *lista = (ListaClientes*)malloc(sizeof(ListaClientes));
    lista->clientes = (Cliente*)malloc(MAX_CLIENTES*sizeof(Cliente));
    lista->quantidade = 0;
    int comparacoes = 0;
    int copiasRealizadas = 0;
    int comparacoesSeq = 0;
    int copiasRealizadasSeq = 0;
    int opcao, opcaoOrdenacao;
    double tempoProcessamento;
    clock_t inicio=0, fim=0;

    do
    {
        // Menu de opções
        printf("\nSelecione uma opção:\n");
        printf("1. Inserir no final da lista\n");
        printf("2. Inserir no início da lista\n");
        printf("3. Inserir na posição N da lista\n");
        printf("4. Remover do final da lista\n");
        printf("5. Remover do início da lista\n");
        printf("6. Remover da posição N da lista\n");
        printf("7. Procurar por RG SEQUENCIAL\n");
        printf("8. Procurar por RG BINARIA\n");
        printf("9. Imprimir lista\n");
        printf("10. Salvar lista em um arquivo\n");
        printf("11. Ler lista do arquivo\n");
        printf("12. Ordenar\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        char nome[100];
        int rg, posicao;
        // Executa a opção escolhida pelo usuário
        switch (opcao)
        {
        case 1:
            printf("NOME: ");
            scanf("%s", nome);
            printf("RG: ");
            scanf("%d", &rg);

            printf("\n\nINSERIDO NA LISTA SEQUENCIAL: \n\n");
            insereNoFimDaListaSeq(lista, nome, rg, &comparacoesSeq, &copiasRealizadasSeq);
            break;
        case 2:
            printf("NOME: ");
            scanf("%s", nome);
            printf("RG: ");
            scanf("%d", &rg);

            printf("\n\nINSERIDO NA LISTA SEQUENCIAL: \n\n");
            insereNoInicioDaListaSeq(lista, nome, rg, &comparacoesSeq, &copiasRealizadasSeq);
            break;
        case 3:
            printf("NOME: ");
            scanf("%s", nome);
            printf("RG: ");
            scanf("%d", &rg);
            printf("POSICAO: ");
            scanf("%d", &posicao);

            printf("\n\nINSERIDO NA LISTA SEQUENCIAL: \n\n");
            insereNoNDaListaSeq(lista, posicao, nome, rg, &comparacoesSeq, &copiasRealizadasSeq);
            break;
        case 4:
            printf("\n\nRETIRADO DA LISTA SEQUENCIAL: \n\n");
            retiraNoFimDaListaSeq(lista, &comparacoesSeq, &copiasRealizadasSeq);
            break;
        case 5:
            printf("\n\nRETIRADO DA LISTA SEQUENCIAL: \n\n");
            retiraNoInicioDaListaSeq(lista, &comparacoesSeq, &copiasRealizadasSeq);
            break;
        case 6:
            printf("POSICAO: ");
            scanf("%d", &posicao);
            printf("\n\nRETIRADO DALISTA SEQUENCIAL: \n\n");
            retiraNoNDaListaSeq(lista, posicao, &comparacoesSeq, &copiasRealizadasSeq);
            break;
        case 7:
            printf("RG: ");
            scanf("%d", &rg);
            printf("\n\nLISTA SEQUENCIAL: \n\n");
            procurarPorRGSeq(lista, rg, &comparacoesSeq, &copiasRealizadasSeq);
            break;
        case 8:
            printf("RG: ");
            scanf("%d", &rg);
            printf("\n\nLISTA SEQUENCIAL: \n\n");
            procurarPorRGBin(lista, rg, &comparacoesSeq, &copiasRealizadasSeq);
            break;
        case 9:
            printf("\n\nLISTA SEQUENCIAL: \n\n");
            imprimirListaSeq(lista, &comparacoesSeq, &copiasRealizadasSeq);
            break;
        case 10:
            salvarListaSeq(lista);
            break;
        case 11:
            // Abre um arquivo TEXTO para LEITURA
            lerListaDeArquivo(lista, &comparacoes, &copiasRealizadas, "NomeRG10K.txt");
            break;
        case 12:
            do
            {
                printf("\nEscolha o método de ordenação:\n");
                printf("1. Selection Sort\n");
                printf("2. Insertion Sort\n");
                printf("3. Bubble Sort\n");
                printf("4. Shell Sort\n");
                printf("5. Quick Sort\n");
                printf("6. Merge Sort\n");
                printf("0. Voltar\n");
                printf("Opção: ");
                scanf("%d", &opcaoOrdenacao);

                switch (opcaoOrdenacao)
                {
                case 1:
                    inicio = clock();
                    selectionSort(lista, &comparacoes, &copiasRealizadas);
                    fim = clock();
                    tempoProcessamento = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                    printf("\nC(n): %d, M(N) %d, Tempo: %f\n", comparacoes, copiasRealizadas, tempoProcessamento);
                    opcaoOrdenacao = 0;
                    break;
                case 2:
                    inicio = clock();
                    insertionSort(lista, &comparacoes, &copiasRealizadas);
                    fim = clock();
                    tempoProcessamento = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                    printf("\nC(n): %d, M(N) %d, Tempo: %f\n", comparacoes, copiasRealizadas, tempoProcessamento);
                    opcaoOrdenacao = 0;
                    break;
                case 3:
                    inicio = clock();
                    bubbleSort(lista, &comparacoes, &copiasRealizadas);
                    fim = clock();
                    tempoProcessamento = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                    printf("\nC(n): %d, M(N) %d, Tempo: %f\n", comparacoes, copiasRealizadas, tempoProcessamento);
                    opcaoOrdenacao = 0;
                    break;
                case 4:
                    inicio = clock();
                    shellSort(lista, &comparacoes, &copiasRealizadas);
                    fim = clock();
                    tempoProcessamento = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                    printf("\nC(n): %d, M(N) %d, Tempo: %f\n", comparacoes, copiasRealizadas, tempoProcessamento);
                    opcaoOrdenacao = 0;
                    break;
                case 5:
                    inicio = clock();
                    comparacoes = 0;
                    copiasRealizadas = 0;
                    quickSort(lista, 0, lista->quantidade - 1, &comparacoes, &copiasRealizadas);
                    fim = clock();
                    tempoProcessamento = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                    printf("\nC(n): %d, M(N) %d, Tempo: %f\n", comparacoes, copiasRealizadas, tempoProcessamento);
                    opcaoOrdenacao = 0;
                    break;
                case 6:
                    inicio = clock();
                    comparacoes = 0;
                    copiasRealizadas = 0;
                    mergeSort(lista, 0, lista->quantidade - 1, &comparacoes, &copiasRealizadas);
                    fim = clock();
                    tempoProcessamento = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                    printf("\nC(n): %d, M(N) %d, Tempo: %f\n", comparacoes, copiasRealizadas, tempoProcessamento);
                    opcaoOrdenacao = 0;
                    break;
                case 0:
                    printf("Voltando...\n");
                    break;
                default:
                    printf("Opção inválida!\n");
                    break;
                }
            }
            while (opcaoOrdenacao != 0);
            break;

        case 0:
            printf("Saindo...\n");
            for (int i = 0; i < lista->quantidade; i++)
            {
                free(lista->clientes[i].nome);
            }
            free(lista);
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    }
    while (opcao != 0);

    return 0;
}
