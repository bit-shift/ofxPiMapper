#pragma once

#include <ofTexture.h>
#include <ofMesh.h>

namespace ofx {
namespace piMapper {
namespace drawing {

using namespace std;

// ----------------------------------------------------------------------------

struct image_source {
    image_source(const string& filename) :
    #if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0     
        image_(new ofImage(filename)),
        texture_(image_->getTexture()),
        path_(filename) {}
    #else
        image_(new ofImage(filename)),
        texture_(image_->getTextureReference()),
        path_(filename) {}
    #endif
    image_source(image_source&&) = default;

    void draw(const ofMesh& mesh) const
    {
        ofLogNotice("ImageSource") << "draw()";
    }

    const string& id() const
    {
        return path_;
    }

    const size_t width() const
    {
        return 0;
    }

    const size_t height() const
    {
        return 0;
    }

private:
    unique_ptr<ofImage> image_;
    ofTexture& texture_;
    string path_;    
};

// ----------------------------------------------------------------------------

class video_source {
    video_source(const string& filepath) : filepath_(filepath) {}
    video_source(video_source&&) = default;

    void draw(const ofMesh& mesh) const
    {

    }

private:
    string filepath_;
    unique_ptr<ofTexture> texture_;
};

// ----------------------------------------------------------------------------

struct fbo_source {
    fbo_source(const string& name) : name_(name) {}
    fbo_source(fbo_source&&) = default;

    const string& id() const
    {
        return name_;
    }

    void draw(const ofMesh& mesh) const
    {
        ofLogNotice("FboSource") << "draw()";
    }

    void update()
    {
        ofLogNotice("FboSource") << "update()";
    }

    const size_t width() const
    {
        return 0;
    }

    const size_t height() const
    {
        return 0;
    }

private:
    string name_;
    unique_ptr<ofTexture> texture_;
};

// ----------------------------------------------------------------------------

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