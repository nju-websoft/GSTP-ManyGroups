#include<bits/stdc++.h>
using namespace std;
struct Answer
{
	int n,g; 
	double at1,at2,at3,ar2,ar3;
	double st1,st2,st3,sr2,sr3;
};
double sqr(double x)
{
	return x*x;
}
vector<Answer> ans;
double T1[10005],T2[10005],T3[10005],R2DR1[10005],R3DR1[10005];
int main()
{
	for(int g=50;g<=500;g+=50)
	{
		int n=2000;
		double ave_t1=0,ave_t2=0,ave_t3=0,ave_r2dr1=0,ave_r3dr1=0;
		for(int T=1;T<=30;++T)
		{ 
			freopen("tmp.txt","w",stdout);
			printf("%d %d\n",n,g);
			fclose(stdout);
			system("./gen <tmp.txt >point.txt");
			system("./KeyKG <point.txt >KeyKG_result.txt");
      		system("./GSTGrow <point.txt >Grow_result.txt");
      		system("./GSTMerge <point.txt >Merge_result.txt"); 
      		double t1,r1,t2,r2,t3,r3;
			freopen("KeyKG_result.txt","r",stdin);
			scanf("%lf%lf",&t1,&r1);
			fclose(stdin);
			freopen("Grow_result.txt","r",stdin);
			scanf("%lf%lf",&t2,&r2);
			fclose(stdin);
			freopen("Merge_result.txt","r",stdin);
			scanf("%lf%lf",&t3,&r3);
			fclose(stdin);
			cerr<<n<<" "<<g<<" "<<t1<<" "<<t2<<" "<<t3<<" "<<r2/r1<<" "<<r3/r1<<endl;
			T1[T]=t1;T2[T]=t2;T3[T]=t3;R2DR1[T]=r2/r1;R3DR1[T]=r3/r1;
			ave_t1+=t1;ave_t2+=t2;ave_t3+=t3;ave_r2dr1+=r2/r1;ave_r3dr1+=r3/r1;
		}
		ave_t1/=30.0;ave_t2/=30.0;ave_t3/=30.0;ave_r2dr1/=30.0;ave_r3dr1/=30.0;
		double var_t1=0,var_t2=0,var_t3=0,var_r2dr1=0,var_r3dr1=0;
		for(int i=1;i<=30;++i)
		{
			var_t1+=sqr(T1[i]-ave_t1)/30.0;var_t2+=sqr(T2[i]-ave_t2)/30.0;var_t3+=sqr(T3[i]-ave_t3)/30.0;
			var_r2dr1+=sqr(R2DR1[i]-ave_r2dr1)/30.0;var_r3dr1+=sqr(R3DR1[i]-ave_r3dr1)/30.0; 
		}
		Answer x;
		x.n=n;x.g=g;
		x.at1=ave_t1;x.at2=ave_t2;x.at3=ave_t3;x.ar2=ave_r2dr1;x.ar3=ave_r3dr1;
		x.st1=sqrt(var_t1);x.st2=sqrt(var_t2);x.st3=sqrt(var_t3);x.sr2=sqrt(var_r2dr1);x.sr3=sqrt(var_r3dr1);
		ans.push_back(x); 
	}
	for(int n=200;n<=2000;n+=200)
	{
		int g=200;
		double ave_t1=0,ave_t2=0,ave_t3=0,ave_r2dr1=0,ave_r3dr1=0;
		for(int T=1;T<=30;++T)
		{ 
			freopen("tmp.txt","w",stdout);
			printf("%d %d\n",n,g);
			fclose(stdout);
			system("./gen <tmp.txt >point.txt");
			system("./KeyKG <point.txt >KeyKG_result.txt");
      		system("./GSTGrow <point.txt >Grow_result.txt");
      		system("./GSTMerge <point.txt >Merge_result.txt");
			double t1,r1,t2,r2,t3,r3;
			freopen("KeyKG_result.txt","r",stdin);
			scanf("%lf%lf",&t1,&r1);
			fclose(stdin);
			freopen("Grow_result.txt","r",stdin);
			scanf("%lf%lf",&t2,&r2);
			fclose(stdin);
			freopen("Merge_result.txt","r",stdin);
			scanf("%lf%lf",&t3,&r3);
			fclose(stdin);
			cerr<<n<<" "<<g<<" "<<t1<<" "<<t2<<" "<<t3<<" "<<r2/r1<<" "<<r3/r1<<endl;
			T1[T]=t1;T2[T]=t2;T3[T]=t3;R2DR1[T]=r2/r1;R3DR1[T]=r3/r1;
			ave_t1+=t1;ave_t2+=t2;ave_t3+=t3;ave_r2dr1+=r2/r1;ave_r3dr1+=r3/r1;
		}
		ave_t1/=30.0;ave_t2/=30.0;ave_t3/=30.0;ave_r2dr1/=30.0;ave_r3dr1/=30.0;
		double var_t1=0,var_t2=0,var_t3=0,var_r2dr1=0,var_r3dr1=0;
		for(int i=1;i<=30;++i)
		{
			var_t1+=sqr(T1[i]-ave_t1)/30.0;var_t2+=sqr(T2[i]-ave_t2)/30.0;var_t3+=sqr(T3[i]-ave_t3)/30.0;
			var_r2dr1+=sqr(R2DR1[i]-ave_r2dr1)/30.0;var_r3dr1+=sqr(R3DR1[i]-ave_r3dr1)/30.0; 
		}
		Answer x;
		x.n=n;x.g=g;
		x.at1=ave_t1;x.at2=ave_t2;x.at3=ave_t3;x.ar2=ave_r2dr1;x.ar3=ave_r3dr1;
		x.st1=sqrt(var_t1);x.st2=sqrt(var_t2);x.st3=sqrt(var_t3);x.sr2=sqrt(var_r2dr1);x.sr3=sqrt(var_r3dr1);
		ans.push_back(x); 
	}
	freopen("table.txt","w",stdout);
	for(auto x:ans)
	{
		printf("%d %d %.5f %.5f %.5f %.5f %.5f\n",x.n,x.g,x.at1,x.at2,x.at3,x.ar2,x.ar3);
	}
  fclose(stdout);
}
