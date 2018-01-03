#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<cctype>
using namespace std;
#define int long long 
const int N=50045,E=355003,inf=1e18;
int La[N],To[E],Ne[E],We[E],TOT=1,n,m,Fi[N];
int ED,ST,CNT,Dis[N],Cnt[N],Flow[N];
char buf[500053*100],*in=buf;
void AE(int x,int y,int w) {
	To[++TOT]=y;
	Ne[TOT]=La[x];
	Fi[x]=La[x]=TOT;
	We[TOT]=w;
}
int SAP(int u,int f) {
	int i,v,d,t,r;
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
	La[u]=Fi[u];++Cnt[++Dis[u]];return d;
}
int  Ans;
main() {
	int i,j,k,s,t,d,u,x,y;
	fread(buf,1,sizeof buf,stdin);
	n=G();m=G();s=G();t=G();
	for(i=1;i<=m;i++) {
		x=G();y=G();d=G();u=G();
		u-=d;if(u) AE(x,y,u),AE(y,x,0);
		Flow[x]+=d;Flow[y]-=d;
	}

	ST=n+1;ED=n+2;
	for(i=1;i<=n;i++) {
		if(Flow[i]==0) continue;
		if(Flow[i]>0) AE(i,ED,Flow[i]),AE(ED,i,0);
		else AE(ST,i,-Flow[i]),AE(i,ST,0),Ans+=-Flow[i];
	}
	CNT=n+2;ST=n+1;ED=n+2;
	while(Dis[ST]<CNT) Ans-=SAP(ST,inf);
	AE(t,s,inf);AE(s,t,0);
	fill(Dis,Dis+N,0);
	fill(Cnt,Cnt+N,0);
	while(Dis[ST]<CNT) Ans-=SAP(ST,inf);
	if(Ans!=0) return puts("please go home to sleep"),0;
	printf("%lld\n",We[TOT]);
}