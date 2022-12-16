#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#include "MQTTClient.h"

#define ADDRESS     "mqtt://broker.emqx.io:1883"
#define CLIENTID    "mqttx_13cda998"
#define TOPIC       "esp32/final"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L

int winner = 3;
char board[9];
    
void rules(){
    printf("\n\nEnter the coordinates according to the feild below\n\n");
    printf("+-----------------+\n");
    printf("|  1  |  2  |  3  |\n");
    printf("|  4  |  5  |  6  |\n");
    printf("|  7  |  8  |  9  |\n");
    printf("+-----------------+\n");
}

void currentBoard(){
     printf("+-----------------+\n");
    printf("|  %C  |  %C  |  %C  |\n", board[0], board[1], board[2]);
    printf("|  %C  |  %C  |  %C  |\n", board[3], board[4], board[5]);
    printf("|  %C  |  %C  |  %C  |\n", board[6], board[7], board[8]);
    printf("+-----------------+\n");
}
void setBoardP1(int move){
if(move == 1){
    board[0] = 'O';
}else if(move == 2){
    board[1] = 'O';
}else if(move == 3){
    board[2] = 'O';
}else if(move == 4){
    board[3] = 'O';
}else if(move == 5){
    board[4] = 'O';
}else if(move == 6){
    board[5] = 'O';
}else if(move == 7){
    board[6] = 'O';
}else if(move == 8){
    board[7] = 'O';
}else if(move == 9){
    board[8] = 'O';
}
}

void setBoardP2(int move){
if(move == 1){
    board[0] = 'X';
}else if(move == 2){
    board[1] = 'X';
}else if(move == 3){
    board[2] = 'X';
}else if(move == 4){
    board[3] = 'X';
}else if(move == 5){
    board[4] = 'X';
}else if(move == 6){
    board[5] = 'X';
}else if(move == 7){
    board[6] = 'X';
}else if(move == 8){
    board[7] = 'X';
}else if(move == 9){
    board[8] = 'X';
}
}
void declairWin(int turns){
    for(int i = 1; i < 9; i += 2){
        if(turns == i){
            printf("Player One Wins!\n");
        }
        if(turns == (i + 1)){
            printf("Player Two Wins!\n");
        }
    }
    if(turns == 9 && winner > 0){
        printf("Draw");
    }
}

int checkHorizP1(char board[]){
    if((board[0] == 'O') && (board[1] == 'O') && (board[2] == 'O')  ){
        return 1;
        
    }else if((board[3] == 'O') && (board[4] == 'O') && (board[5] == 'O') ){
        return 1;
        
    }else if((board[6] == 'O') && (board[7] == 'O') && (board[8] == 'O')){
        return 1;
        
    }else 
        return 0;
}

int checkHorizP2(char board[]){
    if((board[0] == 'X') && (board[1] == 'X') && (board[2] == 'X')  ){
        return 1;
        
    }else if((board[3] == 'X') && (board[4] == 'X') && (board[5] == 'X') ){
        return 1;
        
    }else if((board[6] == 'X') && (board[7] == 'X') && (board[8] == 'X')){
        return 1;
        
    }else 
        return 0;
}

int checkVertP1(char board[]){
    if((board[0] == 'O') && (board[3] == 'O') && (board[6] == 'O')  ){
        return 1;
        
    }else if((board[1] == 'O') && (board[4] == 'O') && (board[7] == 'O') ){
        return 1;
        
    }else if((board[2] == 'O') && (board[5] == 'O') && (board[8] == 'O')){
        return 1;
        
    }else 
        return 0;
}

int checkVertP2(char board[]){
    if((board[0] == 'X') && (board[3] == 'X') && (board[6] == 'X')  ){
        return 1;
        
    }else if((board[1] == 'X') && (board[4] == 'X') && (board[7] == 'X') ){
        return 1;
        
    }else if((board[2] == 'X') && (board[5] == 'X') && (board[8] == 'X')){
        return 1;
        
    }else 
        return 0;
}

int checkDiagP1(char board[]){
    if((board[0] == 'O') && (board[4] == 'O') && (board[8] == 'O')  ){
        return 1;
        
    }else if((board[2] == 'O') && (board[4] == 'O') && (board[6] == 'O') ){
        return 1;
    }else 
        return 0;
}

