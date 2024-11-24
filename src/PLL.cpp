#include<bits/stdc++.h>
#define maxn 6000005
using namespace std;
const double eps = 1e-5;
const double inf = 1e12;
int n,m;
int has[maxn];
pair<int,int> ord[maxn];
vector<pair<int,double>> g[maxn];
struct Hub
{
	int v,pred;
	double dis;
	Hub(int v=0,double dis=0,int pred=0):v(v),dis(dis),pred(pred){}
};
bool operator  < (const Hub &A,const Hub &B)
{
	return A.v<B.v;
}
vector<Hub> HL[maxn];
int used[maxn],pre[maxn];
double DHL[maxn],dis[maxn];
double getD(int u)
{
	double ans=inf;
	for(Hub o:HL[u])
	{
		double t=DHL[o.v]+o.dis;
		if(ans>t)ans=t;
	}
	return ans;
}
void dij(int s)
{
	priority_queue<pair<double,int>> pq;
	vector<int> usedvis,DHLvis;
	for(Hub o:HL[s])
	{
		int v=o.v;
		double d=o.dis;
		DHL[v]=d;
		DHLvis.push_back(v);
	}
	dis[s]=0;pre[s]=s;
	pq.push(make_pair(0,s));
	while(!pq.empty())
	{
		int u=pq.top().second;
		pq.pop();
		if(used[u])continue;
		used[u]=1;
		usedvis.push_back(u);
		if(has[u])continue;
		if(dis[u]<getD(u)-eps)
		{
			HL[u].push_back(Hub(s,dis[u],pre[u]));
			for(auto e:g[u])if(!used[e.first])
			{
				int v=e.first;
				double w=e.second;
				if(dis[v]>dis[u]+w+eps)
				{
					dis[v]=dis[u]+w+eps;
					pre[v]=u;
					pq.push(make_pair(-dis[v],v));
				}
			}
		}
	}
	for(int x:DHLvis)DHL[x]=inf;
	for(int x:usedvis)
	{
		used[x]=0;
		dis[x]=inf;
		pre[x]=-1;
	}
	
	has[s]=1;
}
int main()
{
	freopen("Weightgraph.txt","r",stdin);
	freopen("WeightPLLlabel.txt","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int u,v;
		double w;
		scanf("%d%d%lf",&u,&v,&w);
		g[u].push_back(make_pair(v,w));
		g[v].push_back(make_pair(u,w)); 
	}
	for(int i=1;i<=n;++i)ord[i]=make_pair(-(int)g[i].size(),i);
	sort(ord+1,ord+n+1);
	//cerr<<ord[1].first<<" "<<ord[1].second<<endl;
	for(int i=1;i<=n;++i)
	{
		dis[i]=inf;
		pre[i]=-1;
		DHL[i]=inf;
		used[i]=0;
	}
	for(int i=1;i<=n;++i)
	{
		int s=ord[i].second;
		//cerr<<i<<" start"<<endl;
		dij(s);
		//cerr<<i<<" finished"<<endl;
	}
	for(int i=1;i<=n;++i)
	{
		sort(HL[i].begin(),HL[i].end());
	}
	for(int u=1;u<=n;++u)
	{
		printf("%d %d\n",u-1,HL[u].size());
		for(Hub x:HL[u])
		{
			printf("%d %lf %d\n",x.v-1,x.dis,x.pred-1);
		}
	}
}
