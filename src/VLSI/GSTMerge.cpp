#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define maxn 3005
using namespace std;
int p,g;
struct Point
{
	int x,y;
	Point(int x=0,int y=0):x(x),y(y){} 
}a[maxn];
int bx[maxn],by[maxn],dx,dy;
int id[maxn][maxn];
int n,m;
struct edge
{
	int u,v,w;
	edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
}e[maxn*maxn*4];
int getD(pair<int,int> A,pair<int,int> B)
{
	return abs(bx[A.first]-bx[B.first])+abs(by[A.second]-by[B.second]);
}
void getSP(pair<int,int> A,pair<int,int> B,vector< pair<int,int> > &nT,vector< pair< pair<int,int>,pair<int,int> > > &SP)
{
	int x0=A.first,y0=A.second,x1=B.first,y1=B.second;
	nT.clear();SP.clear();
	while(x0<x1)
	{
		nT.push_back(make_pair(x0,y0));
		SP.push_back(make_pair(make_pair(x0,y0),make_pair(x0+1,y0)));
		++x0;
	}
	while(x0>x1)
	{
		nT.push_back(make_pair(x0,y0));
		SP.push_back(make_pair(make_pair(x0,y0),make_pair(x0-1,y0)));
		--x0;
	}
	while(y0<y1)
	{
		nT.push_back(make_pair(x0,y0));
		SP.push_back(make_pair(make_pair(x0,y0),make_pair(x0,y0+1)));
		++y0;
	}
	while(y0>y1)
	{
		nT.push_back(make_pair(x0,y0));
		SP.push_back(make_pair(make_pair(x0,y0),make_pair(x0,y0-1)));
		--y0;
	}
}
struct Group
{
	int sz;
	vector< pair<int,int> > a;
}grp[maxn];
bool operator < (const Group &A,const Group &B)
{
	return A.sz<B.sz;
}

const int inf=1000000000;

vector< pair<int,int> > solve1()
{
	vector< pair<int,int> > Ans;
	int AnsW=inf;
	for(auto x:grp[1].a)
	{
		vector< pair<int,int> > tmp;
		tmp.clear();
		int tmpW=0;
		for(int i=2;i<=g;++i)
		{
			int mindis=inf;
			pair<int,int> minid=make_pair(0,0);
			for(auto y:grp[i].a)
			{
				int dis=getD(x,y);
				if(dis<mindis)
				{
					mindis=dis;
					minid=y;
				}
			}
			tmp.push_back(minid);
			tmpW+=mindis;
		}
		if(tmpW<AnsW)
		{
			AnsW=tmpW;
			Ans.clear();
			for(auto x:tmp)Ans.push_back(x);
		}
	}
	return Ans;
}

int w[maxn][maxn];
int inT[maxn][maxn];
int fa[maxn];

int find(int x)
{
	if(!x)return 0;
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}

vector<int> ss[maxn];
int used[maxn];
void join(int x,int y)
{
	if(ss[x].size()<ss[y].size())
	{
		for(int z:ss[x])ss[y].push_back(z);
		swap(ss[x],ss[y]);
	}
	else
	{
		for(int z:ss[y])ss[x].push_back(z);
	}
}

int solve2(vector< pair<int,int> > P, vector< pair< pair<int,int>,pair<int,int> > > &Ans,pair<int,int> rt)
{
	int ans=0;
	Ans.clear();
	int r=lower_bound(P.begin(),P.end(),rt)-P.begin(); 
	for(int i=1;i<=g;++i)fa[i]=i,ss[i].push_back(i);
	for(int i=1;i<=g;++i)inT[P[i-1].first][P[i-1].second]=i;
	int cnt=g-1;
	while(cnt)
	{
		vector<int> s2;
		for(int i=1;i<=g;++i)used[i]=1;
		for(int i=1;i<=g;++i)if(fa[i]==i&&i!=r)s2.push_back(i);
		random_shuffle(s2.begin(),s2.end());
		for(int i=0;i<max(1,(int)s2.size()/8);++i)
		{
			int x=s2[i];
			used[x]=0;
		}
		
		vector< pair<int,int> > op;
		
		for(int i=1;i<=g;++i)if(fa[i]==i&&(!used[i]))
		{
			int h=-1,j=-1,ad=inf,u,v;
			for(int k=1;k<=g;++k)if(fa[k]==k&&used[k])
			{
				int md=inf,tu,tv;
				for(int x:ss[i])
					for(int y:ss[k])
					{
						int t=getD(P[x-1],P[y-1]);
						if(t<md)
						{
							md=t;tu=x;tv=y;
						}
					}
				if(h==-1||md<ad)
				{
					h=j=k;
					ad=md;
					u=tu;v=tv;
				}
			}
			--cnt;
			vector< pair<int,int> > nT;
			vector< pair< pair<int,int>,pair<int,int> > > SP;
			getSP(P[u-1],P[v-1],nT,SP);
			int sz=SP.size();
			int st=0,en=sz-1;
			for(int k=0;k<sz;++k)
			{
				auto x=SP[k].first;
				if(find(inT[x.first][x.second])==i)st=k;
			}
			for(int k=st;k<sz;++k)
			{
				auto x=SP[k].first,y=SP[k].second;
				ans+=getD(x,y);
				Ans.push_back(SP[k]);
				inT[x.first][x.second]=i;
				int bel=find(inT[y.first][y.second]);
				if(bel&&bel!=i)
				{
					j=bel;
					break;
				}
			}
			op.push_back(make_pair(i,j));
		}
		
		for(auto p:op)
		{
			int x=p.first,y=p.second;
			join(find(y),x);
			fa[x]=find(y);
		}
	}
	return ans;
}
int start_time;
int main()
{
	scanf("%d%d",&p,&g);
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
	for(int i=1;i<=g;++i)
	{
		int sz,t;
		scanf("%d",&sz);
		grp[i].sz=sz;
		while(sz--) 
		{
			scanf("%d",&t);
			grp[i].a.push_back(make_pair(a[t].x,a[t].y));
		}
	}
	sort(grp+1,grp+g+1);
	start_time=clock();
	vector< pair<int,int> > P=solve1();
	pair<int,int> rt=P[0];
	sort(P.begin(),P.end());
	P.erase(unique(P.begin(),P.end()),P.end());
	g=P.size();
	vector<pair<pair<int,int>,pair<int,int> > > Ans;
	Ans.clear();
	int ans=solve2(P,Ans,rt);
	printf("%d\n",clock()-start_time);
	printf("%d\n",ans);
  	/*for(auto p:Ans)
  	{
  		int x0=p.first.first,y0=p.first.second;
  		int x1=p.second.first,y1=p.second.second;
  		printf("%d %d %d %d\n",bx[x0],by[y0],bx[x1],by[y1]);
  	}*/
}
