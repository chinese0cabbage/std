//
// Created by zhangjun on 21-2-19.
//

#ifndef STD_PRIMERPLUS_H

#include "vector"
#include "iostream"
#include "iterator"
#include "rttr/registration"

#include "algorithm"
#include "string"
#include "memory"
#include "iostream"
#define STD_PRIMERPLUS_H

namespace oo {
    class test1 {
    public:
        test1(const int a) : a(a) {}

        const int a;

        virtual void fun() = 0;
    };

    void test1::fun() {}

    class test2 : public test1 {
    public:
        test2(int a) : test1(a) {

        }

        void fun() override {
            std::cout << "!!!!!!!!!!!!!!!!!!!!!!";
        }
    };

    class test : private std::vector<int> {
        using std::vector<int>::push_back;
    };

    void execute() {
        using namespace oo;
        int a = 10;
        test2 *test21 = new test2(a);
        test1 *t = (test1 *) test21;
        t->fun();
    }
}

namespace sp {

    using ::std::string;
    using std::shared_ptr;
    using std::unique_ptr;

    string *strs[] = {new string("11111111111"), new string("2222222222222"), new string("33333333333333")};

    void shared_ptr_test() {
        shared_ptr<string> s_ptr[3] = {
                shared_ptr<string>(strs[0]),
                shared_ptr<string>(strs[1]),
                shared_ptr<string>(strs[2])
        };
        auto tmp = s_ptr[1];
        std::for_each(s_ptr, s_ptr + 3, [](shared_ptr<string> str) { std::cout << *str << "\t"; });
    }

    void unique_ptr_test() {
        unique_ptr<string> u_ptr[3] = {
                unique_ptr<string>(strs[0]),
                unique_ptr<string>(strs[1]),
                unique_ptr<string>(strs[2])
        };
        auto tmp=std::move(u_ptr[1]);//auto tmp=u_ptr[1];会报错
//        std::for_each(u_ptr, u_ptr + 3, [](unique_ptr<string> str) { std::cout << *str << "\t"; });
        std::cout<<*u_ptr[0];
        std::cout<<*u_ptr[1];//打印为空
        std::cout<<*u_ptr[2];
    }
}

namespace iterator_tt {

    void ostream_iterator_test() {
        ::std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
        ::std::vector<int >::iterator i;
        ::std::ostream_iterator<int, char> out_iter(::std::cout, " ");
        std::copy(v.rbegin(), v.rend(), out_iter);
    }

//    std::back_insert_iterator;
//    std::front_insert_iterator;
//    std::insert_iterator;
}

namespace type_tt{
    void decltype_simple_test(){
        double x;
        int n=1;
        decltype(x*n) t1=10;//t1 is double
        std::cout << t1;
        std::string str="xxxx";
        decltype(str+std::to_string(n)) s1;//s1 is string
    }

    template<typename T=int,typename U=double >
    auto decltype_fun(T t,U u)-> decltype(t*u){

    }

    /*IsOverloadOsOperator为判断数据类型是否定义了输出流函数,void_t在C++14中才存在*/
    /*type_tt::IsOverloadOsOperator<std::string>::value adjust if define <<*/

    //模板重定义
    template <typename...Ts> using void_t=void;

    template <typename T,typename =void_t <>>
            struct IsOverloadOsOperator:std::false_type{};

    template <typename T>
    struct IsOverloadOsOperator<T,void_t<decltype(*(std::ostream *) nullptr<<std::declval<T>())>
            >:std::true_type{};


    //递归解包入口函数，会自行调用以下重载
    template<typename T>
    std::ostream& print(std::ostream &out,T const &val) {
        return (out << val << " ");
    }

    template<template<typename,typename...> class TT,typename... Args>
    std::ostream& operator<<(std::ostream &out,TT<Args...> const &cont);

    //打印键值对类型
    template<typename T1,typename T2>
    std::ostream& print(std::ostream &out,std::pair<T1,T2> const &val) {
        return (out << "{" << val.first << ":" << val.second << "}");
    }

    //模板的模板参数，但参数依然为参数包，可递归解开,为了解决容器中嵌套容器的情形
    template<template<typename,typename...> class TT,typename... Args>
    std::ostream& operator<<(std::ostream &out,TT<Args...> const &cont) {
        out<<"[";
        for(auto&& elem : cont) {
            print(out, elem);
        }
        out<<"]";
        return out;
    }

    /*problem in print function,not generic*/
    //递归解包结束时调用
    template <typename T>
    void print(const T &lastArg){
        std::cout<<lastArg<<"\n";
    }

    //模板和函数参数包
    template <typename T,typename ... Types>
    void print(const T &firstArg, const Types&... args){
        if(IsOverloadOsOperator<T>::value) {
            //递归展开并打印包内的内容
            std::cout << firstArg << std::endl;/*replace cout with LOG(INFO)*/
            print(args...);
        }
    }
}

