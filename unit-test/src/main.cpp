#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <source.h>
#include <source_types.h>

namespace ofx { namespace piMapper {

using namespace drawing;

TEST_CASE( "image_source returns path as id", "[image_source]" ) 
{
	string path{ "data/sources/images/image1.jpg" };
	image_source source{ path };
	REQUIRE( source.id() == path );
}

TEST_CASE( "fbo_source returns name as id", "[fbo_source]" ) 
{
	fbo_source source{ "fbo #1" };
	REQUIRE( source.id() == "fbo #1" );
}

TEST_CASE( "stream_source returns url as id", "[stream_source]" ) 
{
	stream_source source{ "url" };
	REQUIRE( source.id() == "url" );
}

TEST_CASE( "source_forwarder can be created returns path as id", "[source_forwarder]" ) 
{
	using source_ptr_t = shared_ptr<image_source>;
	using source_fwd_t = source_forwarder<source_ptr_t>;

	string path{ "data/sources/images/image1.jpg" };
	source_ptr_t source_ptr( new image_source( path ));
	source_fwd_t fwd( source_ptr );
	REQUIRE( fwd.id() == path );
}

TEST_CASE( "source_model can be created from image_source", "[source_model]" ) 
{
	using source_ptr_t = shared_ptr<source>;

	string path{ "data/sources/images/image1.jpg" };
	image_source img{ path };
	
	auto model = new source_model<image_source>(move(img));
	auto source_ptr = source_ptr_t(model);
}

}}