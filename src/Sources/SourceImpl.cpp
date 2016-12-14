#include <SourceImpl.h>

#include <ofImage.h>

#include <Helper.h>

namespace ofx {
namespace piMapper {
namespace source {

using namespace std;

// ----------------------------------------------------------------------------

#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
ImageSource::ImageSource(const string& filename) :
    image_(new ofImage(filename)),
    texture_(image_->getTexture()) 
{
}
#else
ImageSource::ImageSource(const string& filename) :
    image_(new ofImage(filename)),
    texture_(image_->getTextureReference())
{
}
#endif

void ImageSource::draw(const ofMesh& mesh) const
{
    ofLogNotice("ImageSource") << "draw()";
}

const string& ImageSource::id() const
{
    return path_;
}

const size_t ImageSource::width() const
{
    return size_t{0};
}

const size_t ImageSource::height() const
{
    return size_t{0};
}

// ----------------------------------------------------------------------------

FboSource::FboSource(const string& name) :
    name_(name)
{
}

const string& FboSource::id() const
{
    return name_;
}

void FboSource::draw(const ofMesh& mesh) const
{
    ofLogNotice("FboSource") << "draw()";
}

void FboSource::update()
{
    ofLogNotice("FboSource") << "update()";
}

const size_t FboSource::width() const
{
    return size_t{0};
}

const size_t FboSource::height() const
{
    return size_t{0};
}

}}}