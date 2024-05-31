#include<bits/stdc++.h>
using namespace std;
struct Answer
{
	int n,g; 
	double at1,at2,at3,ar2,ar3,ati,ari,atp,arp;
};
vector<Answer> ans;
double T1[10005],T2[10005],T3[10005],R2DR1[10005],R3DR1[10005],TI[10005],RIDR1[10005],TP[10005],RPDR1[10005];
int main()
{
	for(int n=200;n<=2000;n+=200)
	{
		int g=200;
		double ave_t1=0,ave_t2=0,ave_t3=0,ave_ti=0,ave_tp=0,ave_r2dr1=0,ave_r3dr1=0,ave_ridr1=0,ave_rpdr1=0;
		for(int T=1;T<=20;++T)
		{ 
			freopen("tmp.txt","w",stdout);
			printf("%d %d\n",n,g);
			fclose(stdout);
			system("./gen <tmp.txt >point.txt");
			system("./KeyKG <point.txt >KeyKG_result.txt");
      		system("./GSTGrow <point.txt >Grow_result.txt");
      		system("./GSTMerge <point.txt >Merge_result.txt"); 
      		system("./ImprovAPP <point.txt >ImprovAPP_result.txt");
      		system("./PartialOPT <point.txt >PartialOPT_result.txt");
      		double t1,r1,t2,r2,t3,r3,ti,ri,tp,rp;
			freopen("Grow_result.txt","r",stdin);
			scanf("%lf%lf",&t1,&r1);
			fclose(stdin);
			freopen("KeyKG_result.txt","r",stdin);
			scanf("%lf%lf",&t2,&r2);
			fclose(stdin);
			freopen("Merge_result.txt","r",stdin);
			scanf("%lf%lf",&t3,&r3);
			fclose(stdin);
			freopen("ImprovAPP_result.txt","r",stdin);
			scanf("%lf%lf",&ti,&ri);
			fclose(stdin);
			freopen("PartialOPT_result.txt","r",stdin);
			scanf("%lf%lf",&tp,&rp);
			fclose(stdin);
			cerr<<n<<" "<<g<<" "<<t1<<" "<<t2<<" "<<t3<<" "<<ti<<" "<<tp<<" "<<r2/r1<<" "<<r3/r1<<" "<<ri/r1<<" "<<rp/r1<<endl;
			T1[T]=t1;T2[T]=t2;T3[T]=t3;R2DR1[T]=r2/r1;R3DR1[T]=r3/r1;
			TI[T]=ti;RIDR1[T]=ri/r1;TP[T]=tp;RPDR1[T]=rp/r1;
			ave_t1+=t1;ave_t2+=t2;ave_t3+=t3;ave_r2dr1+=r2/r1;ave_r3dr1+=r3/r1;
			ave_ti+=ti;ave_tp+=tp;ave_ridr1+=ri/r1;ave_rpdr1+=rp/r1;
		}
		ave_t1/=20.0;ave_t2/=20.0;ave_t3/=20.0;ave_r2dr1/=20.0;ave_r3dr1/=20.0;
		ave_ti/=20.0;ave_tp/=20.0;ave_ridr1/=20.0;ave_rpdr1/=20.0;
		Answer x;
		x.n=n;x.g=g;
		x.at1=ave_t1;x.at2=ave_t2;x.at3=ave_t3;x.ar2=ave_r2dr1;x.ar3=ave_r3dr1;
		x.ati=ave_ti;x.atp=ave_tp;x.ari=ave_ridr1;x.arp=ave_rpdr1;
		ans.push_back(x); 
	}
	for(int g=50;g<=500;g+=50)
	{
		int n=2000;
		double ave_t1=0,ave_t2=0,ave_t3=0,ave_ti=0,ave_tp=0,ave_r2dr1=0,ave_r3dr1=0,ave_ridr1=0,ave_rpdr1=0;
		for(int T=1;T<=20;++T)
		{ 
			freopen("tmp.txt","w",stdout);
			printf("%d %d\n",n,g);
			fclose(stdout);
			system("./gen <tmp.txt >point.txt");
			system("./KeyKG <point.txt >KeyKG_result.txt");
      		system("./GSTGrow <point.txt >Grow_result.txt");
      		system("./GSTMerge <point.txt >Merge_result.txt"); 
      		system("./ImprovAPP <point.txt >ImprovAPP_result.txt");
      		system("./PartialOPT <point.txt >PartialOPT_result.txt");
      		double t1,r1,t2,r2,t3,r3,ti,ri,tp,rp;
			freopen("Grow_result.txt","r",stdin);
			scanf("%lf%lf",&t1,&r1);
			fclose(stdin);
			freopen("KeyKG_result.txt","r",stdin);
			scanf("%lf%lf",&t2,&r2);
			fclose(stdin);
			freopen("Merge_result.txt","r",stdin);
			scanf("%lf%lf",&t3,&r3);
			fclose(stdin);
			freopen("ImprovAPP_result.txt","r",stdin);
			scanf("%lf%lf",&ti,&ri);
			fclose(stdin);
			freopen("PartialOPT_result.txt","r",stdin);
			scanf("%lf%lf",&tp,&rp);
			fclose(stdin);
			cerr<<n<<" "<<g<<" "<<t1<<" "<<t2<<" "<<t3<<" "<<ti<<" "<<tp<<" "<<r2/r1<<" "<<r3/r1<<" "<<ri/r1<<" "<<rp/r1<<endl;
			T1[T]=t1;T2[T]=t2;T3[T]=t3;R2DR1[T]=r2/r1;R3DR1[T]=r3/r1;
			TI[T]=ti;RIDR1[T]=ri/r1;TP[T]=tp;RPDR1[T]=rp/r1;
			ave_t1+=t1;ave_t2+=t2;ave_t3+=t3;ave_r2dr1+=r2/r1;ave_r3dr1+=r3/r1;
			ave_ti+=ti;ave_tp+=tp;ave_ridr1+=ri/r1;ave_rpdr1+=rp/r1;
		}
		ave_t1/=20.0;ave_t2/=20.0;ave_t3/=20.0;ave_r2dr1/=20.0;ave_r3dr1/=20.0;
		ave_ti/=20.0;ave_tp/=20.0;ave_ridr1/=20.0;ave_rpdr1/=20.0;
		Answer x;
		x.n=n;x.g=g;
		x.at1=ave_t1;x.at2=ave_t2;x.at3=ave_t3;x.ar2=ave_r2dr1;x.ar3=ave_r3dr1;
		x.ati=ave_ti;x.atp=ave_tp;x.ari=ave_ridr1;x.arp=ave_rpdr1;
		ans.push_back(x); 
	}
	freopen("table.txt","w",stdout);
	for(auto x:ans)
	{
		printf("%d %d %.5f %.5f %.5f %.5f %.5f %.5f %.5f %.5f %.5f\n",x.n,x.g,x.at1,x.at2,x.at3,x.ati,x.atp,x.ar2,x.ar3,x.ari,x.arp);
	}
  fclose(stdout);
}
