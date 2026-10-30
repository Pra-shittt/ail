#include<iostream>
#include<climits>
using namespace std;
char board[3][3]={
    {' ',' ',' '},
    {' ',' ',' '},
    {' ',' ',' '}
};
bool checkWin(char player){
    for(int i=0;i<3;i++){
        if(board[i][0]==player&&board[i][1]==player&&board[i][2]==player){
            return true;
        }
        if(board[0][i]==player&&board[1][i]==player&&board[2][i]==player){
            return true;
        }
    }
    if(board[0][0]==player&&board[1][1]==player&&board[2][2]==player){
        return true;
    }
    if(board[0][2]==player&&board[1][1]==player&&board[2][0]==player){
        return true;
    }
    return false;
}
bool isDraw(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' '){
                return false;
            }
        }
    }
    return true;
}
int minimax(int depth,bool ismaximizing,int alpha,int beta){
    if(checkWin('O')){
        return 10;
    }
    if(checkWin('X')){
        return -10;
    }
    if(isDraw()){
        return 0;
    }
    if(ismaximizing){
        int bestscore=INT_MIN;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==' '){
                    board[i][j]='O';
                    int score=minimax(depth+1,false,alpha,beta);
                    board[i][j]=' ';

                    if(score>bestscore){
                        bestscore=score;
                    }
                    if(bestscore>alpha){
                        alpha=bestscore;
                    }
                    if(beta<=alpha){
                        break;
                    }
                }
            }
            if(beta<=alpha){
                break;
            }
        }
        return bestscore;
    }
    else{
        int bestscore=INT_MAX;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==' '){
                    board[i][j]='X';
                    int score=minimax(depth+1,true,alpha,beta);
                    board[i][j]=' ';

                    if(score<bestscore){
                        bestscore=score;
                    }
                    if(bestscore<beta){
                        beta=bestscore;
                    }
                    if(beta<=alpha){
                        break;
                    }
                }
            }
            if(beta<=alpha){
                break;
            }
        }
        return bestscore;
    }
}
void computermove(){
    int bestscore=INT_MIN;
    int bestrow=-1;
    int bestcol=-1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' '){
                board[i][j]='O';
                int score=minimax(0,false,INT_MIN,INT_MAX);
                board[i][j]=' ';
                if(score>bestscore){
                    bestscore=score;
                    bestrow=i;
                    bestcol=j;
                }
            }
        }
    }
    if(bestrow!=-1){
        board[bestrow][bestcol]='O';
        cout<<"Computer played "<<bestrow+1<<","<<bestcol+1<<endl;
    }
}
void displayboard(){
    cout<<"\n";
    for(int i=0;i<3;i++){
        cout<<" ";
        for(int j=0;j<3;j++){
            cout<<board[i][j];
            if(j<2){
                cout<<" | ";
            }
        }
        cout<<"\n";
        if(i<2){
            cout<<"---+---+---\n";
        }
    }
    cout<<"\n";
}
int main(){
    int row,col;
    cout<<"TIC-TAC-TOE: Minimax with Alpha-Beta Pruning\n";
    cout<<"You are X and the computer is O.\n";
    cout<<"Enter row and column between 1 and 3.\n";
    while(true){
        displayboard();
        cout<<"Enter row and column: ";
        cin>>row>>col;
        if(row<1||row>3||col<1||col>3||board[row-1][col-1]!=' '){
            cout<<"Invalid move\n";
            continue;
        }
        board[row-1][col-1]='X';
        if(checkWin('X')){
            displayboard();
            cout<<"You win!\n";
            break;
        }
        if(isDraw()){
            displayboard();
            cout<<"Draw\n";
            break;
        }
        computermove();
        if(checkWin('O')){
            displayboard();
            cout<<"Computer wins!\n";
            break;
        }
        if(isDraw()){
            displayboard();
            cout<<"Draw\n";
            break;
        }
    }
    return 0;
}
