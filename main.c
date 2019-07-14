// Arthur Santana
#include <stdio.h>
#include <stdlib.h>
// Uso de expressão para que o uso de um system('clear') ou 'CLS' não diminua a compatibilidade
// do código com outros SO, tal expressão foi encontrada em um tópico de fórum sobre programação
#ifdef _WIN32
# define CLEAR_SCREEN system ("cls")
#else
# define CLEAR_SCREEN puts("\x1b[H\x1b[2J")
#endif
//		Declarando os arquivos em que serão armazenados os dados dos usuários
FILE *arqClient;
FILE *arqProduct;
FILE *arqSales;

//		Estrutura para os clientes
struct _client
{
    char cod[20];
    char name[60];
    char cpf[15];
};
//		Estrutura para os produtos
struct _product
{
    char cod[20];
    char description[250];
    char value[20];
};
//		Estrutura para as vendas
struct _sales
{
    char amount[20];
    char value[20];
    char data[11];
    char codProduct[20];
    char codClient[20];
};
//		Função para limpar o buffer
void flush_in(); // Função de autoria desconhecida, encontrada em um tópico do fórum Viva o Linux.
//		Funções para registrar nos arquivos
void registerClient(struct _client *fclients);
void registerProduct(struct _product *fproducts);
void registerSale(struct _sales *fsales);
//		Funções para listagem do conteúdo dos arquivos
void listClient(void);
void listProduct(void);
void listSale(void);
//      Funções verificadoras de caracteres
int verify(char *palavra);
int verifyDate(char *data);

int main(void)
{
    int x;
//		Declarando as structs que serão usadas nas funções para cada ação do programa
    struct _client _registerClients;
    struct _product _registerProducts;
    struct _sales _registerSales;

    do
    {
        printf("--------MENU--------\n1 - Cadastrar Cliente\n");
        printf("2 - Listar Clientes\n3 - Cadastrar Produto\n");
        printf("4 - Listar Produtos\n5 - Cadastrar Vendas\n");
        printf("6 - Listar Vendas\n7 - Sair\n");
        printf("Digite sua opção: ");

        scanf("%d", &x);
//		É necessário passar o endereço de memória da struct, para que possa ser acessada fora da função main
        switch(x)
        {
            case 1:
	            CLEAR_SCREEN;
	            arqClient = fopen("clients.bin", "ab");
	            registerClient(&_registerClients);
	            fclose(arqClient);
            	break;
            case 2:
	            CLEAR_SCREEN;
	            arqClient = fopen("clients.bin", "rb");
	            listClient();
	            fclose(arqClient);
	            break;
            case 3:
	            CLEAR_SCREEN;
	            arqProduct = fopen("products.bin", "ab");
	            registerProduct(&_registerProducts);
	            fclose(arqProduct);
	            break;
            case 4:
            	CLEAR_SCREEN;
	            arqProduct = fopen("products.bin", "rb");
	            listProduct();
	            fclose(arqProduct);
	            break;
            case 5:
	            CLEAR_SCREEN;
	            arqSales = fopen("sales.bin", "ab");
	            registerSale(&_registerSales);
	            fclose(arqSales);
	            break;
            case 6:
            	CLEAR_SCREEN;
	            arqSales = fopen("sales.bin", "rb");
	            listSale();
	            fclose(arqSales);
	            break;
            case 7:
            	exit(1);
        }
    }while(x != 7);
    
    return 0;
}

