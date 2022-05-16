#ifndef GOLDEN_BISECT
#define GOLDEN_BISECT

#include "bisect_base.hpp"
class golden_bisect:public bisect_base{
    public:
    golden_bisect():bisect_base(){}
    golden_bisect(vector<node*>g):bisect_base(g){}
    void bisect(node*end,vector<int>&process,node* real_bad);
    void start(vector<int> &process,int real_bad,int last_in_master);
};
#endif