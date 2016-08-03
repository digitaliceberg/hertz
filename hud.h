#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <unistd.h>

using namespace cv;
using namespace std;


class Hud
{

	public: int mark_target(Mat img)
	{
		int average, total;
		Hud marker;
		Mat imggray;
		vector<Rect> detected;
		cvtColor(img, imggray, COLOR_BGR2GRAY);
        	CascadeClassifier search_cascade;
        	search_cascade.load("xml/person.xml");
        	cout << "DEBUG: Started pattern recognition." << endl;
		//Resize image for processing
		Size canvas = img.size();
		Size size((canvas.width/2),(canvas.height/2));
                resize(imggray,imggray,size);
        	search_cascade.detectMultiScale(imggray, detected, 1.1, 5);
        	cout << "DEBUG: Found " << detected.size() << " entities in this picture." << endl;
		//Draw markers around objects
        	for (int i = 0; i < detected.size(); i++)
        	{
                	int xa = detected[i].x;
                	int ya = detected[i].y;
                	int xb = (detected[i].x) + (detected[i].width);
                	int yb = (detected[i].y) + (detected[i].height);
                	marker.draw_square(img, Point(xa*2,ya*2),Point(xb*2,yb*2), Scalar(0,215,255));
        	}
		return 0;
	}

	public: int waitforpress()
	{
    	char key;
    	do{
    	key = waitKey(0);
	    }while(key != 'q');
		return 0;
	}

        public: int draw_crosshair(Point loc, Mat img, Scalar color)
        {
                Size canvas = img.size();
                int x = loc.x;
                int y = loc.y;
                if(canvas.height > 10 && canvas.width > 10)
                {
                        line(img, Point(x,y), Point(x,y), color, 1, 8);//Center dot
                        line(img, Point(x-17,y), Point(x-3,y), color, 1, 8);//Left line
                        line(img, Point(x+17,y), Point(x+3,y), color, 1, 8);//Right line
                        line(img, Point(x,y-17), Point(x,y-3), color, 1, 8);//Up line
                        line(img, Point(x,y+17), Point(x,y+3), color, 1, 8);//Down line
                        cout << "DEBUG: Crosshair drawn at X: " << x << " Y: " << y << endl;
                }
                else
                {
                        cout << "DEBUG: Image too small to draw crosshair" << endl;
                }
                return 0;
        }

	public: int draw_square(Mat img, Point Point1, Point Point2, Scalar color)
        {
		Point Corner1 = Point(Point1.x,Point1.y);//Location of Corner1
		Point Corner2 = Point(Point2.x,Point1.y);//Location of Corner2
		Point Corner3 = Point(Point1.x,Point2.y);//Location of Corner3
		Point Corner4 = Point(Point2.x,Point2.y);//Location of Corner4
		rectangle(img,Point(Point1.x,Point1.y),Point(Point2.x,Point2.y),color,1); //Outline rectangle
                line(img, Corner1, Point(Point1.x+7,Point1.y), color, 2, 8); // Corner-1 X
		line(img, Corner1, Point(Point1.x,Point1.y+7), color, 2, 8); // Corner-1 Y
		line(img, Corner2, Point(Point2.x-7,Point1.y), color, 2, 8); // Corner-2 X
		line(img, Corner2, Point(Point2.x,Point1.y+7), color, 2, 8); // Corner-2 Y
		line(img, Corner3, Point(Point1.x+7,Point2.y), color, 2, 8); // Corner-3 X
		line(img, Corner3, Point(Point1.x,Point2.y-7), color, 2, 8); // Corner-3 Y
		line(img, Corner4, Point(Point2.x-7,Point2.y), color, 2, 8); // Corner-4 X
		line(img, Corner4, Point(Point2.x,Point2.y-7), color, 2, 8); // Corner-4 Y
                return 0;
        }

        public: Point find_center(int x, int y)
        {
                int resultx = x / 2;
                int resulty = y /2;
                cout << "DEBUG: Calculated center at X: " << resultx << " Y: " << resulty << endl;
                return Point(resultx, resulty);
        }

	public: string formatted_time()
	{
		time_t now = time(0);
                tm *ltm = localtime(&now);
		string hours, minutes, seconds = "";
		if(ltm->tm_hour < 10)
			hours = "0";
		if(ltm->tm_min < 10)
                        minutes = "0";
                if(ltm->tm_sec < 10)
                        seconds = "0";
                stringstream ss;
                ss << hours << ltm->tm_hour << ":" << minutes << ltm->tm_min << ":" << seconds << ltm->tm_sec;
                string formatted_time = ss.str();
		return formatted_time;
	}

        public: int draw_time(Mat img, Scalar color)
        {
                Size canvas = img.size();
                cout << "DEBUG: Drawing: " << formatted_time() << endl;
                putText(img, formatted_time(), Point(5,(canvas.height-5)),  FONT_HERSHEY_PLAIN, 1, color, 1, 8);
                return 0;
        }

};