//		Função registradora de clientes
void registerClient(struct _client *fclients)
{
    do
    {
    printf("Digite o código do cliente: ");
    scanf("%s", fclients->cod);
    flush_in();
    CLEAR_SCREEN;
    }while(verify(fclients->cod) != 1);
    
    printf("Digite o nome do cliente: ");
    scanf("%[^\n]s", fclients->name);
    flush_in();
    CLEAR_SCREEN;
    
    do
    {
    printf("Digite o cpf do cliente: ");
    scanf("%s", fclients->cpf);
    flush_in();
    CLEAR_SCREEN;
    }while(verify(fclients->cpf) != 1);

    fprintf(arqClient, "---------------------------------------------------------------------------------");
    fprintf(arqClient,"\nCódigo cliente: %s\nCliente: %s\nCPF: %s\n", fclients->cod, fclients->name, fclients->cpf);
}
//		Função registradora dos produtos
void registerProduct(struct _product *fproducts)
{
    do
    {
	printf("Digite o código do produto: ");
    scanf("%s", fproducts->cod);
    flush_in();
    CLEAR_SCREEN;
    }while(verify(fproducts->cod) != 1);
    
    printf("Digite a descrição do produto: ");
    scanf("%[^\n]s", fproducts->description);
    flush_in();
    CLEAR_SCREEN;
    
    do
    {
    printf("Digite o valor do produto: ");
    scanf("%s", fproducts->value);
    flush_in();
    CLEAR_SCREEN;
    }while(verify(fproducts->value) != 1);
    
    fprintf(arqProduct, "---------------------------------------------------------------------------------");
    fprintf(arqProduct,"\nCódigo produto: %s\nDescrição: %s\nValor: R$%s\n", fproducts->cod, fproducts->description, fproducts->value);
}
//		Função registradora das vendas
void registerSale(struct _sales *fsales)
{
    int a;
    float b;

    do
    {
	printf("Digite a data da venda: ");
    scanf("%s", fsales->data);
    flush_in();
    CLEAR_SCREEN;
    }while(verifyDate(fsales->data) != 1);
    
    do
    {
    printf("Digite o código do produto: ");
    scanf("%s", fsales->codProduct);
    flush_in();
    CLEAR_SCREEN;
    }while(verify(fsales->codProduct) != 1);
    
    do
    {
    printf("Digite o código do cliente: ");
    scanf("%s", fsales->codClient);
    flush_in();
    CLEAR_SCREEN;
    }while(verify(fsales->codClient) != 1);

    do
    {
    printf("Digite a quantidade: ");
    scanf("%s", fsales->amount);
    flush_in();
    CLEAR_SCREEN;
    }while(verify(fsales->amount) != 1);
    
    do
    {
    printf("Digite o valor do produto: ");
    scanf("%s", fsales->value);
    flush_in();
    CLEAR_SCREEN;
    }while(verify(fsales-> value) != 1);

    a = atoi(fsales->amount);   // Fazendo a conversão do string para inteiro possibilitando o cálculo do valor total
    b = atof(fsales->value);    // [...float...]

    fprintf(arqSales, "---------------------------------------------------------------------------------");
    fprintf(arqSales,"\nData: %s\nCódigo do produto: %s\nCódigo do cliente: %s\nQuantidade: %d\nValor do produto: R$%.2f\nValor total: R$%.2f\n", fsales->data, fsales->codProduct, fsales->codClient, a, b, b*a);
}
//		Função para listar os clientes
void listClient(void)
{
	char listador[100];
	while(fgets(listador,100,arqClient) != NULL)
	{
		printf("%s", listador);
	}
    printf("\nPressione ENTER para voltar...\n");
    int c = getchar();
    flush_in();
	CLEAR_SCREEN;
}
//		Função para listar os produtos
void listProduct(void)
{
	char listador[100];
	while(fgets(listador,100,arqProduct) != NULL)
	{
		printf("%s", listador);
	}
    printf("\nPressione ENTER para voltar...\n");
    int c = getchar();
    flush_in();
	CLEAR_SCREEN;
}
//		Função para listar as vendas
void listSale(void)
{
	char listador[100];
	while(fgets(listador,100,arqSales) != NULL)
	{
		printf("%s", listador);
	}
    printf("\nPressione ENTER para voltar...\n");
    int c = getchar();           // Emulando um system pause
    flush_in();
	CLEAR_SCREEN;
}

//		Função para limpar o buffer
void flush_in() 
{
    int c;
    do {
        c = fgetc(stdin);
    } while (c != EOF && c != '\n');
}

int verify(char *palavra)
{
    for(int i=0; i<20; i++)
    {
        if((palavra[i] > 47 && palavra[i] < 58) || palavra[i] == 46)
        {
            return 1;
        }
        else
        {
            printf("Digite apenas números no código\n");
            printf("\nPressione ENTER para voltar...\n");
            int c = getchar();
            CLEAR_SCREEN;
            return 0;
        }
    }
}

int verifyDate(char *data)
{
    for(int i=0; i<10; i++)
    {
        if(i != 2 && i != 5)
        {
            if(data[i] > 47 && data[i] < 58)
            {
                if(data[2] == 47 && data[5] == 47)
                {
                    return 1;
                }
                else
                {
                    printf("Digite no formato padrão de data\n");
                    printf("DD/MM/AA\n");
                    printf("\nPressione ENTER para voltar...\n");
                    int c = getchar();
                    CLEAR_SCREEN;

                    return 0;     
                }            
            }
            else
                {
                    printf("Digite no formato padrão de data\n");
                    printf("DD/MM/AA\n");
                    printf("\nPressione ENTER para voltar...\n");
                    int c = getchar();
                    CLEAR_SCREEN;

                    return 0;     
                }
            
        }
    }
}
