#!/bin/bash -e

export REDSHIFT_HOST=
export REDSHIFT_PORT=
export REDSHIFT_DB=
export REDSHIFT_USERNAME=
export REDSHIFT_PASSWORD=

export AMAZONREDSHIFTODBCINI=$PWD/amazon.redshiftodbc.ini
export ODBCINI=$PWD/odbc.ini
./bin/consumer --dsn=Redshift --hostname=$REDSHIFT_HOST --port=$REDSHIFT_PORT --database=$REDSHIFT_DB --username=$REDSHIFT_USERNAME --password=$REDSHIFT_PASSWORD "$@"
