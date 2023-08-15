This is a Faker UDF for MySQL


# run this to compile a UDF for ur mysql
g++ -shared -I/usr/include/mysql -o faker.so main.cpp

# move faker.so to mysql plugin dir
# add function to mysql
mysql "DROP FUNCTION IF EXISTIS faker;"
mysql "CREATE FUNCTION faker RETURNS integer SONAME 'faker.so';"

# or use upload.sh but change server name

# use ur function
mysql "select faker();"
