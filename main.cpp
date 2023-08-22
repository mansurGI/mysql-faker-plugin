#include <mysql.h>
#include <string>
#include <random>
#include <vector>
#include <cstring>
#include <algorithm>
#include <ctime>

std::vector<std::string> types = {"name", "lastname", "age", "date", "email", "phone", "address", "company", "job", "text", "longtext"};

std::vector<std::string> name = {
	"Jhon", "Steve", "Kelvin", "Gwen", "Marry", "Tatiana",
	"Ivan", "Alexander", "Dmitry", "Olga", "Jessica",
	"Robert", "Jennifer", "Jan", "Lisa", "Markus",
	"Pierre", "Julien", "Lucas", "Mathieu", "Takashi",
	"Aiko", "Satoshi", "Kazuki", "Emilly"
};
std::vector<std::string> lastname = {
	"Wilson", "Harris", "Lewis", "Walker", "Adams", "Smith",
	"Davis", "Sokolov", "Smirnov", "Petrov", "Kuznetsov",
	"Schimdt", "Becker", "Fischer", "Wagner", "Weber",
	"Dubois", "Lambert", "Roussel", "Laurent", "Suzuki",
	"Sato", "Ito", "Nakamuru", "Tanaka", "Popov"
};
std::vector<std::string> email = {"@yahoo.com", "@mail.ru", "@gmail.com", "@haw.cy"};
std::vector<std::string> text = {
	"lorem", "ipsum", "dolor", "sit", "amet", "consectetur", "adipiscing",
	"elit", "sed", "do", "eiusmod", "tempor", "incididunt", "ut", "labore",
	"et", "dolore", "magna", "aliqua", "ut", "enim", "ad", "minim", "veniam",
	"quis", "nostrud", "exercitation", "ullamco", "laboris", "nisi", "aliquip",
	"commodo", "consequat", "duis", "aute", "irure", "dolor", "in", "reprehenderit",
	"voluptate", "velit", "esse", "cillum", "dolore", "fugiat", "nulla", "pariatur",
	"excepteur", "sint", "occaecat", "cupidatat", "non", "proident", "sunt", "culpa"
};
std::vector<std::string> city = {
	"New York", "Moscow", "Paris", "Berlin", "Rio",
	"Tokio", "Kiev", "Kazan", "Lyon", "Marseille",
	"Hamburg", "Munich", "Cologne", "Boston"
};
std::vector<std::string> street = {
	"Oak Avenue", "Pine Lane", "Lenina Avenu", "Maple Street",
	"Pushkin Prospect", "Sumida Street", "Fuji Heights", "Sakura Lane",
	"Rue de la Tour Eiffel", "Place Bellecour", "Rue de Vieux Port",
	"Alsterufer", "Schillerplatz", "Brandenburg"
};
std::vector<std::string> company = {
	"Google LLC", "Rusal OJSC", "Yahoo PLC", "Lockblock Inc.",
	"Robox Co., Ltd.", "Yokohama GK", "Kyoto TCC", "Osaka KK",
	"Gourmes SARL", "Divan SAS", "Lille EURL", "BMW GmbH",
	"Airbus UG", "Munich Zuch AG", "DLH Co. KG"
};
std::vector<std::string> job = {
	"Manager", "Writer", "Counsel", "Designer", "CEO", "Developer",
	"Financial Analyst", "Supervisor", "Scientist", "Coordinator",
	"Ambassador", "Planner", "Coach", "Pilot", "Hacker"
};
std::vector<std::string> phone = {
	"+1", "+7", "+355", "+52"
};

extern "C" bool faker_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
  if (args->arg_count != 1) {
		strncpy(message, "1 argument required!", MYSQL_ERRMSG_SIZE);
    return true;
  }

	if (std::find(types.begin(), types.end(), args->args[0]) == types.end()) {
		strncpy(message, "undefined type", MYSQL_ERRMSG_SIZE);
		return true;
	}

	if (args->args[0] == std::string("longtext")) {
		char* ptr = static_cast<char*>(std::malloc(3000));
		initid->ptr = ptr;
	}

  return false;
}

extern "C" void faker_deinit(UDF_INIT *initid) {
	std::free(initid->ptr);
}

extern "C" char *faker(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error) {
  std::random_device rd;
  std::srand(rd());

	std::string value;

	if (args->args[0] == std::string("name"))
		value = name[std::rand() % name.size()];	
	
	if (args->args[0] == std::string("lastname"))
		value = lastname[std::rand() % lastname.size()];
	
	if (args->args[0] == std::string("age"))
		value = std::to_string(1 + std::rand() % 89);

	if (args->args[0] == std::string("date")) {
		value = std::to_string(1900 + std::rand() % 200) + "-" + std::to_string(1 + std::rand() % 11) + "-" + std::to_string(1 + std::rand() % 30);
	}

	if (args->args[0] == std::string("email"))
		value = name[std::rand() % name.size()] + "." + lastname[std::rand() % lastname.size()] + email[std::rand() % email.size()];

	if (args->args[0] == std::string("phone"))
		value = phone[std::rand() % phone.size()] + std::to_string(100 + std::rand() % 899) + std::to_string(100 + std::rand() % 899)  + std::to_string(10 + std::rand() % 89) + std::to_string(10 + std::rand() % 89);

	if (args->args[0] == std::string("address"))
		value = std::to_string(1 + std::rand() % 200) + " " + street[std::rand() % street.size()] + ", " + city[std::rand() % city.size()]; 

	if (args->args[0] == std::string("job"))
		value = job[std::rand() % job.size()];
	
	if (args->args[0] == std::string("company"))
		value = company[std::rand() % company.size()];
	
	if (args->args[0] == std::string("text") || args->args[0] == std::string("longtext")) {
		int length = (args->args[0] == std::string("text")) ? 70 : 400;
		
		std::string word = text[std::rand() % text.size()];
  	word[0] = std::toupper(word[0]);
  	value += word;
    
		for (int i = 1; i < length; ++i) {
    	word = text[std::rand() % text.size()];
     	if (i % 6 == 0) {
       	word[0] = std::toupper(word[0]);
       	value += ". " + word;
     	} else { value += " " + word; }
   	}
  	value += ".";
	}

	*length = value.size();
	if (args->args[0] == std::string("longtext")) {
		value.copy(initid->ptr, value.size());
		return initid->ptr;
	}

	value.copy(result, value.size());
	return result;
}
