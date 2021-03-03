//
// Created by zhangjun on 21-2-19.
//

#ifndef STD_STD_ALGORITHM_TEST_H

#include "algorithm"
#include "iostream"
#include "vector"
#include "iterator"
#include "set"
#include "functional"
#include "valarray"
#include "initializer_list"

#define STD_STD_ALGORITHM_TEST_H

/**
 * std::move函数不会改变原来变量的地址，但是原来变量不指向原来的值了，新的变量指向原来的值
 */
void std_move_test() {
    std::string a = "10", b = "20";
    std::cout << "original a:" << a << " pointer:" << &a;
    std::string tmp = std::move(a);
    std::cout << "\na:" << a << " pointer:" << &a
              << "\nb:" << b << " pointer:" << &b
              << "\ntmp:" << tmp << " pointer:" << &tmp;
}

/**
 * std::remove函数只会将符合要求的n个元素移动(使用的是std::move函数)到容器的末尾，并使用删除前容器中的后n个元素覆盖移动到末尾的n个元素，返回后n个元素的第一个元素的迭代器
 */
void std_remove_int_test() {
    std::vector<int> v{10, 20, 30, 10, 200, 30, 10, 10, 50};
    std::remove(v.begin(), v.end(), 10);
//    v.erase(std::remove(v.begin(), v.end(), 10), v.end()); //如果不使用erase方法进行擦除，尾部会出现废数据，array无法擦除
    std::for_each(v.begin(), v.end(), [](int i) { std::cout << i << "\n"; });
}

void std_remove_string_test() {
    std::vector<std::string> v{"1111", "2222", "3333", "1111", "2222", "1111"};
    std::remove(v.begin(), v.end(), "1111");
    std::for_each(v.begin(), v.end(), [](const std::string &str) { std::cout << str << "\n"; });
}

/**
 * std::copy方法并未进行迭代器类型检查，因此SRC迭代器和dest迭代器都可以自由选择，但 c++ pp上建议最好限定
 * 当前编译器编译不通过，但是cpp官方网站在线编译运行可以通过
 */
void std_copy_test() {
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    std::vector<int> d(6);
//    std::copy(v.begin(), v.end() - 2, d.begin());
    std::insert_iterator<std::vector<int>> insertIterator(d, d.begin());
    std::copy(v.begin(), v.end(), insertIterator);
    std::for_each(d.begin(), d.end(), [](int i) { std::cout << i << "\t"; });
}

/**
 * std::all_of函数会遍历容器中的所有元素，判断元素中是否所有元素都满足其后lambda表达式的条件，都满足则返回True，否则返回false
 * std::none_of函数与all_of函数类似，但是会在所有元素都不满足条件时返回True
 * std::any_of函数会遍历容器，查找是否有一个元素满足条件，有就返回True，否则返回false
 */
void std_all_of_test() {
    std::vector<int> v{10, 20, 30, 40, 50};
    std::cout << std::all_of(v.begin(), v.end(), [](int i) { return i % 10 == 0; });
}

/**
 * set_uniond的输出值只能使用输出迭代器进行接收，但是如vector::begin的是常量迭代器，因此不能作为set_union的输出迭代器
 */
void std_set_union_test() {
    std::set<std::string> str1{"1111", "2222"}, str2{"3333", "4444"};
    std::vector<std::string> v;
    std::set_union(str1.begin(), str1.end(), str2.begin(), str2.end(),
                   std::insert_iterator<std::vector<std::string>>(v, v.begin()));
    std::for_each(v.begin(), v.end(), [](std::string str) { std::cout << str << "\n"; });
}

/**
 * std::transform可以对迭代器范围内的所有元素做指定的函数符运算，函数符可以是仿函数，函数和lambda表达式
 * 该程序片段transform接收的是一元函数符
 */
