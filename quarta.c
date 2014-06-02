
#include <my_global.h>
#include <mysql.h>

#include <stdio.h>
#include <string.h>

//funcs infile

void finish_with_error(MYSQL *con);
int inserirArtigo(MYSQL *con, char *descri, char* marca, char* price, char* amount, char* box, char* barcode, char* directory);
int get_line(char *buffer, int bsize);
float get_float();
char *itoa(long i, char* s, int dummy_radix);
void desenhaInserirArtigo(char *descri, char* marca, char* price, char* amount, char* box, char* barcode, char* directory);
void desenhaMenuInit();
void fazRename(char* codbarras);
void cicloSubmit(MYSQL *con);


//codigo

void finish_with_error(MYSQL *con) {
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

int inserirArtigo(MYSQL *con, char *descri, char* marca, char* price, char* amount, char* box, char* barcode, char* directory) {
      char myStatement[300] = "INSERT INTO tabelaPrimal (Descricao, Marca, Pvp, Quant, Caixa, CODbarras, Foto) VALUES(\"";

      strcat(myStatement, descri);
      strcat(myStatement, "\", \"");
      strcat(myStatement, marca);
      strcat(myStatement, "\", ");
      strcat(myStatement, price);
      strcat(myStatement, ", ");
      strcat(myStatement, amount);
      strcat(myStatement, ", ");
      strcat(myStatement, box);
      strcat(myStatement, ", ");
      strcat(myStatement, barcode);
      strcat(myStatement, ", \"");
      strcat(myStatement, directory);
      strcat(myStatement, ".jpeg");
      strcat(myStatement, "\")");
      
      
      //printf("olha o estate:\n%s\n", myStatement);

      if (mysql_query(con, myStatement)) 
      {
	    printf("erro com inserção do artigo\nFechar tudo e mensagem de erro é:\n");
	    finish_with_error(con);
      }
      return 0;
}


int get_line(char *buffer, int bsize) {
    int ch, len;

    fgets(buffer, bsize, stdin);

    /* remove unwanted characters from the buffer */
    buffer[strcspn(buffer, "\r\n")] = '\0';

    len = strlen(buffer);

    /* clean input buffer if needed */
    if(len == bsize - 1)
        while ((ch = getchar()) != '\n' && ch != EOF);

    return len;
}


float get_float() {
    int len;
    char *buffer;
    double covertFloat;
    len = get_line(buffer, 6);
    covertFloat = atof(buffer);
    
    return (float)covertFloat;
}


char *itoa(long i, char* s, int dummy_radix) {
    sprintf(s, "%ld", i);
    return s;
}

void desenhaInserirArtigo(char *descri, char* marca, char* price, char* amount, char* box, char* barcode, char* directory) {
      if (system("clear") == -1)
	    printf("error clearing\n");
      printf("+++++++++++++++++++++++++++++++++");
      printf("\n");
      printf("+                               +");
      printf("\n");
      printf("Descrição:");
      if (descri != NULL)
	    printf(" %s",descri);
      printf("\n");
      printf("Marca:");
      if (descri != NULL)
	    printf(" %s",marca);
      printf("\n");
      printf("Preço:");
      if (descri != NULL)
	    printf(" %s",price);
      printf("\n");
      printf("Quantidade:");
      if (descri != NULL)
	    printf(" %s",amount);
      printf("\n");
      printf("Nrº caixa:");
      if (descri != NULL)
	    printf(" %s",box);
      printf("\n");
      printf("Cód. Barras:");
      if (descri != NULL)
	    printf(" %s",barcode);
      printf("\n");
      printf("Diretório da foto:");
      if (descri != NULL)
	    printf(" %s.jpeg",directory);
      printf("\n");
      printf("+                               +");
      printf("\n");
      printf("+++++++++++++++++++++++++++++++++");
      printf("\n");
}


void desenhaMenuInit() {
      if (system("clear") == -1)
	    printf("error clearing\n");
      printf("+++++++++++++++++++++++++++++++++");
      printf("\n");
      printf("+                               +");
      printf("\n");
      printf("+ 1- inserir artigos em série   +");
      printf("\n");
      printf("+ 2- inserir apenas um artigo   +");
      printf("\n");
      printf("+ q- sair                       +");
      printf("\n");
      printf("+                               +");
      printf("\n");
      printf("+++++++++++++++++++++++++++++++++");
      printf("\n");
      
      printf("\ninserir escolha:");
}


void fazRename(char* codbarras) {
      char primmetade [] = "rename stockimage ";
      char comando [50];
      
      strcpy(comando, primmetade);

      strcat(comando, codbarras);
      strcat(comando, " ");
      strcat(comando, "stock/stockimage.jpeg");
      
      printf("olha o rename:\n%s\n", comando);
      if (system(comando) == -1) {
	    printf("deu berro para renomear a foto\n");
	    exit(1);
      }
}


void cicloSubmit(MYSQL *con) {
      int lineSize;
      
      char descript [50];
      char brand [20];
      char covertPvp [10];
      char covertQnt [10];	
      char covertCaixa [10];
      char covertBarra [30];
      
      char nomeFile [50];
      char resposta [5]; 	
      char confirmate [] = "c"; char bigConf [] = "C";
      char sayyes [] = "y"; 	char bigYes [] = "Y";

//make sure its all neat

      memset(nomeFile, ' ', (unsigned)strlen(nomeFile));
      memset(descript, ' ', (unsigned)strlen(descript));
      memset(brand, ' ', (unsigned)strlen(brand));
      memset(resposta, ' ', (unsigned)strlen(resposta));
      nomeFile[0] = descript[0] = brand[0] = resposta[0] = '\0';
      
      desenhaInserirArtigo(NULL, NULL, NULL, NULL, NULL, NULL ,NULL);
      printf("|Dá-me uma descrição: ");
      lineSize = get_line(descript, 49);
      
      desenhaInserirArtigo(descript, NULL, NULL, NULL, NULL, NULL, NULL);
      printf("|Dá-me uma marca: ");
      lineSize = get_line(brand, 19);
      
      desenhaInserirArtigo(descript, brand, NULL, NULL, NULL, NULL, NULL);
      printf("|Dá-me um PVP: ");
      lineSize = get_line(covertPvp, 19);
      
      desenhaInserirArtigo(descript, brand, covertPvp, NULL, NULL, NULL, NULL);
      printf("|Dá-me a quantidade de stock: ");
      lineSize = get_line(covertQnt, 4);
      
      desenhaInserirArtigo(descript, brand, covertPvp, covertQnt, NULL, NULL, NULL);
      printf("|Dá-me o número da caixa:\n");
      lineSize = get_line(covertCaixa, 4);
      
      desenhaInserirArtigo(descript, brand, covertPvp, covertQnt, covertCaixa, NULL, NULL);
      printf("|Dá-me a leitura do código de barras\n");
      lineSize = get_line(covertBarra, 29);
      
      desenhaInserirArtigo(descript, brand, covertPvp, covertQnt, covertCaixa, covertBarra, NULL);
      
      printf("!Vamos tirar agora a foto\n|||pressiona [c] para tirar a foto\n");
      lineSize = get_line(resposta, 4);
      if (!(strcmp(resposta, confirmate)  == 0 || strcmp(resposta, bigConf)  == 0) ) {
	    
	    printf("isso não é a tecla para tirar a foto '>_>\nMandar tudo abaixo...\n");
	    mysql_close(con);
	    exit(0);
      }
      
      if (system("killall -s USR2 guvcview") == -1) {
	    printf("deu berro para tirar a foto\n");
	    mysql_close(con);
	    exit(1);
      }
      
      fazRename(covertBarra);
      strcpy(nomeFile, "stock/");
      strcat(nomeFile, covertBarra);
      
      desenhaInserirArtigo(descript, brand, covertPvp, covertQnt, covertCaixa, covertBarra, nomeFile);
      printf("*foto tirada com sucesso\n");
      printf("Vamos agora confirmar os dados:\n");
      printf("confirmar? [y]\n");
      lineSize = get_line(resposta, 4);
      if (!(strcmp(resposta, sayyes)  == 0 || strcmp(resposta, bigYes)  == 0) ) {
	    printf("Um ou mais campos errados\nComeça de novo\n");
	    return;
      }
      inserirArtigo(con, descript, brand, covertPvp, covertQnt, covertCaixa, covertBarra, nomeFile);
}

int main(int argc, char** argv) {

      char resposta [4];
      
      printf("...ligando ao servidor sql...\n");
      
      MYSQL *con = mysql_init(NULL);

      if (con == NULL) {
	    fprintf(stderr, "%s\n", mysql_error(con));
	    exit(1);
      }
      if (mysql_real_connect(con, "localhost", "root", "Oliveira-90", NULL, 0, NULL, 0) == NULL) {
	    printf("ligação ao servidor falhou!!\n");
	    finish_with_error(con);
      }  
      printf("ligação ao servidor sucesso  :)\n");
      
      if (mysql_query(con, "USE lista_artigos")) {
	    fprintf(stderr, "%s\n", mysql_error(con));
      }
      printf("tabela esta disponivel\ncomeça o ciclo de submissoes:\n");
      
      desenhaMenuInit();
      while(1) {
	    fgets(resposta, 3, stdin);
	    
	    if (strcmp(resposta, "1\n")  == 0) {
		  while(1) {
			cicloSubmit(con);
			
			printf("continuar a inserir? [y]\n");
			fgets(resposta, 3, stdin);
			if (strcmp(resposta, "y\n")  != 0) {
			      desenhaMenuInit();
			      break;
			}
		  }
	    } else if (strcmp(resposta, "2\n") == 0) {
		  cicloSubmit(con);
		  desenhaMenuInit();
	    } else if (strcmp(resposta, "q\n") == 0) {
		  finish_with_error(con);
	    } else {
		  printf("error...\n");
		  printf("\nescolha recebida é: %s\n", resposta);
	    }
	    
      }
      return 0;
      
}