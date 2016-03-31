#include<iostream>
#include <stdlib.h>
#include <time.h>
#include"Sudoku.h"
#include<vector>
using namespace std;
Sudoku::Sudoku(){
int map[81]={2,8,3,1,4,5,7,6,9,
9,6,4,2,7,3,1,5,8,
7,1,5,6,8,9,2,4,3,
3,5,8,4,2,1,9,7,6,
4,2,7,9,5,6,8,3,1,
1,9,6,7,3,8,4,2,5,
8,4,9,3,6,7,5,1,2,
6,7,1,5,9,2,3,8,4,
5,3,2,8,1,4,6,9,7};
mapin.resize(81);
for(int i=0;i<81;i++)
	mapin.at(i)=map[i];
}

void Sudoku::readIn(){
	mapin.resize(81);
	for(int i=0;i<81;i++){
	int y;
	cin>>y;
	mapin.at(i)=y;	
}
}

void Sudoku::giveQuestion(){
	srand(time(NULL));
	for(int i=0;i<81;i++){
		int random_num=rand()%10;
		if(mapin.at(i)==random_num) mapin.at(i)=0;
		if(mapin.at(i)==random_num+1) mapin.at(i)=0;
		if(mapin.at(i)==random_num-1) mapin.at(i)=0;
	}
	mapin.resize(81);
	for(int i=0;i<81;i++){
		cout<<mapin[i]<<" ";
		if(i%9==8) cout<<endl;
	}
}

void Sudoku::transform(){
	srand(time(NULL));
	int num=rand()%5;
	if (num==1)		 flip(num);
	else if (num==2) changeCol();
	else if (num==3) changeRow();
	else if (num==4) changeNum(); 
	else if (num==0) flip(num);
	for(int i=0;i<81;i++){
		cout<<mapin[i]<<" ";
		if(i%9==8) cout<<endl;
	}
}

void Sudoku::changeNum(){
	for(int i=0;i<81;++i){
		if(mapin[i]==5) mapin[i]=mapin[i]+2;
		else if(mapin[i]==7) mapin[i]=mapin[i]-2;
	}
}

void Sudoku::changeRow(){
	int tmp;
	for(int i=27;i<54;i++){
		tmp=mapin[i];
		mapin[i]=mapin[i+27];
		mapin[i+27]=tmp;
	}
}

void Sudoku::changeCol(){
	int tmp;
	for(int i=0;i<75;i+=9){
		for(int j=0;j<3;j++){
			tmp=mapin[i+j];
			mapin[i+j]=mapin[i+j+6];
			mapin[i+j+6]=tmp;
		}
	}
}

void Sudoku::flip(int i){
	int tmp;
	if(i==0){
	for(int i=0;i<9;i++){
		tmp=mapin[i];
		mapin[i]=mapin[i+72];
		mapin[i+72]=tmp;}
	for(int i=9;i<18;i++){
		tmp=mapin[i];
		mapin[i]=mapin[i+54];
		mapin[i+54]=tmp;}
	for(int i=18;i<27;i++){
		tmp=mapin[i];
		mapin[i]=mapin[i+36];
		mapin[i+36]=tmp;}
	for(int i=27;i<36;i++){
		tmp=mapin[i];
		mapin[i]=mapin[i+18];
		mapin[i+18]=tmp;}
}
	else {
	for(int i=0;i<81;i+=9){
		tmp=mapin[i];
		mapin[i]=mapin[i+8];
		mapin[i+8]=tmp;}
	for(int i=1;i<81;i+=9){
		tmp=mapin[i];
		mapin[i]=mapin[i+6];
		mapin[i+6]=tmp;}
	for(int i=2;i<81;i+=9){
		tmp=mapin[i];
		mapin[i]=mapin[i+4];
		mapin[i+4]=tmp;}
	for(int i=3;i<81;i+=9){
		tmp=mapin[i];
		mapin[i]=mapin[i+2];
		mapin[i+2]=tmp;}
}
}

