/*******************************************************************/
/** IME-USP
/** MAC 110 - BMAC Noturno **/
/** Prof: Manoel Marcílio **/
/** **/
/** Segundo Exercicio Programa -- Listas Ligadas **/
/** **/
/** <Alexandre da Gama Lima> <N°USP: 5714645> **/
/*******************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TAMANHO_TABELA 50
#define TAMANHO_NOME_AGENCIA 4
#define INICIO_DA_NOTICIA 12
#define NUMERO_USP 5714645
#define TAMANHO_MSG 1000

typedef struct Cada_Noticia *Noticia;

struct Cada_Noticia {
   char Fonte[TAMANHO_NOME_AGENCIA];    /* 4 caracteres identificam a Fonte */
   char Texto[TAMANHO_MSG]; /* texto da notícia */
   Noticia PF;       /* ponteiro para a próxima notícia desta agência */
   Noticia PP;       /* ponteiro para a próxima notícia mais recente */
};

char TAB_AG[TAMANHO_TABELA][TAMANHO_NOME_AGENCIA]; /* nome de todas as agências */
Noticia PAG[TAMANHO_TABELA]; /* ponteiros para a primeira de cada agência */
Noticia PR; /* ponteiro para a lista em ordem de chegada */
int posicaoTabela = 0;

/*******************************************************************************
  Função utilizada para criar notícias de forma aleatória
 *******************************************************************************/
void GereNoticia(char nm[]) {
   static int nummsg = 0;
   
   static char n1[20][15] = {"BOVESPA", "CAMINHAO", "AVIAO", "POLITICO", "BARANGA", "CARRO", "CARRUAGEM", "CACHORRO",
      "CABRITO", "OLARIA", "JORNAL", "FILHO", "PAI", "AVO", "ALFINETE", "AGULHA", "SAPATO","RUA","LIVRO","QUADRO"};
   
   static char n2[20][15] = {"CORRE", "VOA", "ANDA", "MEXE", "CAPOTA", "SEGURA", "ESCULHAMBA", "VIRA", "SEPARA", 
      "MATA","RECEBE", "PAVONEIA", "SE TRANCA", "BEBE", "LOTA", "CELEBRA", "CHEIRA","MOVE","ABRE","LUBRIFICA"};
      
   static char n3[20][15] = {"RAPIDO","BAIXO", "O TERNO", "A CAMISA", "O SAPATO", "DORMINDO", "O TELEFONE", "ALTO", "CHAPADO",
      "A FACA", "TONTO", "LENTO", "GRANDE", "BONITO", "PEQUENO", "FEIO","BARATO", "CHORANDO","LOTADO", "VAZIO"};
   
   static char f[20][10] = {"UPII","UOLL","IGIG","GLOB","SBST","GAZT","RNTT","RPRES","EURO",
      "SCND","IBER","FRAN","KVTX","LIGO","KRIM","FATH","FBCC","SPFC","FDXT","FEKK"};
      
   int i,j,k,l; 
   char lf[] = {10, 0}; 
   char linha[] = {"*linha*00X\n"};
   
   /* cabecalho da noticia "AAAA - NNNNN" */
   nm[0] = 0;
   i = rand() % 20;
   strncat(nm, f[i], 4);
   strncat(nm, " - ", 3);
   sprintf(nm + 7, "%05d\n", ++ nummsg);
   
   /* concatena 3 */
   /* primeiro */
   i = rand() % 20;
   strncat(nm, n1[i], 15);
   strncat(nm, " ", 1);
   
   /* segundo nome */
   i = rand() % 20;
   strncat(nm, n2[i], 15);
   strncat(nm, " ", 1);
   
   /* terceiro nome */
   i = rand() % 20;
   strncat(nm, n3[i], 15);
   strncat(nm, " ", 1);
   
   /* proximas linhas */
   strncat(nm, lf, 1);
   j = rand() % 10; /* ate 10 linhas */
   
   for (i = 0; i <= j; i++) {
      k = rand() % 6;
      linha[8] = '0' + i / 10;
      linha[9] = '0' + i % 10;
   
      for(l = 0; l <= k; l++) 
         strncat(nm, linha, 10);
      strncat(nm, lf, 1);
   }   
}
   
