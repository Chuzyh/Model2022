#pragma GCC optimize(3)
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#include "geometry.h"
using namespace std;

point s[N];
const int n=9;
const int T1=1000;
const int T2=100000;

int id[N];

int tot,tot_wrongc,tot_wrong_verifiable;
double seg[1000][10][10][2][2];
double mx=0;
int totR;
double in(double l,double r,double x){return l-eps<=x&&x<=r+eps;}
pair<double,double> solve2_vote(int num,double ang1,double ang2,double ang3,int trueC)
{
    int sum[10];
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=totR;i++)
    {
        for(int j=2;j<=9;j++)
        if(j!=num)
        {
            if(in(seg[i][num][j][0][0],seg[i][num][j][0][1],ang1)&&in(seg[i][num][j][1][0],seg[i][num][j][1][1],ang3))sum[j]++;
        }
    }
    vector<pair<int,int> > tmp;
    for(int j=2;j<=9;j++)if(j!=num)tmp.push_back(make_pair(-sum[j],j));
    sort(tmp.begin(),tmp.end());

    int C=tmp[0].second;
    tot_wrongc+=C!=trueC;
    int B=1;
    if(cross(s[B],s[C])<0)swap(B,C),swap(ang2,ang3);

    return get_rt(B,C,num,ang2,ang3);
}
pair<double,double> solve2_vote2(int num,double ang1,double ang2,double ang3,int trueC,double ang1_2,double ang2_2,double ang3_2,int trueC_2)
{
    int sum[10][10];
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=totR;i++)
    {
        for(int j=2;j<=9;j++)
        for(int j2=2;j2<=9;j2++)
        if(j!=num&&j2!=num&&j!=j2)
        {
            if(in(seg[i][num][j][0][0],seg[i][num][j][0][1],ang1)&&in(seg[i][num][j][1][0],seg[i][num][j][1][1],ang3)
            &&in(seg[i][num][j2][0][0],seg[i][num][j2][0][1],ang1_2)&&in(seg[i][num][j2][1][0],seg[i][num][j2][1][1],ang3_2))sum[j][j2]++;
        }
    }
    vector<pair<int,pair<int,int> > > tmp;
    for(int j=2;j<=9;j++)
        for(int j2=2;j2<=9;j2++)
        if(j!=num&&j2!=num&&j!=j2)
            tmp.push_back(make_pair(-sum[j][j2],make_pair(j,j2)));
    sort(tmp.begin(),tmp.end());

    int C1=tmp[0].second.first,C2=tmp[0].second.second;
    tot_wrongc+=(C1!=trueC)||(C2!=trueC_2);
    int B=1;
    if(cross(s[B],s[C2])<0)swap(B,C2),swap(ang2_2,ang3_2);

    return get_rt(B,C2,num,ang2_2,ang3_2);
}

int main()
{
    srand(233);
    freopen("task2_vote2_data","w",stdout);
    for(int i=1;i<=n;i++)
        s[i]=get_xy(radius,(double)(i-1)/n*2*pi),id[i]=i;
    for(double range=0.1;range<=40+eps;range+=0.1)
    {
        totR++;
        for(int rec=2;rec<=9;rec++)
        {
            for(int se=2;se<=9;se++)
            if(se!=rec)
            {
                seg[totR][rec][se][0][0]=INF;
                seg[totR][rec][se][0][1]=-INF;
                seg[totR][rec][se][1][0]=INF;
                seg[totR][rec][se][1][1]=-INF;
                
                for(int i=1;i<=T1;i++)
                {
                    point fake_rec=add_ran_on_circle_edge(s[rec],range);
                    seg[totR][rec][se][0][0]=min(seg[totR][rec][se][0][0],angle(fake_rec,s[1],s[se]));
                    seg[totR][rec][se][0][1]=max(seg[totR][rec][se][0][1],angle(fake_rec,s[1],s[se]));
                    seg[totR][rec][se][1][0]=min(seg[totR][rec][se][1][0],angle(fake_rec,s[0],s[se]));
                    seg[totR][rec][se][1][1]=max(seg[totR][rec][se][1][1],angle(fake_rec,s[0],s[se]));
                    
                }
                // cout<<seg[totR][rec][se][0][0]<<' '<<seg[totR][rec][se][0][1]<<' '<<seg[totR][rec][se][1][0]<<' '<<seg[totR][rec][se][1][1]<<endl;
            }
        }
    }
    for(double range=10;range<=40.05;range+=0.1)
    {
        mx=0,tot=0;tot_wrongc=0;tot_wrong_verifiable=0;
        for(int i=1;i<=T2;i++)
        {
            random_shuffle(id+2,id+10);
            int b=1,c=id[2],d=id[3];
            point fakeD=add_ran(s[d],range);

            double ang1=angle(fakeD,s[c],s[b]);
            double ang2=angle(fakeD,s[0],s[b]);
            double ang3=angle(fakeD,s[0],s[c]);
            
            pair<double,double> ans=solve2_vote(d,ang1,ang2,ang3,c);
            point ansXY=get_xy(ans.first,ans.second);
            point err=(point){ang1-angle(ansXY,s[c],s[b]),ang2-angle(ansXY,s[0],s[b])};

            int c2=id[4];
            double ang1_2=angle(fakeD,s[c2],s[b]);
            double ang2_2=angle(fakeD,s[0],s[b]);
            double ang3_2=angle(fakeD,s[0],s[c2]);
            if(len(err)>eps)ans=solve2_vote2(d,ang1,ang2,ang3,c,ang1_2,ang2_2,ang3_2,c2),tot_wrongc--;
            ansXY=get_xy(ans.first,ans.second);
            err=(point){ang1-angle(ansXY,s[c],s[b]),ang2-angle(ansXY,s[0],s[b])};

            tot_wrong_verifiable+=len(err)>eps;
            tot+=len(fakeD-ansXY)>eps;
            mx=max(mx,len(fakeD-ansXY));
        }
        cerr<<range<<endl;
        cout<<range<<' '<<mx<<' '<<(double)tot/T2<<' '<<(double)tot_wrongc/T2<<' '<<(double)tot_wrong_verifiable/T2<<endl;
    }
    return 0;
}