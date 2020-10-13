/*
Run the program like this : ./a.exe <file.txt>
where <file.txt> contains a sudoku table that should be looking like this :
0 0 0 0 9 0 0 0 6
7 8 0 0 0 0 0 0 0
0 9 2 0 0 8 4 0 5
0 0 0 4 0 0 0 2 0
0 3 0 1 0 2 0 5 0
0 1 0 0 0 9 0 0 0
4 0 5 8 0 0 1 6 0
0 0 0 0 0 0 0 8 7
9 0 0 0 0 1 0 0 0

note : 0s are empty squares
*/

#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int table[9][9];
int open=0; // # of uncompleted squares
long int backtracks=0;
vector< pair<int,int> > squares;


void readfile(const char* filename){
    pair<int,int> tmp;
    ifstream fin("table.in");

    if(!fin.is_open()){
        fprintf(stderr, "Error opening file. Exiting... \n");
        exit(1);
    }

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            fin>>table[i][j];
            if(table[i][j]==0) {
                open++;
                tmp.first=i;
                tmp.second=j;
                squares.push_back(tmp);
            }
        }
    }
}

void print_table(){

    printf("\n########################################\n");
    for(int i=0;i<9;i++){
        if(i!=0){
            if(i%3==0) {
                printf("\b#\n########################################\n");
            }
            else printf("\b#\n#            #            #            #\n");
        }

        for(int j=0;j<9;j++){
            if(j%3==0) printf("\b# ");
            printf("%d   ",table[i][j]);
        }

    }
    printf("\b#\n########################################\n\n");
}

bool check(pair<int,int> cur){

/// Check column
    for(int i=0;i<cur.first;i++) {
        if(table[i][cur.second]==table[cur.first][cur.second]) return false;
    }
    for(int i=cur.first+1;i<9;i++) {
        if(table[i][cur.second]==table[cur.first][cur.second]) return false;
    }
/// Check row
    for(int j=0;j<cur.second;j++) {
        if(table[cur.first][j]==table[cur.first][cur.second]) return false;
    }
    for(int j=cur.second+1;j<9;j++) {
        if(table[cur.first][j]==table[cur.first][cur.second]) return false;
    }
// Check square
    int start_i,start_j;

    if(cur.first<=2) start_i=0;
    else if(cur.first>=6) start_i=6;
    else start_i=3;

    if(cur.second<=2) start_j=0;
    else if(cur.second>=6) start_j=6;
    else start_j=3;

    for(int i=start_i;i<start_i+3;i++){
        for(int j=start_j;j<start_j+3;j++){
            if(table[i][j]==table[cur.first][cur.second] && (i!=cur.first && j!=cur.second)) return false;
        }
    }

    return true;
}
void run(){
    int idx=0;
    pair<int,int> current;
    bool skipped=false;

    while(idx<open){
        current=squares[idx];
        if(table[current.first][current.second]!=0 && check(current) && !skipped) {
            idx++;
        }
        else {
            if( table[current.first][current.second] == 9 ){
                table[current.first][current.second] = 0;
                skipped=true;
                backtracks++;
                idx--;
            }
            else {
                table[current.first][current.second]++;
                skipped=false;
            }
        }
    }
}

int main(int argc, char** argv){

    if(argc == 1){
        fprintf(stderr, "File name not given. Exiting...\n");
        exit(1);
    }
    readfile(argv[1]);
    run();
    print_table();
    printf("backtracks : %d\n\n",backtracks);

    return 0;
}
