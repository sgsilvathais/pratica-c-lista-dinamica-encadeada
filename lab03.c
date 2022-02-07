#include <stdio.h>
#include <stdlib.h>

typedef struct produto
{
    int idProduto;
    int qtdProduto;
    float lucroProduto;
    float lucroTotalProduto;
    struct produto *prox;
} TipoProduto;

typedef struct listaLDE
{
    TipoProduto *primeiro;
    TipoProduto *ultimo;
    int tamanho;
} TipoListaLDE;


void inicializaListaLDE(TipoListaLDE *listaAux)
{
    listaAux->primeiro = NULL;
    listaAux->ultimo = NULL;
    listaAux->tamanho = 0;
}

void insereProduto(TipoListaLDE *listaAux, int novoID, int novaQtde, float novoLucro)
{

    TipoProduto *novoElemento = malloc(sizeof(TipoProduto)), *pAuxProx = listaAux->primeiro, *pAuxAnt;
    int i;

    novoElemento->idProduto = novoID;
    novoElemento->qtdProduto = novaQtde;
    novoElemento->lucroProduto = novoLucro;
    novoElemento->lucroTotalProduto = 0;

    if (listaAux->tamanho == 0)
    {
        novoElemento->prox = NULL;
        listaAux->primeiro = novoElemento;
        listaAux->ultimo = novoElemento;        
    }
    else
    {
        for (i = 0; i < listaAux->tamanho; i++)
        {
            if(novoElemento->lucroProduto < pAuxProx->lucroProduto && pAuxProx != NULL)
            {
                pAuxAnt = pAuxProx;
                pAuxProx = pAuxProx->prox;
            }
        }
        
        if(pAuxProx == listaAux->primeiro)
        {
            novoElemento->prox = pAuxProx;
            listaAux->primeiro = novoElemento;            
        }
        else
        {
            if(pAuxProx == NULL)
                listaAux->ultimo = novoElemento; 
            pAuxAnt->prox = novoElemento;
            novoElemento->prox = pAuxProx;
        }
    }
    listaAux->tamanho++;
    
}

int buscaProduto(TipoListaLDE *listaAux, int idProcurado)
{
    int i;
    TipoProduto *pAux = listaAux->primeiro;

    if (listaAux->tamanho != 0)
    {
        for (i = 0; i < listaAux->tamanho; i++)
        {
            if (pAux->idProduto == idProcurado)
                return 0;
            pAux = pAux->prox;
        }
    }
    return -1;
}

int alteraProduto(TipoListaLDE *listaAux, int idProcurado, int addQtde)
{
    int cont;
    TipoProduto *pAux = listaAux->primeiro;

    while(pAux->idProduto != idProcurado && cont < listaAux->tamanho)
    {
        pAux = pAux->prox;
    }
    pAux->qtdProduto += addQtde;

    if (pAux->qtdProduto < 0)
    {
        pAux->qtdProduto++;
        return -1;
    }

    return 0;
}

void retiraProduto(TipoListaLDE *listaAux, int idProcurado)
{
    TipoProduto *pAux = listaAux->primeiro, *pAuxAnt = listaAux->primeiro;
    int i;

    if(listaAux->tamanho == 1)
    {
        listaAux->primeiro = NULL;
        listaAux->ultimo = NULL;
    }
    else{   
        for (i = 0; i < listaAux->tamanho; i++)
        {
            if (pAux->idProduto == idProcurado)
            {
                if (pAux == listaAux->primeiro)
                    listaAux->primeiro = pAux->prox;
                if(pAux == listaAux->ultimo)
                    listaAux->ultimo = pAuxAnt;            
                    pAuxAnt->prox = pAux->prox;
            }
            else 
            {
                pAuxAnt = pAux;
                pAux = pAux->prox;
            }
        }
    }
    free(pAux);
    listaAux->tamanho--;
    
}

void somaLucros(TipoListaLDE *listaAux, int idProcurado)
{
    int i;
    TipoProduto *pAux = listaAux->primeiro;

    for (i = 0; i < listaAux->tamanho; i++){
        if (pAux->idProduto == idProcurado)
            pAux->lucroTotalProduto += pAux->lucroProduto;
        pAux = pAux->prox;
    }
}

void imprimeLista(TipoListaLDE *listaAux)
{
    TipoProduto *pAux = listaAux->primeiro;
    int i;

    for (i = 0; i < listaAux->tamanho; i++)
    {
        printf("%d %f\n", pAux->idProduto, pAux->lucroTotalProduto);
        pAux = pAux->prox;
    }
}

int main (void)
{
    TipoListaLDE listaLDE;
    int qtdOperacoes, operacao, id, quantidade, i;
    float lucro;

    inicializaListaLDE(&listaLDE);
    scanf("%d", &qtdOperacoes);

    if (qtdOperacoes >= 1 && qtdOperacoes <= 100)
    {
        for (i = 0; i < qtdOperacoes; i++)
        {
            scanf("%d", &operacao);

            switch(operacao)
            {
                case 1: scanf("%d %d %f", &id, &quantidade, &lucro);
                        if (buscaProduto(&listaLDE, id) == -1)
                        { 
                            insereProduto(&listaLDE, id, quantidade, lucro);
                        }else printf("ja existe\n"); 
                break;

                case 2: scanf("%d %d", &id, &quantidade);
                        if (buscaProduto(&listaLDE, id) == 0)
                        { 
                            alteraProduto(&listaLDE, id, quantidade);
                        }else printf("nao existe\n");
                break;

                case 3: scanf("%d", &id);
                        quantidade = -1;
                        if (buscaProduto(&listaLDE, id) == 0 && alteraProduto(&listaLDE, id, quantidade) == 0)
                            somaLucros(&listaLDE, id);
                        else printf("nao existe\n");                           
                break;

                case 4: scanf("%d", &id);
                        if (buscaProduto(&listaLDE, id) == 0)
                            retiraProduto(&listaLDE, id);
                        else printf("nao existe");
                break;

                default: exit(1);
                break;
            }
        }

    }else exit(1);

    imprimeLista(&listaLDE);  

    return 0;
}
