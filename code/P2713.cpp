#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=505,E=500005,inf=2e9;
int La[N],Ne[E],To[E],We[E],Fi[N],TOT=1;
int M[N][N],Dis[N],Cnt[N],Flow[N];
int n,m,Ans,ST,ED,CNT;
void AE(int x,int y,int w) {
	To[++TOT]=y;
	Ne[TOT]=La[x];
	Fi[x]=La[x]=TOT;
	We[TOT]=w;
}
int SAP(int u,int f) {
	int i,v,d,t;
	if(u==ED) return f; d=0;
	for(i=La[u];i;La[u]=i=Ne[i]) {
		v=To[i];
		if(We[i]>0&&Dis[u]==Dis[v]+1) {
			t=SAP(v,min(f-d,We[i]));
			We[i]-=t;We[i^1]+=t;d+=t;
			if(d==f||Dis[ST]>=CNT) return d;
		}
	}
	if(!--Cnt[Dis[u]]) Dis[ST]=CNT;
	La[u]=Fi[u];Cnt[++Dis[u]]++;return d;
}
int main() {
	int i,j,k,x,y,u,d;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d%d",&x,&y,&d,&u);
		u-=d;M[x][y]+=u;
		Flow[x]+=d;Flow[y]-=d;
	}
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
			if(M[i][j]||M[j][i])
				AE(i,j,M[i][j]),AE(j,i,M[j][i]);
	ST=n+1;ED=n+2;CNT=ED;
	for(i=1;i<=n;i++) {
		if(Flow[i]==0) continue;
		if(Flow[i]>0) AE(i,ED,Flow[i]),AE(ED,i,0);
		else AE(ST,i,-Flow[i]),AE(i,ST,0);
	}
	while(Dis[ST]<CNT) SAP(ST,inf);
	AE(n,1,inf);AE(1,n,0);
	fill(Dis,Dis+N,0);
	fill(Cnt,Cnt+N,0);
	while(Dis[ST]<CNT) SAP(ST,inf);
	printf("%d\n",We[TOT]);
}