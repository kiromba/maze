/*
   Programa para demonstrar o uso de grafos de caminhamento
   dentro de um labirinto.
   Versao: 0.1a           Data:  15/11/2007

   Autor: Diogo Abreu Viana
   Autor: Eder Moreira
   Autor: Rui Fernandes
   Autor: Guilherme
   
   Obs.: Versao final desenvolvida com base
         na versão anterior de testes.
         Gfafo utilizado: Busca em Largura
*/

// lista de dependencias
#include <iostream>
#include <fstream>         // trabalhar com arquivos
#include <conio.h>         // trabalhar com posicionamento na tela
#include <conio2.h>        // trabalhar com posicionamento na tela
#include <consolecolor.h>  // trabalha com coloração de textos
#include <string.h>        // trabalha com tratamento strings
#include <dos.h>           // comandos do DOS como limpar tela
#include <stack>           // tratamento de pilha
#include <queue>           // tratamento de lista


using namespace std;

// ----------------------------------------------- estrutura criadas

/**
 * estrutura labirinto
 * criada para criar os atributos
 * que o labirinto possui.
 */
struct SLabirinto {
       string cor;   // cor da peça ( verde ou branco )
       char state;   // estado da peça ( branco ou preto )
       int  peca;    // código ASCII da peça
       bool left;    // se a peca existe saida pra esquerda ( true ou false )  
       bool right;   // se a peca existe saida pra esquerda ( true ou false )
       bool up;      // se a peca existe saida pra esquerda ( true ou false )
       bool down;    // se a peca existe saida pra esquerda ( true ou false )
       int  id;      // um numero identificador para a peça
       int  line;    // linha em que a peça está posicionada
       int  col;     // coluna em que a peça está posicionada
};

/**
 * estrutura ponto
 * criada para definir os atributos
 * dos pontos de origem e destino.
 */
struct SPonto {
       int line;
       int col;
};

// ----------------------------------------------- definicao de tipos

typedef queue <int> intQueue;
typedef stack <int> intStack;

// ------------------------------------------------ métodos 
/**
 * ler arquivo
 * @param matriz - matriz que guardará valores
 * @param limite - numero maximo de linhas utilizadas
 */
