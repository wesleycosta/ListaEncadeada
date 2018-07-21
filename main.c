#include <stdio.h>
#include <stdlib.h>
#include "cLibAluno.h"

void LimparTela()
{
	system("cls");
}

// CRIA UMA NOVA "STRING", CONTENDO O TEXTO N VEZES 
char *NovaStr(char texto[], int vezes)
{
	int  i = 0;
	char *novoTexto = (char *)malloc(sizeof(char)* 128);
	strcpy(novoTexto, "");

	for (i = 0; i < vezes; i++)
		strcat(novoTexto, texto);

	return novoTexto;
}

//  IMPRIME O TITULO SELECIONADO
void ImprmirTitulo(char titulo[])
{
	LimparTela();
	int vezes = 40 - 6 - strlen(titulo);
	printf("****************************************\n");
	printf("***%s%s%s***\n", NovaStr(" ", vezes / 2), titulo, NovaStr(" ", vezes - (vezes / 2)));
	printf("****************************************\n");
}

//  FAZ A LEITURA DO PRONTUARIO DO ALUNO
void LeiaProntuario(int *prontuario)
{
	printf("\nEntre com o prontuario.....: ");
	scanf("%d", prontuario);
	LimparBuffer();
}

//  FAZ A LEITURA DO NOME DO ALUNO
void LeiaNome(char *nome)
{
	printf("\nEntre com o nome...........: ");
	scanf("%[^\n]", nome);
	LimparBuffer();
}

//  FAZ A LEITURA DE UM ALUNO
void LeiaAluno(ALUNO *aluno)
{
	LeiaProntuario(&aluno->prontuario);
	LeiaNome(&aluno->nome);

	printf("\nEntre com o idade..........: ");
	scanf("%d", &aluno->idade);
	LimparBuffer();

	printf("\nEntre com o sexo (M ou F)..: ");
	scanf("%c", &aluno->sexo);
	LimparBuffer();
}

//  IMPRIME MENU DE OPÇÕES
void Menu()
{
	LimparTela();
	printf("****************************************\n");
	printf("***                MENU              ***\n");
	printf("****************************************\n");
	printf("* [1] - INSERIR		               *\n");
	printf("* [2] - ALTERAR		               *\n");
	printf("* [3] - EXCLUIR		               *\n");
	printf("* [4] - CONSULTAR	               *\n");
	printf("* [5] - LISTAR		               *\n");
	printf("* [6] - SAIR		               *\n");
	printf("****************************************\n");

	printf("\n\n OPCAO: ");
}

//  FUNCAO PARA INSERIR UM NOVO ALUNO
LISTA *MantemInserir(LISTA *pLista)
{
	ALUNO aluno;
	int *existeAluno;

	ImprmirTitulo("[1]. INSERIR ALUNO");
	LeiaAluno(&aluno);
	existeAluno = BuscarElementoPorProntuario(pLista, aluno.prontuario);

	if (existeAluno)
	{
		printf("\nJA EXISTE UM ALUNO CADASTRADO COM O PRONTUARIO %d \n", aluno.prontuario);
		Pause();
	}
	else
		pLista = Inserir(pLista, aluno);

	return pLista;
}

//  FUNCAO PARA ALTERAR UM ALUNO
LISTA *MantemAlterar(LISTA *pLista)
{
	ImprmirTitulo("[2]. ALTERAR ALUNO");
	int prontuario = 0;
	LeiaProntuario(&prontuario);
	int *exiteProntuario = BuscarElementoPorProntuario(pLista, prontuario);

	if (exiteProntuario)
	{
		ImprmirTitulo("[2]. ALTERAR ALUNO");
		printf("\nENTRE COM OS DADOS DO ALUNO ATUALIZADOS \n");
		ALUNO aluno;
		LeiaAluno(&aluno);
		Atualizar(pLista, prontuario, aluno);
	}
	else
	{
		printf("\n ALUNO NAO ENCONTRADO...\n");
		Pause();
	}

	return pLista;
}

//  FUNCAO PARA EXLUIR UM ALUNO
LISTA *MantemExcluir(LISTA *pLista)
{
	ImprmirTitulo("[3]. EXCLUIR ALUNO");
	int prontuario = 0;
	LeiaProntuario(&prontuario);
	int *exiteProntuario = BuscarElementoPorProntuario(pLista, prontuario);

	if (exiteProntuario)
	{
		pLista = Retirar(pLista, prontuario);
		printf("\n ALUNO REMOVIDO COM SUCESSO...\n");
		Pause();
	}
	else
	{
		printf("\n ALUNO NAO ENCONTRADO...\n");
		Pause();
	}
}

//  FUNCAO PARA CONSULTAR UM ALUNO
void MantemConsultar(LISTA *pLista)
{
	ImprmirTitulo("[4].CONSULTAR ");
	int prontuario = 0, opcao = 0;
	char *nome = (char *)malloc(sizeof(char)* 128);

	strcpy(nome, "");
	do
	{
		printf("\n CONSULTAR ALUNO POR: ");
		printf("\n [1]. PRONTUARIO");
		printf("\n [2]. NOME ");
		printf("\n\n OPCAO: ");
		scanf(" %d", &opcao);
		LimparBuffer();

		if (opcao = 2)
			LeiaNome(nome);
		else if (opcao == 1)
			LeiaProntuario(&prontuario);
	} while (opcao != 1 && opcao != 2);
	
	Consultar(pLista, prontuario, nome);
	Pause();
}

//  FUNCAO PARA LISTAR TODOS OS ALUNOS
void MantemListaAlunos(LISTA *pLista)
{
	ImprmirTitulo("[5]. LISTA DE ALUNOS");
	ImprimirLista(pLista);
	Pause();
}

int main()
{
	LISTA *pLista;
	int opcao = 0;
	pLista = InicializarLista();

	do
	{
		Menu();
		scanf("%d", &opcao);
		LimparBuffer();
		LimparTela();
		if (opcao == 1)
			pLista = MantemInserir(pLista);
		else if (opcao == 2)
			pLista = MantemAlterar(pLista);
		else if (opcao == 3)
			pLista = MantemExcluir(pLista);
		else if (opcao == 4)
			MantemConsultar(pLista);
		else if (opcao == 5)
			MantemListaAlunos(pLista);
	} while (opcao != 6);

	LiberarLista(pLista);
	return 0;
}