void std_transform_one_para_test() {
    struct test {
        std::string str;

        int i = 1;

        test(const std::string &str) : str(str) {}
    };

    std::vector<test> v;
    v.push_back(test("1111"));
    v.push_back(test("2222"));
    std::vector<std::string> n;
    std::transform(v.begin(), v.end(), std::insert_iterator<std::vector<std::string>>(n, n.begin()),
                   [](const test &t) { return t.str; });

    std::for_each(n.begin(), n.end(), [](const std::string &str) { std::cout << str << "\t"; });
}

/**
 * 该程序片段接收二元函数符,第一二个参数表示第一个迭代器的起点和终点，第三个参数表示第二个迭代器的起点，第四个参数是输出迭代器，第五个参数是二元函数符
 */
void std_transform_two_para_test() {
    std::vector<int> v1{1, 2, 3}, v2{4, 5, 6};
    std::plus<int> p;
    std::transform(v1.begin(), v1.end(), v2.begin(), std::ostream_iterator<int, char>(std::cout, " "), p);
}

/**
 * 预定义的函数符
 */
void std_plus_test() {
    std::plus<int> p;
//    std::plus +
//    std::minus -
//    std::multiplies *
//    std::divides /
//    std::modulus %
//    std::negate-（取负值）
//    std::equal_to ==
//    std::not_equal_to !=
//    std::greater >
//    std::less <
//    std::greater_equal >=
//    std::less_equal <=
//    std::logical_and &&
//    std::logical_or |
//    std::logical_not!
    std::cout << p(1, 2);
}

/**
 * 函数适配器,采用预定义的形式，将一个固定值绑定到二元函数符中，使得可以像调用一元函数符调用二元函数符，固定值会作为二元函数符中的另外一个值
 * bind1st是将值绑定到的第一个参数，bind2st是将值绑定到第二个参数
 */
void std_bind1st_test() {
    auto f = std::bind1st(std::plus<int>(), 10);
    std::cout << f(100);
}

/**
 * stl的容器valarray没有vector那么多的算法操作功能，但它是一个更适合于进行运算的容器
 */
void std_valarray_test() {
    using std::valarray;
    valarray<int> arr1{1, 2, 3, 4, 5};
    valarray<int> arr2{3, 3, 3, 3, 3};
    valarray<int> result(5);
    std::ostream_iterator<int, char> out(std::cout, " ");
#define _out std::copy(std::begin(result),std::end(result),out)

    result = arr1 * 2;
    std::cout << "arr * 2 = ";
    _out;

    result = arr1 + arr2;
    std::cout << "\narr1 + arr2 = ";
    _out;

    result = arr1 * arr2;
    std::cout << "\narr1 * arr2 = ";
    _out;

    result = arr1.apply([](int i) { return 2 * i; });
//    result=arr1.apply(std::bind1st(std::plus<int>(),10));//应该可行的
    std::cout << "\narr1.apply(lambda) = ";
    _out;

    result = std::pow(arr1, 2);
    std::cout << "\npow(arr1,2) = ";
    _out;

    std::copy(std::begin(arr1), std::end(arr1), std::begin(result));
    std::sort(std::begin(result), std::end(result), std::greater<int>());
    std::cout << "\narr1 sort result:";
    _out;

    valarray<bool> r = arr1 > 3;
    std::transform(std::begin(r), std::end(r), std::begin(result), [](bool b) { return int(b); });
    std::cout << "\narr1 > 3 : ";
    _out;

    result[std::slice(1, 2, 2)] = 2;
    std::cout << "\nslice(1,2,2) : ";
    _out;
}

/**
 * 接受initializer_list传参的函数
 * @param inputs
 * @return
 */
double sum(std::initializer_list<double> inputs){
    static double total=0;
    std::for_each(inputs.begin(),inputs.end(),[](double d){total+=d;});
    return total;
}

void std_initializer_list_test(){
    std::initializer_list<double > d={1,2,3,4,5,6};
    // sum({1,2,3,4,5,6}); //等价
    std::cout<<sum(d);
}

void std_sort_test(){

}

#endif //STD_STD_ALGORITHM_TEST_H
