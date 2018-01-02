#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=512,E=500005,inf=1e9;
int La[N],To[E],Ne[E],We[E],TOT=1;
int M[N][N],ST,ED,Cnt[N],Dis[N];
int Flow[N],CUR;
void AE(int x,int y,int w) {
	To[++TOT]=y;
	Ne[TOT]=La[x];
	La[x]=TOT;
	We[TOT]=w;
}
int SAP(int u,int f) {
	int i,v,d,t;
	if(u==ED) return f; d=0;
	for(i=La[u];i;i=Ne[i]) {
		v=To[i];
		if(i<=TOT&&We[i]>0&&Dis[v]+1==Dis[u]) {
			t=SAP(v,min(f-d,We[i]));
			We[i]-=t;We[i^1]+=t;d+=t;
			if(d==f||Dis[ST]>=ED) return d;
		}
	}
	if(!--Cnt[Dis[u]]) Dis[ST]=ED;
	++Cnt[++Dis[u]];return d;
}
int n,m,Ans;
int main() {
	int i,j,k,x,y,low,up;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d%d",&x,&y,&low,&up);
		up-=low;M[x][y]+=up;
		Flow[x]+=low;Flow[y]-=low;
	}
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
			if(M[i][j]||M[j][i]) {
				AE(i,j,M[i][j]);
				AE(j,i,M[j][i]);
			}
	CUR=TOT;
	ST=n+1;ED=n+2;
	for(i=1;i<=n;i++) {
		if(Flow[i]==0) continue;
		if(Flow[i]<0) AE(ST,i,-Flow[i]),AE(i,ST,0);
		else AE(i,ED,Flow[i]),AE(ED,i,0);
	}
	AE(n,1,inf);AE(1,n,0);
	while(Dis[ST]<ED) SAP(ST,inf);
	// printf("%d\n",We[TOT]);
	fill(Dis,Dis+N,0);
	fill(Cnt,Cnt+N,0);
	ST=1;ED=n;swap(TOT,CUR);//TOT=CUR;
	while(Dis[ST]<ED) Ans+=SAP(ST,inf);
	printf("%d\n",Ans+We[CUR]);
}
