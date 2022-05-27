int n,rk[MAXN],sa[MAXN];
char s[MAXN];
inline bool cmp(int x,int y){
	return s[x]<s[y];
}
void SA(){
	for(int i=1; i<=n; i++)
		sa[i]=i;
	sort(sa+1,sa+n+1,cmp);
	for(int i=1,j=1; i<=n; i++){
		if(i>1&&s[sa[i]]!=s[sa[i-1]]) j++;
		rk[sa[i]]=j;
	}
	static int a[MAXN],cnt[MAXN];
	for(int k=0; 1<<k<n; k++){
		int m=0;
		for(int i=1; i<=n; i++){
			m=max(m,rk[i]);
			cnt[i+(1<<k)<=n?rk[i+(1<<k)]+1:1]++;
		}
		for(int i=1; i<=m; i++)
			cnt[i]+=cnt[i-1];
		for(int i=1; i<=n; i++)
			sa[++cnt[i+(1<<k)<=n?rk[i+(1<<k)]:0]]=i;
		for(int i=0; i<=m; i++)
			cnt[i]=0;
		for(int i=1; i<=n; i++)
			cnt[rk[sa[i]]+1]++;
		for(int i=1; i<=m; i++)
			cnt[i]+=cnt[i-1];
		for(int i=1; i<=n; i++)
			a[++cnt[rk[sa[i]]]]=sa[i];
		for(int i=1,j=0; i<=n; i++){
			if(i==1||rk[a[i]]!=rk[a[i-1]]||(a[i]+(1<<k)<=n?rk[a[i]+(1<<k)]:0)!=(a[i-1]+(1<<k)<=n?rk[a[i-1]+(1<<k)]:0)) j++;
			sa[a[i]]=j;
		}
		for(int i=0; i<=m+1; i++)
			cnt[i]=0;
		for(int i=1; i<=n; i++)
			rk[i]=sa[i];
	}
	for(int i=1; i<=n; i++)
		sa[rk[i]]=i;
	return ;
}
