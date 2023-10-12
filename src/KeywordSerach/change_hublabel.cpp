#include<bits/stdc++.h>
#define maxn 20000005
using namespace std;
int n,m;
struct Hub
{
	int u,h,pred;
	long long preid;
	double dis,prew;
	Hub(int u=0,int h=0,double dis=0,int pred=0,double prew=0):u(u),h(h),dis(dis),pred(pred),prew(prew){preid=0;}
};
vector<Hub> H;
long long cnt;
vector<long long> L[maxn];
void read_hublabel()
{
	H.push_back(Hub(0,0,0,0));
	freopen("WeightPLLlabel.txt","r",stdin);
	scanf("%d%d",&n,&m);
	int u,k,v,pred;
	double dis;
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&u,&k);
		++u;
		while(k--)
		{
			++cnt;
			scanf("%d%lf%d",&v,&dis,&pred);
			++v;++pred;
			H.push_back(Hub(u,v,dis,pred,1.0));
			L[u].push_back(cnt);
			if(cnt%10000000LL==0)cerr<<cnt<<endl;
		}
	}
	cerr<<"read ok"<<endl;
	fclose(stdin); 
}
void getpreid()
{
	for(int i=1;i<=cnt;++i)if(H[i].h!=H[i].u)
	{
		long long preid=-1;
		int pred=H[i].pred;
		for(long long x:L[pred])
		{
			if(H[x].h==H[i].h)
			{
				preid=x;
				break;
			}
		}
		if(preid==-1)assert(0);
		H[i].preid=preid;
	}
}
void print()
{
	freopen("newhublabel.txt","w",stdout);
	for(int i=1;i<=cnt;++i)
	{
		printf("%d %d %lf %d %lld\n",H[i].u,H[i].h,H[i].dis,H[i].pred,H[i].preid);
	}
	fclose(stdout);
}
int main()
{
	read_hublabel();
	getpreid();
	print();
}
