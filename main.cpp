#include "mysql.h"

extern "C" bool faker_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
  return false;
}

extern "C" int faker(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error) {
  return 777;
}

