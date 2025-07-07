/* 
Features:
  - Computer v/s player
  - two level of difficulty( human mode v/s God mode)
  -impossible to win against God mode
  -who will do first move will be decided at random
*/

#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define BOARD_SIZE 3

typedef struct {
  int player;
  int computer;
  int draw;
} Score;

int difficulty;
Score score ={.player = 0, .computer =0, .draw=0};

void input_difficulty();
void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE],char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE],int row, int col);

int main(){
  srand(time(NULL));
  int choice;
  input_difficulty();
  do{
    play_game();
    printf("\nplay again? (1 for yes, 0 for no): ");
    scanf("%d",&choice);
  }while (choice == 1);
  printf("\nBye bye, Thanks for Playing");
  return 0;

}

void play_game(){
  char board[BOARD_SIZE][BOARD_SIZE] = {
    {' ',' ',' '},
    {' ',' ',' '},
    {' ',' ',' '}
  };
  char current_player = rand() %2 ==0 ? 'X' : 'O';
  print_board(board);
  while(1){
    
    if (current_player == 'X'){
      player_move(board);
      print_board(board);
      if(check_win(board,'X')){
        score.player++;
        printf("Congratulations You have Won!!!");
        break;
      }
      current_player ='O';
    }else{
      computer_move(board);
      print_board(board);
      if(check_win(board,'O')){
        score.computer++;
        print_board(board);
        printf("I won !!! But you played well....");
        break;
      }
      current_player='X';
    }

    if (check_draw(board)){
      score.draw++;
      printf("\nIt's a draw!");
      break;
    }
  }

}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
  return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
}


void player_move(char board[BOARD_SIZE][BOARD_SIZE]) {
  char input[100];
  int row, col;

  while (1) {
    printf("\nPlayer X's turn.\n");
    printf("Enter row and column (1-3): ");
    fflush(stdout);
    if (fgets(input, sizeof(input), stdin)) {
      if (sscanf(input, "%d %d", &row, &col) == 2) {
        row--; col--;
        if (is_valid_move(board, row, col)) {
          board[row][col] = 'X';
          break;
        } else {
          printf("Invalid move: out of range or already occupied.\n");
        }
      } else {
        printf("Invalid input. Please enter two numbers (e.g. 1 3).\n");
      }
    }
  }
}


void computer_move(char board[BOARD_SIZE][BOARD_SIZE]){
  //1. Play for immediate win
  for (int i=0; i < BOARD_SIZE; i++){
    for(int j=0; j < BOARD_SIZE; j++){
      if(board[i][j]==' '){
        board[i][j] = 'O';
        if (check_win(board,'O')){
          return;
        }
        board[i][j]= ' ';
      }
    }
  }

   //2. Play for immediate block
   for (int i=0; i < BOARD_SIZE; i++){
    for(int j=0; j < BOARD_SIZE; j++){
      if(board[i][j]==' '){
        board[i][j] = 'X';
        if (check_win(board,'X')){
          board[i][j] = 'O';
          return;
        }
        board[i][j]= ' ';
      }
    }
  }

  // GOD Mode
  if (difficulty == 2){
    //3. Play Centre if Available
    if (board[1][1] == ' '){
      board[1][1]='O';
      return;
    }

    // 4. play corner if available
    int corner[4][2] = {
      {0,0},
      {0,2},
      {2,0},
      {2,2}
    };

    for (int i =0; i < 4; i++){
      if (board[corner[i][0]][corner[i][1]] ==' '){
        board[corner[i][0]][corner[i][1]] = 'O';
        return;
      }
    }
  }

  //5. Play first available move
   for (int i=0; i < BOARD_SIZE; i++){
    for(int j=0; j < BOARD_SIZE; j++){
      if(board[i][j]==' '){
        board[i][j] = 'O';
        return;
      }
    }
  }

}


int check_win(char board[BOARD_SIZE][BOARD_SIZE],char player){
  for(int i=0; i< BOARD_SIZE; i++){
    if(board[i][0]== player && board[i][1]== player && board[i][2]== player){
      return 1;
    }

    if(board[0][i]== player && board[1][i]== player && board[2][i]== player){
      return 1;
    }
  }

  if((board[0][0]== player && board[1][1]== player && board[2][2]== player) || (board[0][2]== player && board[1][1]== player && board[2][0]== player)){
    return 1;
  }

  return 0;
}


int check_draw(char board[BOARD_SIZE][BOARD_SIZE]){
  for(int i=0; i< BOARD_SIZE; i++){
    for(int j=0; j< BOARD_SIZE; j++){
      if(board[i][j] == ' '){
        return 0;
      }
    }
  }
  return 1;
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]){
  clear_screen();
  printf("\nScore - Player X: %d, Computer: %d, Draws: %d", score.player, score.computer, score.draw);
  printf("\nTic-Tac-Toe\n");

  for (int i=0; i<BOARD_SIZE ;i++){
    printf("\n");
    for (int j=0; j<BOARD_SIZE;j++){
      printf(" %c ",board[i][j]);
      if (j< BOARD_SIZE-1){
        printf("|");
      }
    }
    
    if (i < BOARD_SIZE-1){
      printf("\n---+---+---");
    }
  }
  printf("\n\n");

}

void input_difficulty(){
  while(1){
    printf("\nSelect difficulty level:");
    printf("\n1. Human (Standard)");
    printf("\n2. God ( Impossible to win)");
    printf("\nEnter your choice: ");
    fflush(stdout);
    scanf("%d",&difficulty);
    if (difficulty !=1 && difficulty !=2){
      printf("\nIncorrect choice enter (1/2)!!");
    }else{
      break;
    }
  }
}

void clear_screen(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}