#include "stl_allocation_test.h"

#define SIZE 10

int main() {
    execute();
//    timespec tn;
//    std::valarray<double> a1(SIZE);
//    for (int i = 0; i < SIZE; ++i) {
//        a1[i]=rand()%10;
//    }
//
//    clock_gettime(CLOCK_REALTIME,&tn);
//    auto before=tn.tv_nsec;
//    std::valarray<double> a2;
//    std::copy(std::begin(a1),std::end(a1),std::insert_iterator<std::valarray<double>>(a2,std::begin(a2)));
//    clock_gettime(CLOCK_REALTIME,&tn);
//    auto after=tn.tv_nsec;
//    std::cout<<"迭代器复制："<<(after-before)/1e9;
    return 0;
}
