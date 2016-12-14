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
    unique_ptr<ofImage> image_;
    ofTexture& texture_;
    string path_;    
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

struct stream_source {
    stream_source(const string& url) : url_(url) {}
    stream_source(stream_source&&) = default;

    void draw(const ofMesh& mesh) const {

    }

    const string& id() const {
        return url_;
    }

    const size_t width() const {
        return 0;
    }

    const size_t height() const {
        return 0;
    }

private:
    string url_;
};

}}}