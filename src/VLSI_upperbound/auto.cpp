#include<bits/stdc++.h>
using namespace std;
struct Answer
{
	int n,g; 
	double ar2,ar3;
};
vector<Answer> ans;
double R2DR1[10005],R3DR1[10005];
int main()
{
	for(int n=200;n<=2000;n+=200)
	{
		int g=200;
		double ave_r2dr1=0,ave_r3dr1=0;
		for(int T=1;T<=20;++T)
		{ 
			freopen("tmp.txt","w",stdout);
			printf("%d %d\n",n,g);
			fclose(stdout);
			system("./gen <tmp.txt >point.txt");
			system("./UpperBound < point.txt >UpperBound_result.txt");
      		system("./GSTGrow <point.txt >Grow_result.txt");
      		system("./GSTMerge <point.txt >Merge_result.txt");
      		double t1,r1,t2,r2,t3,r3,ti,ri,tp,rp;
			freopen("UpperBound_result.txt","r",stdin);
			scanf("%lf%lf",&t1,&r1);
			fclose(stdin);
			freopen("Grow_result.txt","r",stdin);
			scanf("%lf%lf",&t2,&r2);
			fclose(stdin);
			freopen("Merge_result.txt","r",stdin);
			scanf("%lf%lf",&t3,&r3);
			fclose(stdin);
			cerr<<n<<" "<<g<<" "<<r2/r1<<" "<<r3/r1<<endl;
			R2DR1[T]=r2/r1;R3DR1[T]=r3/r1;
			ave_r2dr1+=r2/r1;ave_r3dr1+=r3/r1;
		}
		ave_r2dr1/=20.0;ave_r3dr1/=20.0;
		Answer x;
		x.n=n;x.g=g;
		x.ar2=ave_r2dr1;x.ar3=ave_r3dr1;
		ans.push_back(x); 
	}
	for(int g=50;g<=500;g+=50)
	{
		int n=2000;
		double ave_r2dr1=0,ave_r3dr1=0;
		for(int T=1;T<=20;++T)
		{ 
			freopen("tmp.txt","w",stdout);
			printf("%d %d\n",n,g);
			fclose(stdout);
			system("./gen <tmp.txt >point.txt");
			system("./UpperBound < point.txt >UpperBound_result.txt");
      		system("./GSTGrow <point.txt >Grow_result.txt");
      		system("./GSTMerge <point.txt >Merge_result.txt");
      		double t1,r1,t2,r2,t3,r3,ti,ri,tp,rp;
			freopen("UpperBound_result.txt","r",stdin);
			scanf("%lf%lf",&t1,&r1);
			fclose(stdin);
			freopen("Grow_result.txt","r",stdin);
			scanf("%lf%lf",&t2,&r2);
			fclose(stdin);
			freopen("Merge_result.txt","r",stdin);
			scanf("%lf%lf",&t3,&r3);
			fclose(stdin);
			cerr<<n<<" "<<g<<" "<<r2/r1<<" "<<r3/r1<<endl;
			R2DR1[T]=r2/r1;R3DR1[T]=r3/r1;
			ave_r2dr1+=r2/r1;ave_r3dr1+=r3/r1;
		}
		ave_r2dr1/=20.0;ave_r3dr1/=20.0;
		Answer x;
		x.n=n;x.g=g;
		x.ar2=ave_r2dr1;x.ar3=ave_r3dr1;
		ans.push_back(x); 
	}
	freopen("table.txt","w",stdout);
	for(auto x:ans)
	{
		printf("%d %d %.5f %.5f\n",x.n,x.g,x.ar2,x.ar3);
	}
  	fclose(stdout); 
}
