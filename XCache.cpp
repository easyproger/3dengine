#include "XCache.h"


XCache::XCache(void)
{

}


void XCache::addCache(const char*path,int index,Mesh*mesh) {

	if (_cache_meshs[path].size() <= index) {
		_cache_meshs[path].resize(index);
	}

	_cache_meshs[path][index] = mesh;
}


XCache::~XCache(void)
{
}
