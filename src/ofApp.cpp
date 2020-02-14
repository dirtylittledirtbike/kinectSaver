#include "ofApp.h"


void ofApp::setup()
{
    ofBackground(80);

    // Open the default connect.
    vector <ofxKinectV2::KinectDeviceInfo> deviceList = ofxKinectV2().getDeviceList();
    
    // Check to see if there is a KinectV2 attached.
    if (deviceList.size() > 0)
    {
        std::cout<< "Success: Kinect V2 found" << std::endl;
    } else {
        std::cerr<< "Failure: No Kinect V2 found" << std::endl;
        return;
    }
    
    // Reset min/max distances (as per ofxKinectV2).
    //    kinect.params.getFloat("minDistance").set(1200);
    //    kinect.params.getFloat("maxDistance").set(12000);
    
    kinect.open(deviceList[0].serial);
    
    int width = kinect.getRegisteredPixels().getWidth();
    int height = kinect.getRegisteredPixels().getHeight();
    
//    rgbTexture.allocate(width, height, OF_PIXELS_RGB);
    
    

}


void ofApp::update()
{
    kinect.update();
    
    
    if (kinect.isFrameNew())
    {
        rgbPixels = kinect.getRegisteredPixels();
        
       // rgbPixels.resize(640, 360);
        rgbTexture.loadData(rgbPixels);
        
        if (takeSnapshot)
        {
            std::string timestamp = ofGetTimestampString();
            ofSaveImage(kinect.getRegisteredPixels(), timestamp + ".png");
            
            ofJson json;            
            json["width"] = kinect.getRawDepthPixels().getWidth();
            json["height"] = kinect.getRawDepthPixels().getHeight();
            std::vector<float> data(kinect.getRawDepthPixels().getData(),
                                    kinect.getRawDepthPixels().getData() + kinect.getRawDepthPixels().size());
            json["data"] = data;
            ofSaveJson(timestamp + ".json", json);
            
            takeSnapshot = false;
        }
    }
}


void ofApp::draw()
{
    
    rgbTexture.draw(0, 0);
    
}


void ofApp::keyPressed(int key)
{
    if (key == ' ')
    {
        takeSnapshot = true;
    }
}
