namespace Fenwick {
	int sum[MAXN];
	inline ll query(int x){
		ll res=0;
		for(int i=x; i; i-=i&-i)
			res += sum[i];
		return res;
	}
	inline void add(int x, int y){
		for(int i=x; i<=n; i+=i&-i)
			sum[i] += y;
	}
}
using namespace Fenwick;
