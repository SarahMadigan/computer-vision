/* 
    This file is part of WARG's computer-vision

    Copyright (c) 2015, Waterloo Aerial Robotics Group (WARG)
    All rights reserved.
 
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Usage of this code MUST be explicitly referenced to WARG and this code
       cannot be used in any competition against WARG.
    4. Neither the name of the WARG nor the names of its contributors may be used
       to endorse or promote products derived from this software without specific
       prior written permission.

    THIS SOFTWARE IS PROVIDED BY WARG ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL WARG BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "object_detector.h"
#include "pixel_target.h"
#include <vector>
#include "frame.h"

using namespace std;
using namespace cv;

ObjectDetector::ObjectDetector(Filter * filter, ContourCreator * contourCreator){
    this->filter = filter;
    this->ccreator = contourCreator;
}

void ObjectDetector::process_frame(Frame * f){
    Mat & src = f->get_img();
    Mat * filtered = filter->filter(src);
    vector<vector<Point> > contours = *(ccreator->get_contours(*filtered));
    delete filtered;
    for(vector<Point> contour : contours){
        string type;
        Point2d centroid;
        double area;
        double perimeter;
        Scalar colour;
        Point2d error;
        double errorAngle;

        // get info from contours/image

        PixelTarget * p = new PixelTarget(type, centroid, area, perimeter, colour, error, errorAngle);
        f->add_target(p);
    }
}

ObjectDetector::~ObjectDetector(){

}
