/*
   Programa para demonstrar o uso de grafos de caminhamento
   dentro de um labirinto.
   Versao: 0.1a           Data:  15/11/2007

   Autor: Diogo Abreu Viana
   Autor: Eder Moreira
   Autor: Rui Fernandes
   Autor: Guilherme
   
   Obs.: Versao final desenvolvida com base
         na vers�o anterior de testes.
         Gfafo utilizado: Busca em Largura
*/

// lista de dependencias
#include <iostream>
#include <fstream>         // trabalhar com arquivos
#include <conio.h>         // trabalhar com posicionamento na tela
#include <conio2.h>        // trabalhar com posicionamento na tela
#include <consolecolor.h>  // trabalha com colora��o de textos
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
       string cor;   // cor da pe�a ( verde ou branco )
       char state;   // estado da pe�a ( branco ou preto )
       int  peca;    // c�digo ASCII da pe�a
       bool left;    // se a peca existe saida pra esquerda ( true ou false )  
       bool right;   // se a peca existe saida pra esquerda ( true ou false )
       bool up;      // se a peca existe saida pra esquerda ( true ou false )
       bool down;    // se a peca existe saida pra esquerda ( true ou false )
       int  id;      // um numero identificador para a pe�a
       int  line;    // linha em que a pe�a est� posicionada
       int  col;     // coluna em que a pe�a est� posicionada
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

// ------------------------------------------------ m�todos 
/**
 * ler arquivo
 * @param matriz - matriz que guardar� valores
 * @param limite - numero maximo de linhas utilizadas
 */
