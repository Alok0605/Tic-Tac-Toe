#include<iostream>
using namespace std;

char board[3][3]{

{'_','_','_'},
{'_','_','_'},
{'_','_','_'}
};

void printboard() {
    cout << "\n";
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            cout << board[i][j] << " ";
        cout << endl;
        }
    }
}    

bool movesleft() {
    for (int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]=='_')
                return true;
    return false;
}

int evaluate() {
    for(int row=0;row<3;row++)
        if(board[row][0]==board[row][1] &&
           board[row][1]==board[row][2] &&
           board[row][0]!='_')
            return (board[row][0]=='X')?
10:-10;

    for(int col=0;col<3;col++)
        if(board[0][col]==board[1][col] &&
           board[1][col]==board[2][col] &&
           board[0][col]!='_')
            return (board[0][col]=='X')?
10:-10;

    if(board[0][0]==board[1][1] &&
       board[1][1]==board[2][2] &&
       board[0][0]!='_')
        return(board[0][0]=='X')?10:-10;
    
    if(board[0][2]==board[1][1] &&
       board[1][1]==board[2][0] &&
       board[0][2]!='_')
        return (board[0][2]=='X')?10:-10;
    
    return 0;
}

int minimax(bool isMax) {
    int score = evaluate();

    if(score==10 || score==-10)
        return score;

        if(!movesleft())
            return 0;

        if(isMax) {
            int best = -1000;
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    if(board[i][j]=='_') {
                        board[i][j]='X';
                        best = max(best, minimax(false));
                        board[i][j]='_';
                    }
            return best;
        }
        else {
            int best = 1000;
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    if(board[i][j]=='_') {
                        board[i][j]='0';
                        best = min(best, minimax(true));
                        board[i][j]='_';
                    }
            return best;
        }
    }

    void bestmove() {
        int bestVal = -1000;
        int row = -1, col = -1;

        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(board[i][j]=='_') {
                    board[i][j]='X';
                    int moveVal = minimax(false);
                    board[i][j]='_';
                    if(moveVal>bestVal) {
                        row = i;
                        col = j;
                        bestVal = moveVal;
                    }
                }
        board[row][col]='X';
    }

    int main() {
        cout << "Tic-Tac-Toe AI\n";

        while(true) {
            printboard();

            int r,c;
            cout << "Enter your move (row col):";
            cin>>r>>c;

            if(board[r][c]=='_')
                board[r][c]='0';
            else {
                cout<<"Invalid move!\n";
                continue;
            }

            if(evaluate()==-10) {
                printboard();
                cout<<"You Win!\n";
                break;
            }

            if(!movesleft()) {
                printboard();
                cout<<"Draw!\n";
                break;
            }

            bestmove();

            if(evaluate()==10) {
                printboard();
                cout<<"AI Wins!\n";
                break;
            }

            if(!movesleft()) {
                printboard();
                cout<<"Draw!\n";
                break;
            }
        }

        return 0;
    }

