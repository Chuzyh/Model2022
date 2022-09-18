#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include "geometry.h"
using namespace std;
point p[N];
int id[N];

int sum[5];
const int T=10000000;
int main()
{
    srand(time(0));
    for(int i=1;i<=9;i++)p[i]=get_xy(radius,40.0*(i-1)/360*2*pi),id[i]=i;
    // freopen("data3","w",stdout);
    double mx=0;
    for(int i=1;i<=T;i++)
    {
        random_shuffle(id+1,id+1+9);
        int b=id[1],c=id[2],d=id[3],a=0;
        if(cross(p[b],p[c])<0)swap(b,c);
        point fakeD=add_ran(p[d]);
        double a1=angle(fakeD,p[b],p[a]);
        double a2=angle(fakeD,p[c],p[a]);

        //p[d].out();
        //fakeD.out();
        //cout<<b<<' '<<c<<' '<<d<<endl;
        //cout<<len(fakeD)<<' '<<atan2(fakeD.y,fakeD.x)+pi*2*(atan2(fakeD.y,fakeD.x)<0?1:0)<<endl;
        pair<double,double> ans=get_rt(b,c,d,a1,a2);
        //cout<<ans.first<<' '<<ans.second<<endl;
        point q=(point){ans.first*cos(ans.second),ans.first*sin(ans.second)};
        double err=len(q-fakeD);
        mx=max(err,mx);
        if(err>eps)
        {
            cout<<b<<' '<<c<<' '<<d<<' ';
            int t=abs(b-c);
            if(t>4)t=9-t;
            cout<<t<<endl;sum[t]++;
            fakeD.out();
        }
    }
    printf("%d %d %d %d\n",sum[1],sum[2],sum[3],sum[4]);
    cout<<mx<<endl;
    return 0;
}