//g++ -std=c++0x test.cpp -lX11 `pkg-config --cflags opencv` `pkg-config --libs opencv` -o main
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <unistd.h>
#include <string>
#include <time.h>
#include <iostream>
#include <bits/stdc++.h> 


using namespace std;
using namespace cv;

struct ScreenShot
{
    ScreenShot(int x, int y, int width, int height):
        x(x),
        y(y),
        width(width),
        height(height)
    {
        display = XOpenDisplay(nullptr);
        root = DefaultRootWindow(display);

        init = true;
    }

    void operator() (Mat& cvImg)
    {
        if(init == true)
            init = false;
        else
            XDestroyImage(img);

        img = XGetImage(display, root, x, y, width, height, AllPlanes, ZPixmap);

        cvImg = Mat(height, width, CV_8UC4, img->data);
    }

    ~ScreenShot()
    {
        if(init == false)
            XDestroyImage(img);

        XCloseDisplay(display);
    }

    Display* display;
    Window root;
    int x,y,width,height;
    XImage* img;

    bool init;
};


// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

int main(int argc, char** argv)
{
	// int iter = atoi(argv[1]); // Number of frames to be saved

    ScreenShot screen(65,55,1000,700); // Edit the Rectangle coordinates here

    Mat img;

    
    while(true)
    {
    	screen(img);
    	// cvtColor(img, img, CV_BGR2RGB);

    	string path = "./folder/"+(currentDateTime())+".jpg";
    	std::cout<<path<<std::endl;
	    // writer<<img;

	    imwrite(path, img);

	    usleep(300000);
	}
	return 0;
}


// Scrapped 
/*
// VideoWriter writer;
    // int codec = CV_FOURCC('M', 'J', 'P', 'G');  // select desired codec (must be available at runtime)
    // double fps = 125.0;                          // framerate of the created video stream
    // string filename = "./live.avi";             // name of the output video file
    // writer.open(filename, codec, fps, Size(320,240), true);
 //    cout<<"Press 'Ctrl+C' to close program"<<endl;
 */