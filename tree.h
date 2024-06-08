int cnte, h[MAXN], nx[MAXN<<1], to[MAXN<<1];
inline void adde(int u, int v){
	cnte++;
	nx[cnte]=h[u];
	to[cnte]=v;
	h[u]=cnte;
}

#define TREE_SIZ
#define TREE_DFN // Depends on TREE_SIZ
#define TREE_DEP 0 // The value is the depth of the root
#define TREE_STORE_CH // Store sons into a vector ch[u]

namespace Tree {
	/*
	 * Tree data structure in a namespace. Supports siz, dfn, dep, ch, subtree()
	 *
	 */
	int fa[MAXN];

#ifdef TREE_SIZ
	int siz[MAXN];
#endif

#ifdef TREE_DFN
	int dfn[MAXN], dfn_count, rev[MAXN];
	inline bool subtree(int x, int y){
		// Check whether y is in subtree of x (inclusive).
		return dfn[x] <= dfn[y] && dfn[y] < dfn[x] + siz[x];
	}
#endif

#ifdef TREE_DEP
	int dep[MAXN];
#endif

#ifdef TREE_STORE_CH
	vector<int> ch[MAXN];
#endif

	void dfs(int u){
#ifdef TREE_SIZ
		siz[u] = 1;
#endif
#ifdef TREE_DFN
		dfn[u] = ++dfn_count;
		rev[dfn_count] = u;
#endif
		for(int i=h[u]; i; i=nx[i]){
			int v=to[i];
			if(v==fa[u]) continue;
			fa[v] = u;
#ifdef TREE_DEP
			dep[v] = dep[u] + 1;
#endif
			dfs(v);
#ifdef TREE_SIZ
			siz[u] += siz[v];
#endif
#ifdef TREE_STORE_CH
			ch[u].push_back(v);
#endif
		}
		return ;
	}

	void clear(){
		// Clean up some memory, especially ch[u].
		cnte = 0;
		for(int i=1; i<=n; i++){
			h[i] = fa[i] = 0;
#ifdef TREE_STORE_CH
			ch[i].clear();
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
#ifdef TREE_DEP
		dep[rt] = TREE_DEP;
#endif
#ifdef TREE_DFN
		dfn_count = 0;
#endif
		dfs(rt);
	}
}
using namespace Tree;
