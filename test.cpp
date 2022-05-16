#include"golden_bisect.hpp"
#include"git_bisect.hpp"
#include <Winbase.h>
#include <fstream>
#include <sstream>



int main(){
    // srand(GetTickCount());
    // int times;
    // cout<<"the times you need to run:"<<endl;
    // cin>>times;
    // double all=0;
    // double afs=0;
    // double ass=0;
    // double aen=0;
    // double aene=0;
    // double agitn=0;
    // double agoln=0;

    // while(times--){
    //     int fs=0;
    //     int ss=0;
    //     int en=0;
    //     int ene=0;
    //     int gitn=0;
    //     int goln=0;
    //     bisect_base base;
    //     base.create_graph(800,0.1,15,0.3,0.2,0.5);
    //     //git.show_graph();
    //     vector<node*>graph=base.get_graph();
        

    //     node* last_in_master=graph[0];
    //     while(last_in_master->child1!=nullptr){
    //         last_in_master=last_in_master->child1;
    //     }
    //     // 
    //     vector<node*> record;
    //     base.node_in_route(last_in_master,record);
    //     cout<<"the node number in route is "<<record.size()<<endl;
    //     for(auto x:record){
    //         git_bisect git(graph);
    //         golden_bisect golden(graph);
    //         int real_bad=x->identifier;
    //         vector<int> process1;
    //         git.start(process1,real_bad,last_in_master->identifier);
    //         vector<int> process2;
    //         golden.start(process2,real_bad,last_in_master->identifier);
    //         gitn+=process1.size();
    //         goln+=process2.size();
    //         if(process1.size()==process2.size()){
    //             en++;
    //             for(int i=0;i<process1.size();i++){
    //                 if(process1[i]!=process2[i]){
    //                     ene++;
    //                     break;
    //                 }
    //             }
    //         }else if(process1.size()<process2.size()){
    //             fs++;
    //         }else if(process1.size()>process2.size()){
    //             ss++;
    //         }
    //     }

    //     cout<<"git bisect good times "<<fs<<endl;
    //     cout<<"golden bisect good times "<<ss<<endl;
    //     cout<<"the equal bisect times "<<en<<endl;
    //     cout<<"the equal bisect but not totally same times "<<ene<<endl;
    //     cout<<"git num "<<gitn<<endl;
    //     cout<<"gol num "<<goln<<endl;
    //     all+=record.size();
    //     afs+=fs;
    //     ass+=ss;
    //     aen+=en;
    //     aene+=ene;
    //     agitn+=gitn*1.0/record.size();
    //     agoln+=goln*1.0/record.size();
    // }
    // cout<<"ave num "<<all/10<<endl;
    // cout<<"git good "<<afs/10<<endl;
    // cout<<"golden good "<<ass/10<<endl;
    // cout<<"ave test num "<<agitn/10<<endl;
    // cout<<"ave test num "<<agoln/10<<endl;
    


    srand(GetTickCount());
    int times;
    int fs=0;
    int ss=0;
    int en=0;
    int ene=0;
    int gitn=0;
    int goln=0;
    cout<<"the times you need to run:"<<endl;
    cin>>times;
    while(times--){
        git_bisect git;
        git.create_graph(10000,0.25,50,0.2,0.5,0.3);
        //git.show_graph();
        vector<node*>graph=git.get_graph();
        golden_bisect golden(graph);

        node* last_in_master=graph[0];
        while(last_in_master->child1!=nullptr){
            last_in_master=last_in_master->child1;
        }
        int real_bad=rand()%graph.size();
        while(!git.is_ancestor(last_in_master,graph[real_bad])){
            real_bad=rand()%graph.size();
        }
        // cout<<"last_in_master="<<last_in_master->identifier<<endl;
        // cout<<"real_bad="<<real_bad<<endl;

        vector<int> process1;
        git.start(process1,real_bad,last_in_master->identifier);
        // cout<<endl;
        vector<int> process2;
        golden.start(process2,real_bad,last_in_master->identifier);
        gitn+=process1.size();
        goln+=process2.size();
        if(process1.size()==process2.size()){
            en++;
            for(int i=0;i<process1.size();i++){
                if(process1[i]!=process2[i]){
                    ene++;
                    break;
                }
            }
        }else if(process1.size()<process2.size()){
           // for(auto x:process1)cout<<x<<" ";
           // cout<<endl;
           // for(auto x:process2)cout<<x<<" ";
           // cout<<endl;
            fs++;
        }else if(process1.size()>process2.size()){
           // for(auto x:process1)cout<<x<<" ";
           // cout<<endl;
           // for(auto x:process2)cout<<x<<" ";
           // cout<<endl;
            ss++;
        }
    }
    
    cout<<"git bisect good times"<<fs<<endl;
    cout<<"golden bisect good times"<<ss<<endl;
    cout<<"the equal bisect times"<<en<<endl;
    cout<<"the equal bisect but not totally same times"<<ene<<endl;
    cout<<"git num "<<gitn<<endl;
    cout<<"gol num "<<goln<<endl;

    //单个自定义图的测试
    
    // ifstream in;
    // in.open("graph1.txt");
    // vector<GNode> g;
    // while(!in.eof()){
    //     string s;
    //     getline(in,s);
    //     istringstream iss(s);
    //     GNode gn;
    //     iss>>gn.tag>>gn.parent1>>gn.parent2>>gn.child1;
    //     int x;
    //     while(iss>>x){
    //         gn.child2.push_back(x);
    //     }
    //     g.push_back(gn);
    // }
    // git_bisect git;
    // //golden_bisect golden;


    // int git_good=0;
    // int golden_good=0;
    // int real_bad=0;
    // while(real_bad<21){
    //     git.change_to_this_graph(g);
        
    //     //golden.change_to_this_graph(g);
    //     vector<node*>graph=git.get_graph();
    //     golden_bisect golden(graph);
    //     node* last_in_master=graph[16];
        
    //     //cout<<"last_in_master="<<last_in_master->identifier<<endl;
    //     cout<<"real_bad="<<real_bad<<endl;
    //     vector<int> process1;
    //     git.start(process1,real_bad,last_in_master->identifier);
    //     cout<<"git result="<<process1.size()<<endl;
    //     for(auto x:process1){
    //         cout<<x<<" ";
    //     }
    //     cout<<endl;
        
    //     vector<int> process2;
    //     golden.start(process2,real_bad,last_in_master->identifier);
    //     cout<<"golden result="<<process2.size()<<endl;
    //     for(auto x:process2){
    //         cout<<x<<" ";
    //     }
    //     cout<<endl;
    //     if(process1.size()<process2.size()){
    //         git_good++;
    //     }else if(process1.size()>process2.size()){
    //         golden_good++;
    //     }
    //     real_bad++;
    // }
    // cout<<endl;
    // cout<<"git good="<<git_good<<endl;
    // cout<<"golden good="<<golden_good<<endl;
    
    return 0;
}