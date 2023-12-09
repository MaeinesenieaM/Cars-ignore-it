#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "read.c"

typedef struct Carro
{
	char proprietario [30], modelo [24], cor [12], chassi [18], placa [8];
	int combustivel; //1 = álcool, 2 = diesel, 3 = gasolina.
	int ano;
	Carro *proximo;
} Carro;

Carro *alocaCarro ()
{
	Carro *novocarro = (Carro*) calloc (1, sizeof(Carro));
	if (novocarro == NULL)
	{
		printf ("!!ERROR!!\n!!NÃO FOI POSSÍVEL ALOCAR MEMORIA!!\n");
		exit(1);
	}
	return novocarro;
}

int tamanhoPlaca (char placa[])
{
	size_t tamanho = strlen (placa);
	if (tamanho == 7) return 1;
	else
	{
		printf("\n!CODIGO INVALIDO!\n!NECESSARIO 7 LETRAS EXATAS!\n\n");
		return 0;
	}
}

void criaPlaca (Carro *memoria)
{
	for (int letra = 0; letra < 3; letra++)
	{
		memoria->placa[letra] = (rand () % 26 + 65); //Gera uma letra aleatoria para cada posição de acordo com ASCII. 
	}
	for (int numero = 3; numero < 7; numero++)
	{
		memoria->placa[numero] = (rand () % 10 + 48); //Gera um número aleatorio para cada posição de acordo com ASCII. 
	}
}

void registraCarro (Carro *registro)
{
	int opcao;
	do  
	{
		switch (readInt ("Insira o combustível\nÁlcool (1)\nDiesel (2)\nGasolina (3)\n#", &opcao))
		{
			case 1:
				registro->combustivel = 1;
				break;
			case 2:
				registro->combustivel = 2;
				break;
			case 3:
				registro->combustivel = 3;
				break;
			default:
				printf ("\n!Opção invalida!\n\n");
 		}
	} while (opcao < 1 || opcao > 3);

//	readString ("placa", registro->placa);
	criaPlaca (registro);
	readString ("proprietario", registro->proprietario);
	readString ("modelo", registro->modelo);
	readString ("cor", registro->cor);
	readString ("chassi", registro->chassi);
	
	readInt  ("ano", &registro->ano);
	registro->proximo = NULL;
}

Carro *ultimos (Carro *memoria, int toggle) //toggle = 0 para ultimo; toggle = 1 para penúltimo.
{
	Carro *ultimo = memoria;
	Carro *penultimo = NULL;
	while (ultimo->proximo != NULL) 
	{
		penultimo = ultimo;
		ultimo = ultimo->proximo;
	}
	switch (toggle)
	{
		case 0:
			return ultimo;
		case 1:
			return penultimo;
		default:
			printf("!!ERROR!!\n!!VALOR DE TOGGLE INVALIDO!!\n");
			exit(2);
	}
}

void mostraRegistro (Carro *memoria)
{
	//eu odeio essa linha :)
	printf ("===+===\n");
	printf ("proprietario: %s\ncombustivel: %d\nmodelo: %s\ncor: %s\nchassi: %s\nplaca: %s\nano: %d\n", memoria->proprietario, memoria->combustivel, memoria->modelo, memoria->cor, memoria->chassi, memoria->placa, memoria->ano);
}

Carro *procuraRegistro (Carro *memoria)
{
	Carro *procura = memoria;
	char placa[32];
	do	{ readString ("Insira o codigo da placa", placa); } while (tamanhoPlaca (placa) == 0);
	while (strcmp(procura->placa, placa) != 0 && procura->proximo != NULL) procura = procura->proximo;
	switch (strcmp(procura->placa, placa))
	{
		case 0:
			return procura;
		default:
			return NULL;
	}
}
//Requisito avaliativo ( A )
void caminhoneirosA (Carro *memoria)
{
	if (memoria == NULL)
	{
		printf ("\n!A MEMORIA ESTA VAZIA!\n\n");
		return;
	}
	Carro *procura = memoria;
	while (procura->proximo != NULL)
	{
		if (procura->ano == 2010 && procura->combustivel == 2) printf ("\nA\n==*==\nProprietário do veiculo %s: %s\n", procura->placa, procura->proprietario);
		procura = procura->proximo;
	}
	if (procura->ano == 2010 && procura->combustivel == 2) printf ("\nA\n==*==\nProprietário do veiculo %s: %s\n", procura->placa, procura->proprietario);
}

