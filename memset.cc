#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <libmemcached/memcached.h>

#include "mem.h"

using namespace std;

int main()
{
	memcached_st st;
	memcached_create(&st);
	
	char servers_str[]="localhost:21201";
	memcached_server_st* servers=memcached_servers_parse(servers_str);
	memcached_server_push(&st, servers);
	memcached_server_list_free(servers);
	memcached_behavior_set(&st, MEMCACHED_BEHAVIOR_BINARY_PROTOCOL, 0);

	string ln;
	while (getline(cin,ln))
	{
		docid_list docids;
		
		istringstream ss(ln);
		string key;
		ss >> key;
		do
		{
			size_t docid=0;
			ss >> docid;
			if (docid)
			{
				docids.add(docid);
			}
		}
		while (ss.good());
		
		memcached_return r=memcached_set(&st,key.c_str(),key.length(),docids.ptr(),docids.ptrlen(),0,0);
		switch (r)
		{
		case MEMCACHED_SUCCESS:
			break;
		default:
			cout << "Error: " << memcached_strerror(&st,r) << endl;
			break;
		}
	}
	
	return 0;
}