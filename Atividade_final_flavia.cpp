#include <iostream>
#include <string.h>
#include <Windows.h>
#include <locale>
struct Contato
{
	char nome[20];
	char telefone[20];
	char email[20];
	char status;
};
int calcularTamanho(FILE *);
void cadastrarContato(FILE *);
void consultarContato(FILE *);
void gerarArquivoTexto(FILE *);
void excluirContato(FILE *);
int main()
{
	int opcao;
	FILE *arquivo;
	if ((arquivo = fopen("dados1.dat", "rb+")) == NULL)
	{
		if ((arquivo = fopen("dados1.dat", "wb+")) == NULL)
		{
			printf("Falha ao abrir o arquivo!\n");
			system("pause");
		}
	}
	do
	{
		system("CLS");
		printf("\n======= AGENDA ======= \n");
		printf("1. Cadastrar\n");
		printf("2. Consultar por c�digo\n");
		printf("3. Gerar arquivo\n");
		printf("4. Excluir registro\n");
		printf("5. Sair\n");
		printf("===========Contatos:%d=\n", calcularTamanho(arquivo));
		printf("Op��o:");
		scanf("%d", &opcao);
		switch (opcao)
		{
		case 1:
			cadastrarContato(arquivo);
			break;
		case 2:
			consultarContato(arquivo);
			break;
		case 3:
			gerarArquivoTexto(arquivo);
			break;
		case 4:
			excluirContato(arquivo);
			break;
		case 5:
			fclose(arquivo);
		}
	} while (opcao != 5);
}
void cadastrarContato(FILE *arquivo)
{
	Contato contato;
	char confirma;
	contato.status = ' ';
	fflush(stdin);
	printf("Cadastrando novo registro:\n");
	printf("\nN�mero do registro:%d\n", calcularTamanho(arquivo) + 1);
	printf("Nome..........:");
	gets(contato.nome);
	printf("Telefone......:");
	gets(contato.telefone);
	printf("E-mail........:");
	gets(contato.email);
	printf("\nConfirma <s/n>:");
	fflush(stdin);
	scanf("%c", &confirma);
	if (toupper(confirma) == 'S')
	{
		printf("\nGravando...\n\n");
		fseek(arquivo, 0, SEEK_END);
		fwrite(&contato, sizeof(Contato), 1, arquivo);
	}
	system("pause");
}
void consultarContato(FILE *arquivo)
{
	Contato contato;
	int numero;
	printf("\nConsulta pelo c�digo\n");
	printf("\nInforme o C�digo...:");
	scanf("%d", &numero);
	if ((numero <= calcularTamanho(arquivo)) && (numero > 0))
	{
		fseek(arquivo, (numero - 1) * sizeof(Contato), SEEK_SET);
		fread(&contato, sizeof(Contato), 1, arquivo);
		if (contato.status == ' ')
		{
			printf("\nNome......:%s", contato.nome);
			printf("\nTelefone..:%s", contato.telefone);
			printf("\nE-mail....:%s\n\n", contato.email);
		}
		else
			printf("\nRegistro exclu�do! \n");
	}
	else
	{
		printf("\nN�mero de registro inv�lido!\n");
	}
	system("pause");
}
void gerarArquivoTexto(FILE *arquivo)
{
	char nomeArquivoTexto[20];
	printf("Nome do arquivo texto:");
	scanf("%s", nomeArquivoTexto);
	strcat(nomeArquivoTexto, ".txt");
	FILE *arquivoTexto = fopen(nomeArquivoTexto, "w");
	if (!arquivoTexto)
	{
		printf("N�o foi poss�vel criar esse arquivo!\n");
		system("pause");
	}
	fprintf(arquivoTexto, "Nome                Telefone    E-mail                   Status\n");
	fprintf(arquivoTexto, "================================================================\n");
	int numero;
	Contato contato;
	for (numero = 0; numero < calcularTamanho(arquivo); numero++)
	{
		fseek(arquivo, numero * sizeof(Contato), SEEK_SET);
		fread(&contato, sizeof(Contato), 1, arquivo);
		fprintf(arquivoTexto, "%-20s%-12s%-25s- %c\n", contato.nome, contato.telefone, contato.email, contato.status);
	}
	fprintf(arquivoTexto, "================================================================\n");
	fclose(arquivoTexto);
}
void excluirContato(FILE *arquivo)
{
	Contato contato;
	char confirma;
	int numero;
	printf("\nInforme o c�digo do registro para excluir\n");
	scanf("%d", &numero);
	if ((numero <= calcularTamanho(arquivo)) && (numero > 0))
	{
		fseek(arquivo, (numero - 1) * sizeof(Contato), SEEK_SET);
		fread(&contato, sizeof(Contato), 1, arquivo);
		if (contato.status == ' ')
		{
			printf("\nNome......:%s", contato.nome);
			printf("\nTelefone..:%s", contato.telefone);
			printf("\nE-mail....:%s\n", contato.email);
			printf("\nConfirma a exclus�o: <s/n>\n");
			getchar();
			scanf("%c", &confirma);

			if (toupper(confirma) == 'S')
			{
				printf("\nExcluindo...\n\n");
				fseek(arquivo, (numero - 1) * sizeof(Contato), SEEK_SET);
				contato.status = '*';
				fwrite(&contato, sizeof(Contato), 1, arquivo);
			}
		}
		else
			printf("Registro inexistente! \n");
	}
	else
	{
		printf("\nN�mero de registro inv�lido!\n");
	}
	system("pause");
}
int calcularTamanho(FILE *arquivo)
{
	fseek(arquivo, 0, SEEK_END);
	return ftell(arquivo) / sizeof(Contato);
}
