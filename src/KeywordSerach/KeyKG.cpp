#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define maxn 6000005
using namespace std;
int n,g;
struct Hub
{
	int h,pred,preid;
	double dis,prew;
	Hub(int h=0,double dis=0,int pred=0,int preid=0,double prew=0):h(h),dis(dis),pred(pred),preid(preid),prew(prew){}
};
vector<Hub> H;
int hubcnt;
vector<int> L[maxn];
const double inf = 1e12;
double getD(int u,int v)
{
	double ans=inf;
	int i=0,j=0,sz1=L[u].size(),sz2=L[v].size();
	while(i<sz1&&j<sz2)
	{
		int x=L[u][i],y=L[v][j];
		if(H[x].h==H[y].h)
		{
			ans=min(ans,H[x].dis+H[y].dis);
			++i;++j;
		}
		else if(H[x].h<H[y].h)++i;
		else ++j;
	}
	return ans;
}
void getSP(int u,int v,vector< pair<pair<int,int>,double> > &SP)
{
	double ans=inf;
	int i=0,j=0,sz1=L[u].size(),sz2=L[v].size(),hmin=-1,p1=-1,p2=-1;
	while(i<sz1&&j<sz2)
	{
		int x=L[u][i],y=L[v][j];
		if(H[x].h==H[y].h)
		{
			if(H[x].dis+H[y].dis<ans)ans=H[x].dis+H[y].dis,hmin=H[x].h,p1=x,p2=y;
			++i;++j;
		}
		else if(H[x].h<H[y].h)++i;
		else ++j;
	}
	assert(hmin!=-1);
	assert(p1!=-1);
	assert(p2!=-1);
	vector< pair<pair<int,int>,double> > SP1,SP2;
	SP.clear();SP1.clear();SP2.clear();
	int y=u;
	while(y!=hmin)
	{
		int pred=H[p1].pred,preid=H[p1].preid;
		SP1.push_back(make_pair(make_pair(y,pred),H[p1].prew));
		y=pred;p1=preid;
	}
	y=v;
	while(y!=hmin)
	{
		int pred=H[p2].pred,preid=H[p2].preid;
		SP2.push_back(make_pair(make_pair(pred,y),H[p2].prew));
		y=pred;p2=preid;
	}
	for(int i=0;i<SP1.size();++i)SP.push_back(SP1[i]);
	for(int i=(int)SP2.size()-1;i>=0;--i)SP.push_back(SP2[i]);
}

void read_hublabel()
{
	freopen("newhublabel.txt","r",stdin);
	int u,v,pred,preid;
	double dis;
	H.push_back(Hub(0,0,0,0));
	while(~scanf("%d%d%lf%d%d",&u,&v,&dis,&pred,&preid))
	{
		++hubcnt;
		H.push_back(Hub(v,dis,pred,preid,1.0));
		L[u].push_back(hubcnt);
		n=max(n,u);n=max(n,v);
	}
	fclose(stdin);
	for(int i=1;i<=hubcnt;++i)
	{
		int preid=H[i].preid;
		H[i].prew=H[i].dis-H[preid].dis;
	}
}
struct Group
{
	int sz;
	vector<int> a;
}grp[maxn];
bool operator < (Group A,Group B){return A.sz<B.sz;}

int ut[16][maxn];
double dt[16][maxn];


vector<int> work1()
{
	sort(grp+1,grp+g+1);
	double ans=inf;
	vector<int> Ans;
	for(int i=2;i<=g;++i)
	{
		for(int o:grp[i].a)
		{
			for(int x:L[o])
			{
				int h=H[x].h;
				double dis=H[x].dis;
				if((!ut[i][h])||dis<dt[i][h])
				{
					dt[i][h]=dis;
					ut[i][h]=o;
				}
			}
		}
	}
	for(int x:grp[1].a)
	{
		vector<int> tmp;
		tmp.clear();
		double tot=0;
		tmp.push_back(x);
		for(int i=2;i<=g;++i)
		{
			double mn=inf;
			int mnid=-1;
			for(int id:L[x])
			{
				int h=H[id].h;
				double dis=H[id].dis;
				if(ut[i][h]&&dis+dt[i][h]<mn)
				{
					mn=dis+dt[i][h];
					mnid=ut[i][h];
				}
			}
			tmp.push_back(mnid);
			tot+=mn;
		}
		if(tot<ans)
		{
			ans=tot;
			Ans.clear();
			for(int y:tmp)Ans.push_back(y);
		}
	}
	return Ans;
}

