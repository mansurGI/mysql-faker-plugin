
# delete image 
docker rmi -f mariadb_faker_development


# delete container
docker stop database && docker rm -f database 
