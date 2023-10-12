#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define maxn 10000005
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
}
struct Group
{
	int sz;
	vector<int> a;
}grp[maxn];
bool operator < (Group A,Group B){return A.sz<B.sz;}
void read_group()
{
	freopen("invertedTable.txt","r",stdin);
	g=0;
	string buf;
	map<string,int> kwmp;
	while(getline(cin,buf))
	{
		int len=buf.length();
		string name;
		name.clear();
		int u=0,i=0;
		for(;i<len;++i)
		{
			if(buf[i]==':')
			{
				i++;break;
			}
			name.push_back(buf[i]);
		}
		for(;i<len;++i)
		{
			if('0'<=buf[i]&&buf[i]<='9')u=u*10+buf[i]-'0';
			else break;
		}
		u++;
		if(!kwmp.count(name))
		{
			kwmp[name]=++g;
			grp[g].sz=0;
			grp[g].a.clear();
		}
		int id=kwmp[name];
		grp[id].sz++;
		grp[id].a.push_back(u);
		//cout<<"name id u = "<<name<<" "<<id<<" "<<u<<endl;
	}
	fclose(stdin); 
}


vector<int> work1()
{
	sort(grp+1,grp+g+1);
	double ans=inf;
	vector<int> Ans;
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
			for(int y:grp[i].a)
			{
				double t=getD(x,y);
				if(t<mn)
				{
					mn=t;
					mnid=y;
				}
			}
			tmp.push_back(mnid);
			tot+=mn;
		}
		if(tot<ans)
		{
			ans=tot;
			Ans.clear();
			for(int x:tmp)Ans.push_back(x);
		}
	}
	return Ans;
}

int inT[maxn];
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

double work2(int rt,vector<int> P,vector<pair<pair<int,int>,double> > &Ans)
{
	for(int i=1;i<=n;++i)u_table[i]=-1,dis_table[i]=inf,inT[i]=0;
	add_table(rt);
	inT[rt]=1;
	double res=0;
	for(int x:P)if(x!=rt)
	{
		double td;
		pair<int,int> p=getSettoSet(x,td);
		int s=p.first,t=p.second;
		vector< pair<pair<int,int>,double> > SP;
		getSP(s,t,SP);
		for(auto e:SP)
		{
			int a=e.first.first,b=e.first.second;
			if(!inT[a])inT[a]=1;
			else break;
			Ans.push_back(e);
			res+=e.second;
		}
     add_table(x);
	}
	return res;
}



int main()
{
	read_hublabel();
	read_group();
	cerr<<"READ OK"<<endl;
	int start_time=clock();
	vector<int> P=work1();
	freopen("Grow_result.txt","w",stdout);
	printf("%d %d\n",n,g);
	if(!P.size())
	{
		puts("-1");
	}
	else
	{
		int rt=P[0];
		sort(P.begin(),P.end());
		P.erase(unique(P.begin(),P.end()),P.end());
		g=P.size();
		vector< pair< pair<int,int>,double > > Ans;
		double ans=work2(rt,P,Ans);
		printf("time = %d\n",clock()-start_time); 
		printf("%.10f\n",ans);
		for(auto p:Ans)printf("%d %d %.10f\n",p.first.first,p.first.second,p.second);
	}
}