void fileRead( string nomeArquivo, SLabirinto matriz[45][55], int &limite )
{
    // vetor de associacao do codigo ASCII com as pecas
    int associacao[] = {16,30,200,17,205,188,202,31,201,186,204,187,203,185,206};

    char linha[ 80 ];             // guardar o conteúdo string de uma linha do arquivo
    char nome[ 15 ];              // guardar o nome do arquivo escolhido
    int  line,col;                // guardar a localização da peça extraída do arquivo
    int  peca,id = 0;             // guardar o código da peça extraido do arquivo
    FILE * arquivo;               // associar descritor ao arquivo externo   

    // transforma string em caractere, já que a função fopen nao aceita string
    strcpy ( nome, nomeArquivo.c_str ( ) );    

    // abrir arquivo para leitura
    arquivo = fopen( nome,"r" );

    // enquanto houver dados    
    while ( ! feof ( arquivo ) )
    {
       // ler outra linha do arquivo
       fscanf ( arquivo, "%s\n", linha );   // le o nome da peça
       fscanf ( arquivo, "%d\n", &col );    // le a coluna que a peça deve ser posicionada
       fscanf ( arquivo, "%d\n", &line );   // le a linha que a peça deve ser posicionada
       fscanf ( arquivo, "%d\n", &peca );   // le o código da peça

       // verifica qual a maior linha
       if ( line > limite ) limite = line;

       // grava o tile na posicao
       switch( associacao[ peca - 1 ] )
       {
         // verifica qual o código da peça ( total são 15 )
         case 16: matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça
                  matriz[ line ][ col ].cor  = "white";                // cor que a peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça
                  matriz[ line ][ col ].left = false;                  // saída para esquerda?
                  matriz[ line ][ col ].right= true;                   // saída para direita?
                  matriz[ line ][ col ].up   = false;                  // saída pra cima?
                  matriz[ line ][ col ].down = false;                  // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha em que está
                  matriz[ line ][ col ].col  = col;                    // coluna em que está
                  // termina a estrutura da peça 
                  break;

         case 17: matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça
                  matriz[ line ][ col ].cor  = "white";                // cor que peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça
                  matriz[ line ][ col ].left = true;                   // saída pra esquerda?
                  matriz[ line ][ col ].right= false;                  // saída pra direita?
                  matriz[ line ][ col ].up   = false;                  // saída pra cima?
                  matriz[ line ][ col ].down = false;                  // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha em que está
                  matriz[ line ][ col ].col  = col;                    // coluna em que está
                  // termina a estrutura da peça
                  break;

         case 30: matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça
                  matriz[ line ][ col ].cor  = "white";                // cor que a peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça   
                  matriz[ line ][ col ].left = false;                  // saída pra esquerda?
                  matriz[ line ][ col ].right= false;                  // saída pra direita?
                  matriz[ line ][ col ].up   = true;                   // saída pra cima?
                  matriz[ line ][ col ].down = false;                  // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha em que está
                  matriz[ line ][ col ].col  = col;                    // coluna em que está
                  // termina a estrutura da peça 
                  break;

         case 31: matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça
                  matriz[ line ][ col ].cor  = "white";                // cor que a peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça
                  matriz[ line ][ col ].left = false;                  // saída pra esquerda?
                  matriz[ line ][ col ].right= false;                  // saída pra direita?
                  matriz[ line ][ col ].up   = false;                  // saída pra cima?
                  matriz[ line ][ col ].down = true;                   // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha em que está
                  matriz[ line ][ col ].col  = col;                    // coluna em que está
                  // termina a estrutura da peça
                  break;

         case 185:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça
                  matriz[ line ][ col ].cor  = "white";                // cor que a peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça
                  matriz[ line ][ col ].left = true;                   // saída pra esquerda?
                  matriz[ line ][ col ].right= false;                  // saída pra direita?
                  matriz[ line ][ col ].up   = true;                   // saída pra cima?   
                  matriz[ line ][ col ].down = true;                   // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha em que está
                  matriz[ line ][ col ].col  = col;                    // coluna que está
                  // termina a estrutura da peça
                  break;

         case 186:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça
                  matriz[ line ][ col ].cor  = "white";                // cor que a peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça
                  matriz[ line ][ col ].left = false;                  // saída pra esquerda?
                  matriz[ line ][ col ].right= false;                  // saída pra direita?
                  matriz[ line ][ col ].up   = true;                   // saída pra cima?
                  matriz[ line ][ col ].down = true;                   // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que está
                  matriz[ line ][ col ].col  = col;                    // coluna que está
                  // termina a estrutura da peça
                  break;

         case 187:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça
                  matriz[ line ][ col ].cor  = "white";                // cor que a peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça
                  matriz[ line ][ col ].left = true;                   // saída pra esquerda?
                  matriz[ line ][ col ].right= false;                  // saída pra direita?
                  matriz[ line ][ col ].up   = false;                  // saída pra cima?
                  matriz[ line ][ col ].down = true;                   // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que está
                  matriz[ line ][ col ].col  = col;                    // coluna que está
                  // termina a estrutura da peça
                  break;

         case 188:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça
                  matriz[ line ][ col ].cor  = "white";                // cor que a peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça
                  matriz[ line ][ col ].left = true;                   // saída pra esquerda?
                  matriz[ line ][ col ].right= false;                  // saída pra direita?
                  matriz[ line ][ col ].up   = true;                   // saída pra cima?
                  matriz[ line ][ col ].down = false;                  // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que está
                  matriz[ line ][ col ].col  = col;                    // coluna que está
                  // termina a estrutura da peça
                  break;

         case 200:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça
                  matriz[ line ][ col ].cor  = "white";                // cor que a peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça
                  matriz[ line ][ col ].left = false;                  // saída pra esquerda?
                  matriz[ line ][ col ].right= true;                   // saída pra direita?
                  matriz[ line ][ col ].up   = true;                   // saída pra cima?
                  matriz[ line ][ col ].down = false;                  // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha em que está
                  matriz[ line ][ col ].col  = col;                    // coluna em que está
                  // termina a estrutura da peça
                  break;

         case 201:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça 
                  matriz[ line ][ col ].cor  = "white";                // cor que a peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça 
                  matriz[ line ][ col ].left = false;                  // saída pra esquerda?
                  matriz[ line ][ col ].right= true;                   // saída pra direita?
                  matriz[ line ][ col ].up   = false;                  // saída pra cima?
                  matriz[ line ][ col ].down = true;                   // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha em que está
                  matriz[ line ][ col ].col  = col;                    // coluna em que está
                  // termina a estrutura da peça
                  break;

         case 202:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça
                  matriz[ line ][ col ].cor  = "white";                // cor que a peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça
                  matriz[ line ][ col ].left = true;                   // saída pra esquerda?
                  matriz[ line ][ col ].right= true;                   // saída pra direita?
                  matriz[ line ][ col ].up   = true;                   // saída pra cima?
                  matriz[ line ][ col ].down = false;                  // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que está
                  matriz[ line ][ col ].col  = col;                    // coluna que está
                  // termina a estrutura da peça
                  break;

         case 203:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça
                  matriz[ line ][ col ].cor  = "white";                // cor que a peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça
                  matriz[ line ][ col ].left = true;                   // saída pra esquerda? 
                  matriz[ line ][ col ].right= true;                   // saída pra direita?
                  matriz[ line ][ col ].up   = false;                  // saída pra cima?
                  matriz[ line ][ col ].down = true;                   // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que está
                  matriz[ line ][ col ].col  = col;                    // coluna que está
                  // termina a estrutura da peça
                  break;

         case 204:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça
                  matriz[ line ][ col ].cor  = "white";                // cor que a peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça
                  matriz[ line ][ col ].left = false;                  // saída pra esquerda?
                  matriz[ line ][ col ].right= true;                   // saída pra direita?
                  matriz[ line ][ col ].up   = true;                   // saída pra cima?
                  matriz[ line ][ col ].down = true;                   // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que está  
                  matriz[ line ][ col ].col  = col;                    // coluna que está
                  // termina a estrutura da peça
                  break;

         case 205:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça
                  matriz[ line ][ col ].cor  = "white";                // cor que a peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça
                  matriz[ line ][ col ].left = true;                   // saída pra esquerda?
                  matriz[ line ][ col ].right= true;                   // saída pra direita?
                  matriz[ line ][ col ].up   = false;                  // saída pra cima?
                  matriz[ line ][ col ].down = false;                  // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que está
                  matriz[ line ][ col ].col  = col;                    // coluna que está
                  // termina a estrutura da peça
                  break;

         case 206:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // código da peça
                  matriz[ line ][ col ].cor  = "white";                // cor que a peça deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da peça
                  matriz[ line ][ col ].left = true;                   // saída pra esquerda?
                  matriz[ line ][ col ].right= true;                   // saída pra direita?
                  matriz[ line ][ col ].up   = true;                   // saída pra cima?
                  matriz[ line ][ col ].down = true;                   // saída pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que está
                  matriz[ line ][ col ].col  = col;                    // coluna que está 
                  // termina a estrutura da peça
                  break;
        };        

    } // fim enquanto houver dados
   
    // fechar arquivo apos ler tambem e' recomendavel
    fclose ( arquivo );
} // fim do método 

