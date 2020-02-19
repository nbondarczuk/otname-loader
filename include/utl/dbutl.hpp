#ifndef __DBUTL_HPP__
#define __DBUTL_HPP__

#include <string>

using namespace std;

inline void valid_env_var(const char* name) {
	if (!name) {
		string message("USed empty env variable name: ");
		throw logic_error(message + name);		
	}
	
	const char* val = getenv(name);
	if (!val) {
		string message("Misisng env variable: ");
		throw logic_error(message + name);
	}
}

inline void valid_db_env() {
	valid_env_var("ORACLE_USER");
	valid_env_var("ORACLE_PASSWD");
	valid_env_var("ORACLE_DB");
}

#endif  // __DBUTL_HPP__
