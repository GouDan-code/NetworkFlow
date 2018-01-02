#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=360,E=40005,inf=1e9;
int La[N],To[E],Ne[E],We[E],TOT=1;
int Cnt[N],Dis[N],ST,ED,Flow[N];
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
		if(We[i]>0&&Dis[v]+1==Dis[u]) {
			t=SAP(v,min(f-d,We[i]));
			We[i]-=t;We[i^1]+=t;d+=t;
			if(d==f||Dis[ST]>=ED) return d;
		}
	}
	if(!--Cnt[Dis[u]]) Dis[ST]=ED;
	++Cnt[++Dis[u]];return d;
}
int n,m,MaxFlow,Flag;
void solve() {
	int i,j,k,x,y,low,up;
	scanf("%d%d",&n,&m);
	ST=n+1;ED=ST+1;
	Flag=0;
	TOT=1;MaxFlow=0;
	fill(La,La+N,0);
	fill(Cnt,Cnt+N,0);
	fill(Dis,Dis+N,0);
	fill(Flow,Flow+N,0);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d%d",&x,&y,&low,&up);
		if(Flag) continue;
		up-=low;
		if(up>0) AE(x,y,up),AE(y,x,0);
		else if(up<0) Flag=1;
		Flow[x]+=low;Flow[y]-=low;
	}
	if(Flag) {puts("No");return;}
	for(i=1;i<=n;i++) {
		if(Flow[i]==0) continue;
		if(Flow[i]<=0) AE(ST,i,-Flow[i]),AE(i,ST,0);
		else AE(i,ED,Flow[i]),AE(ED,i,0),MaxFlow+=Flow[i];
	}
	while(Dis[ST]<ED) MaxFlow-=SAP(ST,inf);
	if(MaxFlow!=0) puts("No");
	else puts("Yes");
}
int main() {
	int T;scanf("%d",&T);
	while(T--) solve();
}