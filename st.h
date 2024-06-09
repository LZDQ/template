typedef unsigned long long u64;
namespace ST {
	// Store the array in ST::n and ST::a, and then call ST::init().
	const int B=64, MAXB=MAXN/B+2;
	int n, a[MAXN]; // the array.

	int mi[B][MAXB], lg[MAXN], pre[MAXN], suf[MAXN], stk[B+5];
	u64 st[MAXN];

	void init(){
		lg[0] = -1;
		u64 s=0;
		for(int i=1, l=1; i<=n; i++){
			lg[i] = lg[i>>1] + 1;
			pre[i] = a[i];
			if(i!=l) pre[i] = min(pre[i], pre[i-1]);
			while(*stk && a[stk[*stk]] >= a[i])
				s ^= 1ull<<stk[(*stk)--]-l;
			s ^= 1ull<<(stk[++*stk]=i)-l;
			st[i] = s;
			if(!(i & B-1) || i==n)
				mi[0][(i+B-1)/B] = a[stk[1]], *stk=s=0, l=i+1;
		}
		suf[n] = a[n];
		for(int i=n-1; i; i--){
			suf[i] = a[i];
			if(i & B-1) suf[i] = min(suf[i], suf[i+1]);
		}
		for(int i=1; i<=lg[n]; i++)
			for(int j=1; j+(1<<i)-1<=n; j++)
				mi[i][j] = min(mi[i-1][j], mi[i-1][j+(1<<i-1)]);
	}

	inline int rmq(int l, int r){
		assert(l<=r);
		int x=(l+B-1)>>6, y=(r+B-1)>>6;
		if(x==y){
			x = (x-1)<<6|1;
			return a[l+__builtin_ctzll(st[r]>>l-x)];
		}
		int res=min(suf[l], pre[r]);
		x++;
		y--;
		l = lg[y-x+1];
		if(~l) res = min(res, min(mi[l][x], mi[l][y-(1<<l)+1]));
		return res;
	}
}
using ST::rmq;
