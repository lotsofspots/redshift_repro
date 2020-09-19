#!/bin/bash -e

# connection object
/usr/bin/g++ -fPIC -Wall -Iinclude -std=c++0x \
    src/connection.cpp \
-lodbc -shared -Wl,-soname -Wl,libconnection.so.0 -o lib/libconnection.so.0.0.0

cd lib
rm -f libconnection.so.0 && ln -s libconnection.so.0.0.0 libconnection.so.0
rm -f libconnection.so && ln -s libconnection.so.0.0.0 libconnection.so
cd ..

# connection cache
/usr/bin/g++ -fPIC -Wall -Iinclude -std=c++0x \
    src/cache.cpp \
-lssl -lcrypto -Wl,-rpath=lib -Llib -lconnection -shared -Wl,-soname -Wl,libcache.so.0 -o lib/libcache.so.0.0.0

cd lib
rm -f libcache.so.0 && ln -s libcache.so.0.0.0 libcache.so.0
rm -f libcache.so && ln -s libcache.so.0.0.0 libcache.so
cd ..

# executable consumer
/usr/bin/g++ -std=c++0x -Wall -Iinclude src/consumer.cpp -Wl,-rpath=lib -Llib -lcache -o bin/consumer
