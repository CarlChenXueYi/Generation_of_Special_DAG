#include "bisect_base.hpp"
using namespace std;

bisect_base::bisect_base(vector<node*> g){
    for(int i=0;i<g.size();i++){  
        node*x=new node{i,false,nullptr,nullptr,nullptr,{}};
        graph.push_back(x);
    }
    
    for(int i=0;i<g.size();i++){
        if(g[i]->parent1!=nullptr)graph[i]->parent1=graph[g[i]->parent1->identifier];
        if(g[i]->parent2!=nullptr)graph[i]->parent2=graph[g[i]->parent2->identifier];
        if(g[i]->child1!=nullptr)graph[i]->child1=graph[g[i]->child1->identifier];
        for(auto x:g[i]->child2){
            graph[i]->child2.push_back(graph[x->identifier]);
        }

    }
    
}

vector<node*> bisect_base::get_graph(){
    return graph;
}

void bisect_base::create_graph(int num,float l,int forknumres,float r,float s,float t){
    if(num==0){
        cout<<"num=0"<<endl;
    }
    vector<node*> tail_Node; 
    for(int i=0;i<num;i++){  
        node*x=new node{i,false,nullptr,nullptr,nullptr,{}};
        graph.push_back(x);
    }
    tail_Node.push_back(graph[0]);
    fork_head.push_back(graph[0]);
    node* master_tail=graph[0];
    for(int i=1;i<num;i++){
        node* one_in_tail;//至少有四分之一概率得到主分支尾节点
        if(rand()*1.0/RAND_MAX<l){
            one_in_tail=master_tail;
        }else{
            one_in_tail=tail_Node[rand()%tail_Node.size()];
        }
        int rand_mode=rand()%10;
        if(forknumres>=0&&(rand()*1.0/RAND_MAX<r)){
            fork_head.push_back(graph[i]);
            forknumres--;
            graph[i]->parent1=one_in_tail;
            one_in_tail->child2.push_back(graph[i]);
            tail_Node.push_back(graph[i]);
        }else
        {
            if(one_in_tail==master_tail){
                master_tail=graph[i];
            }
            tail_Node.erase(find(tail_Node.begin(),tail_Node.end(),one_in_tail));
            tail_Node.push_back(graph[i]);
            one_in_tail->child1=graph[i];
            graph[i]->parent1=one_in_tail;

            if((rand()*1.0/RAND_MAX>=r+s)){
                node* another_in_tail;
                another_in_tail=tail_Node[rand()%tail_Node.size()];
                if(!is_ancestor(graph[i],another_in_tail)){ //another是不是i的祖先，已经是了就不能再加
                    another_in_tail->child2.push_back(graph[i]);
                    graph[i]->parent2=another_in_tail;
                }
            }
        }
    }
}

bool bisect_base::is_ancestor(node*end ,node*x){
    vector<node*>record;
    node_in_route(end,record);
    return is_existed(record,x);
}

void bisect_base::show_graph(){
    for(auto i:fork_head){
        node* x=i;
        cout<<"start:";
        while(x!=nullptr){
            cout<<x->identifier<<" ";
            x=x->child1;
        }
        cout<<endl;
    }
}

void bisect_base::change_to_this_graph(vector<GNode> g){
    graph.clear();
    int n=g.size();
    for(int i=0;i<g.size();i++){  
        node*x=new node{0,false,nullptr,nullptr,nullptr,{}};
        graph.push_back(x);
    }
    for(int i=0;i<g.size();i++){
        graph[i]->identifier=g[i].tag;
        graph[i]->parent1=g[i].parent1==-1?nullptr:graph[g[i].parent1];
        graph[i]->parent2=g[i].parent2==-1?nullptr:graph[g[i].parent2];
        graph[i]->child1=g[i].child1==-1?nullptr:graph[g[i].child1];
        for(auto x:g[i].child2){
            node*m=graph[x];
            graph[i]->child2.push_back(m);
        }
    }
}

void bisect_base::refresh_tag(){
    for(auto i:graph){
        i->variable=false;
    }
}

void bisect_base::node_in_route(node*end,vector<node*>&record){
    refresh_tag();
    dfs(end,record);
}

bool bisect_base::is_existed(vector<node*>&all,node*x){
    for(auto it:all){
        if(x==it)return true;
    }
    return false;
}

void bisect_base::dfs(node*x,vector<node*>&record){
    
    if(x==nullptr)return;
    if(x->variable)return;
    
    record.push_back(x);
    x->variable=true;
    dfs(x->parent1,record);
    dfs(x->parent2,record);
}

void bisect_base::delete_node(node*end){
    vector<node*> record;
    node_in_route(end,record);
    for(auto it:record){
        node* c1=it->child1;
        if(c1){
            if(c1->parent1==it)c1->parent1=nullptr;
            else if(c1->parent2==it)c1->parent2=nullptr;
        }
        for(auto c2:it->child2){
            if(c2->parent1==it)c2->parent1=nullptr;
            else if(c2->parent2==it)c2->parent2=nullptr;
        }
    }
}

node* bisect_base::set_weight(node*end,map<int,int>&weight,vector<node*>&big){
    vector<node*> record;
    node_in_route(end,record);
    int n=record.size();
    weight.insert(pair<int,int>(end->identifier,n));
    record.erase(record.begin());
    // for(auto i:record){
    //     cout<<i->identifier<<endl;
    // }
    for(auto &i:record){
        node*c1=i->child1;
        if(c1&&c1->parent2==nullptr&&weight[c1->identifier]){
            weight.insert(pair<int,int>(i->identifier,weight[c1->identifier]-1));
        }else{
            vector<node*> record1;
            node_in_route(i,record1);
            weight.insert(pair<int,int>(i->identifier,record1.size()));
        }
    }
    node* max_node=nullptr;
    int max_weight=-1;
    for(auto &i:weight){
        if(i.second>n-i.second){
            i.second=n-i.second;
            big.push_back(graph[i.first]);
        }
        if(i.second>max_weight){
            max_weight=i.second;
            max_node=graph[i.first];
        }
    }
    return max_node;
}


