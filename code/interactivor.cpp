#include<bits/stdc++.h>
using namespace std;
#include "geometry.h"

point p[N],s[N],la[N];
double th[N],ri[N];
const double sample[][2]={{0,0},{100,0},{98,40.10},{112,80.21},{105,119.75},{98,159.86},{112,199.96},{105,240.07},{98,280.17},{112,320.28}};
double ang[N];
void move(int p,point del)
{
    point now=del-la[p];
    la[p]=del;
    printf("move %d %lf %lf\n",p,now.x,now.y);
}
int main()
{
    int n=9;double radius=100;
    for(int i=1;i<=n;i++)
    {
        s[i]=get_xy(radius,(double)(i-1)/n*2*pi);
        p[i]=get_xy(sample[i][0],sample[i][1]/360*2*pi);
        la[i]=(point){0,0};
    }
        
    ask(0,1);
    ask(0,2,3,4);
    ask(0,5,6,7);
    ask(0,8,9);
    double L[N],R[N];
    for(int i=2;i<=9;i++)
    {
        L[i]=(double)40*(i-1)/360*2*pi,R[i]=L[i];
        L[i]-=2.0*pi*20/360,R[i]+=2.0*pi*20/360;
        ang[i]=pi-angle(p[1],p[0],p[i])-angle(p[i],p[0],p[1]);
    }
    for(int T=1;T<=20;T++)
    {
        for(int i=2;i<=9;i++)
        if(R[i]-L[i]>eps)
        {
            double mid=(L[i]+R[i])/2;
            point delta=(point){2*cos(mid),2*sin(mid)};delta=delta*0.5*(1);
            move(i,delta);
            delta=delta+p[i];
            double tmp_ang=pi-angle(p[1],p[0],delta)-angle(delta,p[0],p[1]);
            if(i<=5)if(tmp_ang>ang[i])R[i]=mid;else L[i]=mid;
            else if(tmp_ang<ang[i])R[i]=mid;else L[i]=mid;
        }
        ask(0,1);
        ask(0,2,3,4);
        ask(0,5,6,7);
        ask(0,8,9);
    }
    L[1]=R[1]=(L[2]+R[2])/2-ang[2];

    double sum_err=0;
    for(int i=1;i<=9;i++)
    {
        th[i]=(L[i]+R[i])/2;
        int ne=i+1;if(ne==10)ne=1;
        double db=i!=1,da=ne!=1;
        double alpha1=angle(p[i],p[0],p[ne]),alpha2=angle(p[i]+la[i],p[0],p[ne]+la[ne]);
        double beta1=angle(p[ne],p[0],p[i]),beta2=angle(p[ne]+la[ne],p[0],p[i]+la[i]);
        double b=(sin(alpha2)/sin(beta2)*db-da)/(sin(alpha1)/sin(beta1)-sin(alpha2)/sin(beta2));
        ri[i]=b;
    }
    for(int i=1;i<=9;i++)move(i,get_xy(ri[i],th[i])-s[i]);
    for(int i=1;i<=9;i++)s[i].out(),(p[i]-la[i]).out();

    return 0;
}

/*
103.407 -0.585212
104.088 40.2568
97.8435 77.3175
103.147 120.048
102.273 160.142
99.78 -160.74
100.568 -120.705
96.825 -76.9355
99.6751 -38.5416
40.10009766 0.00009766 12
80.21240234 0.00240234 12
119.74853516 -0.00146484 12
159.86083984 0.00083984 12
199.95849609 -0.00150391 12
240.07080078 0.00080078 12
280.16845703 -0.00154297 12
320.28076172 0.00076172 12
*/