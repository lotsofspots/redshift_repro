#ifndef CACHE_H_INCLUDED
#define CACHE_H_INCLUDED

#include <memory>

class Connection;

std::shared_ptr<Connection> getConnection(std::string &connStr);

#endif /* CACHE_H_INCLUDED */
