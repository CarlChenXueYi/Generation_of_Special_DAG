#ifndef GIT_BISECT
#define GIT_BISECT

#include"bisect_base.hpp"
class git_bisect :public bisect_base{
    public:
    git_bisect():bisect_base(){}
    git_bisect(vector<node*>g):bisect_base(g){}
    void bisect(node*end,vector<int>&process,node* real_bad);
    void start(vector<int> &process,int real_bad,int last_in_master);
};
#endif