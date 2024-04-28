/*-----------------------------------------------------
TRABALHO 1 ICSF20-S73 ESTRUTURA DE DADOS
ESTUDANTE: GIOVANNI MIOTO
RA: 2603454
------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Lista
{
    char *nome;
    int rg;
    struct Lista *proximo;
    struct Lista *anterior;
} Lista;

Lista* criaNo(char *nome, int rg, int* copiasRealizadas)
{
    Lista* novoNo = (Lista*) malloc(sizeof(Lista));
    if (novoNo == NULL)
    {
        printf("Erro ao alocar memória para o novo nó\n");
        exit(1);
    }
    novoNo->nome = strdup(nome);
    novoNo->rg = rg;
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;
    return novoNo;
}

int calculaPosicaoEnc(Lista** primeiro, Lista** atual, int *comparacoes, int *copiasRealizadas)
{
    int cont = 0;
    Lista *noTemporario =  *primeiro;

    //(*comparacoes)++;
    //verifica se o no nao esta nulo e nao é o mesmo que o atual
    while (noTemporario != NULL && noTemporario != *atual)
    {
        //passa para o proximo no
        noTemporario = noTemporario->proximo;
        cont++;
        //(*comparacoes)++;
        //(*copiasRealizadas)++;
    }
    return cont;
}

void insereNoFimDaListaEnc(Lista** primeiro, Lista** atual, char *nome, int rg, int* comparacoes, int* copiasRealizadas, int *tamLista)
{
    clock_t inicio = clock();
    int posicao=-1;
    *comparacoes = 0;
    *copiasRealizadas = 0;
    (*tamLista)++;

    Lista *novoNo = criaNo(nome, rg, copiasRealizadas); //criacao novo no

    (*comparacoes)++;
    if (*primeiro == NULL)
    {
        *primeiro = novoNo; //se n existe um primeiro no, recebe o novo no como primeiro
        (*copiasRealizadas)++;
        *atual = novoNo;
        (*copiasRealizadas)++;
    }
    else
    {
        (*comparacoes)++;
        novoNo->anterior = *atual;
        (*copiasRealizadas)++;
        (*atual)->proximo = novoNo;
        (*copiasRealizadas)++;
    }

    *atual = novoNo; // Atualiza o ponteiro atual para apontar para o novo último nó inserido
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    //printf("Nome: %s, RG: %d, C(n):%d, M(n):%d, Tempo de execução: %f, P(n):%d\n", (*atual)->nome, (*atual)->rg,*comparacoes,*copiasRealizadas, tempo, *tamLista);
}

void insereNoInicioDaListaEnc(Lista** primeiro, Lista** atual, char *nome, int rg, int* comparacoes, int* copiasRealizadas, int *tamLista)
{
    clock_t inicio = clock();
    int posicao=-1;
    *comparacoes = 0;
    *copiasRealizadas = 0;
    (*tamLista)++;

    (*comparacoes)++;
    Lista *novoNo = criaNo(nome, rg, copiasRealizadas); //criacao novo no

    (*comparacoes)++;
    if (*primeiro == NULL)
    {
        *primeiro = novoNo; //se n existe um primeiro no, recebe o novo no como primeiro
        (*copiasRealizadas)++;
        *atual = novoNo;
        (*copiasRealizadas)++;
    }
    else
    {
        (*comparacoes)++;
        novoNo->proximo = *primeiro;
        (*copiasRealizadas)++;
        (*primeiro)->anterior = novoNo;
        (*copiasRealizadas)++;
        *primeiro = novoNo;
        (*copiasRealizadas)++;
    }

    posicao = calculaPosicaoEnc(primeiro, primeiro, comparacoes, copiasRealizadas);

    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Nome: %s, RG: %d, C(n):%d, M(n):%d, Tempo de execução: %f, P(n):%d\n\n", (*primeiro)->nome, (*primeiro)->rg,*comparacoes,*copiasRealizadas, tempo, posicao);
}

void insereNoNDaListaEnc(Lista** primeiro, Lista** atual, char *nome, int rg, int posicao, int* comparacoes, int* copiasRealizadas, int *tamLista)
{
    clock_t inicio = clock();

    *comparacoes = 0;
    *copiasRealizadas = 0;
    (*tamLista)++;

    Lista *novoNo = criaNo(nome, rg, copiasRealizadas);
    Lista *noTemporario = NULL;

    (*comparacoes)++;
    (*comparacoes)++;
    if (*primeiro == NULL)
    {
        *primeiro = novoNo; //se n existe um primeiro no, recebe o novo no como primeiro
        (*copiasRealizadas)++;
        *atual = novoNo;
        (*copiasRealizadas)++;
    }

    (*comparacoes)++;
    if (posicao <= 0)   // Se posicao for 0 ou negativo, insere no início
    {
        novoNo->proximo = *primeiro;
        (*copiasRealizadas)++;
        (*primeiro)->anterior = novoNo;
        (*copiasRealizadas)++;
        *primeiro = novoNo;
        (*copiasRealizadas)++;
        clock_t fim = clock();
        double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Nome: %s, RG: %d, C(n):%d, M(n):%d, Tempo de execução: %f, P(n):%d\n\n", novoNo->nome, novoNo->rg,*comparacoes,*copiasRealizadas, tempo,posicao);
        return;
    }

    int cont = 0;
    noTemporario = *primeiro;

    // Percorre a lista até a posição desejada
    (*comparacoes)++;
    while (noTemporario != NULL && cont < posicao)
    {
        noTemporario = noTemporario->proximo;
        (*copiasRealizadas)++;
        cont++;
        (*comparacoes)++;
    }

    // Insere o novo nó na posição encontrada
    (*comparacoes)++;
    if (noTemporario != NULL)   // Se encontrou a posição no meio da lista
    {
        novoNo->proximo = noTemporario;
        (*copiasRealizadas)++;
        novoNo->anterior = noTemporario->anterior;
        (*copiasRealizadas)++;
        noTemporario->anterior->proximo = novoNo;
        (*copiasRealizadas)++;
        noTemporario->anterior = novoNo;
        (*copiasRealizadas)++;
    }
    else   // Se chegou ao final da lista
    {
        (*comparacoes)++;
        Lista *ultimo = *primeiro;
        (*copiasRealizadas)++;
        (*comparacoes)++;
        while (ultimo->proximo != NULL)
        {
            ultimo = ultimo->proximo;
            (*copiasRealizadas)++;
        }
        novoNo->anterior = ultimo;
        ultimo->proximo = novoNo;
        (*copiasRealizadas)++;
    }
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Nome: %s, RG: %d, C(n):%d, M(n):%d, Tempo de execução: %f, P(n):%d\n\n", novoNo->nome, novoNo->rg,*comparacoes,*copiasRealizadas, tempo,posicao);
}

void retiraNoFimDaListaEnc(Lista** primeiro, Lista** atual, int* comparacoes, int* copiasRealizadas, int *tamLista)
{
    clock_t inicio = clock();
    int posicao = -1;
    *comparacoes = 0;
    *copiasRealizadas = 0;
    (*tamLista)--;

    (*comparacoes)++;
    if (*primeiro == NULL)
    {
        printf("Não há nós para excluir\n");
        return;
    }

    (*comparacoes)++;
    if ((*primeiro)->proximo == NULL)//se há um unico no
    {
        free(*primeiro);
        *primeiro = NULL;
        (*copiasRealizadas)++;
        printf("Removido o único nó\n");
        clock_t fim = clock();
        double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Tempo de execução de retiraNoFimDaLista: %f segundos\n\n", tempo);
        return;
    }

    Lista *ultimo = *atual; //salva um ponteiro temporario para o ultimo para fins de impressao
    (*copiasRealizadas)++;

    *atual = (*atual)->anterior; // Atualiza *atual para apontar para o penúltimo nó
    (*copiasRealizadas)++;

    // Remove o último nó da lista
    (*atual)->proximo = NULL;
    (*copiasRealizadas)++;

    posicao = calculaPosicaoEnc(primeiro, &ultimo, comparacoes, copiasRealizadas);
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Nome: %s, RG: %d, C(n):%d, M(n):%d, Tempo de execução: %f, P(n):%d\n\n", ultimo->nome, ultimo->rg,*comparacoes,*copiasRealizadas, tempo, posicao);
    free(ultimo);
}

void retiraNoInicioDaListaEnc(Lista** primeiro, Lista** atual, int* comparacoes, int* copiasRealizadas, int *tamLista)
{
    clock_t inicio = clock();
    int posicao = -1;

    *comparacoes = 0;
    *copiasRealizadas = 0;
    (*tamLista)--;

    (*comparacoes)++;
    if (*primeiro == NULL) //se n existe nenhum no
    {
        printf("Não há nós para excluir\n");
        return;
    }

    (*comparacoes)++;
    if ((*primeiro)->proximo == NULL) //caso seja o unico no
    {
        free(*primeiro);
        *primeiro = NULL;
        printf("Removido o único nó\n");
        (*comparacoes)++;
        (*copiasRealizadas)++;
        clock_t fim = clock();
        double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Tempo de execução de retiraNoInicioDaLista: %f segundos\n\n", tempo);
        return;
    }

    Lista *temporario = *primeiro; //salva um ponteiro temporario para o ultimo para fins de impressao
    (*copiasRealizadas)++;

    *primeiro = (*primeiro)->proximo; // Atualiza *atual para apontar para o penúltimo nó
    (*copiasRealizadas)++;

    // Remove o último nó da lista
    (*primeiro)->anterior = NULL;
    (*copiasRealizadas)++;

    posicao = calculaPosicaoEnc(primeiro, primeiro, comparacoes, copiasRealizadas);
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Nome: %s, RG: %d, C(n):%d, M(n):%d, Tempo de execução: %f, P(n):%d\n\n", temporario->nome, temporario->rg,*comparacoes,*copiasRealizadas, tempo, posicao);
    free(temporario);
}

void retiraNoNDaListaEnc(Lista** primeiro, Lista** atual, int posicao, int* comparacoes, int* copiasRealizadas, int *tamLista)
{
    clock_t inicio = clock();
    *comparacoes = 0;
    *copiasRealizadas = 0;
    (*tamLista)--;

    int cont = 0;
    Lista *noTemporario = NULL;

    noTemporario = *primeiro;
    (*copiasRealizadas)++;

    (*comparacoes)++;
    while (noTemporario != NULL && cont < posicao)//percorre a lista até a posicao desejada
    {
        noTemporario = noTemporario->proximo;
        cont++;
        (*comparacoes)++;
        (*copiasRealizadas)++;
    }

    (*copiasRealizadas)++;
    noTemporario->anterior->proximo = noTemporario->proximo; // Amarra anterior no proximo no
    (*copiasRealizadas)++;
    noTemporario->proximo->anterior = noTemporario->anterior; // Amarra proximo no anterior

    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Nome: %s, RG: %d, C(n):%d, M(n):%d, Tempo de execução: %f, P(n):%d\n\n", noTemporario->nome, noTemporario->rg,*comparacoes,*copiasRealizadas, tempo, posicao);
    free(noTemporario);//retira no que estava no meio
}

void imprimeListaEnc(Lista* primeiro, int *comparacoes, int *copiasRealizadas)
{

    *comparacoes = 0;
    *copiasRealizadas = 0;

    Lista *atual = primeiro;
    //imprime enquanto nao encontrar o ultimo no(nulo)
    while (atual != NULL)
    {
        printf("%s, %d\n", atual->nome, atual->rg);
        atual = atual->proximo;
        *copiasRealizadas++;
        *comparacoes++;
    }
}

void lerListaDeArquivo(Lista **clientes, Lista** atual, int* comparacoes, int* copiasRealizadas, const char *nomeArquivo, int *tamLista)
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
        insereNoFimDaListaEnc(clientes, atual, nome, rg,comparacoes, copiasRealizadas, tamLista);
    }
    fclose(arquivo);

    clock_t fim = clock();
    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Lista lida do arquivo %s\n", nomeArquivo);
}

void procuraNoPeloRGEnc(Lista** primeiro, int rg, int* comparacoes, int* copiasRealizadas)
{
    clock_t inicio = clock();
    int posicao = -1;
    *comparacoes = 0;
    *copiasRealizadas = 0;

    Lista *noTemporario = NULL;

    noTemporario = *primeiro;
    (*copiasRealizadas)++;

    (*comparacoes)++;
    while (noTemporario != NULL && noTemporario->rg != rg) //percorre lista enquanto nao encontra o rg passado como parametro
    {
        noTemporario = noTemporario->proximo;
        (*copiasRealizadas)++;
        (*comparacoes)++;
    }
    (*comparacoes)++;
    if(noTemporario == NULL) //caso percorreu a lista inteiro e nao encontrou o cliente
    {
        printf("\n\n\nCliente nao encontrado\n\n\n");
        clock_t fim = clock();
        double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Tempo de execução de procuraNoPeloRG: %f segundos\n\n", tempo);
        return;
    }

    posicao = calculaPosicaoEnc(primeiro, &noTemporario, comparacoes, copiasRealizadas)+1;

    // Remove o último nó da lista
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Nome: %s, RG: %d, C(n):%d, M(n):%d, Tempo de execução: %f, P(n):%d\n\n", noTemporario->nome, noTemporario->rg,*comparacoes,*copiasRealizadas, tempo, posicao);
}

void salvarListaEnc(Lista *primeiro)
{
    FILE *arquivo2;
    arquivo2 = fopen("ListaNomes.txt", "w"); // Abre o arquivo para escrita, sobrescrevendo o conteúdo se ele já existir

    if (arquivo2 == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    Lista *atual = primeiro;
    while (atual != NULL)
    {
        if (fprintf(arquivo2, "%s, %d\n", atual->nome, atual->rg) < 0)   // Verifica se houve erro ao escrever no arquivo
        {
            printf("Erro ao escrever no arquivo.\n");
            fclose(arquivo2);
            return;
        }
        atual = atual->proximo;
    }

    fclose(arquivo2); // Fecha o arquivo
    printf("Lista salva com sucesso no arquivo 'ListaNomes.txt'.\n");
}

void swap(Lista **primeiro, Lista *no1, Lista *no2)
{
    // Se algum dos nós for NULL ou forem o mesmo nó, não há necessidade de swap
    if (no1 == NULL || no2 == NULL || no1 == no2)
        return;

    // Verificando se no1 é o nó anterior a no2
    if (no1->proximo == no2)
    {
        no1->proximo = no2->proximo;
        no2->anterior = no1->anterior;
        no1->anterior = no2;
        no2->proximo = no1;

        // Atualizando os ponteiros dos nós vizinhos
        if (no1->proximo != NULL)
            no1->proximo->anterior = no1;
        if (no2->anterior != NULL)
            no2->anterior->proximo = no2;
        if (no1 == *primeiro)
            *primeiro = no2;
    }
    // Verificando se no2 é o nó anterior a no1
    else if (no2->proximo == no1)
    {
        no2->proximo = no1->proximo;
        no1->anterior = no2->anterior;
        no2->anterior = no1;
        no1->proximo = no2;

        // Atualizando os ponteiros dos nós vizinhos
        if (no2->proximo != NULL)
            no2->proximo->anterior = no2;
        if (no1->anterior != NULL)
            no1->anterior->proximo = no1;
        if (no2 == *primeiro)
            *primeiro = no1;
    }
    // Caso contrário, os nós estão em posições diferentes na lista
    else
    {
        Lista *temp = no1->anterior;
        no1->anterior = no2->anterior;
        no2->anterior = temp;

        temp = no1->proximo;
        no1->proximo = no2->proximo;
        no2->proximo = temp;

        // Atualizando os ponteiros dos nós vizinhos
        if (no1->proximo != NULL)
            no1->proximo->anterior = no1;
        if (no2->proximo != NULL)
            no2->proximo->anterior = no2;
        if (no1->anterior != NULL)
            no1->anterior->proximo = no1;
        if (no2->anterior != NULL)
            no2->anterior->proximo = no2;

        // Se um dos nós for o início da lista, atualizamos o ponteiro da cabeça
        if (no1 == *primeiro)
            *primeiro = no2;
        else if (no2 == *primeiro)
            *primeiro = no1;
    }
}

void selectionSort(Lista **primeiro, Lista **atual, int *copiasRealizadas,
                   int *comparacoes, int *tamlista)
{
    printf("tamanho lista: %d \n", *tamlista);
    int i;
    Lista *aux = *primeiro;

    while(aux != NULL)
    {

        Lista *menor = aux;
        Lista *noTemporario = aux;

        // Encontra o menor elemento na sublista não ordenada
        while (noTemporario != NULL)
        {
            noTemporario = noTemporario->proximo;
            if (noTemporario != NULL && noTemporario->rg < menor->rg)
            {
                menor = noTemporario;
            }
        }

        if(aux != menor)
        {
            swap(primeiro, aux, menor);
        }



        aux = menor->proximo;
    }
}





int main()
{
    FILE *arquivo;

    Lista *clientes = NULL, *atual = NULL;

    int tamLista = -1;

    int comparacoes = 0;
    int copiasRealizadas = 0;
    int comparacoesSeq = 0;
    int copiasRealizadasSeq = 0;
    int opcao;

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

            printf("INSERIDO NA LISTA ENCADEADA: \n\n");
            insereNoFimDaListaEnc(&clientes, &atual, nome, rg, &comparacoes, &copiasRealizadas, &tamLista);
            break;
        case 2:
            printf("NOME: ");
            scanf("%s", nome);
            printf("RG: ");
            scanf("%d", &rg);
            printf("INSERIDO NA LISTA ENCADEADA: \n\n");
            insereNoInicioDaListaEnc(&clientes, &atual, nome, rg, &comparacoes, &copiasRealizadas, &tamLista);
            break;
        case 3:
            printf("NOME: ");
            scanf("%s", nome);
            printf("RG: ");
            scanf("%d", &rg);
            printf("POSICAO: ");
            scanf("%d", &posicao);

            printf("INSERIDO NA LISTA ENCADEADA: \n\n");
            insereNoNDaListaEnc(&clientes, &atual, nome, rg, posicao, &comparacoes, &copiasRealizadas, &tamLista);
            break;
        case 4:
            printf("RETIRADO DA LISTA ENCADEADA: \n\n");
            retiraNoFimDaListaEnc(&clientes, &atual, &comparacoes, &copiasRealizadas, &tamLista);
            break;
        case 5:
            printf("RETIRADO DA LISTA ENCADEADA: \n\n");
            retiraNoInicioDaListaEnc(&clientes, &atual, &comparacoes, &copiasRealizadas, &tamLista);
            break;
        case 6:
            printf("POSICAO: ");
            scanf("%d", &posicao);
            printf("RETIRADO DA LISTA ENCADEADA: \n\n");
            retiraNoNDaListaEnc(&clientes, &atual, posicao, &comparacoes, &copiasRealizadas, &tamLista);

            break;
        case 7:
            printf("RG: ");
            scanf("%d", &rg);
            printf("LISTA ENCADEADA: \n\n");
            procuraNoPeloRGEnc(&clientes, rg, &comparacoes, &copiasRealizadas);
            break;
        case 8:
            printf("LISTA ENCADEADA: \n\n");
            imprimeListaEnc(clientes, &comparacoes, &copiasRealizadas);
            break;
        case 9:
            salvarListaEnc(clientes);
            break;
        case 10:
            // Abre um arquivo TEXTO para LEITURA
            lerListaDeArquivo(&clientes, &atual, &comparacoes, &copiasRealizadas, "NomeRG10.txt", &tamLista);
            break;
        case 11:
            selectionSort(&clientes, &atual, &comparacoes, &copiasRealizadas, &tamLista);
            break;
        case 0:
            while (clientes != NULL)
            {
                Lista *temp = clientes->proximo;
                free(clientes->nome);
                free(clientes);
                clientes = temp;
            }
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    }
    while (opcao != 0);

    return 0;
}
