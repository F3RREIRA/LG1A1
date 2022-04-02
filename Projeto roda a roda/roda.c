#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

typedef struct
{
	char pista[17];
	int qntd;
	char vetpalavras[3][17];
	char descpalavras[3][17];
} Jogo;
	
Jogo ler_jogo(void);
void ler_premios(float[]);
float sorteio(float[]);
int prepara(Jogo*);
void placar (Jogo,float[], int);
int verificaLetra (Jogo*, char);
int verificacaoPalavra (Jogo);

int main(){

	float placarjogador[3]= {0,0,0}, rodar, premios[12];
	int i=0, j, totalLetras, acerto, totalAcertos=0, contFinal=0, vencedor=-1;
	char letraescolhida;
	Jogo jogo;
	
	jogo = ler_jogo();
	totalLetras = prepara(&jogo);
	ler_premios(premios);
	
	//cabeçalho inicial
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: \n");
	printf("::                                                       :: \n");
	printf("::                 RODA A RODA - O JOGO                  :: \n");
    printf("::                                                       :: \n");
	printf("::::::::::::::::::::::::::: Feito por Rivaildo Ferreira ::: \n\n");
	printf("      Pressione qualquer tecla para iniciar o jogo.\n\n");
	fflush(stdin);
	getch(); //espera o jogador pressionar qualquer tecla
	system("cls"); //limpa tela
	
	do {
		placar(jogo,placarjogador,vencedor);	
		printf("\nJogador %d: Tecle [Enter] para rodar a roda!", i+1);
	  	fflush(stdin);
		getchar();
		rodar = sorteio(premios);

		if (rodar == 0){
			printf("\nPassou a vez!\n");
			i = (i+1)%3; //vai para próximo jogador
      		printf("A vez sera passada para o Jogador %d.\nPressione [Enter] para continuar.", i+1);
      		fflush(stdin);
			getchar(); //espera o jogador pressionar enter
		}
	
		else if(rodar == 0.01f){
			printf("\nPerdeu tudo!\nPressione [Enter] para continuar.");
			placarjogador[i] = 0; //zerar placar do jogador ativo
			i = (i+1)%3; //vai para próximo jogador
			fflush(stdin);
			getchar(); //espera o jogador pressionar enter
		}
		else { 
			do{ //loop até o jogador digitar um caracter válido
				printf("\nValendo R$%.2f\nDigite uma letra e tecle [Enter]: ", rodar);
				fgets(&letraescolhida, 2, stdin);
								
			} while ( letraescolhida < 'A' || ( letraescolhida > 'Z' && letraescolhida < 'a' ) || letraescolhida > 'z' ); 
			
			if ( letraescolhida >= 'a' && letraescolhida <= 'z') letraescolhida -= 32;
			
			acerto = verificaLetra (&jogo, letraescolhida); 
      
			if (acerto>0) {//multiplica a quantidade de letras descobertas pelo valor sorteado
				placarjogador[i] = placarjogador[i] + rodar*acerto;
				totalAcertos += acerto; //armazena total de caracteres descobertos
				if ( totalLetras - totalAcertos == 0 ){ //jogador venceu antes da rodada final
							vencedor = i;
							system("cls"); //limpa tela
							placar (jogo, placarjogador, vencedor );
							return 0;
				}
			}
			else if (acerto == -1){
        		i = (i+1)%3;//vai para próximo jogador
        		printf("\nA letra %c ja foi descoberta.\nA vez sera passada para o Jogador %d.\n\nPressione [Enter] para continuar.", letraescolhida, i+1);
        		fflush(stdin);
				getchar(); //espera o jogador pressionar enter
     		}
			else{
        		i = (i+1)%3;//vai para próximo jogador
        		printf("\nNao existe a letra %c na(s) palavra(s).\nA vez sera passada para o Jogador %d.\n\nPressione [Enter] para continuar.", letraescolhida, i+1);
        		fflush(stdin);
				getchar(); //espera o jogador pressionar enter
			}
		}
      	system("cls"); //limpa a tela
	} while ( totalLetras > totalAcertos + 3 );

	do{ //rodada final
	placar(jogo,placarjogador,vencedor);	
	printf("\nJogador %d: ", i+1);
	fflush(stdin);

	do		rodar = sorteio(premios); //não aceita 'passou a vez' ou 'perdeu tudo'
	while 	( rodar == 0.01f || rodar == 0 );
	printf("Falta(m) %d letra(s) para completar a palavra.\n", totalLetras-totalAcertos);
	printf("Voce tem 5 segundos para pensar e depois digitar a palavra...\n\n");
	for(j=5;j!=0; j--){ //contagem regressiva
		printf("%d...", j);
		Sleep(1000);
	} 
	printf("\n\nValendo R$ %.2f.\n", rodar+placarjogador[i]); //valendo prêmio + placar atual
	acerto = verificacaoPalavra(jogo);
	if (acerto == 1){ //jogador ganhou
		vencedor = i;
		placarjogador[i] += rodar;
      	system("cls"); //limpa tela
		placar (jogo, placarjogador, vencedor );
		
		printf("\nPressione qualquer tecla para finalizar.");
		fflush(stdin);
		getch();  //espera o jogador clicar em qualquer tecla
		return 1;
	}
	else{
		i = (i+1)%3;
		contFinal++;
	}
    system("cls"); //limpa tela
	} while ( vencedor==-1 && contFinal<3 );
	
	placar (jogo, placarjogador, vencedor );
	printf("\nFIM DE JOGO!\nNAO HOUVE VENCEDOR!\n");

	printf("\nPressione qualquer tecla para finalizar.");
	fflush(stdin);
	getch(); //espera o jogador clicar em qualquer tecla
	
return 2; //fecha programa
}

