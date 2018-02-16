//code by Zhengyang Chen

#include <iostream>
#include<fstream>
#include <cstdio>
#include<iomanip>
#define MAX 10000000
#define FALSE 0
#define TRUE 1
#define OK 1
#define ERROR -1
using namespace std;
int arcs[32][32];//邻接矩阵
int D[32];//保存最短路径长度
int p[32][32];//路径
int maxnum[32];//={100000000,82000000,6400000,29000000,15000000,34000000,30200000,7000000,26000000,90000000};
int curnum[32];
int passcost[32];//={1,2,3,2,4,2,1,3,5,2};
int staycost[32];//={12,17,13,19,15,16,28,24,15,19};
int policy_bugdet[32];
int final[32];//若final[i] = 1则说明 顶点vi已在集合S中
int n = 0;//顶点个数
int v,w;
int path_recorder[32];
int economy[32];
void init(int *passby,int *settlement,int n)
{
    int i;
    for (i=0;i<n;i++)
    {
        //cout<<"input maxnum"<<i+1<<":";
       // cin>>maxnum[i];
       //maxnum[i]=50-2*i;
       curnum[i]=0;
       passby[i]=0;
       settlement[i]=0;
       //policy_bugdet[i]=100;
       //passcost[i]=500;
    }

}
void input_nation(char *nation_info[],int n)
{
    int i;
    if (0){
        for(i=1;i<n;i++)
        {
            cout<<"please input nation"<<i+1<<":"<<endl;
            cin>>nation_info[i][20];
        }

    }
    /*if (1)
    {
        nation_info[36][20]={"Syria","Bulgaria"};
    }*/

}
void recorder_init(int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        path_recorder[i]=-1;
    }
}
void output_route()
{
    for (int i = 0; i < n; i++)
    {
        if(D[i]&&D[i]<MAX)
            printf("D[%d] = %d\n",i,D[i]);
    }

}
int policy_calculator(int n)
{
    int i;
    int temp[32];
    for (i=0;i<n;i++)
    {

        temp[i]=economy[i];
        policy_bugdet[i]=(1000+3*temp[i])*(10+policy_bugdet[i])*5/100;

    }//根据经济增长指数确定拿多少预算
    return OK;
}
int staycost_calculator(int n)
{
    int i;
    int temp[32];
    for (i=0;i<n;i++)
    {

        temp[i]=staycost[i];
        staycost[i]=temp[i]*2/100+3000;

    }//根据人均GDP确定留境花费
    return OK;
}
int passcost_calculator(int n)
{
    int i;
    int temp[32];
    for (i=0;i<n;i++)
    {

        temp[i]=passcost[i];
        passcost[i]=temp[i]*1/100;

    }//过境花费
    return OK;
}
int gdp_calculator(int n)
{
    int i;
    int temp[32];
    int sum=0;
    for (i=0;i<n;i++)
    {

        temp[i]=maxnum[i];
        temp[i]*=2;
        sum=temp[i]*policy_bugdet[i];
        maxnum[i]=sum;
    }
    return OK;
}
int open_arc(int n)
{
    int i,j;
    ifstream fin_arc;
    fin_arc.open("arcs.txt",ios::in);
    if (!fin_arc.is_open()){
        cout<<"fail to open arc file"<<endl;
        return ERROR;
    }
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
        {
            fin_arc>>arcs[i][j];
        }

    for (i=0;i<n;i++){
        for (j=0;j<n;j++)
        {
            if (!arcs[i][j])
            {
                arcs[i][j]=MAX;
                //cout<<arcs[i][j]<<' ';
                //cout<<0<<' ';
            }
            else
                arcs[i][j]/=100;
              //  cout<<arcs[i][j]<<' ';
        }
        //cout<<endl;
    }
    fin_arc.close();
    return OK;
}
int open_gdp(int n)
{
    int i;
    ifstream fin_gdp;
    fin_gdp.open("gdp.txt",ios::in);
    if (!fin_gdp.is_open()){
        cout<<"fail to open gdp file"<<endl;
        return ERROR;
    }
    for (i=0;i<n;i++)
        {
            fin_gdp>>maxnum[i];
        }

    fin_gdp.close();
    return OK;
}
int  open_pass(int n)
{
    int i;
    ifstream fin_pass;
    fin_pass.open("passcost.txt",ios::in);
    if (!fin_pass.is_open()){
        cout<<"fail to open passcost file"<<endl;
        return ERROR;
    }
    for (i=0;i<n;i++)
        {
            fin_pass>>passcost[i];
        }

    fin_pass.close();
    return OK;
}
int open_stay(int n)
{
    int i;
    ifstream fin_stay;
    fin_stay.open("staycost.txt",ios::in);
    if (!fin_stay.is_open()){
        cout<<"fail to open staycost file"<<endl;
        return ERROR;
    }
    for (i=0;i<n;i++)
        {
            fin_stay>>staycost[i];
        }

    fin_stay.close();
    return OK;
}
int open_pol(int n)
{
    int i;
    ifstream fin_pol;
    fin_pol.open("pol.txt",ios::in);
    if (!fin_pol.is_open()){
        cout<<"fail to open policy file"<<endl;
        return ERROR;
    }
    for (i=0;i<n;i++)
        {
            fin_pol>>policy_bugdet[i];
        }

    fin_pol.close();
    return OK;
}
int open_eco(int n)
{
    int i;
    ifstream fin_pol;
    fin_pol.open("eco.txt",ios::in);
    if (!fin_pol.is_open()){
        cout<<"fail to open policy file"<<endl;
        return ERROR;
    }
    for (i=0;i<n;i++)
        {
            fin_pol>>economy[i];
        }

    fin_pol.close();
    return OK;
}
int input_data(int n)
{
    if(open_arc(n)==ERROR)
        return ERROR;
    if(open_gdp(n)==ERROR)
        return ERROR;
    if(open_pass(n)==ERROR)
        return ERROR;
    if(open_stay(n)==ERROR)
        return ERROR;
    if(open_pol(n)==ERROR)
        return ERROR;
    if(open_eco(n)==ERROR)
        return ERROR;


    return OK;
}
int data_adjustment(int n)
{

    if(policy_calculator(n)!=OK)
        return ERROR;
    if(passcost_calculator(n)!=OK)
        return ERROR;
    if(staycost_calculator(n)!=OK)
        return ERROR;
    if(gdp_calculator(n)!=OK)
        return ERROR;
    return OK;
}
void data_adjustment_print(int n)
{
    int i;
    cout<<"maxnum:  "<<endl;
    for(i=0;i<n;i++)
    {
        cout<<maxnum[i]<<" ";
        if((i+1)%8==0)
            cout<<endl;
    }
    cout<<endl;
    cout<<"passcost:  "<<endl;
    for(i=0;i<n;i++)
    {
        cout<<passcost[i]<<" ";
        if((i+1)%8==0)
            cout<<endl;
    }
    cout<<endl;
    cout<<"staycost:  "<<endl;
    for(i=0;i<n;i++)
    {
        cout<<staycost[i]<<" ";
        if((i+1)%8==0)
            cout<<endl;
    }
    cout<<endl;
    cout<<"policy:  "<<endl;
    for(i=0;i<n;i++)
    {
        cout<<policy_bugdet[i]<<" ";
        if((i+1)%8==0)
            cout<<endl;
    }
    cout<<endl;
}
void init_matrix(int v0)
{
    for (v = 0; v < n; v++) //循环 初始化
     {
          final[v] = 0;
          D[v] = arcs[v0][v];
          for (w = 0; w < n; w++)
            p[v][w] = 0;//设空路径
          if (D[v] < MAX) {p[v][v0] = 1; p[v][v] = 1;}
     }
}
void visa_officer(int method,int *passby, int *settlement,int i)
{
    if (method==1)
    {
        passby[i]++;
    }

    if(method==2)
    {
        settlement[i]++;
    }

}
void visa_officer_report(int passby[], int settlement[],int nationinfo[],int n,int total)
{
    cout<<"The Visa Officer give out the report:"<<endl;
    cout<<" on condition of :    "<<total<<"    refugees flood into Europe"<<endl;
    int i;
    for (i=0;i<n;i++)
    {
        switch(i)
        {
        case 0:cout<<"Afghanstan ";break;
        case 1:cout<<"Syria      ";break;
        case 2:cout<<"Turkey     ";break;
        case 3:cout<<"Greece     ";break;
        case 4:cout<<"Albania    ";break;
        case 5:cout<<"Macedon    ";break;
        case 6:cout<<"Bulgalia   ";break;
        case 7:cout<<"Romania    ";break;
        case 8:cout<<"Serbia     ";break;
        case 9:cout<<"Hessen     ";break;
        case 10:cout<<"Posenia    ";break;
        case 11:cout<<"Crotia     ";break;
        case 12:cout<<"Hungary    ";break;
        case 13:cout<<"Austria    ";break;
        case 14:cout<<"Ukraine    ";break;
        case 15:cout<<"Slovakia   ";break;
        case 16:cout<<"Czech      ";break;
        case 17:cout<<"Poland     ";break;
        case 18:cout<<"Germany    ";break;
        case 19:cout<<"France     ";break;
        case 20:cout<<"Spain      ";break;
        case 21:cout<<"Morroco    ";break;
        case 22:cout<<"Italy      ";break;
        case 23:cout<<"Libya      ";break;
        case 24:cout<<"England    ";break;
        case 25:cout<<"Denmark    ";break;
        case 26:cout<<"Norway     ";break;
        case 27:cout<<"Sweden     ";break;
        case 28:cout<<"Finland    ";break;
        case 29:cout<<"Russia     ";break;
        case 30:cout<<"Belgium    ";break;
        case 31:cout<<"Netherland ";break;

        }
        cout<<":   ";
        cout<<"refugee pass-by:  "<<setw(15)<<setiosflags(ios::left)<<passby[i]<<"   refugee settlement:  "<<setiosflags(ios::left)<<settlement[i]<<endl;
    }
}
int max_choose(int *maxnum,int n,int v0)
{
    int i;
    int temp;
    int maxval=-999990;
    for (i=0;i<n;i++)
    {
        if (maxnum[i]>maxval&&i!=v0)
        {
            maxval=maxnum[i];
            temp=i;

        }

        //cout<<i<<" "<<v0<<' '<<maxval<<endl;;
    }

    return temp;
}
void printer_maxnum(int n)
{
    int i;
    cout<<"resources: ";
    for(i=0;i<n;i++)
    {
        cout<<maxnum[i]<<' ';
    }
    cout<<endl;
}
void printer_path(int n,int finalpt,int v0)
{
    int i;
    cout<<"the path is: "<< v0<<"->";
    for(i=0;i<n;i++)
    {
        if (path_recorder[i]!=-1)
            cout<<path_recorder[i]<<"->";
    }
    cout<<finalpt<<endl;
    cout<<"finalpt:"<<finalpt<< ' ';
    cout<<endl;
}

