#include<cstdio>
#include<algorithm>
#include<cstring>
typedef long long ll;
using namespace std;
const int mod=998244353;
struct node{
	ll u,r,s1,s2,s3;
	node(ll a=0,ll b=0,ll c=0,ll d=0,ll e=0){
		u=a,r=b,s1=c,s2=d,s3=e;
	}
}tu(1,0,0,0,0),tr(0,1,0,0,0),ans;
node operator +(node a,node b){
	return node(
		(a.u+b.u)%mod,
		(a.r+b.r)%mod,
		(a.s1+b.s1+a.u*b.r)%mod,
		(a.s2+b.s2+2*a.u*b.s1+a.u*a.u%mod*b.r)%mod,
		(a.s3+b.s3+a.u*(b.r*(b.r+1)/2%mod)+a.r*b.s1+a.u*a.r%mod*b.r)%mod
	);
}
node Fstpw(node a,int b){
	node res(0);
	while(b){
		if(b&1) res=res+a;
		b>>=1;
		a=a+a;
	}
	return res;
}
node Euclid(int p,int q,int r,int l,node a,node b){
	if(!l) return node();
	if(p>=q) return Euclid(p%q,q,r,l,a,Fstpw(a,p/q)+b);
	ll cntu=(1ll*p*l+r)/q;
	if(!cntu) return Fstpw(b,l);
	return Fstpw(b,(q-r-1)/p)+a+Euclid(q,p,(q-r-1)%p,cntu-1,b,a)+Fstpw(b,l-(q*cntu-r-1)/p);
}
int main(){
	int _; scanf("%d",&_);
	int n,a,b,c;
	while(_--){
		scanf("%d%d%d%d",&n,&a,&b,&c);
		ans=Fstpw(tu,b/c)+Euclid(a,c,b%c,n,tu,tr);
		printf("%lld %lld %lld\n",(ans.s1+b/c)%mod,(ans.s2+1ll*(b/c)*(b/c))%mod,ans.s3);
	}
	return 0;
}
