#include "ShmSource.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace ofx {
namespace piMapper {

using uchar = unsigned char;

ShmSource::ShmSource()
{
    name = "glmixer";
    loadable = false;
    loaded = false;
    type = SourceType::SOURCE_TYPE_SHM;

    try {
        segment_.reset(new managed_shared_memory(open_only, "glmtexture"));

        image_.setUseTexture(true);
        texture = &(image_.getTexture());
    } catch (boost::interprocess::interprocess_exception ex)
    {
        ofLogWarning("ShmSource") << "Reading SHM glmtexture failed: "
                                 << ex.what();
    }
}

ShmSource::~ShmSource()
{

}

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
//            cv::Mat image(cv::Size(*width, *height), CV_8UC3, matrix, *bpl);
//            cv::Mat img_rgba_cont(cv::Size(*width, *height), CV_8UC3, matrix);
//            cv::cvtColor(img_rgba_cont, frame, CV_BGR2RGBA, 4);

//            cv::Mat img_rgba_cont(cv::Size(*width, *height), CV_8UC1, matrix);

            cv::Mat img_rgba_cont(cv::Size(*width, *height), CV_8UC4, matrix);

            image_.setFromPixels(img_rgba_cont.ptr(), *width, *height);
            image_.updateTexture();

//            cv::imshow("glmixer", img_rgba_cont);
//            cv::waitKey(0);
        }
    }
    else
    {
        // @todo set default texture to prevent crash!
        ofLogWarning("ShmSource") << "No SHM segment found.";
    }

}

void ShmSource::addAppListeners()
{
    ofLogNotice("ShmSource") << "Adding app listeners";
    ofAddListener(ofEvents().update, this,
                   &ShmSource::onAppUpdate, OF_EVENT_ORDER_BEFORE_APP);
}

void ShmSource::removeAppListeners()
{
    ofRemoveListener(ofEvents().update, this,
                     &ShmSource::onAppUpdate, OF_EVENT_ORDER_BEFORE_APP);
}

}}
