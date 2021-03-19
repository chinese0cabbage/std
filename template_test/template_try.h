//
// Created by zhangjun on 21-3-18.
//

#ifndef STD_TEMPLATE_TRY_H
#define STD_TEMPLATE_TRY_H

template <typename T,typename CONT=std::vector<T>>
        class t{
    CONT v;
};

template <typename T,template <typename ELEM> class CONT>
        class s{

};


#endif //STD_TEMPLATE_TRY_H
