#include "ShmSource.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace ofx {
namespace piMapper {

using uchar = unsigned char;

// -----------------------------------------------------------------------------

ShmSource::ShmSource()
{
    name = "glmixer";
    loadable = false;
    loaded = false;
    type = SourceType::SOURCE_TYPE_SHM;
    texture_.reset(new ofTexture);

    try {
        segment_.reset(new managed_shared_memory(open_only, "glmtexture"));
    } catch (boost::interprocess::interprocess_exception ex)
    {
        ofLogWarning("ShmSource") << "Reading SHM glmtexture failed: "
                                 << ex.what();
    }
}

// -----------------------------------------------------------------------------

ShmSource::~ShmSource()
{
    texture_.reset();
}

// -----------------------------------------------------------------------------

void ShmSource::onAppUpdate(ofEventArgs & args)
{
    if (segment_)
    {
        shm_matrix_         = segment_->find<uchar> ("tex");
        shm_bytes_per_line_ = segment_->find<size_t> ("bpl");
        shm_index_          = segment_->find<size_t> ("index");
        shm_width_          = segment_->find<size_t> ("width");
        shm_height_         = segment_->find<size_t> ("height");

        auto matrix = shm_matrix_.first;
        auto bpl    = shm_bytes_per_line_.first;
        auto index  = shm_index_.first;
        auto width  = shm_width_.first;
        auto height  = shm_height_.first;

        if (matrix != nullptr && bpl != nullptr && index != nullptr
                && width != nullptr && height != nullptr)
        {
            if (texture_)
                texture_->loadData(matrix, *width, *height, GL_RGBA);
            else
                ofLogWarning("ShmSource") << "Texture is null.";

            texture = texture_.get();
        }
    }
    else
    {
        // @todo set default texture to prevent crash!
        ofLogWarning("ShmSource") << "No SHM segment found.";
    }

}

// -----------------------------------------------------------------------------

void ShmSource::addAppListeners()
{
    ofLogNotice("ShmSource") << "Adding app listeners";
    ofAddListener(ofEvents().update, this,
                   &ShmSource::onAppUpdate, OF_EVENT_ORDER_BEFORE_APP);
}

// -----------------------------------------------------------------------------

void ShmSource::removeAppListeners()
{
    ofRemoveListener(ofEvents().update, this,
                     &ShmSource::onAppUpdate, OF_EVENT_ORDER_BEFORE_APP);
}

}}
