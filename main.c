#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

//----------------------------------------------------
#ifdef _WIN32
#define limpa_tela() system("cls")
#else
#define limpa_tela() system("clear")
#endif
//----------------------------------------------------
void limpar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}
//----------------------------------------------------
typedef struct usuario
{
    char nome[50];
    char telefone[20];
    char email[50];
    char nascimento[20];
    struct usuario *anterior;
    struct usuario *proximo;
} usuario;

usuario *inicio = NULL;
//-----------------------------------------------------

void ascii()
{
    printf("\n");
    printf("    .--.                   .---.                  .--.             \n");
    printf(".---|__|           .-.     |~~~|              .---|__|            \n");
    printf("|===|--|_          |_|     |~~~|--.   .---.   |===|--|       .----.         \n");
    printf("|===|  |'\\     .---!~|  .--|   |--|---|   |---|===|  |-.     |====|         \n");
    printf("|   |  |.'\\    |===| |--|  |   |  |   |~~~|===|   |  |.'\\    |====|   \n");
    printf("|   |  |\\.'\\   |   | |__|  |   |  |___|   |   |   |  |\\.'\\   |    |       \n");
    printf("|   |  | \\  \\  |===| |==|  |   |  |___|   |===|   |  | \\  \\  |    |  \n");
    printf("|___|__|  \\.'\\ |   |_|__|  |~~~|__|   |~~~|   |___|__|  \\.'\\ |====|   \n");
    printf("|===|--|   \\.'\\|===|~|--|  |~~~|--|   |   |===|===|--|   \\.'\\|====|      \n");
    printf("^---^--^    `-'`---^-^--^--^---'--'---'---'---^---^--^    `-''----'        \n");
    printf("===================================================================\n");
    printf(">>>>>>>>>> SISTEMA DE CADASTRO DE USUARIOS DA BIBLIOTECA <<<<<<<<<<\n");
    printf("===================================================================\n\n");
}

void menu()
{
    printf("                \t[1] Adicionar Usuario\n");
    printf("                \t[2] Buscar Usuario\n");
    printf("                \t[3] Listar Usuarios\n");
    printf("                \t[4] Navegar Usuarios\n");
    printf("                \t[5] Remover Usuario\n");
    printf("                \t[6] Salvar Dados\n");
    printf("                \t[7] Sair\n");
    printf("\n                \t> Escolha uma opção: ");
}

void saida()
{
    limpa_tela();
    printf("\n\t\t (`/\\\n");
    printf("\t\t `=\\/\\ __...--~~~~~-._   _.-~~~~~--...__\n");
    printf("\t\t  `=\\/\\               \\ /               \\\\\n");
    printf("\t\t   `=\\/                V                 \\\\\n");
    printf("\t\t   //_\\___--~~~~~~-._  |  _.-~~~~~~--...__\\\\\n");
    printf("\t\t  //  ) (..----~~~~._\\ | /_.~~~~----.....__\\\\\n");
    printf("\t\t ===( INK )==========\\\\|//====================\n");
    printf("\t\t                     `---`\n");
    printf("\n\n       #+===========================================================+#  \n");
    printf("      |     Sistema desenvolvido por Rafaela, Davi, Julia e Isabele   |  \n");
    printf("     |                                                                 |  \n");
    printf("      |                         - Versao 1.0 -                        |\n");
    printf("       #+===========================================================+#\n");
}

int validar_nome(const char *nome) {
    if (strlen(nome) < 2) return 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        char c = nome[i];
        if (!(isalpha(c) || c == ' ' || (unsigned char)c >= 128)) {
            return 0;
        }
    }
    return 1;
}

int validar_email(const char *email) {
    const char *arroba = strchr(email, '@');
    const char *ponto = strrchr(email, '.');
    return (arroba && ponto && arroba < ponto && ponto > email && strlen(ponto) > 1);
}

int validar_telefone(const char *telefone) {
    for (int i = 0; telefone[i]; i++) {
        if (!isdigit(telefone[i]))
            return 0;
    }
    return strlen(telefone) >= 8;
}

int validar_data(const char *data) {
    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/')
        return 0;

    int dia, mes, ano;
    if (sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano) != 3)
        return 0;

    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900 || ano > 2100)
        return 0;

    return 1;
}