void fileRead( string nomeArquivo, SLabirinto matriz[45][55], int &limite )
{
    // vetor de associacao do codigo ASCII com as pecas
    int associacao[] = {16,30,200,17,205,188,202,31,201,186,204,187,203,185,206};

    char linha[ 80 ];             // guardar o conte�do string de uma linha do arquivo
    char nome[ 15 ];              // guardar o nome do arquivo escolhido
    int  line,col;                // guardar a localiza��o da pe�a extra�da do arquivo
    int  peca,id = 0;             // guardar o c�digo da pe�a extraido do arquivo
    FILE * arquivo;               // associar descritor ao arquivo externo   

    // transforma string em caractere, j� que a fun��o fopen nao aceita string
    strcpy ( nome, nomeArquivo.c_str ( ) );    

    // abrir arquivo para leitura
    arquivo = fopen( nome,"r" );

    // enquanto houver dados    
    while ( ! feof ( arquivo ) )
    {
       // ler outra linha do arquivo
       fscanf ( arquivo, "%s\n", linha );   // le o nome da pe�a
       fscanf ( arquivo, "%d\n", &col );    // le a coluna que a pe�a deve ser posicionada
       fscanf ( arquivo, "%d\n", &line );   // le a linha que a pe�a deve ser posicionada
       fscanf ( arquivo, "%d\n", &peca );   // le o c�digo da pe�a

       // verifica qual a maior linha
       if ( line > limite ) limite = line;

       // grava o tile na posicao
       switch( associacao[ peca - 1 ] )
       {
         // verifica qual o c�digo da pe�a ( total s�o 15 )
         case 16: matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a
                  matriz[ line ][ col ].cor  = "white";                // cor que a pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a
                  matriz[ line ][ col ].left = false;                  // sa�da para esquerda?
                  matriz[ line ][ col ].right= true;                   // sa�da para direita?
                  matriz[ line ][ col ].up   = false;                  // sa�da pra cima?
                  matriz[ line ][ col ].down = false;                  // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha em que est�
                  matriz[ line ][ col ].col  = col;                    // coluna em que est�
                  // termina a estrutura da pe�a 
                  break;

         case 17: matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a
                  matriz[ line ][ col ].cor  = "white";                // cor que pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a
                  matriz[ line ][ col ].left = true;                   // sa�da pra esquerda?
                  matriz[ line ][ col ].right= false;                  // sa�da pra direita?
                  matriz[ line ][ col ].up   = false;                  // sa�da pra cima?
                  matriz[ line ][ col ].down = false;                  // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha em que est�
                  matriz[ line ][ col ].col  = col;                    // coluna em que est�
                  // termina a estrutura da pe�a
                  break;

         case 30: matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a
                  matriz[ line ][ col ].cor  = "white";                // cor que a pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a   
                  matriz[ line ][ col ].left = false;                  // sa�da pra esquerda?
                  matriz[ line ][ col ].right= false;                  // sa�da pra direita?
                  matriz[ line ][ col ].up   = true;                   // sa�da pra cima?
                  matriz[ line ][ col ].down = false;                  // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha em que est�
                  matriz[ line ][ col ].col  = col;                    // coluna em que est�
                  // termina a estrutura da pe�a 
                  break;

         case 31: matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a
                  matriz[ line ][ col ].cor  = "white";                // cor que a pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a
                  matriz[ line ][ col ].left = false;                  // sa�da pra esquerda?
                  matriz[ line ][ col ].right= false;                  // sa�da pra direita?
                  matriz[ line ][ col ].up   = false;                  // sa�da pra cima?
                  matriz[ line ][ col ].down = true;                   // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha em que est�
                  matriz[ line ][ col ].col  = col;                    // coluna em que est�
                  // termina a estrutura da pe�a
                  break;

         case 185:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a
                  matriz[ line ][ col ].cor  = "white";                // cor que a pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a
                  matriz[ line ][ col ].left = true;                   // sa�da pra esquerda?
                  matriz[ line ][ col ].right= false;                  // sa�da pra direita?
                  matriz[ line ][ col ].up   = true;                   // sa�da pra cima?   
                  matriz[ line ][ col ].down = true;                   // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha em que est�
                  matriz[ line ][ col ].col  = col;                    // coluna que est�
                  // termina a estrutura da pe�a
                  break;

         case 186:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a
                  matriz[ line ][ col ].cor  = "white";                // cor que a pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a
                  matriz[ line ][ col ].left = false;                  // sa�da pra esquerda?
                  matriz[ line ][ col ].right= false;                  // sa�da pra direita?
                  matriz[ line ][ col ].up   = true;                   // sa�da pra cima?
                  matriz[ line ][ col ].down = true;                   // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que est�
                  matriz[ line ][ col ].col  = col;                    // coluna que est�
                  // termina a estrutura da pe�a
                  break;

         case 187:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a
                  matriz[ line ][ col ].cor  = "white";                // cor que a pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a
                  matriz[ line ][ col ].left = true;                   // sa�da pra esquerda?
                  matriz[ line ][ col ].right= false;                  // sa�da pra direita?
                  matriz[ line ][ col ].up   = false;                  // sa�da pra cima?
                  matriz[ line ][ col ].down = true;                   // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que est�
                  matriz[ line ][ col ].col  = col;                    // coluna que est�
                  // termina a estrutura da pe�a
                  break;

         case 188:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a
                  matriz[ line ][ col ].cor  = "white";                // cor que a pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a
                  matriz[ line ][ col ].left = true;                   // sa�da pra esquerda?
                  matriz[ line ][ col ].right= false;                  // sa�da pra direita?
                  matriz[ line ][ col ].up   = true;                   // sa�da pra cima?
                  matriz[ line ][ col ].down = false;                  // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que est�
                  matriz[ line ][ col ].col  = col;                    // coluna que est�
                  // termina a estrutura da pe�a
                  break;

         case 200:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a
                  matriz[ line ][ col ].cor  = "white";                // cor que a pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a
                  matriz[ line ][ col ].left = false;                  // sa�da pra esquerda?
                  matriz[ line ][ col ].right= true;                   // sa�da pra direita?
                  matriz[ line ][ col ].up   = true;                   // sa�da pra cima?
                  matriz[ line ][ col ].down = false;                  // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha em que est�
                  matriz[ line ][ col ].col  = col;                    // coluna em que est�
                  // termina a estrutura da pe�a
                  break;

         case 201:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a 
                  matriz[ line ][ col ].cor  = "white";                // cor que a pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a 
                  matriz[ line ][ col ].left = false;                  // sa�da pra esquerda?
                  matriz[ line ][ col ].right= true;                   // sa�da pra direita?
                  matriz[ line ][ col ].up   = false;                  // sa�da pra cima?
                  matriz[ line ][ col ].down = true;                   // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha em que est�
                  matriz[ line ][ col ].col  = col;                    // coluna em que est�
                  // termina a estrutura da pe�a
                  break;

         case 202:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a
                  matriz[ line ][ col ].cor  = "white";                // cor que a pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a
                  matriz[ line ][ col ].left = true;                   // sa�da pra esquerda?
                  matriz[ line ][ col ].right= true;                   // sa�da pra direita?
                  matriz[ line ][ col ].up   = true;                   // sa�da pra cima?
                  matriz[ line ][ col ].down = false;                  // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que est�
                  matriz[ line ][ col ].col  = col;                    // coluna que est�
                  // termina a estrutura da pe�a
                  break;

         case 203:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a
                  matriz[ line ][ col ].cor  = "white";                // cor que a pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a
                  matriz[ line ][ col ].left = true;                   // sa�da pra esquerda? 
                  matriz[ line ][ col ].right= true;                   // sa�da pra direita?
                  matriz[ line ][ col ].up   = false;                  // sa�da pra cima?
                  matriz[ line ][ col ].down = true;                   // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que est�
                  matriz[ line ][ col ].col  = col;                    // coluna que est�
                  // termina a estrutura da pe�a
                  break;

         case 204:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a
                  matriz[ line ][ col ].cor  = "white";                // cor que a pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a
                  matriz[ line ][ col ].left = false;                  // sa�da pra esquerda?
                  matriz[ line ][ col ].right= true;                   // sa�da pra direita?
                  matriz[ line ][ col ].up   = true;                   // sa�da pra cima?
                  matriz[ line ][ col ].down = true;                   // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que est�  
                  matriz[ line ][ col ].col  = col;                    // coluna que est�
                  // termina a estrutura da pe�a
                  break;

         case 205:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a
                  matriz[ line ][ col ].cor  = "white";                // cor que a pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a
                  matriz[ line ][ col ].left = true;                   // sa�da pra esquerda?
                  matriz[ line ][ col ].right= true;                   // sa�da pra direita?
                  matriz[ line ][ col ].up   = false;                  // sa�da pra cima?
                  matriz[ line ][ col ].down = false;                  // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que est�
                  matriz[ line ][ col ].col  = col;                    // coluna que est�
                  // termina a estrutura da pe�a
                  break;

         case 206:matriz[ line ][ col ].peca = associacao[ peca - 1 ]; // c�digo da pe�a
                  matriz[ line ][ col ].cor  = "white";                // cor que a pe�a deve ser colorida
                  matriz[ line ][ col ].state= 'B';                    // estado da pe�a
                  matriz[ line ][ col ].left = true;                   // sa�da pra esquerda?
                  matriz[ line ][ col ].right= true;                   // sa�da pra direita?
                  matriz[ line ][ col ].up   = true;                   // sa�da pra cima?
                  matriz[ line ][ col ].down = true;                   // sa�da pra baixo?
                  matriz[ line ][ col ].line = line;                   // linha que est�
                  matriz[ line ][ col ].col  = col;                    // coluna que est� 
                  // termina a estrutura da pe�a
                  break;
        };        

    } // fim enquanto houver dados
   
    // fechar arquivo apos ler tambem e' recomendavel
    fclose ( arquivo );
} // fim do m�todo 

