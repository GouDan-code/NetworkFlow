#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long 
const int N=50053,E=500053,inf=1e18;
int La[N],To[E],Ne[E],We[E],TOT=1;
int ST,ED,Cnt[N],Dis[N];
int Flow[N],CUR,CNT;
char buf[500053*100],*in=buf;
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
int G() {
	int o=0;
	while(!isdigit(*in)) in++;
	while(isdigit(*in)) o=o*10+*in++-48;
	return o;
}
main() {
	fread(buf,1,sizeof buf,stdin);
	int i,j,k,x,y,low,up,s,t;
	// scanf("%lld%lld%lld%lld",&n,&m,&s,&t);
	n=G();m=G();s=G();t=G();
	for(i=1;i<=m;i++) {
		// scanf("%lld%lld%lld%lld",&x,&y,&low,&up);
		x=G();y=G();low=G();up=G();
		up-=low;
		AE(x,y,up);AE(y,x,0);//M[x][y]+=up;
		Flow[x]+=low;Flow[y]-=low;
	}

	CUR=TOT;
	ST=n+1;ED=n+2;CNT=ED;
	for(i=1;i<=n;i++) {
		if(Flow[i]==0) continue;
		if(Flow[i]<0) AE(ST,i,-Flow[i]),AE(i,ST,0);
		else AE(i,ED,Flow[i]),AE(ED,i,0),Ans+=Flow[i];
	}
	AE(t,s,inf);AE(s,t,0);
	while(Dis[ST]<CNT) Ans-=SAP(ST,inf);
	if(Ans!=0) return puts("please go home to sleep"),0;
	Ans=We[TOT];
	swap(TOT,CUR);ST=t;ED=s;CNT=n;
	while(Dis[ST]<CNT) Ans-=SAP(ST,inf);
	printf("%lld\n",Ans);
}