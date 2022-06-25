#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define test ll t; cin>> t; for(ll u=1; u<=t; u++)

/*
#define mp make_pair
#define x first
#define y second
//#define z second
#define P pair< ll , ll>
*/

ll ans[100009];

bool all[10]={false};


int main(){
    string s; cin>> s;
    ll n=s.size();
    for(ll i=0; i<n; i++) ans[i]=-1;
    ans[0]=0;
    queue<ll> q;
    q.push(0);
    while(!q.empty()){
        ll k=q.front();
        //cout<< k<< endl;
        q.pop();
        if(all[(s[k]-'0')]==false){
            for(ll i=0; i<n; i++){
                all[(s[k]-'0')]==true;
                if(i!=k && s[i]==s[k] && ans[i]==-1){
                    ans[i]=ans[k]+1;
                    q.push(i);
                }
            }
        }
        if(k>1 && ans[k-1]==-1){
            ans[k-1]=ans[k]+1;
            q.push(k-1);
        }
        if(k<n-1 && ans[k+1]==-1){
            ans[k+1]=ans[k]+1;
            q.push(k+1);
        }
    }
    for(ll i=0; i<n; i++){
 //       cout<< ans[i]<< " ";
    }
//cout<< endl;
    cout<< ans[n-1]<< endl;
}



