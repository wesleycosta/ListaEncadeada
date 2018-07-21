#include <stdio.h>
#include <stdlib.h>

typedef struct aluno
{
	int prontuario;
	char nome[128];
	int idade;
	char sexo;
}ALUNO;

typedef struct lista {
	ALUNO info;
	struct lista* prox;
} LISTA;

void LimparBuffer()
{
	while (getchar() != '\n');
}

void Pause()
{
	printf("\nTecle <ENTER> para continuar...");
	getchar();
}

LISTA* InicializarLista()
{
	return NULL;
}

int VerificarListaVazia(LISTA*pLista)
{
	return (pLista == NULL);
}

void LiberarLista(LISTA* pLista){
	LISTA* noRemovido = pLista;
	while (noRemovido != NULL) {
		/* guarda referência para o próximo elemento*/
		LISTA* noAux = noRemovido->prox;
		free(noRemovido); /* libera a memória apontada por noRemovido
						  */
		noRemovido = noAux; /* faz noRemovido apontar para o próximo */
	}
}

LISTA* BuscarElementoPorProntuario(LISTA* pLista, int idProntuario)
{
	LISTA* noProcurado;
	for (noProcurado = pLista; noProcurado != NULL; noProcurado = noProcurado->prox)
	if (noProcurado->info.prontuario == idProntuario)
		return noProcurado;

	return NULL;
}

LISTA* BuscarPorNomeOuProntuario(LISTA* pLista, int idProntuario, char *nome)
{
	LISTA* noProcurado;
	for (noProcurado = pLista; noProcurado != NULL; noProcurado = noProcurado->prox)
	{
		if (noProcurado->info.prontuario == idProntuario || !strcmp(noProcurado->info.nome, nome))
			return noProcurado;
	}

	return NULL;
}

void ImprimirAluno(ALUNO aluno)
{
	printf("\n");
	printf("\nProntuario..: %d", aluno.prontuario);
	printf("\nNome........: %s", aluno.nome);
	printf("\nIdade.......: %d", aluno.idade);
	printf("\nSexo........: %c", aluno.sexo);
	printf("\n");
}

void ImprimirLista(LISTA* pLista)
{
	LISTA* noTemp;
	if (pLista)
	{
		for (noTemp = pLista; noTemp != NULL; noTemp = noTemp->prox)
			ImprimirAluno(noTemp->info);
	}
	else
		printf("\nLISTA VAZIA...\n");
}

void Consultar(LISTA *pLista, int Prontuario, char *nome)
{
	LISTA *pAlunoPesquisado = BuscarPorNomeOuProntuario(pLista, Prontuario, nome);

	if (!pAlunoPesquisado)
		printf("\nO ALUNO CONSULTADO NAO FOI ENCONTRADO... \n");
	else
		ImprimirAluno(pAlunoPesquisado->info);
}

LISTA* Inserir(LISTA* pLista, ALUNO info)
{
	LISTA *pTemProntuario = BuscarElementoPorProntuario(pLista, info.prontuario);

	if (pTemProntuario)
		return pLista;
	else
	{
		LISTA* novoElemento = (LISTA*)malloc(sizeof(LISTA));
		novoElemento->info = info;
		novoElemento->prox = pLista;

		return novoElemento;
	}
}

LISTA* Retirar(LISTA* pLista, int Prontuario)
{
	LISTA* noAnterior = NULL;
	LISTA* noRemovido = pLista;

	while (noRemovido != NULL && noRemovido->info.prontuario != Prontuario)
	{
		noAnterior = noRemovido;
		noRemovido = noRemovido->prox;
	}

	/* verifica se achou elemento */
	if (noRemovido == NULL)
		return pLista; /* não achou: retorna LISTA original */

	/* retira elemento */

	if (noAnterior == NULL) {
		/* retira elemento do inicio */
		pLista = noRemovido->prox;
	}
	else {
		/* retira elemento do meio da LISTA */
		noAnterior->prox = noRemovido->prox;
	}

	free(noRemovido);
	return pLista;
}

int Atualizar(LISTA* pLista, int Prontuario, ALUNO info)
{
	LISTA *pAlunoAtualizar = BuscarElementoPorProntuario(pLista, Prontuario);

	// VERFICA SE EXISTE ALUNO CADASTRADO
	if (!pAlunoAtualizar)
		return 0;
	else
	{
		pAlunoAtualizar->info = info;

		return info.prontuario;
	}
}