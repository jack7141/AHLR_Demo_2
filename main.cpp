#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat  Image ;

int main()
{
    Image = imread("C:/Users/ksrnd/Desktop/Light/20190326_004.png");
    imshow("Original",Image);
    Mat img_gray;
    cvtColor(Image,img_gray,CV_RGB2GRAY);
    imshow("img_gray",img_gray);
    Mat mask;
    blur(img_gray, mask, Size(3, 3));
    Canny(img_gray, mask, 70, 150, 3);
    imshow("Canny",mask);
    vector<vector<Point>> contours;

    Mat element = getStructuringElement(MORPH_RECT,Size(3,3));
    morphologyEx(mask,mask,MORPH_CLOSE,element,Point(-1,-1),10);
    erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    imshow("morphologyEx",mask);
    findContours( mask, contours, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE );
    vector<vector<Point>> contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    Point centerRect;
    for ( size_t i=0; i<contours.size(); i++) {

        approxPolyDP(contours[i],contours_poly[i],3,true);
        boundRect[i]=boundingRect(contours_poly[i]);

    }
    vector<Point> count;
    vector<Point> count2;
    for ( size_t i=0; i<contours.size(); i++ ) {

        //Center Point
        centerRect = (boundRect[i].tl() + boundRect[i].br())*0.5;
        count.push_back(centerRect);
    }

    if ( count.size() > 2 ) {
        for ( size_t i=0; i<count.size(); i++) {
            if ( -(boundRect[i].x - boundRect[i+1].x) > 15 && -(boundRect[i].x - boundRect[i+1].x) < 130 )
            {
                centerRect = (boundRect[i].tl() + boundRect[i].br())*0.5;
                cout << centerRect << endl;
                count2.push_back(centerRect);
                       cout << count2 << endl;
            }
        }

        for ( size_t i=0; i<count2.size(); i++ ) {

            rectangle( Image, boundRect[i].tl(), boundRect[i].br(), Scalar(255,255,0), 2);
            Point centerRect = (boundRect[i].tl() + boundRect[i].br())*0.5;
            circle(Image,centerRect,3,Scalar(255,0,255));
        }

    }

    imshow("Image",Image);
    waitKey();
}
