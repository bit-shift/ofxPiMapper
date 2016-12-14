#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <Source.h>
#include <SourceImpl.h>

namespace ofx { namespace piMapper {

using namespace source;

TEST_CASE( "image_source returns path as id", "[image_source]" ) 
{
	string path{ "data/sources/images/image1.jpg" };
	ImageSource source{ path };
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
	using source_ptr_t = shared_ptr<ImageSource>;
	using source_fwd_t = SourceForwarder<source_ptr_t>;

	string path{ "data/sources/images/image1.jpg" };
	source_ptr_t source_ptr( new ImageSource( path ));
	source_fwd_t fwd( source_ptr );
	REQUIRE( fwd.id() == path );
}

TEST_CASE( "source_model can be created from image_source", "[source_model]" ) 
{
	string path{ "data/sources/images/image1.jpg" };
	ImageSource imageSource{ path };
	
	auto imageModel = new SourceModel<ImageSource>(move(imageSource));
	auto source = shared_ptr<Source>(imageModel);
}

}}