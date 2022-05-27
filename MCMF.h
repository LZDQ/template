int cntp,s,t;
namespace Dinic{
	int cnte=1,h[MAXN],to[MAXM],nx[MAXM],ww[MAXM],cc[MAXM];
	inline void adde(int u,int v,int w,int c){
		cnte++;
		nx[cnte]=h[u];
		to[cnte]=v;
		ww[cnte]=w;
		cc[cnte]=c;
		h[u]=cnte;
	}
	inline void Adde(int u,int v,int w,int c=0){
		adde(u,v,w,c);
		adde(v,u,0,-c);
	}
	queue<int> que;
	int dis[MAXN],flw[MAXN],pre[MAXN];
	bool inq[MAXN];
	bool Spfa(){
		que.push(s);
		memset(dis,0x3f,sizeof(dis));
		dis[s]=0;
		flw[s]=INF;
		flw[t]=0;
		while(!que.empty()){
			int u=que.front();
			que.pop();
			inq[u]=0;
			for(int i=h[u]; i; i=nx[i]){
				int v=to[i];
				if(ww[i]&&dis[v]>dis[u]+cc[i]){
					dis[v]=dis[u]+cc[i];
					flw[v]=min(flw[u],ww[i]);
					pre[v]=i;
					if(!inq[v]){
						inq[v]=1;
						que.push(v);
					}
				}
			}
		}
		return flw[t];
	}
	int Flow(){
		int res=0,f=0;
		while(Spfa()){
			f+=flw[t];
			res+=flw[t]*dis[t];
			int u=t;
			while(u!=s){
				int e=pre[u];
				ww[e]-=flw[t];
				ww[e^1]+=flw[t];
				u=to[e^1];
			}
		}
		return res;
	}
}
using Dinic::Adde;