int checkDiagP2(char board[]){
    if((board[0] == 'X') && (board[4] == 'X') && (board[8] == 'X')  ){
        return 1;
        
    }else if((board[2] == 'X') && (board[4] == 'X') && (board[6] == 'X') ){
        return 1;
    }else 
        return 0;
}

void espMove(int move){
    bool turnOver = false;
    while(!turnOver){
            if (board[move - 1] > 0){
                printf("Sorry this space is taken try again\n\n");
                 printf("Player 1 pick a space(1-9): ");
                 scanf("%d", &move);
            }else{
            setBoardP1(move);
            currentBoard();
            if(checkDiagP1(board)==0){
                winner = 1;
            }else if (checkDiagP1(board)==1){
                winner = 0;
            }
            else if(checkVertP1(board)==1){
                winner = 1;
            }else if(checkVertP1(board)==0) {
                winner = 0;
            }
            else if(checkHorizP1(board)== 0){
                winner = 1;
            }else if (checkHorizP1(board)==1){
                winner = 0;
            }
                turnOver = true;
            }
    }
}

void p2Move(int move){
    bool turnOver = false;
    
    while(!turnOver){
            if (board[move - 1] > 0){
                printf("Sorry this space is taken try again\n\n");
                 printf("Player 2 pick a space(1-9): ");
                 scanf("%d", &move);
            }else{
            setBoardP2(move);
            currentBoard();
            if(checkDiagP2(board)==0){
                winner = 1;
            }else if (checkDiagP2(board)==1){
                winner = 0;
            }
            else if(checkVertP2(board)==0){
                winner = 1;
            }else if(checkVertP2(board)==1) {
                winner = 0;
            }
            else if(checkHorizP2(board)==1){
                winner = 1;
            }else if (checkHorizP2(board)==0){
                winner = 0;
            }
                turnOver = true;
            }
    }
}

void computerMove(){
    bool turnOver = false;
    time_t t;
    srand((unsigned) time(&t));
    int num = (rand() % (9 - 1 + 1)) + 1;;
    while(!turnOver){ 
            if (board[num - 1] > 0){
               num = (rand() % (9 - 1 + 1)) + 1; 
            }else{
            setBoardP2(num);
            currentBoard();
            if(checkDiagP2(board)==0){
                winner = 1;
            }else if (checkDiagP2(board)==1){
                winner = 0;
            }
            else if(checkVertP2(board)==0){
                winner = 1;
            }else if(checkVertP2(board)==1) {
                winner = 0;
            }
            else if(checkHorizP2(board)==1){
                winner = 1;
            }else if (checkHorizP2(board)==0){
                winner = 0;
            }
                turnOver = true;
            }
    }
}

void pvp(){
    int turns = 0;
    int move;
    rules();
    while(turns < 9 && winner > 0){
            printf("Player 1 pick a space(1-9): ");
            scanf("%d", &move);
            espMove(move);
            turns ++;
            
            if(turns < 9 && winner > 0){
            printf("Player 2 pick a space(1-9): ");
            scanf("%d", &move);
            p2Move(move);
            
            turns ++;
            }
        
    }
    declairWin(turns);
    
}

void pvpc(){
    int turns = 0;
    int move;
    rules();
    while(turns < 9 && winner > 0){
        printf("Player 1 pick a space(1-9): ");
        scanf("%d", &move);
        espMove(move);
        turns ++;
            
        if(turns < 9 && winner > 0){
        computerMove();
            
        turns ++;
        }
    }
    declairWin(turns);
}


int main(int argc, char* argv[])
{
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
  
    // MQTT Connection parameters
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }
  
    // Publish message
    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
  
  char choice;
  
  printf("============================\n\n");
    printf("      TIC TAC TOE           \n\n");
    printf("A - Player vs. Player\n\n");
    printf("B - Player vs. Computer\n\n");
    

    //prompt user for the game they want to play
    printf("Enter your choice (A or B): ");

    //read information from console
    choice = getchar();
    if(choice == 'A'){
        pvp();
    }
    if (choice == 'B'){
        pvpc();
    }

    return 0; 
}
    