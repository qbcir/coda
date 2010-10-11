#include <stdio.h>
#include <mysqlslave/logparser.h>

using namespace std;

int main() {

	const char *host	= "192.168.3.102";
	const char *user	= "testy";

	const char *pwd	= "testy";
	mysql::CLogParser p;
	mysql::CDatabase *db;
	
	db = p.monitor_db("test");
	db->monitor_table("t2");
	db->monitor_table("t3");
	
	
	p.set_connection_params(host, user, pwd);
	p.set_binlog_position("mysql_binary_log.000002",106, 1);

	p.connect();
//	p.request_dump("mysql_binary_log.000001",106, 1);

	p.dispatch_events();

	return 0;

}