#ifndef GRAPH_
#define GRAPH_
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
struct node{
    int identifier;
    bool variable;  //is visited
    node*parent1;
    node*parent2;
    node*child1;
    vector<node*>child2;
};
typedef struct GNode{
    int tag;
    int parent1;
    int parent2;
    int child1;
    vector<int> child2;
}GNode;
class bisect_base{
    protected:
    vector<node*> graph;
    node*real_bad;
    vector<node*> fork_head;
    public:
    bisect_base(){}
    bisect_base(vector<node*> g);
    vector<node*> get_graph();
    void create_graph(int num=1000,float l=0.25,int forknumres=10,float r=0.2,float s=0.6,float t=0.2);
    void show_graph();
    void refresh_tag();
    void change_to_this_graph(vector<GNode> g);
    void node_in_route(node*end,vector<node*>&record);
    void dfs(node*x,vector<node*>&record);
    bool is_existed(vector<node*>&all,node*x);
    bool is_ancestor(node*end ,node*x);//x是否是end的祖先
    void delete_node(node*end);
    node* set_weight(node*end,map<int,int>&weight,vector<node*>&big);
};


#endif