int pathfinder(int n,int v0,int *passby, int *settlement,int nation_info[])
{
    int num;
    int i;
    int j=0;
    int k;
    int finalpt;
   /* for (i=0;i<n;i++)
     {
         cout<<p[i][v0]<<' ';
         if (p[i][v0])
            curnum[i]++;
         if (curnum[i]>maxnum[i])
         {
            for (w=0;w<n;w++)
            arcs[i][w]=arcs[w][i]=MAX;
         }
     }*/
    recorder_init(n);
    num=max_choose(maxnum,n,v0);
    //cout<<"num="<<num<<" value="<<maxnum[num]<<endl;
    //getchar();
    for (i=0;i<n;i++)
    {
       // cout<<p[num][i]<<' ';
        if(p[num][i]&&i!=v0)
        {
            if (i!=num)
            {
                maxnum[i]-=passcost[i];
                path_recorder[j]=i;
                visa_officer(1,passby,settlement,i);
            }
            else
            {
                maxnum[i]-=staycost[i];
                finalpt=i;
                visa_officer(2,passby,settlement,i);
            }
            if (maxnum[i]<=0)
            {
                for (k=0;k<n;k++)
                arcs[i][k]=arcs[k][i]=MAX;
            }
            j++;

        }
    }
    //getchar();
    if(0){
        //visa_officer_report(passby,settlement,nation_info,n);

        printer_path(n,finalpt,v0);
       // printer_maxnum(n);

    }
    if(D[num]>=MAX){
        return ERROR;
    }
    else return OK;


}

