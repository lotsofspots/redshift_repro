#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include "cache.h"

namespace {
  char toLower(unsigned char c) {
    return std::tolower(c);
  }

  std::string to_lower(const std::string &input) {
    std::string lower(input);
    std::transform(lower.begin(), lower.end(), lower.begin(), toLower);
    return lower;
  }
}

int main(int argc, char **argv) {
  std::string dsn;
  std::string driver;
  std::string hostname;
  std::string port;
  std::string database;
  std::string username;
  std::string password;

  for (int i = 0; i < argc; ++i) {
    if (strstr(argv[i], "--") == argv[i]) {
      char *equals = strchr(argv[i]+2, '=');
      std::string key(argv[i]+2, equals - (argv[i]+2));
      key = to_lower(key);
      std::string value(equals+1);
      if (value.at(0) == '"') {
        value = value.substr(1,value.length()-2);
      }

      if (key == "dsn") {
        dsn = value;
      }
      else if (key == "driver") {
        driver = value;
      }
      else if (key == "hostname") {
        hostname = value;
      }
      else if (key == "port") {
        port = value;
      }
      else if (key == "database") {
        database = value;
      }
      else if (key == "username") {
        username = value;
      }
      else if (key == "password") {
        password = value;
      }
      else {
        std::cout << "Unrecognised parameter: " << key << std::endl;
        return EXIT_FAILURE;
      }
    }
  }

  if ((dsn.empty() && driver.empty()) || hostname.empty() || port.empty() || database.empty() || username.empty() || password.empty()) {
    std::cout << "Usage: " << argv[0] << " --dsn=dsn --hostname=hostname --port=port --database=database --username=username --password=password" << std::endl;
    return EXIT_FAILURE;
  }

  std::string connStr = (!dsn.empty() ? "DSN=" + dsn : "Driver=" + driver) + ";SERVER=" + hostname + ";PORT=" + port + ";DATABASE=" + database + ";UID=" + username + ";PWD=" + password;

  try {
    getConnection(connStr);
  }
  catch (std::runtime_error &error) {
    std::cout << error.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
