#define DOUBLE_HASH
template <typename T, int N=MAXN>
struct HashSeq {
	// Get the hash of an interval
	// if DOUBLE_HASH, store the result in a pair<int, int>
	// otherwise, store the result in a int
	const int M1=1e9+7, K1=19260817, B1=137;
	int n;
	T *a;
	bool rev;
	ll pw1[N], s1[N];
#ifdef DOUBLE_HASH
	const int M2=1e9+9, K2=19491001, B2=167;
	ll pw2[N], s2[N];
#endif
	void init(int _n, T *_a, bool _rev=false){
		// if `rev`, get the hash of the reversed substring (l, r).
		n = _n;
		a = _a;
		rev = _rev;
		pw1[0] = 1;
		for(int i=1; i<=n; i++)
			pw1[i] = pw1[i-1] * K1 % M1;
		if(!rev){
			s1[0] = 0;
			for(int i=1; i<=n; i++)
				s1[i] = (s1[i-1] * K1 + a[i] + B1) % M1;
		} else {
			s1[n+1] = 0;
			for(int i=n; i; i--)
				s1[i] = (s1[i+1] * K1 + a[i] + B1) % M1;
		}
#ifdef DOUBLE_HASH
		pw2[0] = 1;
		for(int i=1; i<=n; i++)
			pw2[i] = pw2[i-1] * K2 % M2;
		if(!rev){
			s2[0] = 0;
			for(int i=1; i<=n; i++)
				s2[i] = (s2[i-1] * K2 + a[i] + B2) % M2;
		} else {
			s2[n+1] = 0;
			for(int i=n; i; i--)
				s2[i] = (s2[i+1] * K2 + a[i] + B2) % M2;
		}
#endif
	}
#ifdef DOUBLE_HASH
	inline pr get_hash(int l, int r){
		int h1=(rev ? s1[l] - s1[r+1] * pw1[r-l+1] % M1 : s1[r] - s1[l-1] * pw1[r-l+1] % M1);
		if(h1 < 0)
			h1 += M1;
		int h2=(rev ? s2[l] - s2[r+1] * pw2[r-l+1] % M2 : s2[r] - s2[l-1] * pw2[r-l+1] % M2);
		if(h2 < 0)
			h2 += M2;
		return make_pair(h1, h2);
	}
#else
	inline int get_hash(int l, int r){
		int h1=(rev ? s1[l] - s1[r+1] * pw1[r-l+1] % M1 : s1[r] - s1[l-1] * pw1[r-l+1] % M1);
		if(h1 < 0)
			h1 += M1;
		return h1;
	}
#endif
	inline bool diff(int l1, int r1, int l2, int r2){
		return get_hash(l1, r1) != get_hash(l2, r2);
	}
};
