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

    const string& id() const;
    const size_t width() const;
    const size_t height() const;

private:
    string path_;
    ofTexture& texture_;
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
    FboSource(const string& name);
    FboSource(FboSource&&) = default;

    void draw(const ofMesh& mesh) const;
    void update();

    const string& id() const;
    const size_t width() const;
    const size_t height() const;

private:
    string name_;
    unique_ptr<ofTexture> texture_;
};

}}}