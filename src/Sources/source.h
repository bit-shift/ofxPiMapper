#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include <ofMesh.h>
#include <ofImage.h>

namespace ofx {
namespace piMapper {
namespace drawing {

using namespace std;

//-----------------------------------------------------------------------------
// Concept-based polymorphism for input sources
//-----------------------------------------------------------------------------

class source {
public:
    source() = default;
    virtual ~source() = default;
    source(source const&) = delete;
    source& operator = (source const& ) = delete;
    
    virtual const string& id() const = 0;
    virtual void draw(const ofMesh& ) const = 0;
    virtual const size_t width() const = 0;
    virtual const size_t height() const = 0;
};

template<class T>
class source_model : public source {
public:
    typedef T model_type;
    
    source_model(T model) : model_(move(model)) { }

    const string& id() const
    {
        return model_.id();
    }
    
    void draw(const ofMesh& mesh) const 
    {
        model_.draw(mesh);
    }   
    
    const size_t width() const
    {
        return model_.width();
    }
    
    const size_t height() const
    {
        return model_.height();
    }

    ~source_model() = default;

private:
    T model_;
};

template<class T>
class source_forwarder {
public:
    source_forwarder(T item) : item_(move(item)) { }
    
    void draw(const ofMesh& mesh) const 
    {
        item_->draw(mesh);
    }

    const string& id() const 
    {
        return item_->id();
    }

private:
    T item_;
};

}}}