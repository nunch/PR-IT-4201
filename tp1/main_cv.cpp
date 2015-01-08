#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>
#include <vector>
#include "neighb2diterator.hh"
#include "box2d_iterator.hh"
#include "highgui.h"
#include "cv.h"


using namespace std;

unsigned dim1;
unsigned dim2;

// Get the size of a file

uchar* im_dim;

image calcMap(image& input){
	image dmap(dim1,dim2);
	image inter(dim1,dim2);

	std::queue<point2d> queue;
	box2d dom(input);
	box2d_iterator it_dom(dom);
	it_dom.start();
	unsigned max = 256;
	//input.affiche();

	std::vector<int> values = input.values();

	image* res = (image*) malloc(values.size()*sizeof(image));
	int num=0;

	while(it_dom.hasNext()){
		point2d p = it_dom.next();
		inter(p) = max;
	}

	for (std::vector<int>::iterator it = values.begin() ; it != values.end(); ++it){
		image t(dim1,dim2);
		res[num] = t;
		it_dom.start();
		/*while(it_dom.hasNext()){
			point2d p = it_dom.next();
			//std::cout << p.i << p.j << std::endl;
			res[num](p) = max;
		}*/
		
		it_dom.start();
		while(it_dom.hasNext()){
			point2d p = it_dom.next();
			res[num](p) = max;
			if(input(p) == values[num]){
				res[num](p) = 0;
				if(res[num](p)<inter(p)) {
					inter(p) = res[num](p);
					dmap(p) = values[num]*255/values.size();
				}
				neighb2diterator it(input,p,dim1,dim2);
				it.start();
				while(it.hasNext()){
					point2d p2 = it.next();
					if(input(p2) == 0){
						queue.push(p);
						//break;
					}
				}
			}
		}

		while(!queue.empty()){
			point2d p = queue.front();
			queue.pop();
			neighb2diterator it(input, p, dim1,dim2);
			it.start();
			while(it.hasNext()){
				point2d p2 = it.next();
				if(res[num](p2) == max){
					res[num](p2) = res[num](p)+1;
					if(res[num](p2)<inter(p2)) {
						inter(p2) = res[num](p2);
						dmap(p2) = values[num]*255/values.size();
					}
					queue.push(p2);
				}
			}
		}
		num++;
	}
	return dmap;
}


int main(int argc, char const *argv[])
{
	
    cvNamedWindow("Input", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Input", 0,0);

	srand (time(NULL));	
	dim1 = 64; // ligne
	dim2 = 64; // colone
	image input(dim1,dim2);
	for(int i=0;i<dim1;i++){
		input(point2d(i,dim2/4)) = 1;
		input(point2d(i,2*dim2/4)) = 2;
		input(point2d(i,3*dim2/4)) = 3;
		input(point2d(i,dim2-1)) = 4;
	}
	image dmap = calcMap(input);//(64,64);// = calcMap(input);
	std::cout << "\ndmap\n" << std::endl;
	//dmap.affiche();

	int width = dim1;
	int height = dim2;

	IplImage *im_in = cvCreateImage(cvSize(width,height),  IPL_DEPTH_8U, 1);
	uchar* im_in_data = (uchar *) im_in->imageData;
	width = im_in-> widthStep;

	for(int i=0;i<width*height;i++){
		im_in_data[i]=dmap[i];
	}

	cvShowImage( "Input", im_in);
	cvWaitKey(10);
	//cvSaveImage("bidule.png", im_in);
	while(1);
	cvDestroyWindow("Input");
	return 0;
}