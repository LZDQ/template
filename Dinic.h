int cntp,s,t;
namespace Dinic{
	int cnte=1,h[MAXN],to[MAXM],nx[MAXM],ww[MAXM];
	inline void adde(int u,int v,int w){
		cnte++;
		nx[cnte]=h[u];
		to[cnte]=v;
		ww[cnte]=w;
		h[u]=cnte;
	}
	inline void Adde(int u,int v,int w){
		adde(u,v,w);
		adde(v,u,0);
	}
	queue<int> que;
	int dis[MAXN],cur[MAXN];
	bool Bfs(){
		que.push(s);
		memset(dis,0,sizeof(dis));
		dis[s]=1;
		while(!que.empty()){
			int u=que.front();
			que.pop();
			for(int i=h[u]; i; i=nx[i]){
				int v=to[i];
				if(ww[i]&&!dis[v]){
					dis[v]=dis[u]+1;
					que.push(v);
				}
			}
		}
		memcpy(cur,h,sizeof(h));
		return dis[t];
	}
	int Dfs(int u,int flw){
		if(u==t) return flw;
		int res=0;
		for(int i=cur[u]; i; i=nx[i]){
			cur[u]=i;
			int v=to[i];
			if(ww[i]&&dis[v]==dis[u]+1){
				int f=Dfs(v,min(flw-res,ww[i]));
				ww[i]-=f;
				ww[i^1]+=f;
				res+=f;
				if(flw==res) break;
			}
		}
		return res;
	}
	int Flow(){
		int res=0;
		while(Bfs()) res+=Dfs(s,INF);
		return res;
	}
}
using Dinic::Adde;
