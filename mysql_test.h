//
// Created by zhangjun on 21-3-1.
//

#ifndef STD_MYSQL_TEST_H

#include "mysql_connection.h"
#include "mysql_driver.h"
#include "cppconn/driver.h"
#include "cppconn/metadata.h"

#define STD_MYSQL_TEST_H

using namespace sql;

int execute(){
    Driver *driver = get_driver_instance();
    Connection *connection = driver->connect("tcp://127.0.0.1:3306", "root", "123");
    std::cout << connection->getAutoCommit() << std::endl;
    std::cout<< connection->getMetaData()->getMaxConnections();
    return 1;
}

#endif //STD_MYSQL_TEST_H
