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

#define maxS 68
vector<int> vis[maxn*maxn];
vector<double> dp[maxn*maxn];

double DPBF(int r,vector<Group> grp,int h)
{
	for(int i=0;i<maxn*maxn;++i)vis[i].resize(maxS),dp[i].resize(maxS);
	for(int i=0;i<maxn*maxn;++i)
		for(int j=0;j<maxS;++j)
		{
	 		vis[i][j]=0;
	  		dp[i][j]=0;
		}
	priority_queue< pair<double,pair<int,int> > > q;
	for(int i=0;i<h-1;++i)
		for(int x:grp[i].a)
		{
			vis[x][1<<i]=1;
			dp[x][1<<i]=0;
			q.push(make_pair(0,make_pair(x,1<<i)));
		}
	vis[r][1<<(h-1)]=1;
	dp[r][1<<(h-1)]=0;
	q.push(make_pair(0,make_pair(r,1<<(h-1))));
	while(!q.empty())
	{
		int u=q.top().second.first,S=q.top().second.second;
		q.pop();
		if(S==(1<<h)-1)
		{
			return dp[u][S];
		}
		for(auto p:g[u])
		{
			int v=p.to,id=p.id;
			double w=p.w;
			if(!vis[v][S]||dp[v][S]>dp[u][S]+w)
			{
				vis[v][S]=1;
				dp[v][S]=dp[u][S]+w;
				q.push(make_pair(-dp[v][S],make_pair(v,S)));
			}
		}
		int T=(1<<h)-1;
		T^=S;
		for(int p=T;p;p=(p-1)&T)if(vis[u][p])
		{
			if(!vis[u][S|p]||dp[u][S|p]>dp[u][S]+dp[u][p])
			{
				vis[u][S|p]=1;
				dp[u][S|p]=dp[u][S]+dp[u][p];
				q.push(make_pair(-dp[u][S|p],make_pair(u,S|p)));
			}
		}
	}
	return inf;
}

vector< pair<double,double> > gp[maxg];

int main()
{
	scanf("%d%d",&p,&k);
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
			gp[i].push_back(make_pair(bx[a[t].x],by[a[t].y]));
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
	sort(grp+1,grp+k+1); 
	vector<Group> grp1;
	vector<int> g1;
	double maxlen=0;
	int t1=0,t2=0;
	for(int i=2;i<=k;++i)
	{
		for(int j=2;j<i;++j)
		{
			double mn=inf;
			for(auto ap:gp[i])
				for(auto bp:gp[j])
				{
					mn=min(mn,abs(ap.first-bp.first)+abs(ap.second-bp.second)); 
				}
			if(mn>maxlen)
			{
				maxlen=mn;
				t1=i;t2=j;
			}
		}
	}
	g1.push_back(t1);
	g1.push_back(t2);
	for(int o=3;o<=4;++o)
	{
		double mx=0;
		int now=0;
		for(int i=2;i<=k;++i)
		{
			double mn=inf;
			for(int j:g1)
			{
				for(auto ap:gp[i])
					for(auto bp:gp[j])
						mn=min(mn,abs(ap.first-bp.first)+abs(ap.second-bp.second));
			}
			if(mn>mx)
			{
				mx=mn;
				now=i;
			}
		}
		g1.push_back(now);
	}
	for(int x:g1)grp1.push_back(grp[x]);
  //cerr<<grp1.size()<<endl;
	int H=(int)grp1.size()+1;
	double ans=inf;
	for(int r:grp[1].a)
	{
    // cerr<<"r = "<<r<<" start"<<endl;
		double w1=DPBF(r,grp1,H);
		ans=min(ans,w1);
	}
   printf("0\n");
	printf("%.10f\n",ans);
}
