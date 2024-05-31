#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define maxm 2005*2005*4
#define maxn 2005
#define maxg 505
using namespace std;
int p,k,n;
struct Point
{
	int x,y;
	Point(int x=0,int y=0):x(x),y(y){} 
}a[maxn];
int bx[maxn],by[maxn],dx,dy;
int id[maxn][maxn];
int U[maxm],V[maxm],idcnt;
double W[maxm];
struct edge
{
	int to,id;
	double w;
	edge(int to=0,double w=0,int id=0):to(to),w(w),id(id){}
};
vector<edge> g[maxn*maxn];
void addedge(int u,int v,double w)
{
	++idcnt;
	g[u].push_back(edge(v,w,idcnt));
	g[v].push_back(edge(u,w,idcnt));
	U[idcnt]=u;V[idcnt]=v;W[idcnt]=w;
}
struct Group
{
	int sz;
	vector<int> a;
}grp[maxg];
bool operator < (const Group &A,const Group &B)
{
	return A.sz<B.sz;
}
const int inf=1000000000;

int used[maxn*maxn];
vector<double> dis2[maxg];
vector<int> preu2[maxg],preid2[maxg];
void sssp(vector<int> s,vector<double> &dis,vector<int> &preu,vector<int> &preid)
{
	dis.resize(maxn*maxn);
	preu.resize(maxn*maxn);
	preid.resize(maxn*maxn);
	for(int i=1;i<=n;++i)dis[i]=inf,used[i]=0,preu[i]=0,preid[i]=0;
	priority_queue < pair<double,int> > pq;
	for(int x:s)pq.push(make_pair(0,x)),dis[x]=0;
	while(!pq.empty())
	{
		int u=pq.top().second;pq.pop();
		if(used[u])continue;
		used[u]=1;
		for(auto p:g[u])
		{
			int v=p.to;
			double w=p.w;
			int id=p.id;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				preu[v]=u;
				preid[v]=id;
				pq.push(make_pair(-dis[v],v));
			}
		}
	}
}
void init()
{
	sort(grp+1,grp+k+1);
	for(int i=2;i<=k;++i)
	{
		vector<int> st;
		st.clear();
		for(int x:grp[i].a)st.push_back(x);
		sssp(st,dis2[i],preu2[i],preid2[i]);
	}
}

void addpath2(vector<int> &e,int r,int u)
{
	int x=u;
	while(preu2[r][x])
	{
		e.push_back(preid2[r][x]);
		x=preu2[r][x]; 
	}
}