/*******************************************************************************
  Função utilizada para criar a lista ligada utilizada para guardar a Agencia
  e o texto em si
 *******************************************************************************/   
Noticia criaLista(Noticia raiz) {
   raiz = (Noticia)malloc(sizeof(struct Cada_Noticia));
   raiz->PF = NULL;
   raiz->PP = NULL;
   
   return (raiz);
}   

/*******************************************************************************
  Função utilizada para atualizar o ponteiro que indica qual foi a última
  notícia que foi criada
 *******************************************************************************/   
void AtualizaListaDeOrdemDeChegada(Noticia nova) {
   if (PR == NULL) {
      PR = criaLista(PR);      
      PR = nova;
   }
   else {
      nova->PP = PR;
      PR = nova;
   }   
}

/*******************************************************************************
  Função utilizada para criar uma noticia de acordo com o texto gerado
  aleatoriamente.
 *******************************************************************************/   
Noticia criaNoticia(char NoticiaInteira[], Noticia n) {
   n = (Noticia)malloc(sizeof(struct Cada_Noticia));
   int i;
   //Nome da Agência    
   for (i = 0; i < TAMANHO_NOME_AGENCIA; i ++) {
      n->Fonte[i] = NoticiaInteira[i];
   }
   //Texto da notícia      
   for (int i = TAMANHO_NOME_AGENCIA; NoticiaInteira[i] != '\0'; i ++) {
      n->Texto[i] = NoticiaInteira[i];
   }
   n->PF = NULL;  
   return (n);   
}

/*******************************************************************************
  Função utilizada para criar a Agencia quando ela não existe na tabela de 
  agencias e cria a noticia
 *******************************************************************************/   
void criaAgenciaComNoticia(char NoticiaInteira[], int IndiceTabela) {
   Noticia n = criaNoticia(NoticiaInteira, n);    
   PAG[IndiceTabela] = n;
   AtualizaListaDeOrdemDeChegada(n);   
}
 
/*******************************************************************************
  Função utilizada para inserir uma noticia no inicio da Lista de Noticias
 *******************************************************************************/    
Noticia insereNoticiaNoInicio(char NoticiaInteira[], Noticia n) {
   Noticia nova;
   nova = (Noticia)malloc(sizeof(struct Cada_Noticia));
   int i;
   //Nome da Agência    
   for (i = 0; i < TAMANHO_NOME_AGENCIA; i ++) {
      nova->Fonte[i] = NoticiaInteira[i];
   }   
   //Texto da notícia      
   for (int i = TAMANHO_NOME_AGENCIA; NoticiaInteira[i] != '\0'; i ++) {
      nova->Texto[i] = NoticiaInteira[i];
   }   
   nova->PF = n;
   
   return (nova);
} 
   
/*******************************************************************************
  Função utilizada para inserir a Noticia na lista de noticias de uma Agencia
  já existente
 *******************************************************************************/      
void insereNoticiaNaAgenciaExistente(char NoticiaInteira[], int indiceTabela) {
   Noticia n = PAG[indiceTabela];
   Noticia nova = insereNoticiaNoInicio(NoticiaInteira, n);
   PAG[indiceTabela] = nova;
   AtualizaListaDeOrdemDeChegada(nova);
}   
   
/*******************************************************************************
  Função utilizada para inserir o nome da Noticia na tabela de noticias
 *******************************************************************************/      
void insereNaTabela(char NoticiaInteira[]) {
   int indiceTabela = 0;
   int i;
   
   for (indiceTabela = 0; indiceTabela < TAMANHO_TABELA && posicaoTabela > indiceTabela; indiceTabela ++) { //se indiceTabela for igual ao posicao, sinal que jah percorreu todos
      for (i = 0; i < TAMANHO_NOME_AGENCIA; i ++) { //Identifica se a Agencia já está na tabela
         if (NoticiaInteira[i] != TAB_AG[indiceTabela][i])          
            break;  
      }
      if (i == TAMANHO_NOME_AGENCIA) { //A Agencia existe na tabela
         insereNoticiaNaAgenciaExistente(NoticiaInteira, indiceTabela);
         break;
      }
   }
   //insere a nova Agencia na tabela com a noticia criada
   if (indiceTabela == posicaoTabela) {
      for (int i = 0; i < TAMANHO_NOME_AGENCIA; i ++) { 
         TAB_AG[indiceTabela][i] = NoticiaInteira[i];
      }   
      criaAgenciaComNoticia(NoticiaInteira, indiceTabela);
      posicaoTabela++;
   }     
}

