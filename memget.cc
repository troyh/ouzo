#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <libmemcached/memcached.h>

#include "mem.h"

using namespace std;

int main(int argc, char* argv[])
{
	memcached_st st;
	memcached_create(&st);
	
	char servers_str[]="localhost:21201";
	memcached_server_st* servers=memcached_servers_parse(servers_str);
	memcached_server_push(&st, servers);
	memcached_server_list_free(servers);
	memcached_behavior_set(&st, MEMCACHED_BEHAVIOR_BINARY_PROTOCOL, 0);
	
	string key=argv[1];

	size_t vallen;
	uint32_t flags;
	memcached_return r;
	char* p=memcached_get(&st,key.c_str(),key.length(),&vallen,&flags,&r);
	docid_list docids(p,vallen);
	
	switch (r)
	{
	case MEMCACHED_SUCCESS:
		cout << key << ":";
		for(size_t i = 0; i < docids.count(); ++i)
		{
			cout << docids.get(i) << ',';
		}
		cout << endl;
		break;
	default:
		cout << "Error: " << memcached_strerror(&st,r) << endl;
		break;
	}

	free(p);
	
	return 0;
}