Jogo ler_jogo(void){	//verificação da existência do arquivo palavras.dat
	int qntd, i,j, sorteio;
	char pista[17], vetpalavras[3][17];
	Jogo jogo[5];
	FILE *arq;
	arq = fopen("PALAVRAS.dat", "r"); //define arq como o arquivo premios.dat para somente ler
	if (arq == NULL)
	{
		printf("\nErro, nao foi possivel encontrar o arquivo 'PALAVRAS.dat'\n");
		printf("\nPressione qualquer tecla para finalizar.");
		fflush(stdin);
		getch();
 		exit(1); //fecha programa
	}
	for (j=0;j<5;j++)
	{
		if (fscanf(arq,"%16s %d", pista, &qntd) != 2) //faz a leitura do nome do arquivo e da quantidade de palavras
		{ //se não conseguiu ler os 2
			if (feof(arq)) //fim do arquivo
				printf("* ok, fim de arquivo\n");
			else
				printf("\nErro no conteudo do arquivo 'PALAVRAS.dat'\n");
			exit(0); //fecha o programa
    	}
		for (i = 0; i < qntd; i++)
		{
			if (fscanf(arq, "%16s", vetpalavras[i]) != 1)
			{
				printf("\nErro no conteudo do arquivo 'PALAVRAS.dat'\n");
 				exit(2); // fecha o programa
      		}
    	}
		strcpy(jogo[j].pista, pista);
		jogo[j].qntd = qntd;
		for (i = 0; i < qntd; i++)
			strcpy(jogo[j].vetpalavras[i], vetpalavras[i]);
	}
  	srand(time(NULL));
	sorteio = rand()%5;
	fclose(arq);
	return jogo[sorteio];
}

void ler_premios(float premios[]){ //verificação da existência do arquivo premios.dat
	int i=0;
	FILE *arq;
	
	arq = fopen("PREMIOS.dat", "r"); //define arq como o arquivo premios.dat para somente ler
	if(arq == NULL) {
		printf("Erro, nao foi poss%cvel encontrar o arquivo 'PREMIOS.dat'\n",177);
		exit(2);
		}
	while ( i<12 ){
		fscanf(arq, "%f\n", &premios[i]);
		i++;
	}
	
	fclose(arq);
}

