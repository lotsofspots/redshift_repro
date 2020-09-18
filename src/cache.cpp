#include <iostream>
#include <map>
#include <openssl/md5.h>
#include <stdio.h>
#include "cache.h"
#include "connection.h"

namespace {
  class Cache {
  public:
    Cache() {
      std::cout << "Cache()" << std::endl;
    }

    std::shared_ptr<Connection> getConnection(std::string &connStr) {
      unsigned char result[MD5_DIGEST_LENGTH];
      MD5((unsigned char*)connStr.c_str(), connStr.size(), result);

      std::string tag;
      for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        char buffer[3] = {0};
        snprintf(buffer, sizeof(buffer), "%02x", result[i]);
        tag += buffer;
      }

      if (mCache.find(tag) != mCache.end()) {
        return mCache[tag];
      }
      else {
        mCache[tag].reset(new Connection(connStr));
        return mCache[tag];
      }
    }

    ~Cache() {
      std::cout << "~Cache()" << std::endl;
    }

  private:
    std::map<std::string, std::shared_ptr<Connection>> mCache;
  };

  Cache &getCache() {
    static Cache cache;
    return cache;
  }
}

std::shared_ptr<Connection> getConnection(std::string &connStr) {
  return getCache().getConnection(connStr);
}
