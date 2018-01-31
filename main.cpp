#include "mainwindow.h"

#include <OpenNI.h>

#include <iostream>

#include <cstddef>

#include <opencv2/opencv.hpp>



#include <QApplication>

using namespace openni;





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

   Mat frame;              // OpenCV Matrix Object, also used to store images

   int h, w;               // Height and Width of the IR VideoFrame

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

                                           // to receive the IR VideoFrames
               //std::cout << imgBuf[500] << std::endl;


               for(int i = 0 ; i < h*w ; i++)
               {
                   imgBuf[i] = ((float) imgBuf[i] / UINT16_MAX) * 255;
               }


               memcpy(frame.data, imgBuf, h*w*sizeof(uint16_t));



                                           // Copy the ir data from memory imgbuf -> frame.data

                                           // using memcpy (a string.h) function

               frame.convertTo(frame, CV_8U);

                                           // OpenCV displays 8-bit data (I'm not sure why?)

                                           // So, convert from 16-bit to 8-bit

               namedWindow("ir", 1);       // Create a named window

               imshow("ir", frame);        // Show the IR VideoFrame in this window

               char key = waitKey(10);

               if(key==27) break;          // Escape key number

           }

       }

   }

   //--------Safe closing--------//

   ir.stop();                              // Stop the IR VideoStream

   ir.destroy();

   device.close();                         // Close the PrimeSense Device

    return app.exec();

}
