#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <string>
#include "point2d.hh"
#include "box2d.hh"
#include "image.hh"
#include "neighb2diterator.hh"
#include "box2d_iterator.hh"

using namespace std;

unsigned dim1;
unsigned dim2;


template <typename T>
image<int> calcMap(image<T>& input){
	image<int> dmap(dim1,dim2);
	dmap.setIsNull(0);

	std::queue<point2d> queue;
	box2d dom = input.domain();
	box2d_iterator it_dom(dom);

	it_dom.start();
	while(it_dom.hasNext()){
		point2d p = it_dom.next();
		dmap(p) = input.getMax();
	}
	
	it_dom.start();
	while(it_dom.hasNext()){
		point2d p = it_dom.next();
		if(input.isOk(input(p))){
			dmap(p) = 0;
			neighb2diterator it(p,dim1,dim2);
			it.start();
			while(it.hasNext()){
				point2d p2 = it.next();
				if(dom.has(p2) && !input.isOk(input(p2))){
					queue.push(p);
					break;
				}
			}
		}
	}

	while(!queue.empty()){
		point2d p = queue.front();
		queue.pop();
		neighb2diterator it(p, dim1,dim2);
		it.start();
		while(it.hasNext()){
			point2d p2 = it.next();
			if(dmap(p2) == input.getMax()){
				dmap(p2) = dmap(p)+1;
				queue.push(p2);
			}
		}
	}

	return dmap;
}

template <typename T>
image<T> comute_dmap(image<T>& input){
	std::vector<T> values = input.values();
	image<T> dmap(dim1,dim2);
	dmap.setIsNull(input.getIsNull());
	image<int> inter(dim1,dim2);
	inter.setIsNull(0);
	inter.fill(255);

	std::vector<image<int> > truc;

	for(int i=0;i<values.size();i++){
		input.setTest(values[i]);
		truc.push_back(calcMap(input));
	}
	box2d dom = input.domain();
	box2d_iterator it_dom(dom);
	it_dom.start();
	while(it_dom.hasNext()){
		point2d p = it_dom.next();
		for(int i=0;i<values.size();i++){
			if(truc[i](p)<inter(p)) {
				inter(p) = truc[i](p);
				dmap(p) = values[i];
			}
		}
	}
	return dmap;
}

void calcInt(){
	dim1 = 10;
	dim2 = 20;
	image<int> input(dim1,dim2);
	input.setIsNull(0);
	for(int i=0;i<10;i++) {
		input(point2d(i,4)) = 1;
		input(point2d(i,9)) = 2;
		input(point2d(i,14)) = 3;
		input(point2d(i,19)) = 4;
	}

	input.affiche();

	image<int> dmap = comute_dmap(input);
	std::cout << "\ndmap\n" << std::endl;
	dmap.affiche();

	std::cout << "\n\n\n";
}

void calcString(){
	dim1 = 10;
	dim2 = 20;
	image<std::string> input(dim1,dim2);
	input.setMax(255);
	input.setIsNull("");
	for(int i=0;i<10;i++) {
		input(point2d(i,4)) = "a";
		input(point2d(i,9)) = "b";
		input(point2d(i,14)) = "c";
		input(point2d(i,19)) = "d";
	}

	input.affiche();

	image<std::string> dmap = comute_dmap(input);
	std::cout << "\ndmap\n" << std::endl;
	dmap.affiche();
}

int main(int argc, char const *argv[])
{
	calcInt();
	calcString();
	return 0;
}