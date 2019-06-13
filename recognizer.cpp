#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <raspicam/raspicam_cv.h>

#include <iostream>
#include <ctime>
#include <fstream>
#include <map>

using namespace cv;
using namespace cv::face;
using namespace std;


int main(){

  raspicam::RaspiCam_Cv Camera;

  Camera.set(CAP_PROP_FRAME_WIDTH, 320);
  Camera.set(CAP_PROP_FRAME_HEIGHT, 240);
  //Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1 );

  map<int, string> labels;

  ifstream infile("./recognizer/labels.txt");

  int a;
  string b;
  while (infile >> a >> b){
    labels[a] = b;
  }

  if (!Camera.open()) {cerr<<"Error opening the camera"<<endl;return -1;}

  CascadeClassifier classifier;
  classifier.load("./cascades/lbpcascade_frontalface.xml");

  Ptr<LBPHFaceRecognizer> recognizer =  LBPHFaceRecognizer::create(2, 2, 7, 7, 17);
  recognizer->read("./recognizer/embeddings.xml");

  Mat windowFrame;
  namedWindow("edges", 1);
  int numframes = 0;
  time_t timer_begin,timer_end;
  time ( &timer_begin );

  for(;;){

    Mat frame;
    Camera.grab();
    Camera.retrieve(frame);
    cvtColor(frame, windowFrame, CV_BGR2GRAY);
    vector<Rect> faces;
    classifier.detectMultiScale(frame, faces, 1.2, 5);
    for(size_t i = 0; i < faces.size(); i++){
      rectangle(frame, faces[i], Scalar(0, 255, 0));
      Mat face = windowFrame(faces[i]);
      double confidence = 0.0;
      int predicted = recognizer->predict(face);
      recognizer->predict(face, predicted, confidence);
      if(labels.find(predicted) == labels.end() || confidence < 25){
         putText(frame, "Unknown", Point(faces[i].x ,faces[i].y - 5), FONT_HERSHEY_DUPLEX, 1, Scalar(0,255,0), 1);
      }else{
         putText(frame, labels[predicted], Point(faces[i].x ,faces[i].y - 5), FONT_HERSHEY_DUPLEX, 1, Scalar(0,255,0), 1);
      }
      cout << "ID: " << predicted << " | Confidence: " << confidence << endl;
    }
    imshow("edges", frame);
    numframes++;

    if(waitKey(30) >=0) break;
  }
  Camera.release();
  time ( &timer_end );
  double secondsElapsed = difftime ( timer_end,timer_begin );
  cout << "FPS:" << numframes / secondsElapsed << endl;
  return 0;
}