/*******************************************************************************
  Função utilizada para imprimir as noticias na ordem de chegada
 *******************************************************************************/    
void imprimeEmOrdemDeChegada(int quantidade) {
   int opcao = 1;
   while (quantidade > 0 && PR != NULL) {
      if (opcao = 1) {
         printf("\nAgencia: ");
         for (int i = 0; i < TAMANHO_NOME_AGENCIA; i ++) {
             printf("%c", PR->Fonte[i]);
         }              
         printf("\nNoticia: ");
         for (int i = INICIO_DA_NOTICIA; PR->Texto[i]; i ++) {
             printf("%c", PR->Texto[i]);
         }                    
         printf("\n");      
         
         PR = PR->PP;
         quantidade --;
         if (quantidade > 0) {
            printf("\nDeseja imprimir a proxima noticia?");
            printf("\n1 - Sim");
            printf("\n0 - Nao");            
            printf("\nOpcao:");
            scanf("%d", &opcao);         
         }
      }
   }    
}

/*******************************************************************************
  Função utilizada para iniciar o progrma e criar as listas Ligadas
 *******************************************************************************/    
void criaAsListasLigadas() {
   char MSG[TAMANHO_MSG];
   int i;
   for (i = 0; i < 50; i++) {
      GereNoticia(MSG);
      insereNaTabela(MSG);
   }      
}

/*******************************************************************************
  Função utilizada para mostrar as Noticias das Agencias solicitadas
 *******************************************************************************/  
void mostrarNoticiasDaAgenciaSolicitada(char agencia[], int quantidade){
   int indiceTabela;
   int i;
   int opcao = 1;   
   
   for (indiceTabela = 0; indiceTabela < posicaoTabela; indiceTabela ++) {
      for (i = 0; i < TAMANHO_NOME_AGENCIA; i ++) {
         if (TAB_AG[indiceTabela][i] != agencia[i])
            break;
      }
      if (i == TAMANHO_NOME_AGENCIA) {         
         Noticia n = PAG[indiceTabela];                  
         while (quantidade > 0 && n != NULL) {          
            if (opcao == 1) {
               printf("\nNoticia: ");
               for (i = INICIO_DA_NOTICIA; n->Texto[i] != '\0'; i ++) {
                  printf("%c", n->Texto[i]);
               }            
               printf("\n");      
               
               n = n->PF;
               quantidade--;            
               if (quantidade > 0) {
                  printf("\nDeseja imprimir a proxima noticia?");
                  printf("\n1 - Sim");
                  printf("\n0 - Nao");            
                  printf("\nOpcao:");
                  scanf("%d", &opcao);                               
               }
            }
            else {
               break;   
            }                       
         }               
         break;   
      }
   }
   if (indiceTabela == posicaoTabela) {
      printf("\nA Agencia informada nao existe e serao impressas as %d ultimas noticias:\n", quantidade);
      imprimeEmOrdemDeChegada(quantidade);      
   }
}

void consultaNoticias() {
   int opcao = 1;
   int quantidade = 0;
   char agencia[TAMANHO_NOME_AGENCIA];
   
   printf("\n1 - Pesquisar noticias\n");
   printf("2 - Sair outro caracter pra sair\n");   
   printf("Digite a opcao desejada:");
   scanf("%d", &opcao);
   
   while (opcao == 1) {
      printf("\nDigite o nome da Agencia: ");
      scanf("%s", &agencia);
      printf("\nDigite a quantidade N de noticias:");
      scanf("%d", &quantidade);
      
      mostrarNoticiasDaAgenciaSolicitada(agencia, quantidade);

      printf("\n\nDigite a opcao desejada:");
      scanf("%d", &opcao);   
   } 
}

int main() {
   srand(NUMERO_USP);
   criaAsListasLigadas();
   consultaNoticias();   
   printf("\n\n");
   system("PAUSE");
}
