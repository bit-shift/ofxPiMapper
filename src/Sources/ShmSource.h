#pragma once

#include <boost/interprocess/managed_shared_memory.hpp>

#include "ofxCvColorImage.h"

#include "BaseSource.h"

namespace ofx {
namespace piMapper {

using namespace boost::interprocess;

using shm_uchar = std::pair<uchar*, managed_shared_memory::size_type>;
using shm_size_t = std::pair<size_t*, managed_shared_memory::size_type>;

class ShmSource : public BaseSource {

	public:
        ShmSource();
        ~ShmSource();

        void onAppUpdate(ofEventArgs & args);

        void addAppListeners();
        void removeAppListeners();

    private:
        ofxCvColorImage image_;

        shm_uchar   shm_matrix_;
        shm_size_t  shm_index_;
        shm_size_t  shm_bytes_per_line_;
        shm_size_t  shm_width_;
        shm_size_t  shm_height_;

        std::unique_ptr<managed_shared_memory> segment_;
        std::shared_ptr<ofTexture> texture_;

};

} // namespace piMapper
} // namespace ofx
