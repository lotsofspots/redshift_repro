#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

#include <sql.h>

class Connection {
public:
  Connection(std::string &connStr);
  ~Connection();
  void disconnect();
private:
  std::string extract_error(SQLSMALLINT type);
  bool mConnected;
  SQLHDBC mDB;
};

#endif /* CONNECTION_H_INCLUDED */
