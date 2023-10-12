#include<bits/stdc++.h>
using namespace std;
struct Answer
{
	int n,g; 
	double t[15];
	double s[15];
};
double sqr(double x)
{
	return x*x;
}
vector<Answer> ans;
double t[15][10005],s[15][10005];
double ave_t[15],ave_s[15];
int main()
{
	for(int g=100;g<=400;g+=100)
	{
		int n=g*5;
		memset(ave_t,0,sizeof(ave_t));
		memset(ave_s,0,sizeof(ave_s));
		for(int T=1;T<=30;++T)
		{ 
			freopen("tmp.txt","w",stdout);
			printf("%d %d\n",n,g);
			fclose(stdout);
			system("./gen < tmp.txt > point.txt");
			system("./KeyKG < point.txt > kkg_result.txt");
			system("./1_1 < point.txt > res_1_1.txt");
			system("./1_2 < point.txt > res_1_2.txt");
			system("./1_3 < point.txt > res_1_3.txt");
			system("./1_4 < point.txt > res_1_4.txt");
			system("./1_5 < point.txt > res_1_5.txt");
			system("./1_6 < point.txt > res_1_6.txt");
			system("./1_7 < point.txt > res_1_7.txt");
			system("./1_8 < point.txt > res_1_8.txt");
			system("./1_9 < point.txt > res_1_9.txt");
			freopen("kkg_result.txt","r",stdin);
			scanf("%lf%lf",&t[0][T],&s[0][T]);
			fclose(stdin);
			freopen("res_1_1.txt","r",stdin);
			scanf("%lf%lf",&t[1][T],&s[1][T]);
			fclose(stdin);
			freopen("res_1_2.txt","r",stdin);
			scanf("%lf%lf",&t[2][T],&s[2][T]);
			fclose(stdin);
			freopen("res_1_3.txt","r",stdin);
			scanf("%lf%lf",&t[3][T],&s[3][T]);
			fclose(stdin);
			freopen("res_1_4.txt","r",stdin);
			scanf("%lf%lf",&t[4][T],&s[4][T]);
			fclose(stdin);
			freopen("res_1_5.txt","r",stdin);
			scanf("%lf%lf",&t[5][T],&s[5][T]);
			fclose(stdin);
			freopen("res_1_6.txt","r",stdin);
			scanf("%lf%lf",&t[6][T],&s[6][T]);
			fclose(stdin);
			freopen("res_1_7.txt","r",stdin);
			scanf("%lf%lf",&t[7][T],&s[7][T]);
			fclose(stdin);
			freopen("res_1_8.txt","r",stdin);
			scanf("%lf%lf",&t[8][T],&s[8][T]);
			fclose(stdin);
			freopen("res_1_9.txt","r",stdin);
			scanf("%lf%lf",&t[9][T],&s[9][T]);
			fclose(stdin);
			for(int i=0;i<=9;++i)ave_t[i]+=t[i][T]/30.0;
			for(int i=1;i<=9;++i)s[i][T]/=s[0][T],ave_s[i]+=s[i][T]/30.0;
			cerr<<n<<" "<<g<<endl;
		}
		Answer x;
		x.n=n;x.g=g;
		for(int i=1;i<=9;++i)x.t[i]=ave_t[i],x.s[i]=ave_s[i];
		ans.push_back(x);
	}
	freopen("table_tau.txt","w",stdout);
	for(auto x:ans)
	{
		printf("%d %d ::\n",x.n,x.g);
		for(int i=1;i<=9;++i)printf("%.4f ",x.t[i]);
		printf("\n");
		for(int i=1;i<=9;++i)printf("%.4f ",x.s[i]);
		printf("\n");
	}
	fclose(stdout);
}
