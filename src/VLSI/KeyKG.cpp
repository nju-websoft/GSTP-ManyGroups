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

double dis_table[maxn][maxn];
pair<int,int> u_table[maxn][maxn];
bool inT[maxn][maxn];

int solve2(vector< pair<int,int> > P, vector< pair< pair<int,int>,pair<int,int> > > &Ans)
{
	for(int i=1;i<=dx;++i)
		for(int j=1;j<=dy;++j)dis_table[i][j]=inf,u_table[i][j]=make_pair(0,0);
	Ans.clear();
	int ansW=inf;
	for(auto rt:P)
	{
		for(auto x:P)
		{
			dis_table[x.first][x.second]=inf,u_table[x.first][x.second]=make_pair(0,0);
		}
		vector< pair< pair<int,int>,pair<int,int> > > tmp;
		tmp.clear();
		int tmpW=0;
		memset(inT,0,sizeof(inT)); 
		vector< pair<int,int> > T;
		T.clear();
		T.push_back(rt);
		inT[rt.first][rt.second]=1;
		for(auto v:P)if(!inT[v.first][v.second])
		{
			int nd=getD(rt,v);
			if(nd<dis_table[v.first][v.second])
			{
				dis_table[v.first][v.second]=nd;
				u_table[v.first][v.second]=rt;
			}
		}
		for(int turn=1;turn<P.size();++turn)
		{
			pair<int,int> u=make_pair(0,0),v=make_pair(0,0);
			int mindis=inf;
			for(auto y:P)if(!inT[y.first][y.second])
			{
				pair<int,int> x=u_table[y.first][y.second];
				if(dis_table[y.first][y.second]<mindis)
				{
					mindis=dis_table[y.first][y.second];
					u=x;v=y;
				}
			}
			vector< pair<int,int> > nT;
			vector< pair< pair<int,int>,pair<int,int> > > SP;
			getSP(v,u,nT,SP);
			for(auto p:SP)
			{
				auto A=p.first,B=p.second;
				inT[A.first][A.second]=1;
				tmpW+=getD(A,B);
				T.push_back(A);
				tmp.push_back(p);
			}
			for(auto x:nT)
			{
				for(auto v:P)if(!inT[v.first][v.second])
				{
					int nd=getD(x,v);
					if(nd<dis_table[v.first][v.second])
					{
						dis_table[v.first][v.second]=nd;
						u_table[v.first][v.second]=x;
					}
				}
			}
		}
		if(tmpW<ansW)
		{
			ansW=tmpW;
			Ans.clear();
			for(auto x:tmp)Ans.push_back(x);
		}
	}
	return ansW;
}
int start_time;
int main()
{
	freopen("point.txt","r",stdin);
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
	sort(P.begin(),P.end());
	P.erase(unique(P.begin(),P.end()),P.end());
	vector<pair<pair<int,int>,pair<int,int> > > Ans;
	Ans.clear();
	int ans=solve2(P,Ans);
	printf("%d\n",clock()-start_time);
	printf("%d\n",ans);
  	/*for(auto p:Ans)
  	{
  		int x0=p.first.first,y0=p.first.second;
  		int x1=p.second.first,y1=p.second.second;
  		printf("%d %d %d %d\n",bx[x0],by[y0],bx[x1],by[y1]);
  	}*/
}
