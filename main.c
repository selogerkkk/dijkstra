#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define INFINITY INT_MAX

typedef struct SVertice
{
    int dado;
    struct SVertice *next;
    struct SListaConexoes *listaConexoes;
    _Bool visitado;
    int distancia;
} TVertice;

typedef struct SListaConexoes
{
    struct SVertice *vertice;
    struct SListaConexoes *next;
    float distancia;
} TListasConexoes;
TVertice *inicio = NULL;
TVertice *fim;

TVertice *buscarVertice(int key)
{
    TVertice *ultimo = inicio;

    while (ultimo != NULL)
    {
        if (ultimo->dado == key)
            return ultimo;
        ultimo = ultimo->next;
    }

    return NULL;
}

TVertice *adicionarVertice(int info)
{
    TVertice *novo;

    novo = buscarVertice(info);
    if (novo != NULL)
        return novo;

    novo = malloc(sizeof(TVertice));
    novo->dado = info;
    novo->next = NULL;
    novo->listaConexoes = NULL;
    novo->visitado = FALSE;
    if (inicio == NULL)
    {
        inicio = novo;
    }
    else
    {
        fim->next = novo;
    }

    fim = novo;
    return novo;
}

void conectarVertices(int info, int info2, float distancia)
{
    TVertice *verticeOrigem, *verticeDestino;

    verticeOrigem = adicionarVertice(info);
    verticeDestino = adicionarVertice(info2);

    TListasConexoes *conexao = malloc(sizeof(TListasConexoes));
    conexao->vertice = verticeDestino;
    conexao->distancia = distancia;
    conexao->next = NULL;

    if (verticeOrigem->listaConexoes == NULL)
    {
        verticeOrigem->listaConexoes = conexao;
    }
    else
    {
        TListasConexoes *ultimaConexao = verticeOrigem->listaConexoes;
        while (ultimaConexao->next != NULL)
        {
            ultimaConexao = ultimaConexao->next;
        }
        ultimaConexao->next = conexao;
    }
}

TVertice *encontrarVerticeNaoVisitadoComMenorDistancia()
{
    TVertice *atual = inicio;
    TVertice *verticeMenorDistancia = NULL;
    int menorDistancia = INFINITY;

    while (atual != NULL)
    {
        if (!atual->visitado && atual->distancia < menorDistancia)
        {
            menorDistancia = atual->distancia;
            verticeMenorDistancia = atual;
        }
        atual = atual->next;
    }

    return verticeMenorDistancia;
}

void verificarVizinhosMenorDistancia(TVertice *vertice)
{
    TListasConexoes *listaConexoes = vertice->listaConexoes;

    while (listaConexoes != NULL)
    {
        TVertice *vizinho = listaConexoes->vertice;
        float novaDistancia = vertice->distancia + listaConexoes->distancia;

        if (novaDistancia < vizinho->distancia)
        {
            vizinho->distancia = novaDistancia;
        }

        listaConexoes = listaConexoes->next;
    }
}

void dijkstra(TVertice *verticeInicial)
{
    verticeInicial->distancia = 0;

    while (1)
    {
        TVertice *atual = encontrarVerticeNaoVisitadoComMenorDistancia();

        if (atual == NULL)
        {
            break;
        }

        atual->visitado = TRUE;
        verificarVizinhosMenorDistancia(atual);
    }
}

void imprimirDistancias()
{
    TVertice *vertice = inicio;

    while (vertice != NULL)
    {
        printf("Distância do vértice %d: %d\n", vertice->dado, vertice->distancia);
        vertice = vertice->next;
    }
}

int main()
{
    int leitura, leitura2;
    float distancia;

    while (1)
    {
        printf("Infome um ou dois número (ou zero para encerrar): ");
        scanf("%d %d", &leitura, &leitura2);

        if (leitura == 0)
            break;

        if (leitura2 == 0)
        {
            adicionarVertice(leitura);
        }
        else
        {
            printf("Informe a distância entre %d e %d: ", leitura, leitura2);
            scanf("%f", &distancia);
            conectarVertices(leitura, leitura2, distancia);
        }
    }

    printf("\n\nAplicando o algoritmo de Dijkstra:\n");
    dijkstra(inicio);

    printf("\nImprimindo as distâncias mínimas:\n");
    imprimirDistancias();

    return 0;
}
