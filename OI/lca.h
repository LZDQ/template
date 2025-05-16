int cnte, h[MAXN], to[MAXN<<1], nx[MAXN<<1];
inline void adde(int u,int v){
	cnte++;
	nx[cnte]=h[u];
	to[cnte]=v;
	h[u]=cnte;
}

typedef unsigned long long u64;
namespace LCA {
	// Get the edge from n and above. Call LCA::init() to init, then lca(x, y) to get lca
	const int B=64, MAXB=MAXN/B+2;
	int fa[MAXN], siz[MAXN], dfn[MAXN], dfn_count, rev[MAXN];
	int m, a[MAXN]; // When switching to the next children, append dfn[u] to this array
	int pos[MAXN]; // pos[u] stores the index to run RMQ

	int mi[B][MAXB], lg[MAXN], pre[MAXN], suf[MAXN], stk[B+5];
	u64 st[MAXN];

	void dfs(int u){
		dfn[u] = ++dfn_count;
		rev[dfn_count] = u;
		siz[u] = 1;
		pos[u] = m;
		bool first=true;
		for(int i=h[u]; i; i=nx[i]){
			int v=to[i];
			if(v==fa[u]) continue;
			fa[v] = u;
			if(first) first = false;
			else a[++m] = dfn[u];
			dfs(v);
			siz[u] += siz[v];
		}
	}

	void init(int rt=1){
		fa[rt] = m = 0;
		dfs(rt);
		lg[0] = -1;
		u64 s=0;
		for(int i=1, l=1; i<=m; i++){
			lg[i] = lg[i>>1] + 1;
			pre[i] = a[i];
			if(i!=l) pre[i] = min(pre[i], pre[i-1]);
			while(*stk && a[stk[*stk]] >= a[i])
				s ^= 1ull<<stk[(*stk)--]-l;
			s ^= 1ull<<(stk[++*stk]=i)-l;
			st[i] = s;
			if(!(i & B-1) || i==m)
				mi[0][(i+B-1)/B] = a[stk[1]], *stk=s=0, l=i+1;
		}
		suf[m] = a[m];
		for(int i=m-1; i; i--){
			suf[i] = a[i];
			if(i & B-1) suf[i] = min(suf[i], suf[i+1]);
		}
		for(int i=1; i<=lg[m]; i++)
			for(int j=1; j+(1<<i)-1<=m; j++)
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

	inline bool subtree(int x, int y){
		return dfn[x] <= dfn[y] && dfn[y] < dfn[x] + siz[x];
	}

	inline int lca(int x, int y){
		if(dfn[x] > dfn[y])
			swap(x, y);
		if(subtree(x, y)) return x;
		return rev[rmq(pos[x]+1, pos[y])];
	}
}
using LCA::lca;
