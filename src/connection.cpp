#include <iostream>
#include <memory>
#include <sqlext.h>
#include "connection.h"

namespace {
  class EnvHolder {
  public:
    EnvHolder() : mInit(false) {
    }
    ~EnvHolder() {
      if (mInit) {
        SQLFreeHandle(SQL_HANDLE_ENV, mEnv);
      }
    }

    SQLHENV *get_env() {
      if (!mInit) {
        std::cout << "Initialise ODBC environment" << std::endl;
        SQLRETURN retVal = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &mEnv);
        if (!SQL_SUCCEEDED(retVal)) {
          return NULL;
        }

        retVal = SQLSetEnvAttr(mEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_UINTEGER);
        if(!SQL_SUCCEEDED(retVal)) {
          return NULL;
        }
        mInit = true;
      }
      else {
        std::cout << "Using existing ODBC environment" << std::endl;
      }
      return &mEnv;
    }

  private:
    bool mInit;
    SQLHENV mEnv;
  };

  std::shared_ptr<EnvHolder> env;
  SQLHENV *get_sql_env() {
    if (!env) {
      env.reset(new EnvHolder());
    }
    return env->get_env();
  }
}

Connection::Connection(std::string &connStr) : mConnected(false) {
  std::cout << "Connection()" << std::endl;

  SQLHENV *env = get_sql_env();
  if (env == NULL) {
    throw std::runtime_error("Could not allocate ODBC environment");
  }
  SQLRETURN retVal = SQLAllocHandle(SQL_HANDLE_DBC, *env, &mDB);
  if(!SQL_SUCCEEDED(retVal)) {
    throw std::runtime_error("Could not allocate database handle");
  }

  retVal = SQLDriverConnect(mDB, NULL,(SQLCHAR*)connStr.c_str(), SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);
  if(SQL_SUCCEEDED(retVal)) {
    std::cout << "Connected" << std::endl;
    mConnected = true;
  }
  else {
    throw std::runtime_error("Could not connect: " + extract_error(SQL_HANDLE_DBC));
  }
}

Connection::~Connection() {
  std::cout << "~Connection()" << std::endl;
  disconnect();
  SQLFreeHandle(SQL_HANDLE_DBC, mDB);
}

void Connection::disconnect() {
  if (mConnected == true) {
    SQLDisconnect(mDB);
    mConnected = false;
  }
}

std::string Connection::extract_error(SQLSMALLINT type) {
  std::string errors;
  SQLINTEGER i = 0;
  SQLINTEGER native;
  SQLCHAR state[7] = {0};
  SQLCHAR text[512] = {0};
  SQLSMALLINT len;
  while(SQL_SUCCEEDED(SQLGetDiagRec(type, mDB, ++i, state, &native, text, sizeof(text), &len))) {
    errors += (char *)text;
    errors += "\n";
  }
  return errors;
}

