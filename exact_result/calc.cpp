#include<bits/stdc++.h>
using namespace std;
struct Dat
{
	int g;
	double t_prunedDP,t_kkg,t_grow,t_merge;
	double r_prunedDP,r_kkg,r_grow,r_merge;
};
int n;
Dat ans[1005];
double t_prunedDP[20],t_kkg[20],t_grow[20],t_merge[20];
double r_kkg[20],r_grow[20],r_merge[20],num[20];
void read_kkg()
{
	freopen("KeyKG_result.txt","r",stdin);
	int cnt=1;
	while(~scanf("%d%lf%lf",&ans[cnt].g,&ans[cnt].t_kkg,&ans[cnt].r_kkg))
	{
		ans[cnt].t_kkg/=1000000.0;
		++cnt;
	}
	fclose(stdin);
	n=cnt-1;
	cerr<<n<<endl;
}
void read_prunedDP()
{
	string s;
	freopen("exact_result.txt","r",stdin);
	int cnt=0;
	for(int i=1;i<=n;++i)
	{
		++cnt;
		cin>>s;
		cin>>s;
		cin>>ans[cnt].t_prunedDP;
		ans[cnt].t_prunedDP/=1000.0;
		cin>>s;
		cin>>s;
		cin>>ans[cnt].r_prunedDP;
		cin>>s;
		cin>>s;
		//cerr<<ans[cnt].t_prunedDP<<" "<<ans[cnt].r_prunedDP<<endl;
	}
	fclose(stdin);
}
void read_grow()
{
	freopen("Grow_result.txt","r",stdin);
	int cnt=0;
	for(int i=1;i<=n;++i)
	{
		scanf("%d%lf%lf",&ans[i].g,&ans[i].t_grow,&ans[i].r_grow);
		ans[i].t_grow/=1000000.0; 
	}
	fclose(stdin);
}
void read_merge()
{
	freopen("Merge_result.txt","r",stdin);
	int cnt=0;
	for(int i=1;i<=n;++i)
	{
		scanf("%d%lf%lf",&ans[i].g,&ans[i].t_merge,&ans[i].r_merge);
		ans[i].t_merge/=1000000.0; 
	}
	fclose(stdin);
}
int main()
{
	read_kkg();
	read_prunedDP(); 
	read_grow();
	read_merge();
	for(int i=1;i<=n;++i)if(ans[i].r_prunedDP>0)
	{
		int g=ans[i].g;
		num[g]+=1.0;
		t_prunedDP[g]+=ans[i].t_prunedDP;
		t_kkg[g]+=ans[i].t_kkg;
		t_grow[g]+=ans[i].t_grow;
		t_merge[g]+=ans[i].t_merge;
		r_kkg[g]+=ans[i].r_kkg/ans[i].r_prunedDP;
		r_grow[g]+=ans[i].r_grow/ans[i].r_prunedDP;
		r_merge[g]+=ans[i].r_merge/ans[i].r_prunedDP;
		//cerr<<ans[i].r_prunedDP<<endl;
	}
	freopen("count.txt","w",stdout);
	for(int g=2;g<=16;++g)
	{
		cout<<g<<" "<<t_prunedDP[g]/num[g]<<" "<<t_kkg[g]/num[g]<<" "<<t_grow[g]/num[g]<<" "<<t_merge[g]/num[g]<<" "<<r_kkg[g]/num[g]<<" "<<r_grow[g]/num[g]<<" "<<r_merge[g]/num[g]<<endl; 
	}
	for(int i=1;i<=n;++i)if(ans[i].r_prunedDP>0)
	{
		int g=0;
		num[g]+=1.0;
		t_prunedDP[g]+=ans[i].t_prunedDP;
		t_kkg[g]+=ans[i].t_kkg;
		t_grow[g]+=ans[i].t_grow;
		t_merge[g]+=ans[i].t_merge;
		r_kkg[g]+=ans[i].r_kkg/ans[i].r_prunedDP;
		r_grow[g]+=ans[i].r_grow/ans[i].r_prunedDP;
		r_merge[g]+=ans[i].r_merge/ans[i].r_prunedDP;
		//cerr<<ans[i].r_prunedDP<<endl; 
	}
	for(int g=0;g<=0;++g)
	{
		cout<<g<<" "<<t_prunedDP[g]/num[g]<<" "<<t_kkg[g]/num[g]<<" "<<t_grow[g]/num[g]<<" "<<t_merge[g]/num[g]<<" "<<r_kkg[g]/num[g]<<" "<<r_grow[g]/num[g]<<" "<<r_merge[g]/num[g]<<endl; 
	}
	fclose(stdout);
}
