#include<iostream>
#include<vector>

using namespace std;

const int N=10;

class Point
{
    public:
        int x;
        int y;
        int g;
        int h;
        int f;
        int type;//0为空，1为起始点，2为终点，3为障碍物。
        Point *Parent;
        Point(int x0,int y0){
            this->x=x0;
            this->y=y0;
            this->f=0;
            this->g=0;
            this->h=0;
            this->type=0;
            this->Parent=NULL;
        };
        Point(int x0,int y0,Point* Parent0){
            this->x=x0;
            this->y=y0;
            this->f=0;
            this->g=0;
            this->h=0;
            this->type=0;
            this->Parent=Parent0;
        };
};

int Map[N+1][N+1];//0为空白，1为起点，2为终点，3为障碍，4为路径。
vector<Point*> OpenList;
vector<Point*> CloseList;

int Mdistance(Point* begin,Point* end)
{
    int a=abs(begin->x - end->x);
    int b=abs(begin->y - end->y);
    int ans=a+b;
    return ans;
}


int havePoint(vector<Point*> list,int x,int y)
{
    int index=-1;
    for(int i=0;i < list.size();i++)
    {
        if (list[i]->x==x && list[i]->y==y)
        {
            index=i;
            break;
        }
    }
    return index;
}

void sortlist(vector<Point*> list)
{
    int len=list.size();
    for(int i=len-1;i>=0;i--)
    {
        for(int j=0;j<i;j++)
        {
            if(list[j]->f>=list[j+1]->f)
            {
                Point* tp=list[j];
                list[j]=list[j+1];
                list[j+1]=tp;
            }
        }
    }
};


void nextStep(int x,int y,Point* now,Point* end)
{
    if(Map[x][y]==3)
    return;
    if(havePoint(CloseList,x,y)==-1)
    {
        int i=havePoint(OpenList,x,y);
        if(i==-1)
        {
            Point* tpoint=new Point(x,y,now);
            tpoint->h=Mdistance(tpoint,end);
            tpoint->g=now->g+1;
            tpoint->f=tpoint->h+tpoint->g;
            OpenList.push_back(tpoint);
        }
        else
        {
            Point* tpoint2=OpenList[i];
            if(tpoint2->g>now->g+1)
            {
                tpoint2->g=now->g+1;
                tpoint2->Parent=now;
                tpoint2->f=tpoint2->g+tpoint2->h;
            }
        }
    }
};

void DrawAns(Point* p)
{
    Point* point_temp=p->Parent;
    while(point_temp->Parent!=NULL)
    {
        Map[point_temp->x][point_temp->y]=4;
        point_temp=point_temp->Parent;
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            if(Map[i][j]==1)
            cout<<"!";
            else if(Map[i][j]==2)
            cout<<"*";
            else if(Map[i][j]==3)
            cout<<"#";
            else if(Map[i][j]==4)
            cout<<"·";
            else
            cout<<" ";
            
        }
        cout<<endl;
    }
}

bool AstarSearch(Point* begin,Point* end){
    begin->h=Mdistance(begin,end);
    begin->g=0;
    begin->f=begin->h+begin->g;
    OpenList.push_back(begin);
    Point* temp = NULL;
    bool ans=false;
    while(OpenList.size()!=0)
    {
        temp=OpenList[0];
        if(temp->x==end->x&&temp->y==end->y)
        {
            ans=true;
            break;
        }
        if(temp->x>1)
        {
            nextStep(temp->x-1,temp->y,temp,end);
        }
        if(temp->x<N)
        {
            nextStep(temp->x+1,temp->y,temp,end);
        }
        if(temp->y>1)
        {
            nextStep(temp->x,temp->y-1,temp,end);
        }
        if(temp->y<N)
        {
            nextStep(temp->x,temp->y+1,temp,end);
        }
        CloseList.push_back(temp);
        OpenList.erase(OpenList.begin());
        sortlist(OpenList);
    }
    if(ans)
    DrawAns(temp);
    else
        cout<<"不能到达！";
    return ans;
    
}

int main()
{
    int beginX,beginY;
    int endX,endY;
    int obstacle_num;
    for(int i=0;i<N+1;i++)
    {
        for(int j=0;j<N+1;j++)
        {
            Map[i][j]=0;
        }
    }
    cout<<"根据坐标寻找路径。!是起点，*是终点，#是障碍物，·是路径"
    cout<<"输入你的起始点坐标："<<endl;
    cin>>beginX>>beginY;
    cout<<"输入你的终点坐标："<<endl;
    cin>>endX>>endY;
    cout<<"输入你的障碍物数量："<<endl;
    cin>>obstacle_num;
    Point* point_begin=new Point(beginX,beginY);
    point_begin->type=1;
    Map[beginX][beginY]=1;
    Point* point_end=new Point(endX,endY);
    point_end->type=2;
    Map[endX][endY]=2;
    for(int i=1;i<=obstacle_num;i++)
    {
        int tx,ty;
        cout<<"输入第"<<i<<"个坐标："<<endl;
        cin>>tx>>ty;
        Map[tx][ty]=3;
    }
    bool OK;
    OK=AstarSearch(point_begin,point_end);
    return 0;

}



