//This code belongs to Amol Dumrewal
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

void print(int *);
double findcost(int *);
int playnext(int *, double cost, double parentcost, int temperature);
void g_rand_neigh(int *, int *);
void g_rand_path(int *, int *);
void g_bpath(int *);
void takeinput();
void copypath(int *, int *);

int ncity;
double maxcost;
double pcity[501][3];
double dcity[501][501];

int main(){
	srand(time(NULL));
	time_t seconds;
	seconds = time(NULL);
	time_t sec = seconds;
	takeinput();
	int *t_bpath;
	t_bpath = (int*)malloc(ncity*sizeof(int));
	double cost = maxcost;
	int *testpath;
	testpath = (int*)malloc(ncity*sizeof(int));;
	double testcost;
	int *neighbour;
	neighbour = (int*)malloc(ncity*sizeof(int));;
	double neighcost;
	int *bpath;
	bpath = (int*)malloc(ncity*sizeof(int));
	while(sec-seconds<280){
		int i;
		g_bpath(bpath);
		double costbpath;
		costbpath = findcost(bpath);
		copypath(testpath,bpath);
		double temperature = 40;
		int count=ncity/4;
		while(count>0){
			copypath(testpath,bpath);
			testcost = costbpath;
			temperature = ncity;
			count--;
			while(temperature>0.0001){
				do{
					g_rand_neigh(neighbour, testpath);
					neighcost = findcost(neighbour);
					if(neighcost<costbpath){
						copypath(bpath,neighbour);
						costbpath = neighcost;
					}
					temperature = temperature-0.001;
					sec = time(NULL);
					if(sec-seconds>280)break;
					if(temperature<0.0005)break;
				}while(playnext(neighbour,neighcost,testcost,temperature)!=1);
				copypath(testpath,neighbour);
				testcost = neighcost;
				sec = time(NULL);
				if(sec-seconds>280)break;
			}
			if(costbpath<cost){
				copypath(t_bpath,bpath);
				cost = costbpath;
				print(t_bpath);
			}
			if(sec-seconds>280)break;
		}
		sec = time(NULL);
	}
	sec = time(NULL);
	return 0;
}

void print(int *path){
	int i;
	printf("\n");
	for(i=0;i<ncity;i++){
		printf("%d ",(path[i]+1));
	}
	return ;
}

double findcost(int *path){
	int i;
	double c = 0;
	for(i=0;i<ncity;i++){
		c = c + dcity[path[i]][path[(i+1)%ncity]];
	}
	return c;
}

int playnext(int *path, double cost, double parentcost, int temperature){
	double ex = -(parentcost-cost);
	ex = ex/temperature;
	ex = exp(ex);
	double prb = 1/(1+ex);
	double gen = rand() % 1000;
	if(gen>(prb*1000))return 0;
	return 0;
}

void g_rand_neigh(int *path, int *path1){
	int i,p,q,t;
	for(i=0;i<ncity;i++)path[i]=path1[i];
	p = rand() % ncity;
	q = rand() % ncity;
	if(p>q){
		t = p;
		p = q;
		q = t;
	}
	for(i=0;i<=(q-p)/2;i++){
		t = path[q-i];
		path[q-i] = path[p+i];
		path[p+i] = t;
	}
	return ;
}

void g_rand_path(int *path, int *path1){
	int i,p,k;
	for(i=0;i<ncity;i++)path[i]=path1[i];
	for(i=0;i<ncity;i++){
		p = rand() % ncity;
		k = path[i];
		path[i] = path[p];
		path[p] = k;
	}
	return ;
}

void g_bpath(int *path){
	int i,j,pos;
	double min;
	for(i=0;i<ncity;i++){
		path[i] = i;
	}
	path[0] = rand() % ncity;
	path[path[0]] = 0;
	for(i=1;i<ncity;i++){
		min = dcity[path[i-1]][path[i]];
		pos = i;
		for(j=i;j<ncity;j++){
			if(dcity[path[i-1]][path[j]]<min){
				min = dcity[path[i-1]][path[j]];
				pos = j;
			}
		}
		j = path[pos];
		path[pos] = path[i];
		path[i] = j;
	}
	return ;
}

void takeinput(){
	int i,j;
	char *s;
	s=(char *)malloc(20*sizeof(char));
	scanf("%s",s);
	scanf("%d",&ncity);
	for(i=0;i<ncity;i++){
		double x,y;
		scanf("%lf %lf",&x,&y);
		pcity[i][0] = x;
		pcity[i][1] = y;
	}
	maxcost = 0;
	for(i=0;i<ncity;i++){
		double x;
		for(j=0;j<ncity;j++){
			scanf("%lf ",&x);
			dcity[i][j] = x;
			if(x>maxcost)maxcost = x;
		}
	}
	maxcost = maxcost*ncity;
	return ;
}

void copypath(int *path, int* old){
	int i;
	for(i=0;i<ncity;i++){
		path[i] = old[i];
	}
	return ;
}