int ShortestPath_DIJ(int v0,int *passby,int *settlement,int *nation_info,int n)
{
    int i;
    int k;
    int mm;
    int temp;

     D[v0] = 0; final[v0]=1; //初始化 v0顶点属于集合S
     //开始主循环 每次求得v0到某个顶点v的最短路径 并加v到集合S中
     for (i = 1; i < n; i++)
     {
          mm = MAX;
          for (w = 0; w < n; w++)
          {
               if (!final[w]) //如果w顶点在V-S中
               {
                    //这个过程最终选出的点 应该是选出当前V-S中与S有关联边
                    //且权值最小的顶点 书上描述为 当前离V0最近的点
                    if (D[w] < mm) {
                        v = w;
                        mm = D[w];
                        }
               }
          }
          final[v] = 1;
          for (w = 0; w < n; w++)
          {
               if (!final[w] && (mm+arcs[v][w]<D[w]))
               {
                    //cout<<"mm:"<<mm<<endl;
                    //cout<<D[w]<<endl;
                    D[w] = mm + arcs[v][w];
                    for (k=0;k<n;k++)
                        p[w][k] = p[v][k];
                    p[w][w] = 1; //p[w] = p[v] +　[w]
                    temp=w;
               }

          }
     }
     //cout<<"----1";
     if (pathfinder(n,v0,passby,settlement,nation_info)==OK)
        return OK;
     else return ERROR;
     //output_route();

}
bool custom_available(int v0,int n,int pathsuccess)
{
    int i;
    if (pathsuccess==ERROR)
        return FALSE;
    for(i=0;i<n;i++)
    {
        //cout<<arcs[i][v0]<<" ";
        if (arcs[i][v0]&&arcs[i][v0]<MAX)
            return TRUE;
    }
    return FALSE;
}


int main()
{
    n=32;
    int t;
    int i;
    int passby[32];
    int settlement[32];
    int nation_info[32];
    int totalcount=0;
    int pathsuccess=1;
    int refnum;
    cout<<"input refugee number"<<endl;
    cin>>refnum;


    int v0 = 8;//源点
    if (input_data(n)==ERROR){
        cout<<"fail to open file"<<endl;
        return -1;
    }
    //data_adjustment_print(n);
    //getchar();
    if (data_adjustment(n)==ERROR){
        cout<<"fail to adjust data"<<endl;
        return -1;
    }
    //getchar();
    //data_adjustment_print(n);
    //getchar();
    init(passby,settlement,n);
    for (t=0;t<refnum;t++)
    {
        if (!custom_available(v0,n,pathsuccess))
            break;
        init_matrix(v0);
        cout<<"1"<<endl;
        pathsuccess=ShortestPath_DIJ(v0,passby,settlement,nation_info,n);
        //getchar();
        totalcount++;
    }
    if (0){
        for (i=0;i<32;i++)
        {
            cout<<curnum[i]<<' ';
        }
    }
    visa_officer_report(passby,settlement,nation_info,n,totalcount);
    cout<<"total refugees : "<<totalcount<<endl;



    return 0;
}
