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
namespace source {

using namespace std;

//-----------------------------------------------------------------------------
// Concept-based polymorphism for input sources
//-----------------------------------------------------------------------------
class CustomizableSource : public Source {
public:
    CustomizableSource() = default;
    virtual ~CustomizableSource() = default;
    CustomizableSource(Source const&) = delete;
    CustomizableSource& operator = (CustomizableSource const& ) = delete;
    
	virtual void update() = 0;
};

template<class T>
class CustomizableSourceModel : public CustomizableSource {
public:
    typedef T model_type;
    
    CustomizableSourceModel(T model) : model_(move(model)) { }

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

    ~CustomizableSourceModel() = default;

private:
    T model_;
};


}}}