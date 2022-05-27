namespace ST{
	const int blks=20,MAXM=MAXN/blks+2;
	int n,m;
	int mx[blks][MAXM],lg[MAXN],pre[MAXN],suf[MAXN],st[MAXN],stk[blks+2];
	void Init(){
		m=(n+blks-1)/blks;
		lg[0]=-1;
		for(int i=1,l=1,s=0; i<=n; i++){
			pre[i]=a[i];
			if(i%blks!=1) pre[i]=max(pre[i],pre[i-1]);
			lg[i]=lg[i>>1]+1;
			while(*stk&&a[stk[*stk]]<=a[i]) s^=1<<stk[(*stk)--]-l;
			s^=1<<(stk[++*stk]=i)-l;
			st[i]=s;
			if(i%blks==0||i==n) mx[0][(i+blks-1)/blks]=a[stk[1]],*stk=s=0,l=i+1;
		}
		suf[n]=a[n];
		for(int i=n-1; i; i--){
			suf[i]=a[i];
			if(i%blks) suf[i]=max(suf[i],suf[i+1]);
		}
		for(int i=1; i<=lg[m]; i++)
			for(int j=1; j+(1<<i)-1<=m; j++)
				mx[i][j]=max(mx[i-1][j],mx[i-1][j+(1<<i-1)]);
		return ;
	}
	int Query(int l,int r){
		int x=(l+blks-1)/blks,y=(r+blks-1)/blks;
		if(x==y){
			x=(x-1)*blks+1;
			return a[l+__builtin_ctz(st[r]>>l-x)];
		}
		int res=max(suf[l],pre[r]);
		x++,y--,l=lg[y-x+1];
		if(~l) res=max(res,max(mx[l][x],mx[l][y-(1<<l)+1]));
		return res;
	}
}
