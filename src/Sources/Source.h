#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include <ofMesh.h>
#include <ofImage.h>

namespace ofx {
namespace piMapper {
namespace source {

using namespace std;

//-----------------------------------------------------------------------------
// Concept-based polymorphism for input sources
//-----------------------------------------------------------------------------

class Source {
public:
    Source() = default;
    virtual ~Source() = default;
    Source(Source const&) = delete;
    Source& operator = (Source const& ) = delete;
    
    virtual const string& id() const = 0;
    virtual void draw(const ofMesh& ) const = 0;
    virtual const size_t width() const = 0;
    virtual const size_t height() const = 0;
};

template<class T>
class SourceModel : public Source {
public:
    typedef T model_type;
    
    SourceModel(T model) : model_(move(model)) { }

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

    ~SourceModel() = default;

private:
    T model_;
};

template<class T>
class SourceForwarder {
public:
    SourceForwarder(T item) : item_(move(item)) { }
    
    void draw(const ofMesh& mesh) const 
    {
        item_->draw(mesh);
    }

private:
    T item_;
};

template<typename T>
shared_ptr<T> construct(const T source)
{
    auto t = new SourceModel<T>(move(source));
    return shared_ptr<Source>(t);
} 

}}}