/**
 * limpa a matriz, para que nao tenha caracteres invalidos
 * @param matriz - matriz a ser limpa
 */
void clear( SLabirinto matriz[ 45 ][ 55 ] )
{
   // declaracao de variaveis do tipo inteira
   int l,c;    // controle da matriz
   int i=0;    // gera um identificador para o código

   // percorrer labirinto    
   for( l=0; l<45; l=l+1 )
   {
      for( c=0; c<55; c=c+1 )    
      {
         // todas as posições recebem o 0, para limpar o lixo 
         matriz[ l ][ c ].peca = 0; 

         // todas as posições recebem um identificador que é contado 
         // da esquerda pra direita, de cima pra baixo.
         matriz[ l ][ c ].id   = i;

         // contabilizamos e incrementamos o contador
         i = i + 1;
      }
      
   } // fim do for
} // fim do método


/**
 * mostrar labirinto na tela
 * @param matriz - matriz que com os valores a serem mostrados
 * @param limite - numero maximo de linhas utilizadas
 * @param ponto  - vetor com os pontos origem e destino 
 * @param i      - quantidade de pontos encontrados
 */
void show( SLabirinto matriz[ 45 ][ 55 ], int limite, SPonto ponto[], int &i )
{
   // declaracao de variaveis inteiras 
   int l,c;   // controlar a matriz 
   int peca;  // código da peça  

   // imprimir labirinto    
   for( l=0; l<limite+2; l=l+1 )
   {
      for( c=0; c<55; c=c+1 )    
      {
         // pega o código da peça 
         peca = matriz[ l ][ c ].peca;

         // se a peça for de origem ou destino, contabilizamos, para depois saber quantas são
         if( peca == 16 || peca == 17 || peca == 30 || peca == 31 )
         {             
             // gravamos a localização do ponto origem ou destino
             ponto[ i ].line = l;
             ponto[ i ].col  = c;
             // contabilizamos a quantidade de pontos encontrados 
             i = i + 1;         
         } // fim se 

         // teste de controle, aqui é verificada qual a cor do TILE 
         if( peca = matriz[ l ][ c ].cor == "green" )
             // imprime verde
             cout << green;
         else
             // imprime branco 
             cout << white;

         // aqui é feita a conversão do código(numero) para o código ASCII
         printf("%c", matriz[ l ][ c ].peca );  

         // se chegou ao final da coluna, desce para a linha de baixo.
         if( c == 54 ) cout << "\n";
         
      }
   } // fim do for

} // fim do método


