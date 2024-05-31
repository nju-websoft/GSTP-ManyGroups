#include<bits/stdc++.h>
using namespace std;
struct Dat
{
	int g;
	double t_prunedDP,t_i,t_p;
	double r_prunedDP,r_i,r_p;
};
int n;
Dat ans[1005];
double t_prunedDP[20],t_i[20],t_p[20];
double r_i[20],r_p[20],num_i[20],num_p[20],num[20];
void read_i()
{
	freopen("ImprovAPP_result.txt","r",stdin);
	int cnt=1;
	while(~scanf("%d%lf%lf",&ans[cnt].g,&ans[cnt].t_i,&ans[cnt].r_i))
	{
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
void read_p()
{
	freopen("PartialOPT_result.txt","r",stdin);
	int cnt=0;
	for(int i=1;i<=n;++i)
	{
		scanf("%d%lf%lf",&ans[i].g,&ans[i].t_p,&ans[i].r_p);
	}
	fclose(stdin);
}
int main()
{
	read_i();
	read_prunedDP(); 
	read_p();
	for(int i=1;i<=n;++i)if(ans[i].r_prunedDP>0)
	{
		int g=ans[i].g;
		if(ans[i].r_i>0&&ans[i].t_i<200+0.001)
		{
			num_i[g]+=1.0;
			r_i[g]+=ans[i].r_i/ans[i].r_prunedDP;
		}
		if(ans[i].r_p>0&&ans[i].t_p<200+0.001)
		{
			num_p[g]+=1.0;
			r_p[g]+=ans[i].r_p/ans[i].r_prunedDP;
		}
	}
	for(int i=1;i<=n;++i)
	{
		int g=ans[i].g;
		num[g]+=1.0;
		t_prunedDP[g]+=ans[i].t_prunedDP;
		t_i[g]+=min(ans[i].t_i,200.0);
		t_p[g]+=min(ans[i].t_p,200.0);
	}
	freopen("count_2.txt","w",stdout);
	for(int g=2;g<=10;++g)
	{
		cout<<g<<" "<<t_i[g]/num[g]<<" "<<t_p[g]/num[g]<<" "<<r_i[g]/num_i[g]<<" "<<r_p[g]/num_p[g]<<endl; 
	}
	for(int i=1;i<=n;++i)if(ans[i].r_prunedDP>0)
	{
		int g=0;
		if(ans[i].r_i>0&&ans[i].t_i<200+0.001)
		{
			num_i[g]+=1.0;
			r_i[g]+=ans[i].r_i/ans[i].r_prunedDP;
			if(ans[i].r_i<ans[i].r_prunedDP-0.001)cerr<<"!!!! "<<i<<" "<<ans[i].r_p<<" "<<ans[i].r_prunedDP<<endl;
		}
		if(ans[i].r_p>0&&ans[i].t_p<200+0.001)
		{
			num_p[g]+=1.0;
			r_p[g]+=ans[i].r_p/ans[i].r_prunedDP;
			if(ans[i].r_p<ans[i].r_prunedDP-0.001)cerr<<"!!!! "<<i<<" "<<ans[i].r_p<<" "<<ans[i].r_prunedDP<<endl; 
		}
	}
	for(int i=1;i<=n;++i)
	{
		int g=0;
		num[g]+=1.0;
		t_prunedDP[g]+=ans[i].t_prunedDP;
		t_i[g]+=min(ans[i].t_i,200.0);
		t_p[g]+=min(ans[i].t_p,200.0);
	}
	for(int g=0;g<=0;++g)
	{
		cout<<g<<" "<<t_i[g]/num[g]<<" "<<t_p[g]/num[g]<<" "<<r_i[g]/num_i[g]<<" "<<r_p[g]/num_p[g]<<endl; 
	}
	fclose(stdout);
}
