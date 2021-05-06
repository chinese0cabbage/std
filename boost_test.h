//
// Created by zhangjun on 21-4-10.
//

#ifndef STD_BOOST_TEST_H

#include <iostream>
#include "boost/any.hpp"
#include "boost/program_options.hpp"
#include "boost/program_options/errors.hpp"
#include "boost/variant.hpp"

#define STD_BOOST_TEST_H

namespace opt=boost::program_options;

void terminalOption(int argc, char *argv[]) {
    opt::options_description desc("All options");
    desc.add_options()
            ("apples,a", opt::value<int>()->default_value(10), "apples that you have")
            ("oranges,o", opt::value<int>(), "oranges that you have")
            ("name,n", opt::value<std::string>(), "your name")
            ("help", "produce help message");
    opt::variables_map vm;
    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    opt::notify(vm);
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return;
    }
    try {
        opt::store(opt::parse_config_file<char>("apples_oranges.cfg", desc), vm);
    } catch (const opt::reading_file &e) {
        std::cout << "Failed to open file 'apples_oranges.cfg':" << e.what();
    }
    opt::notify(vm);
    if (vm.count("name")) {
        std::cout << "Hi," << vm["name"].as<std::string>() << "!\n";
    }
    std::cout << "Fruits count:" << vm["apples"].as<int>() + vm["oranges"].as<int>() << std::endl;
    return;

}

void try_boost_variant() {
    typedef boost::variant<boost::blank, int, const char *, std::string> my_var_t;
    std::vector<my_var_t> some_values;
    some_values.push_back(10);
    some_values.push_back("hello there");
    some_values.push_back(std::string("wow!"));
    std::string &s = boost::get<std::string &>(some_values.back());
    some_values.pop_back();
    s += "that is great!\n";
    std::cout << s;
    my_var_t var;
    if (var.which() == 0) {
        std::cout << "var is empty\n";
    } else {
        std::cout << var;
    }
    var = some_values.back();
    some_values.pop_back();
    if (var.which() == 0) {
        std::cout << "const char * is empty\n";
    } else {
        std::cout << boost::get<const char *>(var) << "\n";
    }
    var = some_values.back();
    some_values.pop_back();
    if (var.which() == 0) {
        std::cout << "int is empty\n";
    } else {
        std::cout << boost::get<int>(var);
    }
}

typedef boost::any cell_t;
typedef std::vector<cell_t> db_row_t;

db_row_t get_row(const char * /*query*/){
    db_row_t row;
    row.push_back(10);
    row.push_back(10.1f);
    row.push_back(std::string("hello again"));
    return row;
}

struct db_sum:public std::unary_function<boost::any,void>{
private:
    double &sum_;
public:
    explicit db_sum(double& sum):sum_(sum){}

    void operator()(const cell_t& value){
        const std::type_info& ti=value.type();
        if(ti== typeid(int)){
            sum_+=boost::any_cast<int>(value);
        } else if(ti== typeid(float)){
            sum_+=boost::any_cast<float>(value);
        }
    }
};

int run(){
    db_row_t row=get_row("Query:Give me some row,please.");
    double res=0.0;
    std::for_each(row.begin(),row.end(),db_sum(res));
    std::cout<<"Sum of artithmetic types in database row is:"<<res<<std::endl;
    return 0;
}

#endif //STD_BOOST_TEST_H