#include "map"

int execute() {
//    type_tt::print("1",std::vector<int >{1,2,3},2,42);
//    type_tt::print<int,std::vector<int >>(std::vector<int >{1,2,3});
    std::map<int,std::vector<std::pair<int ,int >>> m;
    m.insert(std::make_pair<int,std::vector<std::pair<int ,int >>>(13,std::vector<std::pair<int ,int >>{std::make_pair<int ,int >(10,20),std::make_pair<int ,int >(10,20)}));
    type_tt::print("1",m,10);
    return 1;
    //待实现：STL容器，字符串，C++基本类型，rttr可序列化的类型均可转化为字符串的模板方法
}

namespace DBFilter {
    enum ParametricKind {
        Digital,
        String,
        TimeStape
    };

    enum LogicalKind {
        NoLogical,
        LogicalAnd,
        LogicalOr,
        LogicalNot
    };

    class BaseFilter {
    public:
        std::string key;
        ParametricKind para;

        LogicalKind logicalKind = NoLogical;

        BaseFilter *logicalConnectedFilter = nullptr;

        BaseFilter() {}

        BaseFilter(const std::string &key, ParametricKind para) : key(key), para(para) {}

        virtual ~BaseFilter() {
            try {
                if (logicalConnectedFilter != nullptr) {
                    delete (logicalConnectedFilter);
                }
            }
            catch (...) {
                if (logicalConnectedFilter != nullptr) {
                    delete (logicalConnectedFilter);
                }
            }
        }

        inline BaseFilter logicalConnectFilter(BaseFilter another, LogicalKind kind) {
            this->logicalKind = kind;
            logicalConnectedFilter = &another;
            return *this;
        }

        RTTR_ENABLE()
    };

    class EqualFilter:public BaseFilter{
    public:
        bool equal = true;
        std::string value;
        EqualFilter() {}

        EqualFilter(const std::string &key, ParametricKind para) : BaseFilter(key, para) {}

        RTTR_ENABLE(BaseFilter)
    };

    class RangeFilter:public BaseFilter{
    public:
        bool includeUpper = true, includeLower = true;
        std::string upperLimit, lowerLimit;
        RangeFilter() {}

        RangeFilter(const std::string &key, ParametricKind para) : BaseFilter(key, para) {}

        RTTR_ENABLE(BaseFilter)
    };

    static std::vector<EqualFilter> createFilter(const rttr::instance &obj) {
        std::vector<EqualFilter> filters;
        auto t = obj.get_type();
        auto props = t.get_properties();
        for (auto &prop:props) {
            std::string keyType = prop.get_type().get_raw_type().get_name().data();
            if (keyType == "std::string") {
                filters.push_back(EqualFilter(prop.get_name().data(), ParametricKind::String));
            } else {
                filters.push_back(EqualFilter(prop.get_name().data(), ParametricKind::Digital));
            }
        }
        return filters;
    }

    template<class T>
    std::vector<T> getFromDB(const std::vector<BaseFilter> &filters) {
        return std::vector<T>();
    }

    RTTR_REGISTRATION {
    rttr::registration::enumeration<ParametricKind>("ParametricKind")
    (
    rttr::value("Digital", ParametricKind::Digital),
    rttr::value("String", ParametricKind::String),
    rttr::value("TimeStape", ParametricKind::TimeStape)
    );

    rttr::registration::enumeration<LogicalKind>("LogicalKind")
    (
    rttr::value("NoLogical", LogicalKind::NoLogical),
    rttr::value("LogicalAnd", LogicalKind::LogicalAnd),
    rttr::value("LogicalOr", LogicalKind::LogicalOr),
    rttr::value("LogicalNot", LogicalKind::LogicalNot)
    );

    rttr::registration::class_<BaseFilter>("BaseFilter")
    .constructor<>()(rttr::policy::ctor::as_object)
    .property("key", &BaseFilter::key)
    .property("para", &BaseFilter::para)
    .property("logicalKind", &BaseFilter::logicalKind)
    .property("logicalConnectedFilter", &BaseFilter::logicalConnectedFilter);

    rttr::registration::class_<EqualFilter>("EqualFilter")
    .constructor<>()(rttr::policy::ctor::as_object)
    .property("equal", &EqualFilter::equal)
    .property("value", &EqualFilter::value);

    rttr::registration::class_<RangeFilter>("RangeFilter")
    .constructor<>()(rttr::policy::ctor::as_object)
    .property("includeLower", &RangeFilter::includeLower)
    .property("includeUpper", &RangeFilter::includeUpper)
    .property("lowerLimit", &RangeFilter::lowerLimit)
    .property("upperLimit", &RangeFilter::upperLimit);
};
}

#endif //STD_PRIMERPLUS_H