/**
 * método principal que busca o caminho entre os pontos
 * @param matriz - vertice do ponto de origem
 * @param lab[][]- a estrutura inteira do labirinto
 * @param dLine  - linha do ponto destino
 * @param dCol   - coluna do ponto destino
 */
void buscaLargura( SLabirinto &matriz,SLabirinto lab[ 45 ][ 55 ], int dLine,int dCol )
{
   // inicializa fila   
   intQueue    fila;

   // inicializa pilha com as posições de linhas e colunas
   intStack    linhas,colunas;

   // inicializa variável de controle inteiras
   int         i;              // controla o id dos vértices 
   int         line,col;      // controle de colunas e linhas caminhadas

   // inicializa variáveis de controle boolean
   bool        find;          // se encontrou alguma saída da peça
   bool        final = false; // se encontrou o ponto de destino

   // pega a linha e coluna do vertice de origem 
   line = matriz.line;
   col  = matriz.col;

   // marca vertice de origem como visitado e sua cor como verde
   matriz.state = 'P';
   matriz.cor = "green";
 
   // coloca o identificador do vértice no final da fila
   fila.push ( matriz.id );

   // coloca as linhas e as colunas caminhadas em uma pilha
   linhas.push( line );   
   colunas.push( col );
   
   // enquanto a fila não estiver vazia e o destino não for encontrado 
   while( ! fila.empty() && !final )
   {
      // inicializa a abertura dos vertices como falso
      find = false;    

      // retira o vertice da fila 
      fila.pop();

      // pega o tipo da peca  
      i = lab[ line ][ col ].peca;

      // testa se a peça é de ponto destino
      if( i == 16 || i == 17 || i == 30 || i == 31 )
      {
         // verifica se essa peça de ponto de destino é a peça de DESTINO escolhida
         if( line == dLine && col == dCol )
         {
            // recebe true para não procurar por saídas no vértice
            find = true;
            // recebe true para não andar e sair do laço 
            final = true;            
            // escreve mensagem de sucesso na tela
            cout << "\nACHOU CARALHO!";
          } // fim se  
      } // fim se 

      // aqui começamos a verificar as saídas do vértice 

      // testa se há saída para a direita e se já não foi encontrada nenhuma saída       
      if( lab[ line ][ col ].right && !find )
      {
         // testa se o vértice já foi visitado 
         if( lab[ line ][ col + 1 ].state == 'B' )
         {
             // marca como visitado 
             lab[ line ][ col + 1 ].state = 'P';
             // colore como verde ( possível caminho )
             lab[ line ][ col + 1 ].cor   = "green";             

             // empilhamos a localização(linha e coluna) do vértice visitado
             linhas.push( line );
             colunas.push( col + 1 );

             // gravamos a localização(linha e coluna) desse vértice para ele ser o próximo 
             line = linhas.top( );
             col  = colunas.top( );

             // colocamos no final da fila o identificador do vértice
             fila.push( lab[ line ][ col + 1 ].id );

             // find recebe true para que não procure por outras saídas
             find = true;
         }
      } // fim se 

      // testa se há saída para a esquerda e se já não foi encontrada nenhuma saída             
      if( lab[ line ][ col ].left && !find )
      {
        // testa se o vértice já foi visitado 
         if( lab[ line ][ col - 1 ].state == 'B' )
         {
             // marca como visitado
             lab[ line ][ col - 1 ].state = 'P';
             // colore com a cor verde
             lab[ line ][ col - 1 ].cor   = "green";             

             // empilhamos a localização(linha e coluna) do vértice visitado
             linhas.push( line );
             colunas.push( col - 1 );

             // gravamos a localização(linha e coluna) desse vértice para ele ser o próximo 
             line = linhas.top( );
             col  = colunas.top( );

             // colocamos no final da fila o identificador do vértice             
             fila.push( lab[ line ][ col - 1 ].id );

              // find recebe true para que não procure por outras saídas
             find = true;
         }
      } // fim do vertice 

      // testa se há saída para cima e se já não foi encontrada nenhuma saída
      if( lab[ line ][ col ].up  && !find )
      {
         // testa se o vértice já foi visitado 
         if( lab[ line - 1 ][ col ].state == 'B' )
         {
             // marca como visitado
             lab[ line - 1 ][ col ].state = 'P';
             // colore com a cor verde
             lab[ line - 1 ][ col ].cor   = "green";

             // empilhamos a localização(linha e coluna) do vértice visitado
             linhas.push( line - 1 );
             colunas.push( col );

             // gravamos a localização(linha e coluna) desse vértice para ele ser o próximo 
             line = linhas.top( );
             col  = colunas.top( );

             // colocamos no final da fila o identificador do vértice             
             fila.push( lab[ line - 1 ][ col ].id );

              // find recebe true para que não procure por outras saídas             
             find = true;
         }

      } // fim do vértice 

      // testa se há saída para cima e se já não foi encontrada nenhuma saída
      if( lab[ line ][ col ].down  && !find )
      {
         // testa se o vértice já foi visitado 
         if( lab[ line + 1 ][ col ].state == 'B' )
         {
             // marca como visitado
             lab[ line + 1 ][ col ].state = 'P';
             // colore com a cor verde 
             lab[ line + 1 ][ col ].cor   = "green";

             // empilhamos a localização(linha e coluna) do vértice visitado
             linhas.push( line + 1 );
             colunas.push( col );

             // gravamos a localização(linha e coluna) desse vértice para ele ser o próximo 
             line = linhas.top( );
             col  = colunas.top( );

             // colocamos no final da fila o identificador do vértice
             fila.push( lab[ line + 1 ][ col ].id );

             // find recebe true para que não procure por outras saídas
             find = true;
         }

      } // fim do vértice 


      // caso nao encontrado nenhuma saida possível para o vértice
      if( !find  )
      {        
         // inserimos no fim da fila o identificador do vértice 
         fila.push( lab[ line ][ col ].id );

         // colorimos o vértice com a cor branca
         lab[ line ][ col ].cor = "white";

         // o próximo vértice a ser visitado será o anterior a esse, por isso buscamos 
         // a localização no final da pilha 
         line = linhas.top( );
         col  = colunas.top( );

         // retiramos a último vertice da pilha
         linhas.pop();
         colunas.pop();
      
      } // fim se 
      
   } // fim do while
 
} // fim do método 




