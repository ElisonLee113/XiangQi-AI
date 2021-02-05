#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2") 
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cctype>
#include <map>
using namespace std;
/*
Chess Index:
che     = C c
ma      = M m
xiang   = X x
shi     = S s
pao     = P p
bing    = B b
jiang   = J j
empty   = . .
boarder = @ @
upper-case -> red
lower-case -> black
*/
int test1[14],test2[14];
long long int num=0,round=1;
struct move{
	int original_x,original_y,new_x,new_y,max_score,min_score;
};
char board[13][13]={
"@@@@@@@@@@@@",
"@c..b..B..C@",
"@m.p....P.M@",
"@x..b..B..X@",
"@s........S@",
"@j..b..B..J@",
"@s........S@",
"@x..b..B..X@",
"@m.p....P.M@",
"@c..b..B..C@",
"@@@@@@@@@@@@"
};
/* <[board (vertical)]>
		@@@@@@@@@@@
		@cmxsjsxmc@
		@.........@
		@.p.....p.@
		@b.b.b.b.b@
		@.........@
		@.........@
		@B.B.B.B.B@
		@.P.....P.@
		@.........@
		@CMXSJSXMC@
		@@@@@@@@@@@*/
map <char,int> value;
int max_n=5;
void test_data_1(){
	value['C']=5000;
	value['M']=2500;
	value['X']=1000;
	value['S']=750;
	value['P']=4500;
	value['B']=10;
	value['J']=1000000;
	value['c']=5000;
	value['m']=2500;
	value['x']=1000;
	value['s']=750;
	value['p']=4500;
	value['b']=10;
	value['j']=10000;
}
void test_data_2(){
	value['C']=1;
	value['M']=1;
	value['X']=1;
	value['S']=1;
	value['P']=1;
	value['B']=1;
	value['J']=1;
	value['c']=1;
	value['m']=1;
	value['x']=1;
	value['s']=1;
	value['p']=1;
	value['b']=1;
	value['j']=1;
}
bool check(){
	int ans=0;
	for(int i=0;i<12;i++){
		for(int j=0;j<11;j++){
			if(board[i][j]=='j') ans++;
			if(board[i][j]=='J') ans++;
		}
	}
	return ans==2;
}
move best_move(int layer,bool player,int current_score){
	num++;
	if(layer==max_n){
		/*if(current_score==101){
			cout<<layer<<" "<<player<<" "<<current_score<<endl;
			for(int i=0;i<=10;i++){
				for(int j=0;j<=11;j++){
					cout<<board[i][j];
				}
				cout<<endl;
			}
			system("pause");
		}*/
		move temp;
		temp.max_score=current_score;
		return temp;
	}
	int max=-999999,min=999999,total_score=0,n=0;
	move ans;
	ans.max_score=0;
	for(int i=1;i<=9;i++){
		for(int j=1;j<=10;j++){
			if(board[i][j]!='.'){
				if(player){
					if(isupper(board[i][j])){
						if(board[i][j]=='B'){
							if(j<=5&&board[i-1][j]!='@'&&!isupper(board[i-1][j])){
								if(board[i-1][j]=='.'){
									swap(board[i][j],board[i-1][j]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(max<temp){
										max=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i-1;
										ans.new_y=j;
									}
									swap(board[i][j],board[i-1][j]);
								}
								else{
									int temp=value[board[i-1][j]];
									char k=board[i-1][j];
									board[i-1][j]='B';
									board[i][j]='.';
									int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
									total_score+=temp2;
									n++;
									if(max<temp2){
										max=temp2;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i-1;
										ans.new_y=j;
									}
									board[i][j]='B';
									board[i-1][j]=k;
								}
							}
							if(j<=5&&board[i+1][j]!='@'&&!isupper(board[i+1][j])){
								if(board[i+1][j]=='.'){
									swap(board[i][j],board[i+1][j]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(max<temp){
										max=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i+1;
										ans.new_y=j;
									}
									swap(board[i][j],board[i+1][j]);
								}
								else{
									int temp=value[board[i+1][j]];
									char k=board[i+1][j];
									board[i+1][j]='B';
									board[i][j]='.';
									int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
									total_score+=temp2;
									n++;
									if(max<temp2){
										max=temp2;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i+1;
										ans.new_y=j;
									}
									board[i][j]='B';
									board[i+1][j]=k;
								}
							}
							if(board[i][j-1]!='@'&&!isupper(board[i][j-1])){
								if(board[i][j-1]=='.'){
									swap(board[i][j],board[i][j-1]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(max<temp){
										max=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j-1;
									}
									swap(board[i][j],board[i][j-1]);
								}
								else{
									int temp=value[board[i][j-1]];
									char k=board[i][j-1];
									board[i][j-1]='B';
									board[i][j]='.';
									int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
									total_score+=temp2;
									n++;
									if(max<temp2){
										max=temp2;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j-1;
									}
									board[i][j]='B';
									board[i][j-1]=k;
								}
							}
						}
						if(board[i][j]=='C'){
							int temp=1;
							while(board[i-temp][j]=='.'){
								swap(board[i-temp][j],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(max<temp2){
									max=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i-temp;
									ans.new_y=j;
								}
								swap(board[i][j],board[i-temp][j]);
								temp++;
							}
							if(islower(board[i-temp][j])){
								char k=board[i-temp][j];
								board[i-temp][j]='C';
								board[i][j]='.';
								int temp2=value[k];
								int temp3=best_move(layer+1,1-player,current_score+temp2).max_score;
								total_score+=temp3;
								n++;
								if(max<temp3){
									max=temp3;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i-temp;
									ans.new_y=j;
								}
								board[i-temp][j]=k;
								board[i][j]='C';
							}
							temp=1;
							while(board[i+temp][j]=='.'){
								swap(board[i+temp][j],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(max<temp2){
									max=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i+temp;
									ans.new_y=j;
								}
								swap(board[i][j],board[i+temp][j]);
								temp++;
							}
							if(islower(board[i+temp][j])){
								char k=board[i+temp][j];
								board[i+temp][j]='C';
								board[i][j]='.';
								int temp2=value[k];
								int temp3=best_move(layer+1,1-player,current_score+temp2).max_score;
								total_score+=temp3;
								n++;
								if(max<temp3){
									max=temp3;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i+temp;
									ans.new_y=j;
								}
								board[i+temp][j]=k;
								board[i][j]='C';
							}
							temp=1;
							while(board[i][j-temp]=='.'){
								swap(board[i][j-temp],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(max<temp2){
									max=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i;
									ans.new_y=j-temp;
								}
								swap(board[i][j],board[i][j-temp]);
								temp++;
							}
							if(islower(board[i][j-temp])){
								char k=board[i][j-temp];
								board[i][j-temp]='C';
								board[i][j]='.';
								int temp2=value[k];
								int temp3=best_move(layer+1,1-player,current_score+temp2).max_score;
								total_score+=temp3;
								n++;
								if(max<temp3){
									max=temp3;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i;
									ans.new_y=j-temp;
								}
								board[i][j-temp]=k;
								board[i][j]='C';
							}
							temp=1;
							while(board[i-1][j+temp]=='.'){
								swap(board[i][j+temp],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(max<temp2){
									max=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i;
									ans.new_y=j+temp;
								}
								swap(board[i][j],board[i][j+temp]);
								temp++;
							}
							if(islower(board[i][j+temp])){
								char k=board[i][j+temp];
								board[i][j+temp]='C';
								board[i][j]='.';
								int temp2=value[k];
								int temp3=best_move(layer+1,1-player,current_score+temp2).max_score;
								total_score+=temp3;
								n++;
								if(max<temp3){
									max=temp3;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i;
									ans.new_y=j+temp;
								}
								board[i][j+temp]=k;
								board[i][j]='C';
							}
						}
						if(board[i][j]=='X'){
							if(i!=1){
								if(j!=6&&board[i-1][j-1]=='.'){
									if(board[i-2][j-2]=='.'){
										swap(board[i][j],board[i-2][j-2]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-2;
											ans.new_y=j-2;
										}
										swap(board[i][j],board[i-2][j-2]);
									}
									else if(islower(board[i-2][j-2])){
										char k=board[i-2][j-2];
										int temp=value[k];
										board[i-2][j-2]='X';
										board[i][j]='.';
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp2;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-2;
											ans.new_y=j-2;
										}
										board[i][j]='X';
										board[i-2][j-2]=k;
									}
								}
								if(j!=10&&board[i-1][j+1]){
									if(board[i-2][j+2]=='.'){
										swap(board[i][j],board[i-2][j+2]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-2;
											ans.new_y=j+2;
										}
										swap(board[i][j],board[i-2][j+2]);
									}
									else if(islower(board[i-2][j+2])){
										char k=board[i-2][j+2];
										int temp=value[k];
										board[i-2][j+2]='X';
										board[i][j]='.';
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp2;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-2;
											ans.new_y=j+2;
										}
										board[i][j]='X';
										board[i-2][j+2]=k;
									}
								}
							}
							if(i!=9){
								if(j!=6&&board[i+1][j-1]=='.'){
									if(board[i+2][j-2]=='.'){
										swap(board[i][j],board[i+2][j-2]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+2;
											ans.new_y=j-2;
										}
										swap(board[i][j],board[i+2][j-2]);
									}
									else if(islower(board[i+2][j-2])){
										char k=board[i+2][j-2];
										int temp=value[k];
										board[i+2][j-2]='X';
										board[i][j]='.';
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp2;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+2;
											ans.new_y=j-2;
										}
										board[i][j]='X';
										board[i+2][j-2]=k;
									}
								}
								if(j!=10&&board[i+1][j+1]=='.'){
									if(board[i+2][j+2]=='.'){
										swap(board[i][j],board[i+2][j+2]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+2;
											ans.new_y=j+2;
										}
										swap(board[i][j],board[i+2][j+2]);
									}
									else if(islower(board[i+2][j+2])){
										char k=board[i+2][j+2];
										int temp=value[k];
										board[i+2][j+2]='X';
										board[i][j]='.';
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp2;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+2;
											ans.new_y=j+2;
										}
										board[i][j]='X';
										board[i+2][j+2]=k;
									}
								}
							}
						}
						if(board[i][j]=='M'){
							if(i!=9&&board[i+1][j]=='.'){
								if(j<=8&&!isupper(board[i+2][j+1])){
									if(board[i+2][j+1]=='.'){
										swap(board[i+2][j+1],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+2;
											ans.new_y=j+1;
										}
										swap(board[i+2][j+1],board[i][j]);
									}
									else{
										char k=board[i+2][j+1];
										int temp=value[k];
										board[i][j]='.';
										board[i+2][j+1]='M';
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+2;
											ans.new_y=j+1;
										}
										board[i][j]='M';
										board[i+2][j+1]=k;
									}
								}
								if(j<=8&&!isupper(board[i+2][j-1])){
									if(board[i+2][j-1]=='.'){
										swap(board[i+2][j-1],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+2;
											ans.new_y=j-1;
										}
										swap(board[i+2][j-1],board[i][j]);
									}
									else{
										char k=board[i+2][j-1];
										int temp=value[k];
										board[i][j]='.';
										board[i+2][j-1]='M';
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+2;
											ans.new_y=j-1;
										}
										board[i][j]='M';
										board[i+2][j-1]=k;
									}
								}
							}
							if(i!=1&&board[i-1][j]=='.'){
								if(i>=3&&!isupper(board[i-2][j-1])){
									if(board[i-2][j-1]=='.'){
										swap(board[i-2][j-1],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-2;
											ans.new_y=j-1;
										}
										swap(board[i-2][j-1],board[i][j]);
									}
									else{
										char k=board[i-2][j-1];
										int temp=value[k];
										board[i][j]='.';
										board[i-2][j-1]='M';
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-2;
											ans.new_y=j-1;
										}
										board[i][j]='M';
										board[i-2][j-1]=k;
									}
								}
								if(i>=3&&!isupper(board[i-2][j+1])){
									if(board[i-2][j+1]=='.'){
										swap(board[i-2][j+1],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-2;
											ans.new_y=j+1;
										}
										swap(board[i-2][j+1],board[i][j]);
									}
									else{
										char k=board[i-2][j+1];
										int temp=value[k];
										board[i][j]='.';
										board[i-2][j+1]='M';
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-2;
											ans.new_y=j+1;
										}
										board[i][j]='M';
										board[i-2][j+1]=k;
									}
								}
							}
							if(board[i][j+1]=='.'){
								if(j<=8&&!isupper(board[i+1][j+2])){
									if(board[i+1][j+2]=='.'){
										swap(board[i+1][j+2],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+1;
											ans.new_y=j+2;
										}
										swap(board[i+1][j+2],board[i][j]);
									}
									else{
										char k=board[i+1][j+2];
										int temp=value[k];
										board[i][j]='.';
										board[i+1][j+2]='M';
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+1;
											ans.new_y=j+2;
										}
										board[i][j]='M';
										board[i+1][j+2]=k;
									}
									if(j<=8&&!isupper(board[i-1][j+2])){
									if(board[i-1][j+2]=='.'){
										swap(board[i-1][j+2],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-1;
											ans.new_y=j+2;
										}
										swap(board[i-1][j+2],board[i][j]);
									}
									else{
										char k=board[i-1][j+2];
										int temp=value[k];
										board[i][j]='.';
										board[i-1][j+2]='M';
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-1;
											ans.new_y=j+2;
										}
										board[i][j]='M';
										board[i-1][j+2]=k;
									}
								}		
						}
							
							}
							if(board[i][j-1]=='.'){
								if(j>=3&&!isupper(board[i+1][j-2])){
									if(board[i+1][j-2]=='.'){
										swap(board[i+1][j-2],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+1;
											ans.new_y=j-2;
										}
										swap(board[i+1][j-2],board[i][j]);
									}
									else{
										char k=board[i+1][j-2];
										int temp=value[k];
										board[i][j]='.';
										board[i+1][j-2]='M';
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+1;
											ans.new_y=j-2;
										}
										board[i][j]='M';
										board[i+1][j-2]=k;
									}
								}
								if(j>=3&&!isupper(board[i-1][j-2])){
								if(board[i-1][j-2]=='.'){
									swap(board[i-1][j-2],board[i][j]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(max<temp){
										max=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i-1;
										ans.new_y=j-2;
									}
									swap(board[i-1][j-2],board[i][j]);
								}
								else{
									char k=board[i-1][j-2];
									int temp=value[k];
									board[i][j]='.';
									board[i-1][j-2]='M';
									int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
									total_score+=temp2;
									n++;
									if(max<temp2){
										max=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i-1;
										ans.new_y=j+2;
									}
									board[i][j]='M';
									board[i-1][j-2]=k;
								}								
							}
							}
						}
						if(board[i][j]=='J'){
							if(i-1!=3&&board[i-1][j]!='@'&&!isupper(board[i-1][j])){
								if(board[i-1][j]=='.'){
									swap(board[i][j],board[i-1][j]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(max<temp){
										max=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i-1;
										ans.new_y=j;
									}
									swap(board[i][j],board[i-1][j]);
								}
								else{
									int temp=value[board[i-1][j]];
									char k=board[i-1][j];
									board[i-1][j]='J';
									board[i][j]='.';
									int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
									total_score+=temp2;
									n++;
									if(max<temp2){
										max=temp2;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i-1;
										ans.new_y=j;
									}
									board[i][j]='J';
									board[i-1][j]=k;
								}
							}
							if(i+1!=7&&board[i+1][j]!='@'&&!isupper(board[i+1][j])){
								if(board[i+1][j]=='.'){
									swap(board[i][j],board[i+1][j]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(max<temp){
										max=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i+1;
										ans.new_y=j;
									}
									swap(board[i][j],board[i+1][j]);
								}
								else{
									int temp=value[board[i+1][j]];
									char k=board[i+1][j];
									board[i+1][j]='J';
									board[i][j]='.';
									int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
									total_score+=temp2;
									n++;
									if(max<temp2){
										max=temp2;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i+1;
										ans.new_y=j;
									}
									board[i][j]='J';
									board[i+1][j]=k;
								}
							}
							if(board[i][j+1]!='@'&&!isupper(board[i][j+1])){
								if(board[i][j+1]=='.'){
									swap(board[i][j],board[i][j+1]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(max<temp){
										max=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j+1;
									}
									swap(board[i][j],board[i][j+1]);
								}
								else{
									int temp=value[board[i][j+1]];
									char k=board[i][j+1];
									board[i][j+1]='J';
									board[i][j]='.';
									int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
									total_score+=temp2;
									n++;
									if(max<temp2){
										max=temp2;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j+1;
									}
									board[i][j]='J';
									board[i][j+1]=k;
								}
							}
							if(j-1!=7&&board[i][j-1]!='@'&&!isupper(board[i][j-1])){
								if(board[i][j-1]=='.'){
									swap(board[i][j],board[i][j-1]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(max<temp){
										max=temp;
										ans.original_x=i;
										ans.original_y=j-1;
										ans.new_x=i;
										ans.new_y=j-1;
									}
									swap(board[i][j],board[i][j-1]);
								}
								else{
									int temp=value[board[i][j-1]];
									char k=board[i][j-1];
									board[i][j-1]='J';
									board[i][j]='.';
									int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
									total_score+=temp2;
									n++;
									if(max<temp2){
										max=temp2;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j-1;
									}
									board[i][j]='J';
									board[i][j-1]=k;
								}
							}
						}
						if(board[i][j]=='S'){
							if(i==5&&j==9){
								if(!isupper(board[6][10])){
									if(board[6][10]=='.'){
										swap(board[i][j],board[6][10]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=6;
											ans.new_y=10;
										}
										swap(board[i][j],board[6][10]);
									}
									else{
										char k=board[6][10];
										board[6][10]='S';
										board[i][j]='.';
										int temp=value[k];
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp2;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=6;
											ans.new_y=10;
										}
										board[i][j]='S';
										board[6][10]=k;
									}
								}
								if(!isupper(board[4][10])){
									if(board[4][10]=='.'){
										swap(board[i][j],board[4][10]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=4;
											ans.new_y=10;
										}
										swap(board[i][j],board[4][10]);
									}
									else{
										char k=board[4][10];
										board[4][10]='S';
										board[i][j]='.';
										int temp=value[k];
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp2;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=4;
											ans.new_y=10;
										}
										board[i][j]='S';
										board[4][10]=k;
									}
								}
								if(!isupper(board[6][8])){
									if(board[6][8]=='.'){
										swap(board[i][j],board[6][8]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=6;
											ans.new_y=8;
										}
										swap(board[i][j],board[6][8]);
									}
									else{
										char k=board[6][8];
										board[6][8]='S';
										board[i][j]='.';
										int temp=value[k];
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp2;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=6;
											ans.new_y=8;
										}
										board[i][j]='S';
										board[6][8]=k;
									}
								}
								if(!isupper(board[4][8])){
									if(board[4][8]=='.'){
										swap(board[i][j],board[4][8]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=4;
											ans.new_y=8;
										}
										swap(board[i][j],board[4][8]);
									}
									else{
										char k=board[4][8];
										board[4][8]='S';
										board[i][j]='.';
										int temp=value[k];
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp2;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=4;
											ans.new_y=8;
										}
										board[i][j]='S';
										board[4][8]=k;
									}
								}
							}
							else{
								if(!isupper(board[5][9])){
									if(board[5][9]=='.'){
										swap(board[i][j],board[5][9]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(max<temp){
											max=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=5;
											ans.new_y=9;
										}
										swap(board[i][j],board[5][9]);
									}
									else{
										char k=board[5][9];
										board[5][9]='S';
										board[i][j]='.';
										int temp=value[k];
										int temp2=best_move(layer+1,1-player,current_score+temp).max_score;
										total_score+=temp2;
										n++;
										if(max<temp2){
											max=temp2;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=5;
											ans.new_y=9;
										}
										board[i][j]='S';
										board[5][9]=k;
									}
								}
							}
						}
						if(board[i][j]=='P'){
							int temp=1;
							while(board[i-temp][j]=='.'){
								swap(board[i-temp][j],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(max<temp2){
									max=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i-temp;
									ans.new_y=j;
								}
								swap(board[i][j],board[i-temp][j]);
								temp++;
							}
							if(board[i-temp][j]!='@') temp++;
							while(board[i-temp][j]!='@'&&!isupper(board[i-temp][j])){
								if(islower(board[i-temp][j])&&i-temp>0){
									char k=board[i-temp][j];
									int temp2=value[k];
									board[i-temp][j]='P';
									board[i][j]='.';
									int temp3=best_move(layer+1,1-player,current_score+temp2).max_score;
									total_score+=temp3;
									n++;
									if(max<temp3){
										max=temp3;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i-temp;
										ans.new_y=j;
									}
									board[i-temp][j]=k;
									board[i][j]='P';
									break;
								}
								temp++;
							}
							temp=1;
							while(board[i+temp][j]=='.'){
								swap(board[i+temp][j],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(max<temp2){
									max=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i+temp;
									ans.new_y=j;
								}
								swap(board[i][j],board[i+temp][j]);
								temp++;
							}
							if(board[i+temp][j]!='@') temp++;
							while(board[i+temp][j]!='@'&&!isupper(board[i+temp][j])){
								if(islower(board[i+temp][j])&&i+temp<11){
									char k=board[i+temp][j];
									int temp2=value[k];
									board[i+temp][j]='P';
									board[i][j]='.';
									int temp3=best_move(layer+1,1-player,current_score+temp2).max_score;
									total_score+=temp3;
									n++;
									if(max<temp3){
										max=temp3;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i+temp;
										ans.new_y=j;
									}
									board[i+temp][j]=k;
									board[i][j]='P';
									break;
								}
								temp++;
							}
							temp=1;
							while(board[i][j-temp]=='.'){
								swap(board[i][j-temp],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(max<temp2){
									max=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i;
									ans.new_y=j-temp;
								}
								swap(board[i][j],board[i][j-temp]);
								temp++;
							}
							if(board[i][j-temp]!='@') temp++;
							while(board[i][j-temp]!='@'&&!isupper(board[i][j-temp])){
								if(islower(board[i][j-temp])&&j-temp>0){
									char k=board[i][j-temp];
									int temp2=value[k];
									board[i][j-temp]='P';
									board[i][j]='.';
									int temp3=best_move(layer+1,1-player,current_score+temp2).max_score;
									total_score+=temp3;
									n++;
									if(max<temp3){
										max=temp3;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j-temp;
									}
									board[i][j-temp]=k;
									board[i][j]='P';
									break;
								}
								temp++;
							}
							temp=1;
							while(board[i][j+temp]=='.'){
								swap(board[i][j+temp],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(max<temp2){
									max=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i;
									ans.new_y=j+temp;
								}
								swap(board[i][j],board[i][j+temp]);
								temp++;
							}
							if(board[i][j+temp]!='@') temp++;
							while(board[i][j+temp]!='@'&&!isupper(board[i][j+temp])){
								if(islower(board[i][j+temp])&&j+temp<12){
									char k=board[i][j+temp];
									int temp2=value[k];
									board[i][j+temp]='P';
									board[i][j]='.';
									int temp3=best_move(layer+1,1-player,current_score+temp2).max_score;
									total_score+=temp3;
									n++;
									if(max<temp3){
										max=temp3;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j+temp;
									}
									board[i][j+temp]=k;
									board[i][j]='P';
									break;
								}
								temp++;
							}
						}
					}
				}
				else{
					if(islower(board[i][j])){
						if(board[i][j]=='b'){
							if(j>=6&&board[i+1][j]!='@'&&!islower(board[i+1][j])){
								if(board[i+1][j]=='.'){
									swap(board[i][j],board[i+1][j]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(min>temp){
										min=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i+1;
										ans.new_y=j;
									}
									swap(board[i][j],board[i+1][j]);
								}
								else{
									int temp=value[board[i+1][j]];
									char k=board[i+1][j];
									board[i+1][j]='b';
									board[i][j]='.';
									int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
									total_score+=temp2;
									n++;
									if(min>temp2){
										min=temp2;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i+1;
										ans.new_y=j;
									}
									board[i][j]='b';
									board[i+1][j]=k;
								}
							}
							if(j>=6&&board[i-1][j]!='@'&&!islower(board[i-1][j])){
								if(board[i-1][j]=='.'){
									swap(board[i][j],board[i-1][j]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(min>temp){
										min=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i-1;
										ans.new_y=j;
									}
									swap(board[i][j],board[i-1][j]);
								}
								else{
									int temp=value[board[i-1][j]];
									char k=board[i-1][j];
									board[i-1][j]='b';
									board[i][j]='.';
									int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
									total_score+=temp2;
									n++;
									if(min>temp2){
										min=temp2;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i-1;
										ans.new_y=j;
									}
									board[i][j]='b';
									board[i-1][j]=k;
								}
							}
							if(board[i][j+1]!='@'&&!islower(board[i][j+1])){
								if(board[i][j+1]=='.'){
									swap(board[i][j],board[i][j+1]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(min>temp){
										min=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j+1;
									}
									swap(board[i][j],board[i][j+1]);
								}
								else{
									int temp=value[board[i][j+1]];
									char k=board[i][j+1];
									board[i][j+1]='b';
									board[i][j]='.';
									int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
									total_score+=temp2;
									n++;
									if(min>temp2){
										min=temp2;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j+1;
									}
									board[i][j]='b';
									board[i][j+1]=k;
								}
							}
						}
						if(board[i][j]=='c'){
							int temp=1;
							while(board[i-temp][j]=='.'){
								swap(board[i-temp][j],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(min>temp2){
									min=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i-temp;
									ans.new_y=j;
								}
								swap(board[i][j],board[i-temp][j]);
								temp++;
							}
							if(isupper(board[i-temp][j])){
								char k=board[i-temp][j];
								board[i-temp][j]='c';
								board[i][j]='.';
								int temp2=value[k];
								int temp3=best_move(layer+1,1-player,current_score-temp2).max_score;
								total_score+=temp3;
								n++;
								if(min>temp3){
									min=temp3;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i-temp;
									ans.new_y=j;
								}
								board[i-temp][j]=k;
								board[i][j]='c';
							}
							temp=1;
							while(board[i+temp][j]=='.'){
								swap(board[i+temp][j],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(min>temp2){
									min=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i+temp;
									ans.new_y=j;
								}
								swap(board[i][j],board[i+temp][j]);
								temp++;
							}
							if(isupper(board[i+temp][j])){
								char k=board[i+temp][j];
								board[i+temp][j]='c';
								board[i][j]='.';
								int temp2=value[k];
								int temp3=best_move(layer+1,1-player,current_score-temp2).max_score;
								total_score+=temp3;
								n++;
								if(min>temp3){
									min=temp3;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i+temp;
									ans.new_y=j;
								}
								board[i+temp][j]=k;
								board[i][j]='c';
							}
							temp=1;
							while(board[i][j-temp]=='.'){
								swap(board[i][j-temp],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(min>temp2){
									min=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i;
									ans.new_y=j-temp;
								}
								swap(board[i][j],board[i][j-temp]);
								temp++;
							}
							if(isupper(board[i][j-temp])){
								char k=board[i][j-temp];
								board[i][j-temp]='c';
								board[i][j]='.';
								int temp2=value[k];
								int temp3=best_move(layer+1,1-player,current_score-temp2).max_score;
								total_score+=temp3;
								n++;
								if(min>temp3){
									min=temp3;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i;
									ans.new_y=j-temp;
								}
								board[i][j-temp]=k;
								board[i][j]='c';
							}
							temp=1;
							while(board[i][j+temp]=='.'){
								swap(board[i][j+temp],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(min>temp2){
									min=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i;
									ans.new_y=j+temp;
								}
								swap(board[i][j],board[i][j+temp]);
								temp++;
							}
							if(isupper(board[i][j+temp])){
								char k=board[i][j+temp];
								board[i][j+temp]='c';
								board[i][j]='.';
								int temp2=value[k];
								int temp3=best_move(layer+1,1-player,current_score-temp2).max_score;
								total_score+=temp3;
								n++;
								if(min>temp3){
									min=temp3;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i;
									ans.new_y=j+temp;
								}
								board[i][j+temp]=k;
								board[i][j]='c';
							}
						}
						if(board[i][j]=='m'){
							if(board[i+1][j]=='.'){
								if(i<=8&&!isupper(board[i+2][j-1])){
									if(board[i+2][j-1]=='.'){
										swap(board[i+2][j-1],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(min>temp){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+2;
											ans.new_y=j-1;
										}
										swap(board[i+2][j-1],board[i][j]);
									}
									else{
										char k=board[i+2][j-1];
										int temp=value[k];
										board[i][j]='.';
										board[i+2][j-1]='m';
										int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
										total_score+=temp2;
										n++;
										if(min>temp2){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+2;
											ans.new_y=j-1;
										}
										board[i][j]='m';
										board[i+2][j-1]=k;
									}
								}
								if(i<=8&&!isupper(board[i+2][j+1])){
									if(board[i+2][j+1]=='.'){
										swap(board[i+2][j+1],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(min>temp){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+2;
											ans.new_y=j+1;
										}
										swap(board[i+2][j+1],board[i][j]);
									}
									else{
										char k=board[i+2][j+1];
										int temp=value[k];
										board[i][j]='.';
										board[i+2][j+1]='m';
										int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
										total_score+=temp2;
										n++;
										if(min>temp2){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+2;
											ans.new_y=j+1;
										}
										board[i][j]='m';
										board[i+2][j+1]=k;
									}
								}
							}
							if(board[i-1][j]=='.'){
								if(i>=3&&!isupper(board[i-2][j-1])){
									if(board[i-2][j-1]=='.'){
										swap(board[i-2][j-1],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(min>temp){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-2;
											ans.new_y=j-1;
										}
										swap(board[i-2][j-1],board[i][j]);
									}
									else{
										char k=board[i-2][j-1];
										int temp=value[k];
										board[i][j]='.';
										board[i-2][j-1]='m';
										int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
										total_score+=temp2;
										n++;
										if(min>temp2){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-2;
											ans.new_y=j-1;
										}
										board[i][j]='m';
										board[i-2][j-1]=k;
									}
								}
								if(i>=3&&!isupper(board[i-2][j+1])){
									if(board[i-2][j+1]=='.'){
										swap(board[i-2][j+1],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(min>temp){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-2;
											ans.new_y=j+1;
										}
										swap(board[i-2][j+1],board[i][j]);
									}
									else{
										char k=board[i-2][j+1];
										int temp=value[k];
										board[i][j]='.';
										board[i-2][j+1]='m';
										int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
										total_score+=temp2;
										n++;
										if(min>temp2){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-2;
											ans.new_y=j+1;
										}
										board[i][j]='m';
										board[i-2][j+1]=k;
									}
								}
							}
							if(board[i][j+1]=='.'){
								if(j<=8&&!isupper(board[i-1][j+2])){
									if(board[i-1][j+2]=='.'){
										swap(board[i-1][j+2],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(min>temp){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-1;
											ans.new_y=j+2;
										}
										swap(board[i-1][j+2],board[i][j]);
									}
									else{
										char k=board[i-1][j+2];
										int temp=value[k];
										board[i][j]='.';
										board[i-1][j+2]='m';
										int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
										total_score+=temp2;
										n++;
										if(min>temp2){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-1;
											ans.new_y=j+2;
										}
										board[i][j]='m';
										board[i-1][j+2]=k;
									}
								}
								if(j<=8&&!isupper(board[i+1][j+2])){
									if(board[i+1][j+2]=='.'){
										swap(board[i+1][j+2],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(min>temp){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+1;
											ans.new_y=j+2;
										}
										swap(board[i+1][j+2],board[i][j]);
									}
									else{
										char k=board[i+1][j+2];
										int temp=value[k];
										board[i][j]='.';
										board[i+1][j+2]='m';
										int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
										total_score+=temp2;
										n++;
										if(min>temp2){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+1;
											ans.new_y=j+2;
										}
										board[i][j]='m';
										board[i+1][j+2]=k;
									}
								}
							}
							if(board[i][j-1]=='.'){
								if(j>=3&&!isupper(board[i-1][j-2])){
									if(board[i-1][j-2]=='.'){
										swap(board[i-1][j-2],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(min>temp){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-1;
											ans.new_y=j-2;
										}
										swap(board[i-1][j-2],board[i][j]);
									}
									else{
										char k=board[i-1][j-2];
										int temp=value[k];
										board[i][j]='.';
										board[i-1][j-2]='m';
										int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
										total_score+=temp2;
										n++;
										if(min>temp2){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i-1;
											ans.new_y=j+2;
										}
										board[i][j]='m';
										board[i-1][j-2]=k;
									}
								}
								if(j>=3&&!isupper(board[i+1][j-2])){
									if(board[i+1][j-2]=='.'){
										swap(board[i+1][j-2],board[i][j]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(min>temp){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+1;
											ans.new_y=j-2;
										}
										swap(board[i+1][j-2],board[i][j]);
									}
									else{
										char k=board[i+1][j-2];
										int temp=value[k];
										board[i][j]='.';
										board[i+1][j-2]='m';
										int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
										total_score+=temp2;
										n++;
										if(min>temp2){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=i+1;
											ans.new_y=j-2;
										}
										board[i][j]='m';
										board[i+1][j-2]=k;
									}
								}
							}
						}
						if(board[i][j]=='j'){
							if(i-1!=3&&board[i-1][j]!='@'&&!islower(board[i-1][j])){
								if(board[i-1][j]=='.'){
									swap(board[i][j],board[i-1][j]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(min>temp){
										min=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i-1;
										ans.new_y=j;
									}
									swap(board[i][j],board[i-1][j]);
								}
								else{
									int temp=value[board[i-1][j]];
									char k=board[i-1][j];
									board[i-1][j]='j';
									board[i][j]='.';
									int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
									total_score+=temp2;
									n++;
									if(min>temp2){
										min=temp2;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i-1;
										ans.new_y=j;
									}
									board[i][j]='j';
									board[i-1][j]=k;
								}
							}
							if(i+1!=7&&board[i+1][j]!='@'&&!islower(board[i+1][j])){
								if(board[i+1][j]=='.'){
									swap(board[i][j],board[i+1][j]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(min>temp){
										min=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i+1;
										ans.new_y=j;
									}
									swap(board[i][j],board[i+1][j]);
								}
								else{
									int temp=value[board[i+1][j]];
									char k=board[i+1][j];
									board[i+1][j]='j';
									board[i][j]='.';
									int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
									total_score+=temp2;
									n++;
									if(min>temp2){
										min=temp2;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i+1;
										ans.new_y=j;
									}
									board[i][j]='j';
									board[i+1][j]=k;
								}
							}
							if(j+1!=4&&board[i][j+1]!='@'&&!islower(board[i][j+1])){
								if(board[i][j+1]=='.'){
									swap(board[i][j],board[i][j+1]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(min>temp){
										min=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j+1;
									}
									swap(board[i][j],board[i][j+1]);
								}
								else{
									int temp=value[board[i][j+1]];
									char k=board[i][j+1];
									board[i][j+1]='j';
									board[i][j]='.';
									int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
									total_score+=temp2;
									n++;
									if(min>temp2){
										min=temp2;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j+1;
									}
									board[i][j]='j';
									board[i][j+1]=k;
								}
							}
							if(board[i][j-1]!='@'&&!islower(board[i][j-1])){
								if(board[i][j-1]=='.'){
									swap(board[i][j],board[i][j-1]);
									int temp=best_move(layer+1,1-player,current_score).max_score;
									total_score+=temp;
									n++;
									if(min>temp){
										min=temp;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j-1;
									}
									swap(board[i][j],board[i][j-1]);
								}
								else{
									int temp=value[board[i][j-1]];
									char k=board[i][j-1];
									board[i][j-1]='j';
									board[i][j]='.';
									int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
									total_score+=temp2;
									n++;
									if(min>temp2){
										min=temp2;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j-1;
									}
									board[i][j]='j';
									board[i][j-1]=k;
								}
							}
						}
						if(board[i][j]=='s'){
							if(i==5&&j==2){
								if(!islower(board[6][1])){
									if(board[6][1]=='.'){
										swap(board[i][j],board[6][1]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(min>temp){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=6;
											ans.new_y=1;
										}
										swap(board[i][j],board[6][1]);
									}
									else{
										char k=board[6][1];
										board[6][1]='s';
										board[i][j]='.';
										int temp=value[k];
										int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
										total_score+=temp2;
										n++;
										if(min>temp2){
											min=temp2;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=6;
											ans.new_y=1;
										}
										board[i][j]='s';
										board[6][1]=k;
									}
								}
								if(!islower(board[4][1])){
									if(board[4][1]=='.'){
										swap(board[i][j],board[4][1]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(min>temp){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=4;
											ans.new_y=1;
										}
										swap(board[i][j],board[4][1]);
									}
									else{
										char k=board[4][1];
										board[4][1]='s';
										board[i][j]='.';
										int temp=value[k];
										int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
										total_score+=temp2;
										n++;
										if(min>temp2){
											min=temp2;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=4;
											ans.new_y=1;
										}
										board[i][j]='s';
										board[4][1]=k;
									}
								}
								if(!islower(board[6][3])){
									if(board[6][3]=='.'){
										swap(board[i][j],board[6][3]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(min>temp){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=6;
											ans.new_y=3;
										}
										swap(board[i][j],board[6][3]);
									}
									else{
										char k=board[6][3];
										board[6][3]='s';
										board[i][j]='.';
										int temp=value[k];
										int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
										total_score+=temp2;
										n++;
										if(min>temp2){
											min=temp2;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=6;
											ans.new_y=1;
										}
										board[i][j]='s';
										board[6][3]=k;
									}
								}
								if(!islower(board[4][3])){
									if(board[4][3]=='.'){
										swap(board[i][j],board[4][3]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(min>temp){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=4;
											ans.new_y=3;
										}
										swap(board[i][j],board[4][3]);
									}
									else{
										char k=board[4][3];
										board[4][3]='s';
										board[i][j]='.';
										int temp=value[k];
										int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
										total_score+=temp2;
										n++;
										if(min>temp2){
											min=temp2;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=6;
											ans.new_y=1;
										}
										board[i][j]='s';
										board[4][3]=k;
									}
								}
							}
							else{
								if(!islower(board[5][2])){
									if(board[5][2]=='.'){
										swap(board[i][j],board[5][2]);
										int temp=best_move(layer+1,1-player,current_score).max_score;
										total_score+=temp;
										n++;
										if(min>temp){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=5;
											ans.new_y=2;
										}
										swap(board[i][j],board[5][2]);
									}
									else{
										char k=board[5][2];
										board[5][2]='s';
										board[i][j]='.';
										int temp=value[k];
										int temp2=best_move(layer+1,1-player,current_score-temp).max_score;
										total_score+=temp2;
										n++;
										if(min>temp){
											min=temp;
											ans.original_x=i;
											ans.original_y=j;
											ans.new_x=5;
											ans.new_y=2;
										}
										board[i][j]='s';
										board[5][2]=k;
									}
								}
							}
						}
						if(board[i][j]=='p'){
							int temp=1;
							while(board[i-temp][j]=='.'&&i-temp>0){
								swap(board[i-temp][j],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(min>temp2){
									min=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i-temp;
									ans.new_y=j;
								}
								swap(board[i][j],board[i-temp][j]);
								temp++;
							}
							if(board[i-temp][j]!='@') temp++;
							while(i>0&&board[i-temp][j]!='@'&&!islower(board[i-temp][j])){
								if(isupper(board[i-temp][j])&&i-temp>0){
									char k=board[i-temp][j];
									int temp2=value[k];
									board[i-temp][j]='p';
									board[i][j]='.';
									int temp3=best_move(layer+1,1-player,current_score-temp2).max_score;
									total_score+=temp3;
									n++;
									if(min>temp3){
										min=temp3;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i-temp;
										ans.new_y=j;
									}
									board[i-temp][j]=k;
									board[i][j]='p';
									break;
								}
								temp++;
							}
							temp=1;
							while(board[i+temp][j]=='.'){
								swap(board[i+temp][j],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(min>temp2){
									min=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i+temp;
									ans.new_y=j;
								}
								swap(board[i][j],board[i+temp][j]);
								temp++;
							}
							if(board[i+temp][j]!='@') temp++;
							while(board[i+temp][j]!='@'&&!islower(board[i+temp][j])){
								if(isupper(board[i+temp][j])&&i+temp<11){
									char k=board[i+temp][j];
									int temp2=value[k];
									board[i+temp][j]='p';
									board[i][j]='.';
									int temp3=best_move(layer+1,1-player,current_score-temp2).max_score;
									total_score+=temp3;
									n++;
									if(min>temp3){
										min=temp3;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i+temp;
										ans.new_y=j;
									}
									board[i+temp][j]=k;
									board[i][j]='p';
									break;
								}
								temp++;
							}
							temp=1;
							while(board[i][j-temp]=='.'){
								swap(board[i][j-temp],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(min>temp2){
									min=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i;
									ans.new_y=j-temp;
								}
								swap(board[i][j],board[i][j-temp]);
								temp++;
							}
							if(board[i][j-temp]!='@') temp++;
							while(board[i][j-temp]!='@'&&!islower(board[i][j-temp])){
								if(isupper(board[i][j-temp])&&j-temp>0){
									char k=board[i][j-temp];
									int temp2=value[k];
									board[i][j-temp]='p';
									board[i][j]='.';
									int temp3=best_move(layer+1,1-player,current_score-temp2).max_score;
									total_score+=temp3;
									n++;
									if(min>temp3){
										min=temp3;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j-temp;
									}
									board[i][j-temp]=k;
									board[i][j]='p';
									break;
								}
								temp++;
							}
							temp=1;
							while(board[i][j+temp]=='.'){
								swap(board[i][j+temp],board[i][j]);
								int temp2=best_move(layer+1,1-player,current_score).max_score;
								total_score+=temp2;
								n++;
								if(min>temp2){
									min=temp2;
									ans.original_x=i;
									ans.original_y=j;
									ans.new_x=i;
									ans.new_y=j+temp;
								}
								swap(board[i][j],board[i][j+temp]);
								temp++;
							}
							if(board[i][j+temp]!='@') temp++;
							while(board[i][j+temp]!='@'&&!islower(board[i][j+temp])){
								if(isupper(board[i][j+temp])&&j+temp<12){
									char k=board[i][j+temp];
									int temp2=value[k];
									board[i][j+temp]='p';
									board[i][j]='.';
									int temp3=best_move(layer+1,1-player,current_score-temp2).max_score;
									total_score+=temp3;
									n++;
									if(min>temp3){
										min=temp3;
										ans.original_x=i;
										ans.original_y=j;
										ans.new_x=i;
										ans.new_y=j+temp;
									}
									board[i][j+temp]=k;
									board[i][j]='p';
									break;
								}
								temp++;
							}
						}
					}
				}
			}
		}
	}
	ans.max_score=max;
	if(!player){
		ans.max_score=min;
	}
	/*if(layer!=0){
		ans.max_score=total_score/n;
	}*/
	return ans;
}
int main(){
	/*
	cin>>value['C'];
	cin>>value['M'];
	cin>>value['X'];
	cin>>value['S'];
	cin>>value['P'];
	cin>>value['B'];
	cin>>value['J'];
	cin>>value['c'];
	cin>>value['m'];
	cin>>value['x'];
	cin>>value['s'];
	cin>>value['p'];
	cin>>value['b'];
	cin>>value['j'];
	*/
	while(check()){
		test_data_1();
		num=0;
		clock_t start=clock(); 
		double duration;
		cout<<"--COMPUTER 1: MOVE "<<round<<"--\n";
		move ans=best_move(0,1,0);
		cout<<"Number of simulations: ";
		cout<<num<<endl;
		cout<<"Value, original y, original x, new y, new x: ";
		cout<<ans.max_score<<" "<<ans.original_x<<" "<<ans.original_y<<" "<<ans.new_x<<" "<<ans.new_y<<endl;
		board[ans.new_x][ans.new_y]=board[ans.original_x][ans.original_y];
		board[ans.original_x][ans.original_y]='.';
		for(int i=0;i<12;i++){
			for(int j=0;j<12;j++){
				cout<<board[i][j];
			}
			cout<<endl;
		}
		duration=(clock()-start)/(double)(CLOCKS_PER_SEC);
		cout<<"Run Time: "<<duration<<endl;
		if(!check()) break;
		start=clock();
		cout<<"============================================================\n";
		cout<<"--COMPUTER 2: MOVE "<<round<<"--\n";
		test_data_2();
		ans=best_move(0,0,0);
		cout<<"Number of simulations: ";
		cout<<num<<endl;
		cout<<"Value, original y, original x, new y, new x: ";
		cout<<ans.max_score<<" "<<ans.original_x<<" "<<ans.original_y<<" "<<ans.new_x<<" "<<ans.new_y<<endl;
		board[ans.new_x][ans.new_y]=board[ans.original_x][ans.original_y];
		board[ans.original_x][ans.original_y]='.';
		for(int i=0;i<12;i++){
			for(int j=0;j<12;j++){
				cout<<board[i][j];
			}
			cout<<endl;
		}
		duration=(clock()-start)/(double)(CLOCKS_PER_SEC);
		cout<<"Run Time: "<<duration<<endl;
		cout<<"============================================================\n";
		round++;
	}
}
