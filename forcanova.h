#define TAMANHO_PALAVRA 20
#define MAXIMO_DE_CHUTES 26
#define BANCO_DE_DADOS "palavras.txt"

void escreveabertura();
void desenhaforca();
int letraexiste(char l);
void limpatela();
void escolhepalavra();
void escrevermenuprincipal();
int chuteserrados();
int ganhou();
int perdeu();
void solicitachute();
void jogar();
int letraexistenapalavrasecreta(char l);
int letrajafoichutada(char l);
void limparglobais();
void adicionapalavra();
int contarpalavrasnobancodedados();