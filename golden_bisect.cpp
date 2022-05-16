#include "golden_bisect.hpp"

void golden_bisect::bisect(node*end,vector<int>&process,node*real_bad){
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
    if(weight[max_node->identifier]<weight.size()*0.382){
        vector<node*> B_plus_begin;
        for(auto i:big){
            if(find(big.begin(),big.end(),i->parent1)==big.end()&&
            find(big.begin(),big.end(),i->parent2)==big.end())
                B_plus_begin.push_back(i);
        }
        int max_weight=-1;
        for(auto i:B_plus_begin){
            if(weight[i->identifier]>max_weight){
                max_weight=weight[i->identifier];
                max_node=i;
            }
            if(i->parent1&&weight[i->parent1->identifier]>max_weight){
                max_weight=weight[i->parent1->identifier];
                max_node=i->parent1;
            } 
            if(i->parent2&&weight[i->parent2->identifier]>max_weight) {
                max_weight=weight[i->parent2->identifier];
                max_node=i->parent2;
            }
        }
    }

    //cout<<"the bisection node is "<<max_node->identifier<<endl;
    process.push_back(max_node->identifier);
    if(is_ancestor(max_node,real_bad)){
        //cout<<"bad"<<endl;
        bisect(max_node,process,real_bad);
    }else{
        //cout<<"good"<<endl;
        delete_node(max_node);
        bisect(end,process,real_bad);
    }
}

void golden_bisect::start(vector<int> &process,int real_bad,int last_in_master){
    //change_to_this_graph(origin_graph);
    bisect(graph[last_in_master],process,graph[real_bad]);
}