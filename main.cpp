#include <getopt.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include "bits/time.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudaimgproc.hpp>

#include <opencv2/xfeatures2d/cuda.hpp>
#include <opencv2/cudafeatures2d.hpp>

#include "opencv2/core/cuda.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/cudafilters.hpp"

#include "opencv2/calib3d/calib3d.hpp"


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <stdio.h>
#include <math.h>
#include <sstream>

using namespace cv;
using namespace std;

int main(int argc, const char ** argv) {


  VideoCapture video(0);
  Mat colorFrame;
  video>>colorFrame;

  int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    Size captureSize = Size( (int) video.get(CAP_PROP_FRAME_WIDTH),(int) video.get(CAP_PROP_FRAME_HEIGHT));    //Acquire input size
    VideoWriter outputWriter;


  string gst_out="appsrc ! video/x-raw, format=BGR, pixel-aspect-ratio=1/1 ! queue ! videoconvert ! video/x-raw, format=BGRx ! videoconvert ! videoconvert ! video/x-raw,format=I420 ! x264enc pass=qual quantizer=20 tune=zerolatency ! video/x-h264, stream-format=byte-stream ! rtph264pay pt=96 config-interval=1 ! application/x-rtp, media=video, encoding-name=H264 ! udpsink host=34.87.142.156 port=8004 auto-multicast=true";

  outputWriter.open(gst_out.c_str(), codec, 30, captureSize, true);

    while(waitKey(1)!=27)
    {
      video>>colorFrame;
      imshow("Image", colorFrame );
      outputWriter<<colorFrame;
    }


    outputWriter.release();
return 0;
}
