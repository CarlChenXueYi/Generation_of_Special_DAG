#include"git_bisect.hpp"

void git_bisect::bisect(node*end,vector<int>&process,node* real_bad){
    vector<node*>big;
    map<int,int>weight;
    node* max_node=set_weight(end,weight,big);
    // cout<<"weightsize="<<weight.size()<<endl;
    // cout<<"weight["<<max_node->identifier<<"]="<<weight[max_node->identifier]<<endl;
    // for(auto i:weight){
    //     cout<<i.first<<" "<<i.second<<endl;
    // }
    if(weight.size()==1){
        //process.push_back(max_node->identifier);
        //cout<<"First bad node is "<<max_node->identifier<<endl;
        return;
    }
    //cout<<"the bisection node is "<<max_node->identifier<<endl;
    process.push_back(max_node->identifier);
    //cout<<"!!!"<<endl;
    if(is_ancestor(max_node,real_bad)){
        //cout<<"bad"<<endl;
        bisect(max_node,process,real_bad);
    }else{
        //cout<<"good"<<endl;
        delete_node(max_node);
        bisect(end,process,real_bad);
    }
}

void git_bisect::start(vector<int> &process,int real_bad,int last_in_master){
    //change_to_this_graph(origin_graph);
    bisect(graph[last_in_master],process,graph[real_bad]);
}