/**
 * limpa a matriz, para que nao tenha caracteres invalidos
 * @param matriz - matriz a ser limpa
 */
void clear( SLabirinto matriz[ 45 ][ 55 ] )
{
   // declaracao de variaveis do tipo inteira
   int l,c;    // controle da matriz
   int i=0;    // gera um identificador para o c�digo

   // percorrer labirinto    
   for( l=0; l<45; l=l+1 )
   {
      for( c=0; c<55; c=c+1 )    
      {
         // todas as posi��es recebem o 0, para limpar o lixo 
         matriz[ l ][ c ].peca = 0; 

         // todas as posi��es recebem um identificador que � contado 
         // da esquerda pra direita, de cima pra baixo.
         matriz[ l ][ c ].id   = i;

         // contabilizamos e incrementamos o contador
         i = i + 1;
      }
      
   } // fim do for
} // fim do m�todo


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
   int peca;  // c�digo da pe�a  

   // imprimir labirinto    
   for( l=0; l<limite+2; l=l+1 )
   {
      for( c=0; c<55; c=c+1 )    
      {
         // pega o c�digo da pe�a 
         peca = matriz[ l ][ c ].peca;

         // se a pe�a for de origem ou destino, contabilizamos, para depois saber quantas s�o
         if( peca == 16 || peca == 17 || peca == 30 || peca == 31 )
         {             
             // gravamos a localiza��o do ponto origem ou destino
             ponto[ i ].line = l;
             ponto[ i ].col  = c;
             // contabilizamos a quantidade de pontos encontrados 
             i = i + 1;         
         } // fim se 

         // teste de controle, aqui � verificada qual a cor do TILE 
         if( peca = matriz[ l ][ c ].cor == "green" )
             // imprime verde
             cout << green;
         else
             // imprime branco 
             cout << white;

         // aqui � feita a convers�o do c�digo(numero) para o c�digo ASCII
         printf("%c", matriz[ l ][ c ].peca );  

         // se chegou ao final da coluna, desce para a linha de baixo.
         if( c == 54 ) cout << "\n";
         
      }
   } // fim do for

} // fim do m�todo