//Requisito avaliativo ( B )
void placadorB (Carro *memoria)
{
	if (memoria == NULL)
	{
		printf ("\n!A MEMORIA ESTA VAZIA!\n\n");
		return;
	}
	Carro *procura = memoria;
	while (procura->proximo != NULL)
	{
		if (procura->placa[0] == 74 && procura->placa[6] == 48 + 0 && procura->placa[6] == 48 + 2 || procura->placa[6] == 48 + 4 || procura->placa[6] == 48 + 7) 
			printf ("\nB\n==*==\nProprietário do veiculo %s: %s\n", procura->placa, procura->proprietario);
		procura = procura->proximo;
	}
		if (procura->placa[0] == 74 && procura->placa[6] == 48 + 0 && procura->placa[6] == 48 + 2 || procura->placa[6] == 48 + 4 || procura->placa[6] == 48 + 7) 
			printf ("\nB\n==*==\nProprietário do veiculo %s: %s\n", procura->placa, procura->proprietario);
}
//função assistente de C
void assistC (Carro *memoria)
{
	int vogais [5] = {65, 69, 73, 79, 85};
	int encontrado = 0;
	for (int v = 0; v < 5; v++)
	{

		if (memoria->placa[1] == vogais[v])
		{
			encontrado++;
			break;
		}
	}
	if (encontrado == 0) return;
	int soma = 0;
	for (int n = 3; n < 7; n++) soma += memoria->placa[n] - 48;
	if (soma % 2 == 0) encontrado++;

	if (encontrado >= 2) printf ("\nC\n#Carro da placa %s#\nModelo: %s\nCor: %s\n\n", memoria->placa, memoria->modelo, memoria->cor);
}
//Requisito avaliativo ( C )
void cujaC (Carro *memoria)
{
	if (memoria == NULL)
	{
		printf ("\n!A MEMORIA ESTA VAZIA!\n\n");
		return;
	}

	Carro *procura = memoria;
	while (procura->proximo != NULL)
	{
		assistC (procura);
		procura = procura->proximo;
	}
	assistC (procura);
}

void D ()
{

}

void menuAvaliativo (Carro *memoria)
{
	int escolha;
	do
	{
		printf ("\nQuestão A <1>\nQuestão B <2>\nQuestão C <3>\nQuestão D <4> ´indisponivel´\nSair do menu avaliativo <0>\n");
		switch (readInt (NULL, &escolha))
		{
			case 1:
				caminhoneirosA (memoria);
				break;
			case 2:
				placadorB (memoria);
				break;
			case 3:
				cujaC (memoria);
				break;
			case 4:
				break;
			case 0: break;
			default: printf ("\n!OPCAO INVALIDA!\n");
		}
	}
	while (escolha != 0);
}

int main ()
{
	setlocale (LC_ALL, "Portuguese");

	srand (time(0));

	Carro *memoria = NULL;
	int escolha;

	do
	{
		printf ("Registrar um veiculo (1)\nRemover veiculo (2)\nProcurar com a placa (3)\nMostrar o registro inteiro (4)\nQuestões Avaliativas (5)\nSair (0)\n");
		switch (readInt (NULL, &escolha))
		{
			case 1: //Registra
				if (memoria == NULL)
				{ 
					memoria = alocaCarro();
					registraCarro (memoria);
				}
				else
				{
					Carro *novo = ultimos (memoria, 0);
					if (novo == NULL) printf ("ELE E NULO!\n");
					novo->proximo = alocaCarro();
					registraCarro (novo->proximo);
				}
				break;
			case 2: //Remove
				printf ("W.I.P\n\n");
				if (memoria == NULL)
				{
					printf ("\n!A MEMORIA ESTA VAZIA!\n\n");
					break;
				}
				Carro *exclui;
				exclui = procuraRegistro (memoria);
				if (exclui != NULL)
				{				
					if (exclui == memoria)
					{
						free (memoria);
						memoria = NULL;
					}
					else if (exclui->proximo == NULL)
					{
						free (exclui);
						exclui = NULL;
						Carro *penultima = ultimos (memoria, 1);
						if (penultima == NULL) break;
						penultima->proximo = NULL;
					}
					else
					{
						Carro *penultima = memoria;
						while (penultima->proximo != exclui) penultima = penultima->proximo;
						penultima->proximo = exclui->proximo;
						free (exclui);
					}
					break;
				}
				printf ("\nPlaca não encontrada ou invalida!\n");
				break;
			case 3: //Procura				
				if (memoria == NULL)
				{
					printf ("\n!A MEMORIA ESTA VAZIA!\n\n");
					break;
				}
				Carro *procura;
				procura = procuraRegistro (memoria);
				if (procura != NULL) mostraRegistro (procura);
				else printf ("\nPlaca não encontrada ou invalida!\n");
				break;
			case 4: //Imprime a memoria
				printf ("Indisponivel\n\n");
				if (memoria == NULL)
				{
					printf ("\n!A MEMORIA ESTA VAZIA!\n\n");
					break;
				}
				Carro *mostrar;
				mostrar = memoria;
				while (mostrar->proximo != NULL)
				{
					mostraRegistro (mostrar);
					mostrar = mostrar->proximo;
				}
				mostraRegistro (mostrar);
				break;
			case 5:
				menuAvaliativo (memoria);
				break;
			case 0: //Sair
				if (memoria != NULL)
				{
					while (memoria->proximo != NULL)
					{
						Carro *ultima = ultimos (memoria, 0);
						free (ultima);
						Carro *penultima = ultimos (memoria, 1);
						penultima->proximo = NULL;
					}
					free (memoria);
				}
				printf ("\n    __o  bici! \n  _/><_ \n (_)/(_) \n  ");
				exit(0);
				break;
			default: printf ("\n!OPCAO INVALIDA!\n");
		}
	} while (1 == 1);	
	return 0;
}