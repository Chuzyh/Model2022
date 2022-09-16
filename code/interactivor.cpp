#include<bits/stdc++.h>
using namespace std;

const double pi=acos(-1);
const int N=20;
const double eps=1e-8;
struct point
{
    double x,y;
}p[N],s[N],r[N],la[N];
point operator +(point a,point b){return (point){a.x+b.x,a.y+b.y};}
point operator -(point a,point b){return (point){a.x-b.x,a.y-b.y};}
point operator *(point a,double b){return (point){a.x*b,a.y*b};}
point operator /(point a,double b){return (point){a.x/b,a.y/b};}
double cross(point a,point b){return a.x*b.y-a.y*b.x;}
double dot(point a,point b){return a.x*b.x+a.y*b.y;}
double len(point a){return sqrt(a.x*a.x+a.y*a.y);}
double angle(point a,point b1,point b2)
{
    double A=len(b1-b2),B=len(a-b1),C=len(a-b2);
    return acos((B*B+C*C-A*A)/(2*B*C));
}
point get_xy(double r,double theta)
{
    return (point){r*cos(theta),r*sin(theta)};
}
double rand_double(){return ((double)rand()/RAND_MAX-0.5)*2;}
const double sample[][2]={{0,0},{100,10},{98,40.10},{112,80.21},{105,119.75},{98,159.86},{112,199.96},{105,240.07},{98,280.17},{112,320.28}};
void ask(int p0,int p1,int p2,int p3)
{
    cout<<"ask "<<p0<<' '<<p1<<' '<<p2<<' '<<p3<<endl;
}
void ask(int p0,int p1,int p2)
{
    cout<<"ask "<<p0<<' '<<p1<<' '<<p2<<endl;
}
void ask(int p0,int p1)
{
    cout<<"ask "<<p0<<' '<<p1<<endl;
}
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
        r[i]=s[i];r[i].x+=rand_double()*5.0;r[i].y+=rand_double()*5.0;
        //cout<<s[i].x<<' '<<s[i].y<<' '<<p[i].x<<' '<<p[i].y<<' '<<r[i].x<<' '<<r[i].y<<' ';
        cout<<len(r[i])<<' '<<atan2(r[i].y,r[i].x)/(2*pi)*360<<endl;
        
    }
    
    /*for(int i=2;i<=9;i++)
    {
        int tot=0;
        double L=(double)40*(i-1)/360*2*pi,R=L;
        L-=2.0*pi*10/360,R+=2.0*pi*10/360;
        double ang=pi-angle(p[1],p[0],p[i])-angle(p[i],p[0],p[1]);
        while(R-L>eps)
        {
            double mid=(L+R)/2;tot++;
            point delta=(point){2*cos(mid),2*sin(mid)};delta=delta+p[i];
            double tmp_ang=pi-angle(p[1],p[0],delta)-angle(delta,p[0],p[1]);
            if(i<=5)if(tmp_ang>ang)R=mid;else L=mid;
            else if(tmp_ang<ang)R=mid;else L=mid;
        }
        printf("%.8lf %.8lf %d\n",(L+R)/2/pi*180,(L+R)/2/pi*180-sample[i][1],tot);
    }*/
    ask(0,1);
    ask(0,2,3,4);
    ask(0,5,6,7);
    ask(0,8,9);
    double L[N],R[N];
    for(int i=2;i<=9;i++)
    {
        L[i]=(double)40*(i-1)/360*2*pi,R[i]=L[i];
        L[i]-=2.0*pi*10/360,R[i]+=2.0*pi*10/360;
        ang[i]=pi-angle(p[1],p[0],p[i])-angle(p[i],p[0],p[1]);
    }
    for(int T=1;T<=20;T++)
    {
        for(int i=2;i<=9;i++)
        if(R[i]-L[i]>eps)
        {
            double mid=(L[i]+R[i])/2;
            point delta=(point){2*cos(mid),2*sin(mid)};
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
    for(int i=1;i<=9;i++)printf("%.8lf ",(L[i]+R[i])/2/2/pi*360);
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