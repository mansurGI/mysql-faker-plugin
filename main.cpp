#include "mysql.h"
#include "cstring"

extern "C" bool faker_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
  return false;
}

extern "C" char *faker(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error) {
  memcpy(result, "result string", 13);
  *length = 13;

  return result;
}

extern "C" void faker_deinit(UDF_INIT *initid);