int u_table[maxn];
double dis_table[maxn];
void add_table(int o)
{
	for(int x:L[o])
	{
		int h=H[x].h;
		double dis=H[x].dis;
		if(dis<dis_table[h])
		{
			dis_table[h]=dis;
			u_table[h]=o;
		}
	}
}
pair<int,int> getSettoSet(int o,double &ans)
{
	ans=inf;
	int p1=-1,p2=-1;
	for(int x:L[o])
	{
		int h=H[x].h;
		double dis=H[x].dis;
		if(dis+dis_table[h]<ans)
		{
			ans=dis+dis_table[h];
			p1=o,p2=u_table[h];
		}
	}
	return make_pair(p1,p2);
}
bool inT[maxn];
double work2(vector<int> P,vector<pair<pair<int,int>,double> > &Ans)
{
	double ans=inf;
	for(int rt:P)
	{
		//cerr<<rt<<endl;
		double res=0;
		vector< pair<pair<int,int>,double> > Res;
		Res.clear();
		for(int i=1;i<=n;++i)u_table[i]=-1,dis_table[i]=inf,inT[i]=0;
		add_table(rt);
		inT[rt]=1;
		while(1)
		{
			int tot=0;
			double dd=inf;
			int s=-1,t=-1;
			for(int x:P)if(!inT[x])
			{
				++tot;
				double td=0;
				pair<int,int> p=getSettoSet(x,td);
				if(td<dd)
				{
					dd=td;
					s=p.first,t=p.second;
				}
			}
			if(!tot)break;
			vector< pair<pair<int,int>,double> > SP;
			getSP(s,t,SP);
			for(auto e:SP)
			{
				int a=e.first.first,b=e.first.second;
				if(!inT[a])inT[a]=1,add_table(a);
				if(!inT[b])inT[b]=1,add_table(b);
				Res.push_back(e);
				res+=e.second;
			}
		}
		if(res<ans)
		{
			ans=res;
			Ans.clear();
			for(auto x:Res)Ans.push_back(x);
		}
	}
	return ans;
}

int Ansg[maxn];
double Anstime[maxn],Ansres[maxn];

void work()
{
	freopen("newquery.txt","r",stdin);
	int Q;
	scanf("%d",&Q);
	for(int cas=1;cas<=Q;++cas)
	{
		cerr<<cas<<" start"<<endl;
		scanf("%d",&g);
		cerr<<cas<<" g="<<g<<endl;
		for(int i=1;i<=g;++i)
		{
			scanf("%d",&grp[i].sz);
			for(int j=1;j<=grp[i].sz;++j)
			{
				int x;
				scanf("%d",&x);
				grp[i].a.push_back(x); 
			}
		}
		
		Ansg[cas]=g;
		int start_time=clock();
		vector<int> P=work1();
		cerr<<cas<<" work1"<<endl;
		if(!P.size())
		{
			cerr<<cas<<" end -1"<<endl;
			Anstime[cas]=-1;
			Ansres[cas]=-1;
		}
		else
		{
			sort(P.begin(),P.end());
			P.erase(unique(P.begin(),P.end()),P.end());
			g=P.size();
			vector< pair< pair<int,int>,double > > Ans;
			double ans=work2(P,Ans);
			cerr<<cas<<" work2"<<endl;
			cerr<<ans<<endl; 
			Anstime[cas]=clock()-start_time;
			Ansres[cas]=ans;
		}
		
		
		for(int i=1;i<=g;++i)grp[i].a.clear(),grp[i].sz=0;
		memset(u_table,0,sizeof(u_table));
		memset(dis_table,0,sizeof(dis_table));
		memset(inT,0,sizeof(inT));
		memset(ut,0,sizeof(ut));
		memset(dt,0,sizeof(dt)); 
	}
	fclose(stdin);
	
	freopen("KeyKG_result.txt","w",stdout);
	for(int cas=1;cas<=Q;++cas)
	{
		printf("%d %.5f %.5f\n",Ansg[cas],Anstime[cas],Ansres[cas]);
	}
}

int main()
{
	read_hublabel();
	cerr<<"HL READ OK"<<endl;
	work();
}