usuario *entrada_valida_usuario() {
    usuario *novo = (usuario *)malloc(sizeof(usuario));
    if (novo == NULL) {
        printf("                    Erro de alocação de memoria.\n");
        exit(1);
    }

    do {
        printf("                    Nome: ");
        fgets(novo->nome, sizeof(novo->nome), stdin);
        novo->nome[strcspn(novo->nome, "\n")] = '\0';

        if (!validar_nome(novo->nome)) {
            printf("                    \t > Nome invalido! Use apenas letras e espaços.\n");
        }
    } while (!validar_nome(novo->nome));

    do {
        printf("                    Telefone: ");
        fgets(novo->telefone, sizeof(novo->telefone), stdin);
        novo->telefone[strcspn(novo->telefone, "\n")] = '\0';

        if (!validar_telefone(novo->telefone)) {
            printf("                    \t > Telefone invalido! Use apenas números (mín. 8 dígitos).\n");
        }
    } while (!validar_telefone(novo->telefone));

    do {
        printf("                    Data de Nascimento (DD/MM/AAAA): ");
        fgets(novo->nascimento, sizeof(novo->nascimento), stdin);
        novo->nascimento[strcspn(novo->nascimento, "\n")] = '\0';

        if (!validar_data(novo->nascimento)) {
            printf("                    \t > Data invalida! Use o formato DD/MM/AAAA.\n");
        }
    } while (!validar_data(novo->nascimento));

    do {
        printf("                    Email: ");
        fgets(novo->email, sizeof(novo->email), stdin);
        novo->email[strcspn(novo->email, "\n")] = '\0';

        if (!validar_email(novo->email)) {
            printf("                    \t > Email invalido! Lembre-se do '@' e do '.'.\n");
        }
    } while (!validar_email(novo->email));

    novo->anterior = NULL;
    novo->proximo = NULL;

    return novo;
}

void inserir_usuario() {
    limpa_tela();
    ascii();
    printf("                    >>> INSERIR NOVO USUARIO <<<\n\n");

    usuario *novo = entrada_valida_usuario();

    if (inicio == NULL) {
        inicio = novo;
    } else {
        usuario *atual = inicio;
        while (atual->proximo) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
        novo->anterior = atual;
    }

    printf("\n                    Usuario adicionado com sucesso!\n");
    getchar(); // Espera uma tecla
}

void buscar_usuario()
{
    limpa_tela();
    ascii();
    printf("                \t>>> BUSCAR USUARIO <<<\n");

    char busca[50];
    printf("\n                   Digite o nome do usuario: ");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    char busca_min[50];
    for (int i = 0; busca[i]; i++)
        busca_min[i] = tolower((unsigned char)busca[i]);
    busca_min[strlen(busca)] = '\0';

    usuario *atual = inicio;
    int achou = 0;

    while (atual)
    {
        char nome_min[100];
        for (int i = 0; atual->nome[i]; i++)
            nome_min[i] = tolower((unsigned char)atual->nome[i]);
        nome_min[strlen(atual->nome)] = '\0';

        if (strstr(nome_min, busca_min) != NULL)
        {
            printf("\n                \tUsuario encontrado:\n");
            printf("                \tNome: %s\n", atual->nome);
            printf("                \tTelefone: %s\n", atual->telefone);
            printf("                \tEmail: %s\n", atual->email);
            printf("                \tNascimento: %s\n", atual->nascimento);
            achou = 1;
        }

        atual = atual->proximo;
    }

    if (!achou)
    {
        printf("\n Usuario não encontrado!");
    }

    printf("\n Pressione Enter para voltar ao menu...");
    getchar();
}

void listar_usuarios()
{
    limpa_tela();
    ascii();
    printf("                \t>>> LISTANDO USUARIOS <<<\n");

    if (inicio == NULL)
    {
        printf("\n Nenhum usuario cadastrado.\n");
    }
    else
    {
        usuario *atual = inicio;
        int i = 1;
        while (atual)
        {
            printf("\n                \tUsuario %d:\n", i++);
            printf("                \tNome: %s\n", atual->nome);
            printf("                \tTelefone: %s\n", atual->telefone);
            printf("                \tEmail: %s\n", atual->email);
            printf("                \tNascimento: %s\n", atual->nascimento);
            atual = atual->proximo;
        }
    }

    printf("\n Pressione Enter para voltar ao menu...");
    getchar();
}

