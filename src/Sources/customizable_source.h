#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include <ofMesh.h>
#include <ofImage.h>

#include <Source.h>

namespace ofx {
namespace piMapper {
namespace drawing {

using namespace std;

//-----------------------------------------------------------------------------
// Concept-based polymorphism for input sources
//-----------------------------------------------------------------------------
class customizable_source : public Source {
public:
    customizable_source() = default;
    virtual ~customizable_source() = default;
    customizable_source(Source const&) = delete;
    customizable_source& operator = (customizable_source const& ) = delete;
    
	virtual void update() = 0;
};

template<class T>
class customizable_sourceModel : public customizable_source {
public:
    typedef T model_type;
    
    customizable_source_model(T model) : model_(move(model)) { }

    const string& id() const
    {
        return model_.id();
    }

    void draw(const ofMesh& mesh) const 
    {
        model_.draw(mesh);
    }

    void update()
    {
        model_.update();
    }
    
    const size_t width() const
    {
        return model_.width();
    }
    
    const size_t height() const
    {
        return model_.height();
    }

    ~customizable_source_model() = default;

private:
    T model_;
};


}}}