int cov[maxg],bel[maxg];
int eid[maxm];
bool cmp(const int &x,const int &y)
{
	return W[x]<W[y];
}
int par[maxn*maxn];
int find(int x)
{
	if(par[x]==x)return x;
	return par[x]=find(par[x]);
}
int d[maxn*maxn],g_cnt[maxg];
vector< pair<int,int> > G[maxn*maxn];
vector<int> has[maxn*maxn];
double ImprovAPP()
{
	init();
	double ans=inf;
	vector<int> Ans,Ans2,Ans3;
	double mn=inf;
	for(int r:grp[1].a)
	{
		bool ok=1;
		for(int i=2;i<=k;++i)if(dis2[i][r]>1e12)ok=0;
		if(!ok)continue;
		for(int i=1;i<=k;++i)cov[i]=0;
		priority_queue< pair<double,int> > pq;
		for(int i=2;i<=k;++i)pq.push(make_pair(-dis2[i][bel[i]=r],i));
		vector<int> path;
		while(!pq.empty())
		{
			int o=pq.top().second;
			pq.pop();
			if(cov[o])continue;
			addpath2(path,o,bel[o]);
			cov[o]=1;
			int x=bel[o];
			while(x)
			{
				for(int j=2;j<=k;++j)if(!cov[j])
				{
					if(dis2[j][x]<dis2[j][bel[j]])
					{
						pq.push(make_pair(-dis2[j][x],j));
						bel[j]=x;
					}
				}
				x=preu2[o][x];
			}
		}
		sort(path.begin(),path.end());
		path.erase(unique(path.begin(),path.end()),path.end());
		double totw=0;
		for(int e:path)totw+=W[e];
		if(totw<ans)
		{
			ans=totw;
			Ans.clear();
			for(int e:path)Ans.push_back(e);
		}
	}
	if(ans>1e12)return -1;
	int m=Ans.size();
	for(int i=0;i<m;++i)eid[i]=Ans[i];
	for(int i=1;i<=n;++i)par[i]=i;
	sort(eid,eid+m,cmp);
	for(int i=0;i<m;++i)
	{
		int u=U[eid[i]],v=V[eid[i]];
		if(find(u)!=find(v))
		{
			par[find(u)]=find(v);
			Ans2.push_back(eid[i]);
		}
	}
	for(int i=1;i<=n;++i)d[i]=-1;
	for(int e:Ans2)
	{
		int u=U[e],v=V[e];
		G[u].push_back(make_pair(v,e));
		G[v].push_back(make_pair(u,e));
		d[u]++;d[v]++;
	}
	for(int i=1;i<=k;++i)g_cnt[i]=0;
	for(int i=1;i<=k;++i)
		for(int x:grp[i].a)if(d[x]>=0) 
		{
			g_cnt[i]++;
			has[x].push_back(i);
		}
	priority_queue < pair<double,pair<int,int> > > q;
	for(int i=1;i<=n;++i)if(d[i]==0)
	{
		int nx=0;
		for(int j:has[i])if(g_cnt[j]==1)++nx;
		if(nx)continue;
		for(auto p:G[i])
		{
			int x=p.first,e=p.second;
			if(d[x]<=0)continue;
			q.push(make_pair(W[e],make_pair(i,e)));
		}
	}
	unordered_map<int,int> del;
	while(!q.empty())
	{
		int e=q.top().second.second,v=q.top().second.first,u;
		q.pop();
		if(U[e]==v)u=V[e];else u=U[e];
		int nx=0;
		for(int j:has[v])if(g_cnt[j]==1)++nx;
		if(d[v]!=0)continue;
		if(nx)continue;
		for(int j:has[v])g_cnt[j]--;
		--d[u];
		del[e]=1;
		if(d[u]==0)
		{
			int ny=0;
			for(int j:has[u])if(g_cnt[j]==1)++ny;
			if(ny)continue;
			for(auto p:G[u])
			{
				int x=p.first,e=p.second;
				if(d[x]<=0)continue;
				q.push(make_pair(W[e],make_pair(u,e)));
			}
		}
	}
	for(int e:Ans2)if(!del.count(e))Ans3.push_back(e);
	double rr=0;
	for(int e:Ans3)rr+=W[e];
	return rr;
}
int main()
{
	scanf("%d%d",&p,&k);
	//cerr<<p<<" "<<k<<endl;
	for(int i=1;i<=p;++i)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		bx[i]=a[i].x,by[i]=a[i].y;
	}
	sort(bx+1,bx+p+1);
	dx=unique(bx+1,bx+p+1)-bx-1;
	sort(by+1,by+p+1);
	dy=unique(by+1,by+p+1)-by-1;
	for(int i=1;i<=dx;++i)
		for(int j=1;j<=dy;++j)id[i][j]=++n;
	for(int i=1;i<=p;++i)
	{
		a[i].x=lower_bound(bx+1,bx+dx+1,a[i].x)-bx;
		a[i].y=lower_bound(by+1,by+dy+1,a[i].y)-by;
	}
	for(int i=1;i<=k;++i)
	{
		int sz,t;
		scanf("%d",&sz);
		grp[i].sz=sz;
		while(sz--) 
		{
			scanf("%d",&t);
			grp[i].a.push_back(id[a[t].x][a[t].y]);
		}
	}
	for(int i=1;i<=dx;++i)
		for(int j=1;j<=dy;++j)
		{
			if(i<dx)
			{
				addedge(id[i][j],id[i+1][j],abs(bx[i]-bx[i+1]));
			}
			if(j<dy)
			{
				addedge(id[i][j],id[i][j+1],abs(by[j]-by[j+1]));
			}
		}
	int st=clock();
	int ans=ImprovAPP();
	int Tim=clock()-st;
	printf("%d\n%d\n",Tim,ans);
}
