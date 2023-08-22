#This is a Faker UDF for MySQL

##Compiling 
Run this to compile a UDF for your mysql
(sometimes requires to install libmysqlclient/libmysqlclient-dev/libmariadb-dev etc)
```
g++ -fPIC -shared -I/usr/include/mysql -o faker.so main.cpp
```
 
Then move faker.so to mysql plugin dir
(mysql> show variables like '%plugin_dir%'; OR check your my.cnf file)
 
Then add function to mysql
```
mysql "DROP FUNCTION IF EXISTS faker;"
mysql "CREATE FUNCTION faker RETURNS string SONAME 'faker.so';"
```
 
##Usage
```
mysql "select faker("TYPE");"
```
Where 'type' is one of this:
* name
	will return a random name
* lastname
	will return a random lastname
* age
	will return a random age between 1 and 90
* date
	will return a random date between 1900.1.1 and 2100.12.31
* email
	will return a random email in this format = Name.Lastname@MAIL_SERVICE
* phone
	will return a random phone number in format = +COUNTRY_CODE9999999999
* address
	will return a random address in format = HOUSE_NUMBER STREET, CITY
* job
	will return a random job name
* text
	will return a 70 random words separated in sentences by 6 words
* longtext
	will return a 400 random words separated in sentences by 6 words

