#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[500005],b[500005],posa[500005],posb[500005],l,r,m,k,lans=-1;
int ans=1e18;
void setIO(string name = ""){
	ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()){
		freopen((name + ".inP").c_str(), "r", stdin); 
		//freopen((name + ".out").c_str(), "w", stdout);
	}
}
int Check(int x){
    int tmp=0;
    for(int i=1;i<=n;i++){
        int to=(posa[i]+x)%n+1;
        if(posb[to]!=-1&&posb[to]>i)tmp=max(tmp,posb[to]-i);
    }
    return tmp;
}
int main(){
	//setIO("Wrestling");
    cin>>n;
    for(int i=1; i<=n;i++){
        cin>>a[i];
        posa[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
        posb[b[i]]=i;
    }
    for(int i=1;i<=n;i++){
        if(lans==i-1)break;
        l=i-1;
        r=n-1;
        while(l<=r){
            m=(l+r)/2;
            k=Check(m);
            if(k>lans)l=k+1,lans=k,ans=min(ans,m*n+k);
            else r=m-1;
        }
    }
    cout<<lans<<" "<<ans-n*lans<<endl;
    return 0;
}

