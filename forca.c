#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "forca.h"

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void escreveabertura() {
    printf("JOGO DA FORCA\n");
}

void chuta() {
    printf("\nEscreva seu chute: ");
    char chute;
    scanf(" %c", &chute);
    chutes[chutesdados] = chute;
    (chutesdados)++;
}

int jachutou(char letra) {
    int achou = 0;

    for(short j = 0; j < chutesdados; j++) {
        if(letra == chutes[j]) {
            achou = 1;
            break;
        } else {
            
        }
    }

    return achou;
}

void desenhaforca() {

    int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(short i = 0; i < strlen(palavrasecreta); i++) {
        
        int achou = jachutou(palavrasecreta[i]);

        if(achou)
        {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
    }
}

void escolhepalavra() {

    FILE* f;

    f = fopen("palavras.txt", "r");

    if(f == 0) {
        printf("Banco de dados indisponível\n\n");
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

void adicionapalavra() {

    char escolha;
    printf("Deseja adicionar uma nova palavra? (S/N)");
    scanf(" %c", &escolha);

    if(escolha == 'S') {
        char novapalavra[TAMANHO_PALAVRA];

        printf("Qual a nova palavra? ");
        scanf("%s", &novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");

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
    }
}

int chuteserrados() {
    short erros = 0;

    for (short i = 0; i < chutesdados; i++) {
        short existe = 0;

        for(short j = 0; j < strlen(palavrasecreta); j++) {
            if(chutes[i] == palavrasecreta[j]) {
                existe = 1;
                break;
            }
        }

        if(!existe) erros++;
    }

    return erros;
}

int enforcou() {
    return chuteserrados() >= 5;
}

int acertou() {
    for(short i = 0; i < strlen(palavrasecreta); i++) {
        if(!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }

    return 1;
}

int main() {

    escolhepalavra();
    escreveabertura();

    do {

        desenhaforca(palavrasecreta, chutes, chutesdados);
        chuta(chutes, &chutesdados);

    } while (!acertou() && !enforcou());

    if(acertou())
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

    adicionapalavra();
}