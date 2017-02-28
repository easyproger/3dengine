#ifndef XCACHE_H__
#define XCACHE_H__

#include "Mesh.h"
#include <map>
class XCache
{
public:
	XCache(void);
	void addCache(const char*path,int index,Mesh*mesh);
	~XCache(void);
private:

	std::map<std::string,std::vector<Mesh*>> _cache_meshs;

};

#endif