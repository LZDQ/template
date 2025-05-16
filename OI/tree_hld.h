int cnte, h[MAXN], nx[MAXN<<1], to[MAXN<<1];
inline void adde(int u, int v){
	cnte++;
	nx[cnte]=h[u];
	to[cnte]=v;
	h[u]=cnte;
}

#define TREE_HLD_DEP 0 // The value is the depth of the root
#define TREE_HLD_DFN // This will traverse heavy son first. Also used in segment tree id
#define TREE_HLD_STORE_CH // Store sons into a vector ch[u]
#define TREE_HLD_STORE_LINK // Store the link into hl[top[u]]
namespace TreeHLD {
	/*
	 * Tree data structure in a namespace. Implementing Heavy-Link Decomposition.
	 * Supports LCA in O(log n).
	 */
	int fa[MAXN];
	int siz[MAXN], dep[MAXN], son[MAXN], top[MAXN];

#ifdef TREE_HLD_DFN
	int dfn[MAXN], dfn_count, rev[MAXN];
	inline bool subtree(int x, int y){
		// Check whether y is in subtree of x (inclusive).
		return dfn[x] <= dfn[y] && dfn[y] < dfn[x] + siz[x];
	}
#endif

#ifdef TREE_HLD_STORE_CH
	vector<int> ch[MAXN];
#endif

#ifdef TREE_HLD_STORE_LINK
	vector<int> hl[MAXN];
#endif

	void dfs(int u){
		siz[u] = 1;
		son[u] = 0;
		for(int i=h[u]; i; i=nx[i]){
			int v=to[i];
			if(v==fa[u]) continue;
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dfs(v);
			siz[u] += siz[v];
			if(!son[u] || siz[v] > siz[son[u]])
				son[u] = v;
#ifdef TREE_HLD_STORE_CH
			ch[u].push_back(v);
#endif
		}
		return ;
	}

	void dfs_hld(int u){
#ifdef TREE_HLD_DFN
		dfn[u] = ++dfn_count;
		rev[dfn_count] = u;
#endif
#ifdef TREE_HLD_STORE_LINK
		hl[top[u]].push_back(u);
#endif
		if(son[u]){
			top[son[u]] = top[u];
			dfs_hld(son[u]);
			for(int i=h[u]; i; i=nx[i]){
				int v=to[i];
				if(v==fa[u] || v==son[u]) continue;
				top[v] = v;
				dfs_hld(v);
			}
		}
	}

	void clear(){
		// Clean up some memory, especially ch[u].
		cnte = 0;
		for(int i=1; i<=n; i++){
			h[i] = fa[i] = 0;
#ifdef TREE_HLD_STORE_CH
			ch[i].clear();
#endif
#ifdef TREE_HLD_STORE_LINK
			hl[i].clear();
#endif
		}
		return ;
	}

	void init(int rt=1){
		// Read n-1 edges and dfs
		cnte = 0;
		for(int i=1; i<=n; i++)
			h[i] = 0;
		for(int i=1, x, y; i<=n-1; i++){
			scanf("%d%d", &x, &y);
			adde(x, y);
			adde(y, x);
		}
		fa[rt] = 0;
		dep[rt] = TREE_HLD_DEP;
#ifdef TREE_HLD_DFN
		dfn_count = 0;
#endif
		siz[0] = 0;
		dfs(rt);
		top[rt] = rt;
		dfs_hld(rt);
	}

	int lca(int x, int y){
		// LCA in O(log n)
		int l, r; // Segment tree id
		while(top[x] != top[y]){
			if (dep[top[x]] < dep[top[y]])
				swap(x, y);
#ifdef TREE_HLD_DFN
			l = dfn[top[x]];
			r = dfn[x];
			// Do something
#endif
			x = fa[top[x]];
		}
		if (dep[x] > dep[y])
			swap(x, y);
#ifdef TREE_HLD_DFN
		l = dfn[x];
		r = dfn[y];
		// Do something
#endif
		return x;
	}
}
using namespace TreeHLD;
