#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>
#include <vector>
#include "neighb2diterator.hh"
#include "box2d_iterator.hh"

using namespace std;

unsigned dim1;
unsigned dim2;

// Get the size of a file

image<int> calcMap(image<int>& input){
	image<int> dmap(dim1,dim2);
	image<int> inter(dim1,dim2);

	std::queue<point2d> queue;
	box2d<int> dom(input);
	box2d_iterator<int> it_dom(dom);
	it_dom.start();
	unsigned max = 256;
	input.affiche();

	std::vector<int> values = input.values();

	image<int>* res = (image<int>*) malloc(values.size()*sizeof(image<int>));
	int num=0;

	while(it_dom.hasNext()){
		point2d p = it_dom.next();
		inter(p) = max;
	}

	for (std::vector<int>::iterator it = values.begin() ; it != values.end(); ++it){
		image<int> t(dim1,dim2);
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
					dmap(p) = values[num];
				}
				neighb2diterator<int> it(input,p,dim1,dim2);
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
			neighb2diterator<int> it(input, p, dim1,dim2);
			it.start();
			while(it.hasNext()){
				point2d p2 = it.next();
				if(res[num](p2) == max){
					res[num](p2) = res[num](p)+1;
					if(res[num](p2)<inter(p2)) {
						inter(p2) = res[num](p2);
						dmap(p2) = values[num];
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
	srand (time(NULL));	
	dim1 = 10;
	dim2 = 20;
	image<int> input(dim1,dim2);
	for(int i=0;i<10;i++){
		input(point2d(i,4)) = 1;
		input(point2d(i,9)) = 2;
		input(point2d(i,14)) = 3;
		input(point2d(i,19)) = 4;
	}
	image<int> dmap = calcMap(input);
	std::cout << "\ndmap\n" << std::endl;
	dmap.affiche();
	return 0;
}
/*include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>
#include <vector>
#include "neighb2diterator.hh"
#include "box2d_iterator.hh"

using namespace std;

unsigned dim1;
unsigned dim2;

// Get the size of a file

image calcMap(image& input){
	image dmap(dim1,dim2);
	image inter(dim1,dim2);

	std::queue<point2d> queue;
	box2d dom(input);
	box2d_iterator it_dom(dom);
	it_dom.start();
	unsigned max = 256;
	input.affiche();

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
		
		it_dom.start();
		while(it_dom.hasNext()){
			point2d p = it_dom.next();
			res[num](p) = max;
			if(input(p) == values[num]){
				res[num](p) = 0;
				if(res[num](p)<inter(p)) {
					inter(p) = res[num](p);
					dmap(p) = values[num];
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
						dmap(p2) = values[num];
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
	srand (time(NULL));	
	dim1 = 10;
	dim2 = 20;
	image input(dim1,dim2);
	for(int i=0;i<10;i++){
		input(point2d(i,4)) = 1;
		input(point2d(i,9)) = 2;
		input(point2d(i,14)) = 3;
		input(point2d(i,19)) = 4;
	}
	image dmap = calcMap(input);
	std::cout << "\ndmap\n" << std::endl;
	dmap.affiche();
	return 0;
}*/