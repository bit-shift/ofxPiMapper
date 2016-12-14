#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <Source.h>
#include <SourceImpl.h>

namespace ofx { namespace piMapper {

using namespace source;

TEST_CASE( "image_source returns path as id", "[image_source]" ) 
{
	ImageSource source{ "concept.img" };
	REQUIRE( source.id() == "concept.img" );
}

TEST_CASE( "fbo_source returns name as id", "[fbo_source]" ) 
{
	FboSource source{"fbo #1"};
	REQUIRE( source.id() == "fbo #1" );
}

TEST_CASE( "source_forwarder can be created", "[source_forwarder]" ) 
{
	using source_ptr_t = shared_ptr<ImageSource>;
	using source_fwd_t = SourceForwarder<source_ptr_t>;

	source_ptr_t source_ptr(new ImageSource("image.png"));
	source_fwd_t fwd(source_ptr);
}

TEST_CASE( "source_model can be created from image_source", "[source_model]" ) 
{
	ImageSource imageSource{"concept.img"};
	
	auto imageModel = new SourceModel<ImageSource>(move(imageSource));
	auto source = shared_ptr<Source>(imageModel);
}

}}