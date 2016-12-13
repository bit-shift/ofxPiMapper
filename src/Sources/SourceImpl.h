#pragma once

#include <ofTexture.h>
#include <ofMesh.h>

namespace ofx {
namespace piMapper {
namespace source {

using namespace std;

class ImageSource {
public:
    ImageSource(const string& path);
    ImageSource(ImageSource&&) = default;
    
    void draw(const ofMesh& mesh) const;
    const size_t width();
    const size_t height();

private:
    unique_ptr<ofTexture> texture_;
    unique_ptr<ofImage> image_;
};

class VideoSource {
public:
    void draw(const ofMesh& mesh) const;

private:
    unique_ptr<ofTexture> texture_;
};

class FboSource {
public:
    FboSource();
    FboSource(FboSource&&) = default;

    void draw(const ofMesh& mesh) const;
    void update();
    const size_t width();
    const size_t height();

private:
    unique_ptr<ofTexture> texture_;
};

}}}