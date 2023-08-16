#bin/bash

scp main.cpp fvds:/usr/lib/x86_64-linux-gnu/mariadb19/plugin/main.cpp

ssh fvds "mysql -e 'DROP FUNCTION IF EXISTS faker;'
service mysqld restart
rm -f /usr/lib/x86_64-linux-gnu/mariadb19/plugin/faker.so
g++ -shared -I/usr/include/mysql -o /usr/lib/x86_64-linux-gnu/mariadb19/plugin/faker.so /usr/lib/x86_64-linux-gnu/mariadb19/plugin/main.cpp
mysql -e 'CREATE FUNCTION faker RETURNS string SONAME '\''faker.so'\'';'"

