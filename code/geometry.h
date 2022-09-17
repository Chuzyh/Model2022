#include<bits/stdc++.h>
using namespace std;

const double pi=acos(-1);
const int N=20;
const double eps=1e-8;
const double INF=1e16;
double radius=100;
struct point
{
    double x,y;
    void out()
    {
        printf("%.8lf %.8lf\n",x,y);
    }
};
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
point add_ran(point now)
{
    double radius=len(now);
    double ang=atan2(now.y,now.x);
    radius+=rand_double()*5*3;
    ang+=rand_double()*0.052*3;
    return get_xy(radius,ang);
}
point add_ran(point now,double radio)
{
    double radius=len(now);
    double ang=atan2(now.y,now.x);
    radius+=rand_double()*5*radio/10;
    ang+=rand_double()*0.052*radio/10;
    return get_xy(radius,ang);
}
point add_ran_on_circle_edge(point now,double radio)
{
    point delta=get_xy(radio,rand_double()*pi);
    return now+delta;
}
double Atan2(double y,double x)
{
    if(y<0)return atan2(-y,-x);
    else return atan2(y,x);
}
pair<double,double> get_rt(int b,int c,int d,double a1,double a2)
{
    double a3=(double)abs(b-c)*40/360*2*pi;
    if(a3>pi)a3=2*pi-a3;
    double t0=a3-a1-a2;
    double t1[5];
     t1[1]=Atan2(sin(t0),sin(a2)/sin(a1)+cos(t0));//-
     t1[2]=Atan2(-sin(a1+a2+a3),sin(a2)/sin(a1)+cos(a1+a2+a3));//+

    t0=a2-a1-a3;
     t1[3]=Atan2(sin(t0),cos(t0)-sin(a2)/sin(a1));//+
    t0=a1-a2-a3;
     t1[4]=Atan2(sin(t0),sin(a2)/sin(a1)-cos(t0));//-
    
    point ans[5];
    for(int i=1;i<=4;i++)
    {
        double ra=radius*(sin(t1[i])/sin(a1)),td=40.0*(b-1)/360*2*pi+(pi-t1[i]-a1)*((i==1||i==4)?(-1):1);
        ans[i]=get_xy(ra,td);
    }

    point std_ans=get_xy(radius,(d-1)*40.0/360*2*pi);
    
    pair<double,int> tmp[5];
    for(int i=1;i<=4;i++)tmp[i]=make_pair(len(std_ans-ans[i]),i);
    sort(tmp+1,tmp+5);
    int i=tmp[1].second;
    double ra=radius*(sin(t1[i])/sin(a1)),td=40.0*(b-1)/360*2*pi+(pi-t1[i]-a1)*((i==1||i==4)?(-1):1);
    if(td>pi*2)td-=pi*2;
    if(td<0)td+=pi*2;
    return make_pair(ra,td);
}