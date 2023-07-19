#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "forcanova.h"

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[MAXIMO_DE_CHUTES];
short numerodechutes = 0;

void escreveabertura() {
    printf("******************************\n");
    printf("********JOGO DA FORCA*********\n");
    printf("******************************\n");
}

void desenhaforca() {
    int erros = chuteserrados();

    printf("\n");
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c    %s\n", (erros >= 1 ? '('  :' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '), (erros >=6 ? "AAAAAAAAA VOCÊ VAI ME MATAAARRRRR!!!!!!!" : ""));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' :' '), (erros >= 2 ? '|' : ' '), (erros >= 4 ? '/' :  ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|'  :' '));
    printf(" |      %c %c   \n", (erros >= 5 ? '/'  :' '), (erros >= 6 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(short i = 0; i < strlen(palavrasecreta); i++) {
        int jafoichutada = letrajafoichutada(palavrasecreta[i]);

        if(jafoichutada) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
    }

    printf("\n\n");
}

void limparglobais() {
    memset(chutes, '\0', sizeof(chutes));
    numerodechutes = 0;
}

int letrajafoichutada(char l) {
    for (short j = 0; j < strlen(chutes); j++) {

        if(l == chutes[j]) {
            return 1;
        }
    }

    return 0;
}

void limpatela() {
    system("cls");
}

void escolhepalavra() {

    FILE* f;
    f = fopen(BANCO_DE_DADOS, "r");

    if(f == NULL || f == 0) {
        printf("Banco de dados indisponível\n\n");
        system("pause");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(short i = 0; i < randomico; i++) {
        fscanf(f, "%s", &palavrasecreta);
    }

    fclose(f);
}

int contarpalavrasnobancodedados() {
    FILE* f;

    f = fopen(BANCO_DE_DADOS, "r");

    if(f == 0) {
        printf("Banco de dados indisponível\n\n");
        exit(1);
    }

    int quantidadeatual;
    fscanf(f, "%d", &quantidadeatual);

    fclose(f);

    return quantidadeatual;
}

void listartodaspalavras() {
    FILE* f;
    f = fopen(BANCO_DE_DADOS, "r");

    if(f == NULL || f == 0) {
        printf("Banco de dados indisponível\n\n");
        system("pause");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    char palavra[TAMANHO_PALAVRA];
    for(short i = 0; i < qtddepalavras; i++) {
        fscanf(f, "%s", &palavra);
        printf("%d - %s\n", i, palavra);
    }

    fclose(f);

    printf("\n\n");
    system("pause");
}

void adicionapalavra() {

    char escolha;

    do {
        char novapalavra[TAMANHO_PALAVRA];

        printf("Qual a nova palavra? ");
        scanf("%s", &novapalavra);

        FILE* f;

        f = fopen(BANCO_DE_DADOS, "r+");

        if(f == 0) {
            printf("Banco de dados indisponível\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);

        printf("Deseja adicionar uma nova palavra ? (N) - Não");
        scanf(" %c", &escolha);
    } while(escolha != 'N' && escolha != 'n');
}

void escrevermenuprincipal() {
    limpatela();

    printf("Escolha uma opção:\n");
    printf("1 - JOGAR\n");
    printf("2 - INSERIR NOVA PALAVRA\n");
    printf("3 - LISTAR PALAVRAS - (Total de %d palavras)\n", contarpalavrasnobancodedados());
    printf("0 - SAIR\n");
}

int letraexistenapalavrasecreta(char l) {
    for(short i = 0; i < strlen(palavrasecreta); i++) {
        if(palavrasecreta[i] == l) {
            return 1;
        }
    }

    return 0;
}

int chuteserrados() {
    short erros = 0;

    for (short i = 0; i < strlen(chutes); i++) {
        short existe = letraexistenapalavrasecreta(chutes[i]);

        if(!existe) erros++;
    }

    return erros;
}

int ganhou() {

    for(short i = 0; i < strlen(palavrasecreta); i++) {
        if(!letrajafoichutada(palavrasecreta[i])) {
            return 0;
        }
    }

    return 1;
}

int perdeu() {
    return chuteserrados() >= 7;
}

void solicitachute() {
    printf("Digite seu chute: ");

    char chute;
    scanf(" %c", &chute);

    chutes[numerodechutes] = chute;
    numerodechutes++;
}

void jogar() {

    limparglobais();
    escolhepalavra();

    do {
        limpatela();
        escreveabertura();
        desenhaforca();
        solicitachute();
    }
    while (!ganhou() && !perdeu());

    limpatela();

    if(ganhou())
    {
        printf("\n\n");
        printf(" Parabéns, você ganhou!\n");
        printf("\n");
        printf("        ___________      \n");
        printf("       '._==_==_=_.'     \n");
        printf("       .-\\:      /-.    \n");
        printf("      | (|:.     |) |    \n");
        printf("       '-|:.     |-'     \n");
        printf("         \\::.    /      \n");
        printf("          '::. .'        \n");
        printf("            ) (          \n");
        printf("          _.' '._        \n");
        printf("         '-------'\n\n");
    }
    else {
        printf("\n\n");
        printf(" Puxa, você foi enforcado!\n");
        printf(" A palavra secreta era: %s\n", palavrasecreta);
        printf("\n");
        printf("     _______________         \n");
        printf("    /               \\       \n");
        printf("   /                 \\      \n");
        printf(" //                   \\/\\  \n");
        printf(" \\|   XXXX     XXXX   | /   \n");
        printf("  |   XXXX     XXXX   |/     \n");
        printf("  |   XXX       XXX   |      \n");
        printf("  |                   |      \n");
        printf("  \\__      XXX      __/     \n");
        printf("    |\\     XXX     /|       \n");
        printf("    | |           | |        \n");
        printf("    | I I I I I I I |        \n");
        printf("    |  I I I I I I  |        \n");
        printf("    \\_             _/       \n");
        printf("      \\_         _/         \n");
        printf("        \\_______/\n\n");
    }

    system("pause");
}

int main() {

    int op;

    while(op != 0) {

        limpatela();

        escrevermenuprincipal();
        scanf("%d", &op);

        limpatela();

        switch (op)
        {
            case 0:
                exit(0);
                break;
            case 1:
                jogar();
                break;
            case 2:
                adicionapalavra();
                break;
            case 3:
                listartodaspalavras();
                break;
            default:
                op = 1;
        }
    }

    return 0;
}