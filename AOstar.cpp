#include<iostream>
#include<vector>
using namespace std;

int Futility=0xFFFF;
class Node{
public:
    int id;
    int h;
    Node *brother;
    Node *parent;
    Node *bestpath;
    vector<Node*> son;
    bool solved;
    bool havebro;
    bool target;
    
    Node(int id,int h)
    {
        this->h=h;
        this->id=id;
        this->parent=NULL;
        this->brother=NULL;
        this->solved=false;
        this->havebro=false;
        this->target=false;
    }
};

void addson(Node* parent,Node* son)
{
    son->parent=parent;
    parent->son.push_back(son);
}

void addbrother(Node* bro,Node* self)
{
    self->brother=bro;
    bro->brother=self;
    self->havebro=true;
    bro->havebro=true;
}

void calcost(Node* n0)
{
    
    int len = n0->son.size();
    int nh[len];
    for(int i=0;i<len;i++)
    {
        if(n0->son[i]->havebro==true)
            nh[i]=2+n0->son[i]->h+n0->son[i]->brother->h;
        else nh[i]=1+n0->son[i]->h;
    }
    int min=nh[0];
    int best=0;
    for(int j=0;j<len;j++)
    {
        if(min>nh[j])
        {
            min = nh[j];
            best = j;
        }
    }
    n0->h=min;
    n0->bestpath=n0->son[best];
}

bool findinvector(vector<Node*> n,Node *n1)
{
    for(int i=0;i<n.size();i++)
    {
        if(n1==n[i])
            return true;
    }
    return false;
}

void AOstar(Node* n0)
{
    vector<Node*> G;
    G.push_back(n0);
    while(n0->solved!=true and n0->h<Futility)
    {
        Node *TNode=G[0];
        for(int i=0;i<G.size();i++)
        {
            G[i]=G[i+1];
        }
        G.pop_back();
        if(TNode->son.size()==0 and TNode->solved==false)
        {
            TNode->h=Futility;
            continue;;
        }
        else{
        vector<Node*> nodeson = TNode->son;
        for(int i=0;i<nodeson.size();i++)
        {
            if(TNode->parent!=nodeson[i])
            {
                G.push_back(nodeson[i]);
                if(nodeson[i]->target==true)
                {
                    nodeson[i]->solved=true;
                    nodeson[i]->h=0;
                }
            }
        }
        }
        vector<Node*> S;
        S.push_back(TNode);
        while(S.size()>0)
        {
            Node *current;
            int num;
            for(int i=0;i<S.size();i++)
            {
                int OK=1;
                for(int j=0;j<S[i]->son.size();j++)
                {
                    if(findinvector(S, S[i]->son[j]))
                       OK=0;
                }
                if(OK==1){
                    current = S[i];
                    num = i;
                    break;
                }
            }
            for(int i=num;i<S.size();i++)
            {
                S[i]=S[i+1];
            }
            S.pop_back();
            int temp=current->h;
            if(current->solved!=true)
            calcost(current);
            if(
               current->solved==true or
               (current->bestpath->solved==true and (current->bestpath->havebro==false or current->bestpath->brother->solved==true)))
            {
                current->solved=true;
            }
            if(current->solved==true or current->h!=temp)
            {
                while(current->parent!=NULL)
                {
                    S.push_back(current->parent);
                    current=current->parent;
                }
            }
        }
            
    }
}

void print(Node *n0)
{
    if(n0->target==true)
        cout<<n0->id<<"*"<<endl;
    else
    {
        if(n0->havebro==true)
        {
            cout<<"("<<n0->id<<","<<n0->brother->id<<")"<<endl;
            n0->havebro=false;
            n0->brother->havebro=false;
            print(n0);
            print(n0->brother);
        }
        else
        {
            cout<<n0->id<<"->";
            print(n0->bestpath);
        }
    
    }
}

int main()
{
    Node *n1=new Node(1,1);
    Node *n2=new Node(2,4);
    Node *n3=new Node(3,3);
    Node *n4=new Node(4,6);
    Node *n5=new Node(5,5);
    Node *n6=new Node(6,7);
    Node *n7=new Node(7,2);
    Node *n8=new Node(8,1);
    Node *n9=new Node(9,3);
    Node *n10=new Node(10,4);
    addson(n1,n2);
    addson(n1,n3);
    addson(n1,n4);
    addson(n2,n7);
    addson(n2,n8);
    addson(n8,n9);
    addson(n8,n10);
    addson(n3,n5);
    addson(n3,n6);
    addson(n10,n5);
    addbrother(n3,n4);
    n6->target=true;
    n4->target=true;
    
    AOstar(n1);
    print(n1);

}