/**
 * m�todo principal que busca o caminho entre os pontos
 * @param matriz - vertice do ponto de origem
 * @param lab[][]- a estrutura inteira do labirinto
 * @param dLine  - linha do ponto destino
 * @param dCol   - coluna do ponto destino
 */
void buscaLargura( SLabirinto &matriz,SLabirinto lab[ 45 ][ 55 ], int dLine,int dCol )
{
   // inicializa fila   
   intQueue    fila;

   // inicializa pilha com as posi��es de linhas e colunas
   intStack    linhas,colunas;

   // inicializa vari�vel de controle inteiras
   int         i;              // controla o id dos v�rtices 
   int         line,col;      // controle de colunas e linhas caminhadas

   // inicializa vari�veis de controle boolean
   bool        find;          // se encontrou alguma sa�da da pe�a
   bool        final = false; // se encontrou o ponto de destino

   // pega a linha e coluna do vertice de origem 
   line = matriz.line;
   col  = matriz.col;

   // marca vertice de origem como visitado e sua cor como verde
   matriz.state = 'P';
   matriz.cor = "green";
 
   // coloca o identificador do v�rtice no final da fila
   fila.push ( matriz.id );

   // coloca as linhas e as colunas caminhadas em uma pilha
   linhas.push( line );   
   colunas.push( col );
   
   // enquanto a fila n�o estiver vazia e o destino n�o for encontrado 
   while( ! fila.empty() && !final )
   {
      // inicializa a abertura dos vertices como falso
      find = false;    

      // retira o vertice da fila 
      fila.pop();

      // pega o tipo da peca  
      i = lab[ line ][ col ].peca;

      // testa se a pe�a � de ponto destino
      if( i == 16 || i == 17 || i == 30 || i == 31 )
      {
         // verifica se essa pe�a de ponto de destino � a pe�a de DESTINO escolhida
         if( line == dLine && col == dCol )
         {
            // recebe true para n�o procurar por sa�das no v�rtice
            find = true;
            // recebe true para n�o andar e sair do la�o 
            final = true;            
            // escreve mensagem de sucesso na tela
            cout << "\nACHOU CARALHO!";
          } // fim se  
      } // fim se 

      // aqui come�amos a verificar as sa�das do v�rtice 

      // testa se h� sa�da para a direita e se j� n�o foi encontrada nenhuma sa�da       
      if( lab[ line ][ col ].right && !find )
      {
         // testa se o v�rtice j� foi visitado 
         if( lab[ line ][ col + 1 ].state == 'B' )
         {
             // marca como visitado 
             lab[ line ][ col + 1 ].state = 'P';
             // colore como verde ( poss�vel caminho )
             lab[ line ][ col + 1 ].cor   = "green";             

             // empilhamos a localiza��o(linha e coluna) do v�rtice visitado
             linhas.push( line );
             colunas.push( col + 1 );

             // gravamos a localiza��o(linha e coluna) desse v�rtice para ele ser o pr�ximo 
             line = linhas.top( );
             col  = colunas.top( );

             // colocamos no final da fila o identificador do v�rtice
             fila.push( lab[ line ][ col + 1 ].id );

             // find recebe true para que n�o procure por outras sa�das
             find = true;
         }
      } // fim se 

      // testa se h� sa�da para a esquerda e se j� n�o foi encontrada nenhuma sa�da             
      if( lab[ line ][ col ].left && !find )
      {
        // testa se o v�rtice j� foi visitado 
         if( lab[ line ][ col - 1 ].state == 'B' )
         {
             // marca como visitado
             lab[ line ][ col - 1 ].state = 'P';
             // colore com a cor verde
             lab[ line ][ col - 1 ].cor   = "green";             

             // empilhamos a localiza��o(linha e coluna) do v�rtice visitado
             linhas.push( line );
             colunas.push( col - 1 );

             // gravamos a localiza��o(linha e coluna) desse v�rtice para ele ser o pr�ximo 
             line = linhas.top( );
             col  = colunas.top( );

             // colocamos no final da fila o identificador do v�rtice             
             fila.push( lab[ line ][ col - 1 ].id );

              // find recebe true para que n�o procure por outras sa�das
             find = true;
         }
      } // fim do vertice 

      // testa se h� sa�da para cima e se j� n�o foi encontrada nenhuma sa�da
      if( lab[ line ][ col ].up  && !find )
      {
         // testa se o v�rtice j� foi visitado 
         if( lab[ line - 1 ][ col ].state == 'B' )
         {
             // marca como visitado
             lab[ line - 1 ][ col ].state = 'P';
             // colore com a cor verde
             lab[ line - 1 ][ col ].cor   = "green";

             // empilhamos a localiza��o(linha e coluna) do v�rtice visitado
             linhas.push( line - 1 );
             colunas.push( col );

             // gravamos a localiza��o(linha e coluna) desse v�rtice para ele ser o pr�ximo 
             line = linhas.top( );
             col  = colunas.top( );

             // colocamos no final da fila o identificador do v�rtice             
             fila.push( lab[ line - 1 ][ col ].id );

              // find recebe true para que n�o procure por outras sa�das             
             find = true;
         }

      } // fim do v�rtice 

      // testa se h� sa�da para cima e se j� n�o foi encontrada nenhuma sa�da
      if( lab[ line ][ col ].down  && !find )
      {
         // testa se o v�rtice j� foi visitado 
         if( lab[ line + 1 ][ col ].state == 'B' )
         {
             // marca como visitado
             lab[ line + 1 ][ col ].state = 'P';
             // colore com a cor verde 
             lab[ line + 1 ][ col ].cor   = "green";

             // empilhamos a localiza��o(linha e coluna) do v�rtice visitado
             linhas.push( line + 1 );
             colunas.push( col );

             // gravamos a localiza��o(linha e coluna) desse v�rtice para ele ser o pr�ximo 
             line = linhas.top( );
             col  = colunas.top( );

             // colocamos no final da fila o identificador do v�rtice
             fila.push( lab[ line + 1 ][ col ].id );

             // find recebe true para que n�o procure por outras sa�das
             find = true;
         }

      } // fim do v�rtice 


      // caso nao encontrado nenhuma saida poss�vel para o v�rtice
      if( !find  )
      {        
         // inserimos no fim da fila o identificador do v�rtice 
         fila.push( lab[ line ][ col ].id );

         // colorimos o v�rtice com a cor branca
         lab[ line ][ col ].cor = "white";

         // o pr�ximo v�rtice a ser visitado ser� o anterior a esse, por isso buscamos 
         // a localiza��o no final da pilha 
         line = linhas.top( );
         col  = colunas.top( );

         // retiramos a �ltimo vertice da pilha
         linhas.pop();
         colunas.pop();
      
      } // fim se 
      
   } // fim do while
 
} // fim do m�todo 




