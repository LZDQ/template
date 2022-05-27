namespace LCT{
#define lc ch[u][0]
#define rc ch[u][1]
	int ch[MAXN][2],fa[MAXN],siz[MAXN],val[MAXN],tag[MAXN];
	inline bool chk(int u){
		return ch[fa[u]][1]==u;
	}
	inline bool nrt(int u){
		return ch[fa[u]][chk(u)]==u;
	}
	inline void add(int u,int v){
		val[u]+=v;
		tag[u]+=v;
	}
	inline void pushup(int u){
		siz[u]=siz[lc]+siz[rc]+1;
	}
	inline void pushdwn(int u){
		if(tag[u]){
			add(lc,tag[u]);
			add(rc,tag[u]);
			tag[u]=0;
		}
	}
	inline void rotate(int u){
		bool x=chk(u);
		int f=fa[u],ff=fa[f],y=ch[u][!x];
		pushdwn(f);
		pushdwn(u);
		if(nrt(f)) ch[ff][chk(f)]=u;
		fa[u]=ff;
		ch[u][!x]=f;
		fa[f]=u;
		ch[f][x]=y;
		fa[y]=f;
		pushup(f);
		pushup(u);
	}
	void pushall(int u){
		if(nrt(u)) pushall(fa[u]);
		pushdwn(u);
	}
	void Splay(int u){
		pushall(u);
		for(int &f=fa[u]; nrt(u); rotate(u))
			if(nrt(f)) rotate(chk(u)==chk(f)?f:u);
	}
	void Access(int u){
		for(int x=0; u; x=u,u=fa[u])
			Splay(u),rc=x,pushup(u);
	}
#undef lc
#undef rc
}



namespace LCT{
#define lc ch[u][0]
#define rc ch[u][1]
	int ch[MAXN][2],fa[MAXN],siz[MAXN],val[MAXN],tag[MAXN];
	bool rev[MAXN];
	inline bool chk(int u){
		return ch[fa[u]][1]==u;
	}
	inline bool nrt(int u){
		return ch[fa[u]][chk(u)]==u;
	}
	inline void add(int u,int v){
		val[u]+=v;
		tag[u]+=v;
	}
	inline void Rev(int u){
		rev[u]^=1;
		swap(lc,rc);
	}
	inline void pushup(int u){
		siz[u]=siz[lc]+siz[rc]+1;
	}
	inline void pushdwn(int u){
		if(rev[u]){
			Rev(lc);
			Rev(rc);
			rev[u]=0;
		}
		if(tag[u]){
			add(lc,tag[u]);
			add(rc,tag[u]);
			tag[u]=0;
		}
	}
	inline void rotate(int u){
		bool x=chk(u);
		int f=fa[u],ff=fa[f],y=ch[u][!x];
		pushdwn(f);
		pushdwn(u);
		if(nrt(f)) ch[ff][chk(f)]=u;
		fa[u]=ff;
		ch[u][!x]=f;
		fa[f]=u;
		ch[f][x]=y;
		fa[y]=f;
		pushup(f);
		pushup(u);
	}
	void pushall(int u){
		if(nrt(u)) pushall(fa[u]);
		pushdwn(u);
	}
	void Splay(int u){
		pushall(u);
		for(int &f=fa[u]; nrt(u); rotate(u))
			if(nrt(f)) rotate(chk(u)==chk(f)?f:u);
	}
	void Access(int u){
		for(int x=0; u; x=u,u=fa[u])
			Splay(u),rc=x,pushup(u);
	}
	void MakeRt(int u){
		Access(u);
		Splay(u);
		Rev(u);
	}
#undef lc
#undef rc
}