// ------------------------------------------------ parte principal
int main ( void )
{
    // declaracao das variáveis do tipo inteira
    int limite = 0;     // limite de linhas do labirinto 
    int tipo;           // o tipo do labirinto que o usuário quer ( entre 1 e 5 )
    int i=0;            // quantidade de pontos(de destino e origem) encontrados no labirinto
    int origem,destino; // pontos de origem e destino
    int line,col;       // localização dos pontos 

    // declaração das variáveis do tipo struct
    SLabirinto labirinto[ 45 ][ 55 ];  // matriz principal que contém o labirinto
    SPonto ponto[ 130 ];               // vetor que contém todos os pontos(destino e origem) do labirinto
 
    // declaração do vetor com os nome dos arquivos que possuem os labirintos
    string nomeArquivo[] = {"normal1.lab.txt","normal2.lab.txt","normal3.lab.txt","normal4.lab.txt","normal5.lab.txt"};
    

    // identificação do programa 
    do {
        gotoxy(15,2);cout << "IMPLEMENTACAO DE ALGORITMOS DE CAMINHAMENTO EM GRAFOS v0.1a";
        gotoxy(15,3);cout << "-----------------------------------------------------------";

        // opcoes de labirinto
        gotoxy(25,4);cout << "Tipo de labirinto:";
        gotoxy(25,6);cout << "1 - Labirinto 1 (medio)";
        gotoxy(25,7);cout << "2 - Labirinto 2 (medio)";
        gotoxy(25,8);cout << "3 - Labirinto 3 (pequeno)";
        gotoxy(25,9);cout << "4 - Labirinto 4 (grande)";
        gotoxy(25,10);cout << "5 - Labirinto 5 (grande)";
        gotoxy(25,12);cout << "Selecione:";
        gotoxy(35,12);cin >> tipo;

    // ficará preso caso digite uma opção inválida 
    } while( tipo < 1 || tipo > 5 );

    // limpa a tela 
    clrscr();

    // limpa o labirinto para que não apareça caracteres indesejados
    clear( labirinto );

    // chamada do método de leitura do arquivo e montagem do labirinto
    fileRead( nomeArquivo[ tipo - 1 ], labirinto, limite );

    // chamada do método que exibe o labirinto
    show( labirinto, limite, ponto, i );    

    // agora é pedido os pontos de origem e destino 
    cout << "\nDigite o pontos para origem e destino. Entre ( 1 e " << i << " )";
    cout << "\nOrigem:";
    cin  >> origem;
    cout << "\nDestino:";
    cin  >> destino;

    // corrigimos a posição dos pontos de origem e destino 
    origem = origem - 1;
    destino= destino- 1;

    // pega a localização do ponto de origem, que é o "pontapé inicial" do programa
    line = ponto[ origem ].line;
    col  = ponto[ origem ].col;

    // chamada para o método principal que vasculha o labirinto em busca de caminho
    buscaLargura( labirinto[ line ][ col ], labirinto,ponto[ destino ].line,ponto[ destino ].col );   

    // limpa a tela 
    clrscr();

    // após a localização do caminho, imprimimos o labirinto novamente, mas agora com o caminho
    // encontrado colorido de verde 
    show( labirinto, limite, ponto, i );    
    
    // encerrar
    cout << "\nApertar ENTER para terminar." ;
    getch ( );
    return ( EXIT_SUCCESS );
} // fim main ( )
