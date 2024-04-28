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

void selectionSort(ListaClientes *lista)
{
    int i, j, k;
    Cliente temp;

    for (i = 0; i < lista->quantidade; i++)
    {
        k = i;

        // Encontra o índice do menor elemento restante
        for (j = i + 1; j < lista->quantidade; j++)
        {
            if (lista->clientes[j].rg < lista->clientes[k].rg)
            {
                k = j;
            }
        }

        // Troca o menor elemento encontrado com o primeiro não ordenado
        if (k != i)
        {
            temp = lista->clientes[i];
            lista->clientes[i] = lista->clientes[k];
            lista->clientes[k] = temp;
        }
    }
}

void insertionSort(ListaClientes *lista)
{
    int i, j, k;
    Cliente temp;

    for (i = 1; i < lista->quantidade; i++)
    {
        for(j = 0; j<i; j++)
        {
            if(lista->clientes[j].rg > lista->clientes[i].rg)
            {
                temp = lista->clientes[j];
                lista->clientes[j] = lista->clientes[i];
                lista->clientes[i] = temp;
            }
        }
    }
}

void bubbleSort(ListaClientes *lista)
{
    Cliente temp;
    int flag = 1, i;

    while(flag)
    {
        flag = 0;
        for (i = 0; i < lista->quantidade-1; i++)
        {
            if(lista->clientes[i].rg > lista->clientes[i+1].rg)
            {
                flag = 1;
                temp = lista->clientes[i];
                lista->clientes[i] = lista->clientes[i+1];
                lista->clientes[i+1] = temp;
            }
        }
    }

}

void shellSort(ListaClientes *lista)
{
    Cliente temp;
    int i, j, h = 1;
    // Definindo o intervalo inicial h
    while (h < lista->quantidade / 3)
        h = 3 * h + 1;

    while (h >= 1)
    {
        // Loop sobre os elementos com intervalo h
        for (i = h; i < lista->quantidade; i++)
        {
            // Inserção dos elementos com comparação dentro do intervalo
            for (j = i; j >= h && lista->clientes[j - h].rg > lista->clientes[j].rg; j -= h)
            {
                temp = lista->clientes[j];
                lista->clientes[j] = lista->clientes[j - h];
                lista->clientes[j - h] = temp;
            }
        }
        // Atualização do intervalo h
        h /= 2;
    }
}

void quickSort(ListaClientes *lista, int iniVet, int fimVet)
{
    Cliente temp, pivo;
    int i, j;

    i = iniVet;
    j = fimVet;

    pivo = lista->clientes[(iniVet+fimVet)/2];

    while(i<=j)
    {

        while(lista->clientes[i].rg < pivo.rg)
        {
            i = i + 1;
        }

        while(lista->clientes[j].rg > pivo.rg)
        {
            j = j - 1;
        }
        if(i <= j)
        {
            temp = lista->clientes[i];
            lista->clientes[i] = lista->clientes[j];
            lista->clientes[j] = temp;
            i = i + 1;
            j = j - 1;
        }

    }
    if(j > iniVet)
    {
        quickSort(lista, iniVet, j);
    }
    if(i < fimVet)
    {
        quickSort(lista, i, fimVet);
    }

}

void merge(ListaClientes *lista, int esquerda, int meio, int direita)
{
    ListaClientes *helper = (ListaClientes*)malloc(sizeof(ListaClientes));
    helper->quantidade = direita - esquerda + 1; // Corrigindo a alocação de memória
    helper->clientes = (Cliente*)malloc(helper->quantidade * sizeof(Cliente));

    for (int i = 0; i < helper->quantidade; i++)
    {
        helper->clientes[i] = lista->clientes[esquerda + i];
    }

    int i = 0, j = meio - esquerda + 1, k = esquerda;

    while (i <= meio - esquerda && j <= direita - esquerda)
    {
        if (helper->clientes[i].rg <= helper->clientes[j].rg)
        {
            lista->clientes[k] = helper->clientes[i];
            i++;
        }
        else
        {
            lista->clientes[k] = helper->clientes[j];
            j++;
        }
        k++;
    }

    while (i <= meio - esquerda)
    {
        lista->clientes[k] = helper->clientes[i];
        i++;
        k++;
    }

    free(helper->clientes);
    free(helper);
}

void mergeSort(ListaClientes *lista, int esquerda, int direita)
{
    if (esquerda >= direita)
        return;

    int meio = (esquerda + direita) / 2;

    mergeSort(lista, esquerda, meio); // Corrigindo a chamada recursiva
    mergeSort(lista, meio + 1, direita);

    merge(lista, esquerda, meio, direita);
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
        printf("7. Procurar por RG\n");
        printf("8. Imprimir lista\n");
        printf("9. Salvar lista em um arquivo\n");
        printf("10. Ler lista do arquivo\n");
        printf("11. Ordenar\n");
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
            printf("\n\nLISTA SEQUENCIAL: \n\n");
            imprimirListaSeq(lista, &comparacoesSeq, &copiasRealizadasSeq);
            break;
        case 9:
            salvarListaSeq(lista);
            break;
        case 10:
            // Abre um arquivo TEXTO para LEITURA
            lerListaDeArquivo(lista, &comparacoes, &copiasRealizadas, "NomeRG100M.txt");
            break;
        case 11:
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
                    selectionSort(lista);
                    opcaoOrdenacao = 0;
                    break;
                case 2:
                    insertionSort(lista);
                    opcaoOrdenacao = 0;
                    break;
                case 3:
                    bubbleSort(lista);
                    opcaoOrdenacao = 0;
                    break;
                case 4:
                    shellSort(lista);
                    opcaoOrdenacao = 0;
                    break;
                case 5:
                    quickSort(lista, 0, lista->quantidade - 1);
                    opcaoOrdenacao = 0;
                    break;
                case 6:
                    mergeSort(lista, 0, lista->quantidade - 1);
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
