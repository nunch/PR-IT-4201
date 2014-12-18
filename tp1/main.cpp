#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>
#include "neighb2diterator.hh"
#include "box2d_iterator.hh"

using namespace std;

unsigned dim1;
unsigned dim2;

// Get the size of a file

image calcMap(image& input, int etiquette){
	image dmap(dim1,dim2);

	std::queue<point2d> queue;
	box2d dom(input);
	box2d_iterator it_dom(dom);
	it_dom.start();
	unsigned max = 256;
	input.affiche();

	while(it_dom.hasNext()){
		point2d p = it_dom.next();
		//std::cout << p.i << p.j << std::endl;
		dmap(p) = max;
	}
	
	it_dom.start();
	while(it_dom.hasNext()){
		point2d p = it_dom.next();
		
		if(input(p) == etiquette){
			dmap(p) = 0;
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
			if(dmap(p2) == max){
				dmap(p2) = dmap(p)+1;
				queue.push(p2);
			}
		}
	}

	return dmap;
}


int main(int argc, char const *argv[])
{
	srand (time(NULL));	
	dim1 = 50;
	dim2 = 20;
	image input(dim1,dim2);
	for(int i=0;i<10;i++){
		input(point2d(rand()%dim1,rand()%dim2)) = 1;
	}
	image dmap = calcMap(input, 1);
	std::cout << "\ndmap\n" << std::endl;
	dmap.affiche();
	return 0;
}