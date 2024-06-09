template <int N, typename T=int>
struct CartesianTree {
	int n, rt, lc[N], rc[N];
	T *a;

	void init(int _n, T *_a, bool is_big) {
		n = _n;
		a = _a;
		int stk[N], top=0;
		for(int i=1; i<=n; i++){
			lc[i] = rc[i] = 0;
			while(top && ((a[i] < a[stk[top]]) ^ is_big)){
				rc[stk[top]] = lc[i];
				lc[i] = stk[top];
				top--;
			}
			stk[++top] = i;
		}
		rt = 0;
		while (top) {
			rc[stk[top]] = rt;
			rt = stk[top--];
		}
	}

	void dfs(int u){
		int v;
		if(v = lc[u]){
			dfs(v);
		}
		if(v = rc[u]){
			dfs(v);
		}
	}
};