int ProbMapPoint(int *in, int i, int j){
	bool total[9];
	int count=0;
	int v_min,v_max,h_min,h_max;
	if(in[9*i+j]!=0)
		return 0;

	//initial
	for(int k=0;k<9;k++)
	total[k]=true;

	//virtical
	for(int k=0;k<9;k++)
	if(in[9*k+j]!=0)
		total[in[k*9+j]-1]=false;

	//horizontal
	for(int k=0;k<9;k++)
	if(in[9*i+k]!=0)
		total[in[i*9+k]-1]=false;

	//square
	if(i<3){
		v_min=0;v_max=3;
	}else if(i<6){
		v_min=3;v_max=6;
	}else {
		v_min=6;v_max=9;
	}

	if(j<3){
		h_min=0;h_max=3;
	}else if(j<6){
		h_min=3;h_max=6;
	}else{
		h_min=6;h_max=9;
	}

	for(int v=v_min;v<v_max;v++)
		for(int h=h_min;h<h_max;h++)
			if(in[v*9+h]!=0)
				total[in[v*9+h]-1]=false;
	
	count=0;
	for(int i=0;i<9;i++)
		if(total[i])
			count++;
	return count;
}

int ProbMap(int *in,int *out){
	int tmp=0;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			out[9*i+j]=ProbMapPoint(in,i,j);
			tmp=(out[9*i+j]==1)?1:tmp;
		}
	}
	return tmp;
}

int ProbNum(int *in, int i, int j){
	bool total[9];
	int v_min,v_max,h_min,h_max;
	if(in[9*i+j]!=0)
		return 0;

	//initial
	for(int k=0;k<9;k++)
	total[k]=true;

	//virtical
	for(int k=0;k<9;k++)
	if(in[9*k+j]!=0)
		total[in[k*9+j]-1]=false;

	//horizontal
	for(int k=0;k<9;k++)
	if(in[9*i+k]!=0)
		total[in[i*9+k]-1]=false;

	//square
	if(i<3){
		v_min=0;v_max=3;
	}else if(i<6){
		v_min=3;v_max=6;
	}else {
		v_min=6;v_max=9;
	}

	if(j<3){
		h_min=0;h_max=3;
	}else if(j<6){
		h_min=3;h_max=6;
	}else{
		h_min=6;h_max=9;
	}

	for(int v=v_min;v<v_max;v++)
		for(int h=h_min;h<h_max;h++)
			if(in[v*9+h]!=0)
				total[in[v*9+h]-1]=false;
	
	for(int i=0;i<9;i++)
		if(total[i])
			return i+1;
	return 10;
	
}

void ModifiedMap(int *inMap,int *inProMap){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(inProMap[i*9+j]==1){
				inMap[i*9+j]=ProbNum(inMap,i,j);}
		}
	}
}

void Sudoku::solve(){
	int p[9][9],sudo[9][9];
	//transform 1D to 2D
	for(int i=1;i<9;i++){
		for(int j=1;j<9;j++){
			sudo[i][j]=mapin[i*9+j];}}
	
	int tmp=1;
	for(int i=1;;i++){
		tmp=ProbMap(*sudo,*p);
		ModifiedMap(*sudo,*p);
	if(tmp==0) break;
	}

	//transform 2D to 1D
	for(int i=1;i<9;i++){
		for(int j=1;j<9;j++){
			mapin[i*9+j]=sudo[i][j];}}
	
	//check if unsolvable
	for(int i=0;i<81;i++){
		if (mapin[i]==10){
			cout<<"0"<<endl;
			break;}
	}

	//check if more than one answer
	for(int i=0;i<81;i++){
		if (mapin[i]==0){
			cout<<"2"<<endl;
			break;}
	}

	//print the answer
	cout<<"1"<<endl;
	for(int i=0;i<81;i++){
		cout<<mapin[i]<<" ";
		if(i%9==8) cout<<endl;
		}
}
	