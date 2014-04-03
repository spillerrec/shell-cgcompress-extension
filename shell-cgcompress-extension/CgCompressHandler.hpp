#pragma once
#include "ZipHandler.hpp"

class CgCompressHandler : public ZipHandler {
protected:
	virtual std::string mimetype() const { return "image/openraster"; }

	virtual bool isThumbnail( std::string filename ) const 
		{ return filename.find( "Thumbnails/thumbnail." ) == 0; }

	virtual bool isMeta( std::string filename ) const 
		{ return filename == "stack.xml"; }
	
	void readMeta( std::string xml );
};

