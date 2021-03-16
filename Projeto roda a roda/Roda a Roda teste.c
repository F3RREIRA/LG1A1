#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
//Setlocale (LC_ALL, "portuguese");

int number_of_correct_predictions=0;
int player_score=250;
int wheel_position;

void player_choice(){
    char player_input;
    printf("Digite [R] para rodar a roda ou [F] para fechar o jogo: \n");
    scanf("%s",&player_input);
   // system ("cls");
    if(player_input=='r' || player_input=='R'|| player_input=='f' || player_input=='F'){
        if(player_input=='r' || player_input=='R'){
            printf("\nGIRANDO... \n\n");
            game_play();
        }
        if(player_input=='f' || player_input=='F'){
            return exit(0);
        }
    }
    else{
        while(player_input!='r'|| player_input!='R'|| player_input!='f' || player_input!='F'){
            printf("\nO caractere inserido e invalido! \n");
            printf("\nDigite [R] para rodar a roda ou [F] para fechar o jogo: \n");
            scanf("%s",&player_input);
            game_play();
        }
    }
}

void game_playing(){                                                                // comparison with the number generated away from the user prediction
    int counter,generated,prediction;
    for(counter=0;counter<4;counter++){
        generated=number_generator();
        prediction=prediction_input();
        if(generated==prediction){
            number_of_correct_predictions++;
        }
    }
    printf("Quantidade de letras *** encontradas: %d \n",number_of_correct_predictions);
}

int game_play(){
    turn_the_wheel();                                                                            //After game start, operating according to the wheel
    switch(wheel_position){
        case 1:
            printf("Valendo R$ 50 por cada letra encontrada! \n");
            game_playing();
            if(number_of_correct_predictions >= 1){                              //Add 50 Point to Player Score
                player_score=player_score+50;
                printf("\nPlayer Score: %d \n\n",player_score);
                wheel_position=0;
                number_of_correct_predictions=0;
                player_choice();
            }
            else
                printf("\nPlayer Score: %d \n\n",player_score);
        break;
        case 2:
            printf("Valendo R$ 100 por cada letra encontrada!\n");
            game_playing();
            if(number_of_correct_predictions >= 2){                               //Add 100 Point to Player Score
                player_score=player_score+100;
                printf("\nPlayer Score: %d \n\n",player_score);
                wheel_position=0;
                number_of_correct_predictions=0;
                player_choice();
            }
            else
                printf("\nPlayer Score: %d \n\n",player_score);
        break;
        case 3:
            printf("Valendo R$ 250 por cada letra encontrada! \n");
            game_playing();
            if(number_of_correct_predictions >= 3){                                 //Add 250 Point to Player Score
                player_score=player_score+250;
                printf("\nPlayer Score: %d \n\n",player_score);
                wheel_position=0;
                number_of_correct_predictions=0;
                player_choice();
            }
            else
                printf("\nPlayer Score: %d \n\n",player_score);
        break;
        case 4:
            printf("Unfortunately FAILURE! \n");                                     //Failure
            wheel_position=0;
            player_score=0;
            printf("\nPlayer Score: %d \n\n",player_score);
            break;
        case 5:
            printf("Passou a vez! \n");                                //Pass
            wheel_position=0;
            player_choice();
        break;
        case 6:
            player_score=player_score-(player_score*(0.25));                        //Reducition Score
            printf("Score Reduction Was Applied... \n");
            printf("\nPlayer Score: %d \n\n",player_score);
            wheel_position=0;
            player_choice();
            break;
        }
        if (player_score==0){
        return 0;
        }

}

int turn_the_wheel(){
    srand(time(NULL));
    wheel_position=1+rand()%6;
    //printf("Wheel Position: %d \n",wheel_position);                    // Control for wheel positions
}

int number_generator(){
    int generated_number;
    srand(time(NULL));
    generated_number=1+rand()%10;
    //printf("Generated Number= %d \n",generated_number);                // Control for generated  number
    return generated_number;
}

int prediction_input(){
    int player_prediction;
    printf("Digite uma letra: ");
    scanf("%d",&player_prediction);
    if(player_prediction<1 || player_prediction>10){
        printf("O caractere inserido e invalido! \n");
        return prediction_input();
    }
    return player_prediction;
}

int main()
{
    srand(time(NULL));
    printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::: \n");
	printf("::                                                    :: \n");
	printf("::                                                    :: \n");
	printf(":: RRR   OO  DDD   AA      AA     RRR   OO  DDD   AA  :: \n");
    printf(":: R  R O  O D  D A  A    A  A    R  R O  O D  D A  A :: \n");
    printf(":: RRR  O  O D  D AAAA    AAAA    RRR  O  O D  D AAAA :: \n");
    printf(":: R  R  OO  DDD  A  A    A  A    R  R  OO  DDD  A  A :: \n");
    printf("::                                                    :: \n");
    printf("::                     * O JOGO *                     :: \n");
    printf("::                                                    :: \n");
	printf(":::::::::::::::::::::::: Feito por Rivaildo Ferreira ::: \n\n");
    printf("JOGADOR 1 \n\n");
	while(player_score!=0){
        player_choice();
        if(player_score==0){
            return 0;
        }
    }
    return 0;
}
