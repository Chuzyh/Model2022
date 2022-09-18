#pragma GCC optimize(3)
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#include "geometry.h"
using namespace std;

point s[N];
const int n=9;
const int T=1000000;
int id[N];

int tot,tot_wrongc;
pair<double,double> solve2(int num,double ang1,double ang2,double ang3,int trueC)
{
    double per_para=20.0/360*2*pi;
    int para=round(ang1/per_para);
    if(para==0)para++;
    int c1=para+1,c2=10-para;

    double t1=(double)abs(num-c1)*40/360*2*pi;
    if(t1>pi)t1=2*pi-t1;
    double t2=(double)abs(num-c2)*40/360*2*pi;
    if(t2>pi)t2=2*pi-t2;
    
    t1=(pi-t1)/2;t2=(pi-t2)/2;
    int C=(fabs(t1-ang3)<fabs(t2-ang3))?c1:c2;
    tot_wrongc+=C!=trueC;
    int B=1;
    if(cross(s[B],s[C])<0)swap(B,C),swap(ang2,ang3);
    return get_rt(B,C,num,ang2,ang3);
}
double mx=0;
int main()
{
    srand(233);
    freopen("task2_simple_data","w",stdout);
    for(int i=1;i<=n;i++)
        s[i]=get_xy(radius,(double)(i-1)/n*2*pi),id[i]=i;
    for(double range=10;range<=40.05;range+=0.1)
    {
        mx=0,tot=0;tot_wrongc=0;
        for(int i=1;i<=T;i++)
        {
            random_shuffle(id+2,id+10);
            int b=1,c=id[2],d=id[3];
            point fakeD=add_ran(s[d],range);

            double ang1=angle(fakeD,s[c],s[b]);
            double ang2=angle(fakeD,s[0],s[b]);
            double ang3=angle(fakeD,s[0],s[c]);
            
            pair<double,double> ans=solve2(d,ang1,ang2,ang3,c);
            //fakeD.out();
            point ansXY=get_xy(ans.first,ans.second);
            //ansXY.out();
            //cout<<len(fakeD-ansXY)<<endl;
            tot+=len(fakeD-ansXY)>eps;
            mx=max(mx,len(fakeD-ansXY));
        }
        cerr<<range<<endl;
        cout<<range<<' '<<mx<<' '<<(double)tot/T<<' '<<(double)tot_wrongc/T<<endl;
    }
    
    return 0;
}