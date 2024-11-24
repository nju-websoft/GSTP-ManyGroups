#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
int n,g; 
int get(int x)
{
	return rand()%x+1;
}
pair<int,int> a[maxn];
vector<int> grp[maxn];
int main()
{
	scanf("%d%d",&n,&g);
	srand(time(NULL));
	for(int i=1;i<=n;++i)
	{
		int x=get(100000),y=get(100000);
		a[i]=make_pair(x,y);
	}
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-a-1;
	printf("%d %d\n",n,g);
  //cerr<<n<<" "<<g<<endl;
	for(int i=1;i<=n;++i)
	{
		printf("%d %d\n",a[i].first,a[i].second);
	}
	for(int i=1;i<=n;++i)
	{
		if(i>g)grp[get(g)].push_back(i);
		else grp[i].push_back(i);
	}
	for(int i=1;i<=g;++i)
	{
		int sz=grp[i].size();
		printf("%d ",sz);
		for(int x:grp[i])printf("%d ",x);
		printf("\n");
	}
}
