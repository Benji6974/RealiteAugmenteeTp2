#include "mainwindow.h"
#include <OpenNI.h>
#include <iostream>
#include <cstddef>
#include <vector>
#include<list>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <QApplication>
using namespace openni;

RNG rng(12345);

int main(int argc, char **argv)
{
 QApplication app(argc, argv);

    //MainWindow window;

    //window.show();

    Device device;        // Software object for the physical device i.e.

                             // PrimeSense Device Class

   VideoStream ir;       // IR VideoStream Class Object

   VideoFrameRef irf;    //IR VideoFrame Class Object

   VideoMode vmode;      // VideoMode Object

   Status rc = STATUS_OK;

   rc = openni::OpenNI::initialize();    // Initialize OpenNI

   rc = device.open(openni::ANY_DEVICE); // Open the Device


    /*
   std::cout << "VIDEO MODE" << std::endl;
   for(int i = 0 ; i < device.getSensorInfo(SENSOR_DEPTH)->getSupportedVideoModes().getSize() ; i++)
   {
       std::cout << "X : " << device.getSensorInfo(SENSOR_DEPTH)->getSupportedVideoModes()[i].getResolutionX() << " Y : " << device.getSensorInfo(SENSOR_DEPTH)->getSupportedVideoModes()[i].getResolutionY() << std::endl;
   }
   */

   rc = ir.create(device, SENSOR_DEPTH);    // Create the VideoStream for IR

   ir.setVideoMode(device.getSensorInfo(SENSOR_DEPTH)->getSupportedVideoModes()[5]);

   rc = ir.start();                      // Start the IR VideoStream

   Mat frame;     // OpenCV Matrix Object, also used to store images
   Mat frame2;
   int h, w;               // Height and Width of the IR VideoFrame

   std::list<uint16_t*> images;
   while(true)             // Crux of this project

   {


       if(device.getSensorInfo(SENSOR_DEPTH) != NULL)

       {

           rc = ir.readFrame(&irf);        // Read one IR VideoFrame at a time

           if(irf.isValid())               // If the IR VideoFrame is valid

           {

               vmode = ir.getVideoMode();  // Get the IR VideoMode Info for this video stream.

                                           // This includes its resolution, fps and stream format.

               uint16_t* imgBuf = (uint16_t*)irf.getData();
                                           // PrimeSense gives the IR stream as 16-bit data output

               h=irf.getHeight();

               w=irf.getWidth();

               frame.create(h, w, CV_16UC1); // Create the OpenCV Mat Matrix Class Object
//               frame2.create(h, w, CV_16UC1); // Create the OpenCV Mat Matrix Class Object
               for(int i = 0 ; i < h*w ; i++)
               {
                   imgBuf[i] = ((float) imgBuf[i] / UINT16_MAX) * 255;

               }
               images.push_back(imgBuf);

               if (images.size() >3){
                       // to receive the IR VideoFrames
                    //std::cout << imgBuf[500] << std::endl;
                     images.pop_front();
                     uint16_t* imgBufMoyenne = images.front();
                     uint16_t* imgBuf2 = imgBufMoyenne;

                     uint16_t* Buf1 = images.front();
                     images.pop_front();
                     uint16_t* Buf2 = images.front();
                     images.pop_front();
                     uint16_t* Buf3 = images.front();
                     images.pop_front();

                     for(unsigned int i= 0; i< h*w;i++){
                         imgBufMoyenne[i] = (Buf1[i] + Buf2[i] + Buf3[i])/3;
                     }

                     images.push_back(Buf1);
                     images.push_back(Buf2);
                     images.push_back(Buf3);


                    for(int i = 0 ; i < h*w ; i++)
                    {
                        if(imgBufMoyenne[i] < 80 || imgBuf[i] > 200){
                            imgBufMoyenne[i] = -1;
                         }

                    }

                    //               ret,th = cv2.threshold(gray,127,255, 1);



                    memcpy(frame.data, imgBufMoyenne, h*w*sizeof(uint16_t));
//                    memcpy(frame2.data, imgBuf2, h*w*sizeof(uint16_t));




                                       // Copy the ir data from memory imgbuf -> frame.data

                                       // using memcpy (a string.h) function
                    frame.convertTo(frame, CV_8U);
                    frame2.convertTo(frame2, CV_8U);




                    int thresh = 100;
                    std::vector<std::vector<cv::Point> > contours;
                    std::vector<Vec4i> hierarchy;
                    double th = cv::threshold(frame, frame, 127, 255, 1);
                    cv::erode(frame, frame, Mat());
                    cv::dilate(frame, frame, Mat());
                    cv::Mat canny_output;
                    /// Detect edges using canny
                    Canny( frame, canny_output, thresh, thresh*2, 3 );
                    /// Find contours
                    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

                    /// Draw contours
                    Mat drawing = Mat::zeros( canny_output.size(), CV_8U);

                    int sizemax = 0;
                    int imax = 0;

                    for( int i = 0; i< contours.size(); i++ )
                    {
                        if(contours[i].size()>sizemax){
                            sizemax = contours[i].size();
                            imax = i;

                        }


                    }

                    Scalar color = Scalar(255,255,255);
                    drawContours( drawing, contours, imax, color, 2, 8, hierarchy, 0, Point() );







                    namedWindow("ir", 1);       // Create a named window

                    imshow("ir", frame);        // Show the IR VideoFrame in this window
                    imshow("Contours", drawing);

               }


               char key = cv::waitKey(10);

               if(key==27) break;          // Escape key number

           }

       }

   }

   //--------Safe closing--------//

   ir.stop();                              // Stop the IR VideoStream

   ir.destroy();

   device.close();          // Close the PrimeSense Device

   cv::destroyAllWindows();


   return app.exec();




}





