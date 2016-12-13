#pragma once

#include <ofMesh.h>
#include <ofTexture.h>

namespace ofx {
namespace piMapper {
namespace source {

inline void bounded_draw(const ofTexture& texture, const ofMesh& mesh) 
{
    texture.bind();
    mesh.draw();
    texture.unbind();
}

}}}

