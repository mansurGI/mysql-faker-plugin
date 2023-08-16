#include <mysql.h>
#include <string>
#include <ctime>
#include <vector>
	
extern "C" bool faker_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
  return false;
}

extern "C" void faker_deinit(UDF_INIT *initid);

extern "C" char *faker(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error) {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  std::vector<std::string> names = {"Jhon", "Steve", "Tatiana", "Kelvin", "Marry", "Gwen"};
  
  std::string name = names[std::rand() % names.size()];
		
  name.copy(result, name.size());
  *length = name.size();

  return result;
}