void navegar_usuarios()
{
    if (inicio == NULL)
    {
        limpa_tela();
        ascii();
        printf(" Nenhum usuario cadastrado para navegar.\n");
        printf(" Pressione Enter para voltar ao menu...");
        getchar();
        return;
    }

    usuario *atual = inicio;
    char opcao;

    do
    {
        limpa_tela();
        ascii();
        printf("                       >>> NAVEGAR USUARIO <<<\n\n");
        printf("                       Nome: %s\n", atual->nome);
        printf("                       Telefone: %s\n", atual->telefone);
        printf("                       Email: %s\n", atual->email);
        printf("                       Nascimento: %s\n\n", atual->nascimento);

        printf("             [P] Proximo  |  [A] Anterior  |  [S] Sair\n\n");
        printf("                       Escolha uma opção: ");
        opcao = getchar();
        while (getchar() != '\n')
            ;

        if (tolower(opcao) == 'p')
        {
            if (atual->proximo != NULL)
            {
                atual = atual->proximo;
            }
            else
            {
                printf("\nVoce esta no último usuario.\n");
                printf(" Pressione Enter para continuar...");
                getchar();
            }
        }
        else if (tolower(opcao) == 'a')
        {
            if (atual->anterior != NULL)
            {
                atual = atual->anterior;
            }
            else
            {
                printf("\nVocê esta no primeiro usuario.\n");
                printf(" Pressione Enter para continuar...");
                getchar();
            }
        }
        else if (tolower(opcao) == 's')
        {
            break;
        }
        else
        {
            printf("\nOpcao invalida. Tente novamente.\n");
            printf(" Pressione Enter para continuar...");
            getchar();
        }
    } while (1);
}

void carregar_do_arquivo()
{
    FILE *arquivo = fopen("usuarios_biblioteca.txt", "r");
    if (!arquivo)
        return;

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo))
    {
        usuario *novo = (usuario *)malloc(sizeof(usuario));
        sscanf(linha, "%49[^;];%19[^;];%49[^;];%19[^\n]",
               novo->nome, novo->telefone, novo->email, novo->nascimento);
        novo->anterior = NULL;
        novo->proximo = NULL;

        if (inicio == NULL)
        {
            inicio = novo;
        }
        else
        {
            usuario *atual = inicio;
            while (atual->proximo)
                atual = atual->proximo;
            atual->proximo = novo;
            novo->anterior = atual;
        }
    }

    fclose(arquivo);
}

void remover_usuario()
{
    limpa_tela();
    ascii();
    printf("                       >>> REMOVER USUARIO <<<\n");

    char busca[50];
    printf("\n                Digite o nome EXATO do usuario a remover: ");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    for (usuario *atual = inicio; atual != NULL; atual = atual->proximo)
    {
        if (strcasecmp(atual->nome, busca) == 0)
        {
            if (atual->anterior)
                atual->anterior->proximo = atual->proximo;
            else
                inicio = atual->proximo;
            if (atual->proximo)
                atual->proximo->anterior = atual->anterior;

            free(atual);
            printf("\n usuario removido com sucesso!\n");
            getchar();
            return;
        }
    }

    printf("\n usuario não encontrado!\n");
    getchar();
}

void liberar_lista()
{
    usuario *atual = inicio;
    while (atual)
    {
        usuario *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}

void salvar_em_arquivo()
{
    FILE *arquivo = fopen("usuarios_biblioteca.txt", "w");
    if (!arquivo)
    {
        printf("Erro ao abrir arquivo para salvamento.\n");
        return;
    }

    usuario *atual = inicio;
    while (atual)
    {
        fprintf(arquivo, "%s;%s;%s;%s\n", atual->nome, atual->telefone, atual->email, atual->nascimento);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("\n  Usuarios salvos em 'usuarios_biblioteca.txt' com sucesso!\n");
    getchar();
}

int main()
{
    carregar_do_arquivo();

    int opcao;
    char salvar;

    do
    {
        limpa_tela();
        ascii();
        menu();
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao)
        {
        case 1:
            inserir_usuario();
            break;
        case 2:
            buscar_usuario();
            break;
        case 3:
            listar_usuarios();
            break;
        case 4:
            navegar_usuarios();
            break;
        case 5:
            remover_usuario();
            break;
        case 6:
            salvar_em_arquivo();
            break;
        case 7:
            do
            {
                printf("\nDeseja salvar as alteracoes antes de sair? (S/N): ");
                scanf(" %c", &salvar);
                limpar_buffer();

                if (tolower(salvar) == 's')
                {
                    salvar_em_arquivo();
                    saida();
                    break;
                }
                else if (tolower(salvar) == 'n')
                {
                    printf("\n  Alteracoes descartadas!\n");
                    printf("\n > Pressione ENTER para sair...");
                    getchar();
                    saida();
                    break;
                }
                else
                {
                    printf("\n Opcoo invalida. Digite apenas S ou N.\n");
                }

            } while (1);
            break;

        default:
            printf("\n Opção invalida. Tente novamente.\n");
            limpar_buffer();
        }
    } while (opcao != 7);

    liberar_lista();
    return 0;
}
