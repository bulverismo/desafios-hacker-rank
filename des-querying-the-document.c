/*
 * Código feito por José Américo para desafio do site HackerRank
 * https://www.hackerrank.com/challenges/querying-the-document/leaderboard
 *
 * 29/12/2020
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

// Parte do código que eu que fiz

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
  
  return document[n-1][m-1][k-1];

}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
  return document[m-1][k-1];
}

char*** kth_paragraph(char**** document, int k) {
  return document[k-1];
}

char**** get_document(char* text) {
  char *aux=text;     // Variavel auxiliara que ira percorrer por cada char do texto
  char**** tudo;      // Variável que vai conter o texto completo ja separado em 4 dimensões

  tudo = (char****) malloc ( MAX_PARAGRAPHS *sizeof(char***));  // serão no máximo 5 paragrafos dentro de todo o texto
  
  char*** paragrafo; // variavel que guardara cada pargrafo temporariamente
  paragrafo = (char***) malloc ( MAX_CHARACTERS * sizeof(char) );      // o paragrafo terá no máximo 1005 chars

  int qtdPgfs=0;    // variavel usada para contar a quantidade de paragrafos 
 
  char** sentenca; // variavel que guardara cada sentenca temporariamente
  sentenca = (char**) malloc ( MAX_CHARACTERS * sizeof(char) );    // cada sentença terá no máximo 1005 chars 
  
  int qtdStcs=0;      // variavel auxiliar acumula quantidade de sentenças em cada paragrafo temporariamente

  char* palavra;      // variavel que guardara cada palavra temporariamente
  
  int qtdPlvs=0;        // variavel auxiliar para acumular a quantidade de palavras em cada sentença temporariamente

  // documento todo esta na variável
  // text

  // paragrafos
  // contar , usar o \n como fim de um paragrafo
  // ultimo não tem um \n 

  // sentenças
  // contar usando o . (ponto) como fim de uma sentença
  // ao fim de uma sentença sempre há um ponto final
  
  // palavras
  // contar usando o espaço como fim de uma palavra
  // ultima palavra não tem espaço 
  

  // adiciona um \n ao fim do texto para auxiliar na hora de passar o texto para dentro do array
  text[strlen(text)]='\n';

  // reserva um espç de memória para cada palavra, no problema não informava o tamanho máximo de uma palavra
  palavra = (char*) malloc ( 40 * sizeof(char) );

  // inicializa as variáveis auxiliares 
  qtdPlvs=0;
  qtdStcs=0;
  qtdPgfs=0;
  aux = text;

  // variavel atual que vai conter um contador auxiliar para achar ao caracter atual e adicionar na palavra atual
  int ch=0;

  // usa a variavel aux pois ela tem simplesmente um string que acaba com \0 terminador nulo, portanto quando encontrar o terminador nulo
  // não entrará na repetição sendo o fim que necessitamos
  // observação:
  // aux é ponteiro para um char
  // *aux equivale a um char
  while ( *aux )
  {
    // recebe letra atual a partir da posição atual do ponteiro e na sequencia ja move ele para a proxima posição
    char letra = *(aux++);

    // adiciona o char atual na palavra atual, se não for nenhum dos terminadores de palavra, sentença ou paragrafo
    *(palavra+(ch++)) = letra != ' ' && letra != '.' && letra != '\n' ? letra : '\0';

    // se a letra atual for um terminador então entra nesse if
    if ( letra == '\n' || letra =='.' || letra == ' ' )
    {

      // ve qual terminador letra é 
      switch ( letra )
      {

        case ' ' :      // Se char atual é o espaço quer dizer que chegou ao final de uma palavra
                        // então adicionar ao final de sentença atual a palavra atual
          
          *(sentenca+qtdPlvs) = palavra;
         
          // qtdPlvs é a variavel auxiliar que nos ajuda a saber quantas palavras ja foram 
          // adicionadas a sentença atual, quando acaba a sentença atual esta variavel é 
          // zerada e usamos outro endereço de memória para a proxima sentença
          qtdPlvs++;

          // pede um novo espaço de memória para usar para a próxima palavra
          palavra = (char*) malloc ( 40 * sizeof(char) );

        break;
 
        case '.' :      // Se char atual é o ponto final quer dizer que chegou ao final de uma sentença 
                        // então adicionar ao final de paragrafo atual a sentença atual

          // antes de adicionar a sentença atual no paragrafo atual temos que adicionar a ultima palavra da frase
          // na sentença atual pois ele não se enquadrou no caso anterior pois não acabou com espaço mas sim 
          // com ponto final, acontece isso com todas as ultimas palavras das frases como ja descrito acima
          *(sentenca+qtdPlvs) = palavra;

          // zerada a variavel auxiliar que nos ajudava a saber quantas palavras havia dentro desta
          // sentença atual que estamos finalizando agora
          qtdPlvs = 0;

          // mesmo que acontece no caso anterior, reservamos espaço para a proxima palavra em um novo endereço de 
          // memória 
          palavra = (char*) malloc ( 40 * sizeof(char) );

          // agora sim finalmente adicionamos a sentença atual no paragrafo atual
          *(paragrafo+qtdStcs) = sentenca;
          
          // raciocinio analogo ao da descrição da variável qtdPlvs só que para ajudar a sabermos a posição que 
          // devemos adicionar algo na variável paragrafo
          qtdStcs++;

          // finalizando a sentença reservamos espaço em memória para criarmos a proxima sentença
          sentenca = (char**) malloc ( MAX_CHARACTERS * sizeof(char) );

        break;

        case '\n' :     // raciocinio analogo aos outros casos do switch
        
          *(tudo+qtdPgfs) = paragrafo;

          qtdPgfs++;
         
          qtdStcs=0;
          
          paragrafo = (char***) malloc ( MAX_CHARACTERS * sizeof(char) );

        break;

      }

      // se entrou no if quer dizer que terminou a palavra atual, portanto zera a variavel 
      // ch que é uma auxiliar para saber em qual posição da palavra eu estou
      ch=0;
    }

  }
  // retorna variável com tudo   
  return tudo;
}

// Parte do código que já existia

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
            
        }

        

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
            exit (0);
        }
        printf("\n");
    }     
}
