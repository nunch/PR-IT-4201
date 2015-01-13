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


// Get the size of a file
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
				if(dom.isIn(p2) && !input.isOk(input(p2))){
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

	image<int>* res = (image<int>*) malloc(values.size()*sizeof(image<int>));
	std::vector<image<int> > truc;
	image<int> t(dim1,dim2);
	int num=0;

	for(int i=0;i<values.size();i++){
		std::cout << values[i] << "\n";
		input.setTest(values[i]);
		//res[i] = calcMap(input);
		//truc.push_back(calcMap(input));
		//t = calcMap(input);
	}
	/*box2d dom = input.domain();
	box2d_iterator it_dom(dom);
	it_dom.start();
	while(it_dom.hasNext()){
		point2d p = it_dom.next();
		for(int i=0;i<values.size();i++){
			if(res[i](p)<inter(p)) {
				inter(p) = res[i](p);
				dmap(p) = values[i];
			}
		}
	}*/
	return dmap;
}

template <typename T>
void truc(image<T>& i){

}

image<int> comute_dmap_opti(image<int>& input){
	image<int> dmap(dim1,dim2);
	image<int> inter(dim1,dim2);

	std::queue<point2d> queue;
	box2d dom = input.domain();
	box2d_iterator it_dom(dom);
	it_dom.start();
	input.affiche();

	std::vector<int> values = input.values();

	image<int>* res = (image<int>*) malloc(values.size()*sizeof(image<int>));
	int num=0;

	while(it_dom.hasNext()){
		point2d p = it_dom.next();
		inter(p) = input.getMax();
	}

	for (std::vector<int>::iterator it = values.begin() ; it != values.end(); ++it){
		image<int> t(dim1,dim2);
		res[num] = t;
		res[num].setTest(values[num]);
		it_dom.start();
		
		it_dom.start();
		while(it_dom.hasNext()){
			point2d p = it_dom.next();
			res[num](p) = input.getMax();
			if(res[num].isOk(input(p))){
				res[num](p) = 0;
				if(res[num](p)<inter(p)) {
					inter(p) = res[num](p);
					dmap(p) = values[num];
				}
				neighb2diterator it(p,dim1,dim2);
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
			neighb2diterator it(p, dim1, dim2);
			it.start();
			while(it.hasNext()){
				point2d p2 = it.next();
				if(res[num](p2) == input.getMax()){
					res[num](p2) = res[num](p)+1;
					if(res[num](p2)<inter(p2)) {
						inter(p2) = res[num](p2);
						dmap(p2) = res[num].getTest();
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
	/*srand (time(NULL));
	dim1 = 10;
	dim2 = 20;
	image<std::string> input(dim1,dim2);
	input.setMax(255);
	input.setIsNull("");
	input.setTest("s");
	for(int i=0;i<10;i++) {
		input(point2d(i,4)) = "s";
		input(point2d(i,9)) = "ss";
		input(point2d(i,14)) = "sss";
		input(point2d(i,19)) = "ssss";
	}
	//input.affiche();
	image<std::string> dmap = comute_dmap(input);
	//truc(input);
	
	//image<int> dmap = calcMap(input);
	std::cout << "\ndmap\n" << std::endl;
	dmap.affiche();
	
	return 0;*/
	dim1 = 10;
	dim2 = 20;
	image<int> input(dim1,dim2);
	input.setMax(255);
	input.setIsNull(0);
	input.setTest(1);
	for(int i=0;i<10;i++) {
		input(point2d(i,4)) = 1;
		input(point2d(i,9)) = 2;
		input(point2d(i,14)) = 3;
		input(point2d(i,19)) = 4;
	}
	//input.affiche();
	std::vector<int> values = input.values();
	image<int> dmap(dim1,dim2);
	for(int i=0;i<values.size();i++) dmap = calcMap(input);
	//truc(input);
	
	//image<int> dmap = calcMap(input);
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

