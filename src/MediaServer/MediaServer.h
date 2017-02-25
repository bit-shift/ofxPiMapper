//
//  MediaServer.h
//  example
//
//  Created by felix on 13.09.14.
//
//

// TODO (by Krisjanis Rijnieks 2016-06-02): Transform MediaServer into a singleton.

// TODO: move reference counting, enabling and disabling of sources
//       to source classes themselves

#pragma once

#include <boost/optional.hpp>

#include "ofMain.h"
#include "DirectoryWatcher.h"

/* Discussion: This could be the right place for a Factory Method or
 * Abstract Factory design pattern - replace all these includes with a
 * SourceFactory that can create sources with the interfaces below. 
 */
#include "BaseSource.h"
#include "ImageSource.h"
#include "VideoSource.h"
#include "FboSource.h"
#include "ShmSource.h"
#include "SourceType.h"

#define DEFAULT_IMAGES_DIR "sources/images/"
#define DEFAULT_VIDEOS_DIR "sources/videos/"

#define PI_IMAGES_DIR "/boot/ofxpimapper/sources/images"
#define PI_VIDEOS_DIR "/boot/ofxpimapper/sources/videos"

/* 
 * These you can get when you apt-get install usbmount
 */
#define USB0_IMAGES_DIR "/media/usb0"
#define USB1_IMAGES_DIR "/media/usb1"
#define USB2_IMAGES_DIR "/media/usb2"
#define USB3_IMAGES_DIR "/media/usb3"

#define USB0_VIDEOS_DIR "/media/usb0"
#define USB1_VIDEOS_DIR "/media/usb1"
#define USB2_VIDEOS_DIR "/media/usb2"
#define USB3_VIDEOS_DIR "/media/usb3"

// TODO: Change this into a externally configurable list

/*

Considering that the pi has 4 USB ports, there is a possibility to connect 4 USB flash drives. The paths to them would be 
	/media/usb0
	/media/usb1
	/media/usb2
	/media/usb3
We need all of them and we search for mp4, jpg and png files there.

*/

namespace ofx {
namespace piMapper {

using ShmSourcePtr = std::shared_ptr<ShmSource>;

class MediaServer {
	public:
		MediaServer();
		virtual ~MediaServer();

		int getNumVideos();
		int getNumImages();
		int getNumFboSources(); // new
        int getNumShmSources();
		vector <string> & getVideoPaths();
		vector <string>  getVideoNames();
		vector <string> & getImagePaths();
		vector <string>  getImageNames();
		vector <string>  getFboSourceNames(); // new
        vector <string>  getShmSourceNames();

		BaseSource * loadMedia(string & path, int mediaType);
		BaseSource * loadImage(string & path);
		void unloadImage(string & path);
		BaseSource * loadVideo(string & path);
		void unloadVideo(string & path);
		void unloadMedia(string & path);
		void clear(); // Force all loaded source unload
		BaseSource * getSourceByPath(string & mediaPath);
		string getDefaultImageDir();
		string getDefaultVideoDir();
		string getDefaultMediaDir(int sourceType);

		// Do things with FBO sources
		void addFboSource(FboSource & fboSource); // could be called also as register FBO source
		void addFboSource(FboSource * fboSource);
        void addShmSource(ShmSourcePtr shmSource);
	
        BaseSource * loadFboSource(string & fboSourceName);
		void unloadFboSource(string & fboSourceName);

        ShmSourcePtr loadShmSource(string& fboSourceName);
        void unloadShmSource(string& shmSourceName);

		// Custom events, add/remove
		ofEvent <string> onImageAdded;
		ofEvent <string> onImageRemoved;
		ofEvent <string> onVideoAdded;
		ofEvent <string> onVideoRemoved;
		ofEvent <string> onFboSourceAdded;
		ofEvent <string> onFboSourceRemoved;
        ofEvent <string> onShmSourceAdded;
        ofEvent <string> onShmSourceRemoved;
        // load/unload
		ofEvent <string> onImageLoaded;
		ofEvent <string> onImageUnloaded;
		ofEvent <string> onVideoLoaded;
		ofEvent <string> onVideoUnloaded;
		ofEvent <string> onFboSourceLoaded;
		ofEvent <string> onFboSourceUnloaded;
        ofEvent <string> onShmSourceLoaded;
        ofEvent <string> onShmSourceUnloaded;

	private:
		// Directory Watchers
		DirectoryWatcher videoWatcher;
		DirectoryWatcher piVideoWatcher;
		DirectoryWatcher usb0VideoWatcher;
		DirectoryWatcher usb1VideoWatcher;
		DirectoryWatcher usb2VideoWatcher;
		DirectoryWatcher usb3VideoWatcher;
	
		DirectoryWatcher imageWatcher;
        DirectoryWatcher piImageWatcher;
		DirectoryWatcher usb0ImageWatcher;
		DirectoryWatcher usb1ImageWatcher;
		DirectoryWatcher usb2ImageWatcher;
		DirectoryWatcher usb3ImageWatcher;
	
        vector <string> _tempImagePaths;
        vector <string> _tempVideoPaths;
    
		map <string, BaseSource *> loadedSources;
		// imageWatcher event listeners
		void handleImageAdded(string & path);
		void handleImageRemoved(string & path);
		// TODO rest of listeners
		/*
		void onImageModified();
		void onImageMovedFrom();
		void onImageMovedTo();
		*/

		// videoWatcher event listeners
		void handleVideoAdded(string & path);
		void handleVideoRemoved(string & path);
		// TODO rest of listeners
		/*
		 void onVideoModified();
		 void onVideoMovedFrom();
		 void onVideoMovedTo();
		 */

		// Add/remove event listeners.
		// Add event listeners to image and video watcher events.
		void addWatcherListeners();

		// Remove event listeners to image and video watcher events
		void removeWatcherListeners();

        boost::optional<ShmSourcePtr> findShmSource(string& name);

		// FBO source storage before they go to loadedSources
		vector <FboSource *> fboSources; // FBO source storage
        vector <ShmSourcePtr> shmSources; // SHM source storage
};

} // namespace piMapper
} // namespace ofx
