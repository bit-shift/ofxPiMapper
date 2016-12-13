#include <Source.h>

#include <ofTexture.h>

#include <Helper.h>

namespace ofx {
namespace piMapper {
namespace source {

using namespace std;

ImageSource::ImageSource(const string& filename) :
    image_(new ofImage())
{
}

void ImageSource::draw(const ofMesh& mesh) const
{
    ofLogNotice("ImageSource") << "drawing...";
}

const size_t ImageSource::width()
{
    return size_t{0};
}

const size_t ImageSource::height()
{
    return size_t{0};
}

}
}
}