// ------------------------------------------------ parte principal
int main ( void )
{
    // declaracao das vari�veis do tipo inteira
    int limite = 0;     // limite de linhas do labirinto 
    int tipo;           // o tipo do labirinto que o usu�rio quer ( entre 1 e 5 )
    int i=0;            // quantidade de pontos(de destino e origem) encontrados no labirinto
    int origem,destino; // pontos de origem e destino
    int line,col;       // localiza��o dos pontos 

    // declara��o das vari�veis do tipo struct
    SLabirinto labirinto[ 45 ][ 55 ];  // matriz principal que cont�m o labirinto
    SPonto ponto[ 130 ];               // vetor que cont�m todos os pontos(destino e origem) do labirinto
 
    // declara��o do vetor com os nome dos arquivos que possuem os labirintos
    string nomeArquivo[] = {"normal1.lab.txt","normal2.lab.txt","normal3.lab.txt","normal4.lab.txt","normal5.lab.txt"};
    

    // identifica��o do programa 
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

    // ficar� preso caso digite uma op��o inv�lida 
    } while( tipo < 1 || tipo > 5 );

    // limpa a tela 
    clrscr();

    // limpa o labirinto para que n�o apare�a caracteres indesejados
    clear( labirinto );

    // chamada do m�todo de leitura do arquivo e montagem do labirinto
    fileRead( nomeArquivo[ tipo - 1 ], labirinto, limite );

    // chamada do m�todo que exibe o labirinto
    show( labirinto, limite, ponto, i );    

    // agora � pedido os pontos de origem e destino 
    cout << "\nDigite o pontos para origem e destino. Entre ( 1 e " << i << " )";
    cout << "\nOrigem:";
    cin  >> origem;
    cout << "\nDestino:";
    cin  >> destino;

    // corrigimos a posi��o dos pontos de origem e destino 
    origem = origem - 1;
    destino= destino- 1;

    // pega a localiza��o do ponto de origem, que � o "pontap� inicial" do programa
    line = ponto[ origem ].line;
    col  = ponto[ origem ].col;

    // chamada para o m�todo principal que vasculha o labirinto em busca de caminho
    buscaLargura( labirinto[ line ][ col ], labirinto,ponto[ destino ].line,ponto[ destino ].col );   

    // limpa a tela 
    clrscr();

    // ap�s a localiza��o do caminho, imprimimos o labirinto novamente, mas agora com o caminho
    // encontrado colorido de verde 
    show( labirinto, limite, ponto, i );    
    
    // encerrar
    cout << "\nApertar ENTER para terminar." ;
    getch ( );
    return ( EXIT_SUCCESS );
} // fim main ( )
