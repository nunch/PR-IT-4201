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

image calcMap(image& input){
	image dmap(dim1,dim2);

	std::queue<point2d> queue;
	box2d dom(input);
	box2d_iterator it_dom(dom);
	it_dom.start();
	unsigned max = 256;
	input.affiche();

	std::vector<int> values = input.values();
	std::cout << values.size() << std::endl;

	image* res = (image*) malloc(values.size()*sizeof(image));
	int num=0;

	for (std::vector<int>::iterator it = values.begin() ; it != values.end(); ++it){
		image t(dim1,dim2);
		res[num] = t;
		while(it_dom.hasNext()){
			point2d p = it_dom.next();
			//std::cout << p.i << p.j << std::endl;
			res[num](p) = max;
		}
		
		/*it_dom.start();
		while(it_dom.hasNext()){
			point2d p = it_dom.next();
			
			if(input(p) == values[num]){
				res[num](p) = 0;
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
					queue.push(p2);
				}
			}
		}*/
		num++;
	}
	int truc =100;
	for(int k=0;k<dim1*dim2;k++){
		truc = res[0][k];
		for(int i=1;i<values.size();i++){
			if(res[i][k] < truc) truc=res[i][k];
		}
		dmap[k] = truc;		
	}
return res[1];
}


int main(int argc, char const *argv[])
{
	srand (time(NULL));	
	dim1 = 50;
	dim2 = 20;
	image input(dim1,dim2);
	for(int i=0;i<50;i++){
		input(point2d(rand()%dim1,rand()%dim2)) = 1;
		input(point2d(rand()%dim1,rand()%dim2)) = 2;
		input(point2d(rand()%dim1,rand()%dim2)) = 3;
		input(point2d(rand()%dim1,rand()%dim2)) = 4;
	}
	image dmap = calcMap(input);
	std::cout << "\ndmap\n" << std::endl;
	dmap.affiche();
	return 0;
}