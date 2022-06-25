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

vector<ll> v[20009];
bool vis[20009]={false};

ll ans[20009];
bool who[20009]={false};

void dfs(ll n){
    vis[n]=true;
    ll u=0;
    for(ll i=0; i<v[n].size(); i++){
        if(!vis[v[n][i]] && who[n]==0){
            dfs(v[n][i]);
            u++;
        }
    }
    if(who[n]!=0) ans[n]=1;
    else{
        (u==0)? ans[n]=1 : ans[n]=2;
    }
    return;
}



int main(){
    for(ll i=0; i<19683; i++){ // detecting if a state has winning combo or not
        ans[i]=3;


        ll a[3][3];
        ll n=i;
        for(ll j=0; j<9; j++){
            ll k=n%3;
            n/=3;
            a[j/3][j%3]=k;
        }
        ll r[3][3]={0},c[3][3]={0},d1=0,d2=0;
        for(ll j=0; j<3; j++){
            for(ll k=0; k<3; k++){
                r[j][a[j][k]]++;
                c[k][a[j][k]]++;
            }

        }

        if(a[0][0]==a[1][1] && a[2][2]==a[0][0] && a[2][2]>0) d1=1;
        if(a[0][2]==a[1][1] && a[2][0]==a[0][2] && a[2][0]>0) d2=1;


        ll u=0;
        if(d1!=0) u++;
        if(d2!=0) u++;
        for(ll j=0; j<3; j++){
            for(ll k=1; k<3; k++){
                if(r[j][k]==3) u++;
                if(c[j][k]==3) u++;
            }
        }

        if(u!=0) who[i]=true;
    }

    for(ll i=0; i<19683; i++){ //building graph
        ll a[9];
        ll n=i;
        ll o=0, x=0;
        for(ll j=0; j<9; j++){
            ll k=n%3;
            n/=3;
            a[j]=k;
            if(k==1) x++;
            if(k==2) o++;
        }
        ll d=0;
        if(x==o) d=1;
        else d=2;
        for(ll j=0; j<9; j++){
            if(a[j]==0){
                a[j]=d;
                ll s=0;
                for(ll k=8; k>=0; k--){
                    s*=3;
                    s+=a[k];
                }
                if(who[i]==0) v[i].push_back(s);
                a[j]=0;
            }
        }
    }
    dfs(0);
    test{
        string s[3];
        ll a[9];
        for(ll i=0; i<3; i++){
            cin>> s[i];
            for(ll j=0; j<3; j++){
                ll k=i*3+j;
                if(s[i][j]=='_') a[k]=0;
                if(s[i][j]=='X') a[k]=1;
                if(s[i][j]=='O') a[k]=2;
            }
        }
        ll k=0;
        for(ll i=8; i>=0; i--){
            //cout<< a[i];
            k*=3;
            k+=a[i];
        }
        //cout<< endl;
        //cout<< who[k]<< " "<< k<< " ";
        cout<< ans[k]<< endl;
    }
}


