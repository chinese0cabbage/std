//
// Created by zhangjun on 21-3-18.
//

#ifndef STD_TEMPLATE_TRY_H
#define STD_TEMPLATE_TRY_H

template<class T>
inline T const &max(T const &a, T const &b) {
    return a < b ? b : a;
}

void use_template() {
    int i = 42;
    std::cout << "max(7,i):" << ::max(7, i) << std::endl;
    double f1 = 3.4;
    double f2 = -6.7;
    std::cout << "max(f1,f2):" << ::max(f1, f2) << std::endl;
    std::string s1 = "mathematics";
    std::string s2 = "math";
    std::cout << "max(s1,s2):" << ::max(s1, s2) << std::endl;
    std::complex<float> c1(1, 1), c2(2, 2);
//    std::cout << "complex:" << ::max(c1, c2) << std::endl;//模板报错
}


#endif //STD_TEMPLATE_TRY_H
