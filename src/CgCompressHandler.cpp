#include "CgCompressHandler.hpp"

//For properties
#include <propkey.h>
#include <Propvarutil.h>

//Xml parsing
#include "pugixml/pugixml.hpp"

using namespace std;

const PROPERTYKEY PKEY_Spiller_CgCompress_Animation =
	{ { 0x57E4CA6D, 0x8485, 0x484A, 0x85, 0x09, 0x2F, 0x07, 0xD6, 0x28, 0xBC, 0xB4 }, 100 };

const PROPERTYKEY PKEY_Spiller_CgCompress_Pages =
	{ { 0x5A07190B, 0xD3AE, 0x45B1, 0x8B, 0x35, 0x9D, 0x29, 0x07, 0x13, 0x96, 0x5D }, 101 };

void CgCompressHandler::readMeta( string xml ) {
	pugi::xml_document doc;
	doc.load_buffer( xml.c_str( ), xml.size( ) );
	pugi::xml_node image = doc.child( "image" );

	//Read width and height
	PROPVARIANT prop_width = { 0 };
	PROPVARIANT prop_height = { 0 };
	prop_height.vt = prop_width.vt = VT_UI4;
	prop_width.uiVal = image.attribute( "w" ).as_int( 0 );
	prop_height.uiVal = image.attribute( "h" ).as_int( 0 );
	prop_cache->SetValue( PKEY_Image_HorizontalSize, prop_width );
	prop_cache->SetValue( PKEY_Image_VerticalSize, prop_height );

	//width and height in string format
	PROPVARIANT prop_dims = { 0 };
	wstring dims_str = to_wstring( prop_width.uiVal ) + L"x" + to_wstring( prop_height.uiVal );
	InitPropVariantFromString( dims_str.c_str( ), &prop_dims );
	prop_cache->SetValue( PKEY_Image_Dimensions, prop_dims );
	//PropVariantClear( &prop_dims );

	//Read resolution
	PROPVARIANT prop_xres = { 0 };
	PROPVARIANT prop_yres = { 0 };
	prop_xres.vt = prop_yres.vt = VT_R8;
	prop_xres.dblVal = image.attribute( "xres" ).as_double( 72 );
	prop_yres.dblVal = image.attribute( "yres" ).as_double( 72 );
	prop_cache->SetValue( PKEY_Image_HorizontalResolution, prop_xres );
	prop_cache->SetValue( PKEY_Image_VerticalResolution, prop_yres );

	//Pages
	PROPVARIANT prop_pages = { 0 };
	prop_pages.vt = VT_UINT;
	auto frames = doc.child( "image" ).children( "stack" );
	prop_pages.uintVal = distance( frames.begin( ), frames.end( ) );
	prop_cache->SetValue( PKEY_Spiller_CgCompress_Pages, prop_pages );

	//Animation
	PROPVARIANT prop_animation = { 0 };
	prop_animation.vt = VT_BOOL;
	prop_animation.boolVal = (image.attribute( "loops" ).as_int( 0 ) != 0);
	prop_cache->SetValue( PKEY_Spiller_CgCompress_Animation, prop_animation );


	//TODO: save compression settings
}