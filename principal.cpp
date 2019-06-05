
#include <iostream>
#include <fstream>
#include <cstring>

//Constantes de tamanho de imagem

const int MAXALTURA  = 500;			//tamanho maximo aceito (pode ser alterado)
const int MAXLARGURA = 500;

using namespace std;

void lerImagem( ifstream arqentrada, int &largura, int &altura, char tipo[4], ){

}

//Programa principal

int main() {
	unsigned char imagem[MAXALTURA][MAXLARGURA];	//a imagem propriamente dita
	int largura, altura;							//dimensoes da imagem
	char tipo[4];									//tipo da imagem
	ifstream arqentrada;							//arquivo que contem a imagem original
	ofstream arqsaida;								//arquivo que contera a imagem gerada
	char comentario[200], c;						//auxiliares
	int i, j, valor;								//auxiliares


// LEITURA DA IMAGEM-------------------------------------------------------------

//inicialmente nao sera necessario entender nem mudar nada nesta parte

	// Abertura do arquivo

	arqentrada.open("arquivo.pnm",ios::in); //Abre arquivo para leitura
	if (!arqentrada) {
		cout << "Nao consegui abrir arquivo.pnm\n";
		return 0;
	}
//-------------------------------------------------------------------------------

	
	// Leitura do cabecalho -------------------------------------------
	arqentrada >> tipo;	//Le o tipo de arquivo
	arqentrada.get();	//Le e descarta o \n do final da 1a. linha

	if (strcmp(tipo,"P2")==0) {
		cout << "Imagem em tons de cinza\n"; 
	}
	else if (strcmp(tipo,"P3")==0) {
		cout << "Imagem colorida\n";
		cout << "Desculpe, mas ainda nao trabalho com esse tipo de imagem.\n"; 
		arqentrada.close();
		return 0;
	}
	else if (strcmp(tipo,"P5")==0 || strcmp(tipo,"P6")==0) {
		cout << "Imagem no formato RAW\n";
		cout << "Desculpe, mas nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}

	while((c = arqentrada.get()) == '#')	//Enquanto for comentario
		arqentrada.getline(comentario,200);	//Le e descarta a linha "inteira"

	arqentrada.putback(c);	//Devolve o caractere lido para a entrada, pois como
							//nao era comentario, era o primeiro digito da largura

	arqentrada >> largura >> altura;	//Le o numero de pixels da horizontal e vertical
	cout << "Tamanho: " << largura << " x " << altura << endl;
	if (largura>MAXLARGURA) {
		cout << "Desculpe, mas ainda nao trabalho com imagens com mais de " << MAXLARGURA << " pixels de largura.\n";
		arqentrada.close();
		return 0;
	}
	if (largura>MAXALTURA) {
		cout << "Desculpe, mas ainda nao trabalho com imagens com mais de " << MAXALTURA << " pixels de altura.\n";
		arqentrada.close();
		return 0;
	}
	
	arqentrada >> valor;	//Valor maximo do pixel (temos que ler, mas nao sera usado)

	// FIM DA LEITURA DO CABEÇALHO ------------------------------------

	// Leitura dos pixels da imagem -----------------------------------
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
			arqentrada >> valor;
			imagem[i][j] = (unsigned char)valor;
		}
	//-----------------------------------------------------------------

	arqentrada.close();

// FIM DA LEITURA DA IMAGEM -----------------------------------------------------------




// TRATAMENTO DA IMAGEM ---------------------------------------------------------------
//Inicialmente é nesta parte do codigo que voce vai trabalhar

	int fator;
	cout << "Qual o fator de escurecimento (1-100) ? ";
	cin >> fator;

	// Escurece a imagem ----------------------------------------------------
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
			valor = (int)imagem[i][j];				//pega o valor do pixel
			valor -= fator;							//escurece o pixel
			if (valor<0)							//se der negativo
				valor = 0;							//  deixa preto
			imagem[i][j] = (unsigned char)valor;	//modifica o pixel
		}
    //-----------------------------------------------------------------------

// FIM DO TRATAMENTO DA IMAGEM -----------------------------------------------------------



// GRAVACAO DA IMAGEM --------------------------------------------------------------------
//Inicialmente nao sera necessario entender nem mudar nada nesta parte

	// Grava a nova imagem --------------------------------------------------
	arqsaida.open("novaimagem.pnm",ios::out);	//Abre arquivo para escrita
	if (!arqsaida) {
		cout << "Nao consegui criar novaimagem.pnm\n";
		return 0;
	}

	arqsaida << tipo << endl;						//tipo
	arqsaida << "# INF110\n";						//comentario
	arqsaida << largura << " " << altura << endl;	//dimensoes
	arqsaida << 255 << endl;						//maior valor
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++)
			arqsaida << (int)imagem[i][j] << endl;	//pixels

	arqsaida.close();		//fecha o arquivo
	//----------------------------------------------------------------------

// FIM DA GRAVACAO DA IMAGEM -------------------------------------------------------------

	return 0;
}