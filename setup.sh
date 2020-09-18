#!/bin/bash -e
rm -rf $PWD/opt
wget https://s3.amazonaws.com/redshift-downloads/drivers/odbc/1.4.17.1000/AmazonRedshiftODBC-64-bit-1.4.17.1000-1.x86_64.rpm
rpm2cpio AmazonRedshiftODBC-64-bit-1.4.17.1000-1.x86_64.rpm | cpio -idmv

echo "[Redshift]" > odbc.ini
echo "Driver=$PWD/opt/amazon/redshiftodbc/lib/64/libamazonredshiftodbc64.so" >> odbc.ini
echo "Threading=1" >> odbc.ini

echo "[Driver]" > amazon.redshiftodbc.ini
echo "ErrorMessagesPath=$PWD/opt/amazon/redshiftodbc/ErrorMessages" >> amazon.redshiftodbc.ini
echo "SwapFilePath=$PWD" >> amazon.redshiftodbc.ini

mkdir bin
mkdir lib