float sorteio(float premios[]){ //sorteio valor do prêmio
	float valor;
	srand(time(NULL));
	valor =  premios[rand()%12];
 	return valor;
}

int prepara(Jogo*jogo){//verificação da quantidades de letras e palavras 
	int i, j, contagem=0, qntddLetras, qntddPalavras;
	qntddPalavras = (*jogo).qntd;
	for (i=0;i<qntddPalavras;i++) { //percorre todas as palavras
		qntddLetras = strlen((*jogo).vetpalavras[i]);
		for (j=0;j<qntddLetras;j++){ //percorre todas as letras até o tamanho de cada palavra
			(*jogo).descpalavras[i][j]='_';
			contagem++; //conta quantos caracteres existem no total das palavras
		}
	}
	return contagem;
}

void placar (Jogo jogo, float jog[], int iVencedor ){

	int i, j;
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: \n");
	printf("::                                                       :: \n");
	printf("::                 RODA A RODA - O JOGO                  :: \n");  //cabeçalho fixo
    printf("::                                                       :: \n");
	printf("::::::::::::::::::::::::::: Feito por Rivaildo Ferreira ::: \n\n");
	printf("\n\t\t    A pista %c: %s\n\n\t\t\t", 130,jogo.pista);
	for (i=0; i<jogo.qntd; i++) {
		for (j=0;j<strlen(jogo.vetpalavras[i]);j++){
			if ( iVencedor == -1 ) printf("%c ", jogo.descpalavras[i][j]); 
			else printf(" %c ", jogo.vetpalavras[i][j]); //caso algum jogador vença, mostra todas as palvras
		}	
		printf("\n\t\t\t");
	}
	printf("\n\nJogador 01\t\tJogador 02\t\tJogador 03\n");   //placar atual
	printf("==========\t\t==========\t\t==========\n");
	printf("R$%8.2f\t\tR$%8.2f\t\tR$%8.2f\n",jog[0],jog[1],jog[2]);
	switch (iVencedor){ //caso algum jogador vença o jogo
		case 0: printf("*VENCEDOR*\n");
		printf("\nJogador 1: Voc%c %c o VENCEDOR!\n",136,130); // mensagem de vencedor
		break;
		case 1: printf("\t\t\t*VENCEDOR*\n");
		printf("\nJogador 2: Voc%c %c o VENCEDOR!\n",136,130);
		break;
		case 2: printf("\t\t\t\t\t\t*VENCEDOR*\n");
		printf("\nJogador 3: Voc%c %c o VENCEDOR!\n",136,130);
		break;
	}
}

int verificaLetra (Jogo *jogo, char letra){//loop para verificar as letras nas palavras
	int i, j, descob=0;
	for (i=0; i<(*jogo).qntd ; i++){ //percorre todas as palavras
		for (j=0;j<strlen((*jogo).vetpalavras[i]);j++){ //percorre todas as letras até atingir o tamanho da palavra
    		if ((*jogo).descpalavras[i][j] == letra) return -1; //se a letra já¡ foi descoberta, retorna -1
			else if ((*jogo).vetpalavras[i][j] == letra ) { //compara letra por letra da palavra original para ver se é igual
				(*jogo).descpalavras[i][j] = letra; //revela a letra na palavra descoberta
				descob++; //contagem para saber quantas letras foram descobertas
			} 
		}
	}
  return descob;
}

int verificacaoPalavra (Jogo jogo){   //loop para digitar as palavras completas
	int i, verif, descob=0;
	char palavrasFinal[3][17];
	for ( i=0 ; i<jogo.qntd ; i++ ){
		printf("Digite a %d%c palavra e tecle [Enter]: ", i+1,166);
		fflush(stdin);
		gets(palavrasFinal[i]);
		verif = strcmp ( strupr(palavrasFinal[i]),jogo.vetpalavras[i] );
		if ( verif == 0 ) descob++;
	}
	if ( descob == jogo.qntd ) return 1; // verificação de letras descobertas
	else return 0;
	    srand(time(NULL));
  }
