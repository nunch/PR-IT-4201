#include "box2d.hh"
template <typename T>
class neighb2diterator
{
public:
	neighb2diterator(image<T> im, unsigned i, unsigned j, unsigned dim){
		assert(i<dim);
		assert(i>=0);
		assert(j<dim);
		assert(j>=0);
		current = 0;

		if(i==0 && j==0){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i,j+1);
			liste[1] = point2d(i+1,j);
		}else if(i==0 && j==dim-1){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i+1,j);
			liste[1] = point2d(i,j-1);
		}else if(i==dim-1 && j==dim-1){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j-1);
		}else if(i==dim-1 && j==0){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
		}else if(i==0){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i,j+1);
			liste[1] = point2d(i+1,j);
			liste[2] = point2d(i,j-1);
		}else if(i==dim-1){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i,j-1);
		}else if(j==0){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i+1,j);
		}else if(j==dim-1){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i+1,j);
			liste[2] = point2d(i,j-1);
		}else{
			dimension=4;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i+1,j);
			liste[3] = point2d(i,j-1);
		}
	};


	neighb2diterator(image<T> im, point2d p, unsigned dim){
		//std::cout << "neighb2diterator " << p.i << " " << p.j << std::endl;
		int i = p.i;
		int j = p.j;
		assert(i<dim);
		assert(i>=0);
		assert(j<dim);
		assert(j>=0);
		current = 0;

		if(i==0 && j==0){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i,j+1);
			liste[1] = point2d(i+1,j);
		}else if(i==0 && j==dim-1){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i+1,j);
			liste[1] = point2d(i,j-1);
		}else if(i==dim-1 && j==dim-1){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j-1);
		}else if(i==dim-1 && j==0){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
		}else if(i==0){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i,j+1);
			liste[1] = point2d(i+1,j);
			liste[2] = point2d(i,j-1);
		}else if(i==dim-1){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i,j-1);
		}else if(j==0){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i+1,j);
		}else if(j==dim-1){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i+1,j);
			liste[2] = point2d(i,j-1);
		}else{
			dimension=4;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i+1,j);
			liste[3] = point2d(i,j-1);
		}
	};

	neighb2diterator(image<T> im, point2d p, unsigned dimI, unsigned dimJ){
		//std::cout << "neighb2diterator " << p.i << " " << p.j << std::endl;
		int i = p.i;
		int j = p.j;
		assert(i<dimI);
		assert(i>=0);
		assert(j<dimJ);
		assert(j>=0);
		current = 0;

		if(i==0 && j==0){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i,j+1);
			liste[1] = point2d(i+1,j);
		}else if(i==0 && j==dimJ-1){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i+1,j);
			liste[1] = point2d(i,j-1);
		}else if(i==dimI-1 && j==dimJ-1){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j-1);
		}else if(i==dimI-1 && j==0){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
		}else if(i==0){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i,j+1);
			liste[1] = point2d(i+1,j);
			liste[2] = point2d(i,j-1);
		}else if(i==dimI-1){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i,j-1);
		}else if(j==0){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i+1,j);
		}else if(j==dimJ-1){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i+1,j);
			liste[2] = point2d(i,j-1);
		}else{
			dimension=4;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i+1,j);
			liste[3] = point2d(i,j-1);
		}
	};

	~neighb2diterator(){
		//delete liste;
	};

	int getN(){return dimension;};

	int getI(int nn){return i_[nn];};

	int getJ(int nn){return j_[nn];};

	bool hasNext(){
		return (current<dimension);
	}

	point2d& next(){
		current++;
		return liste[current-1];
	}

	void start(){current=0;};
	
private:
	unsigned* i_;
	unsigned* j_;
	point2d* liste;
	unsigned dimension;
	unsigned current;
};
/*
#include "box2d.hh"
class neighb2diterator
{
public:
	neighb2diterator(image im, unsigned i, unsigned j, unsigned dim){
		assert(i<dim);
		assert(i>=0);
		assert(j<dim);
		assert(j>=0);
		current = 0;

		if(i==0 && j==0){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i,j+1);
			liste[1] = point2d(i+1,j);
		}else if(i==0 && j==dim-1){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i+1,j);
			liste[1] = point2d(i,j-1);
		}else if(i==dim-1 && j==dim-1){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j-1);
		}else if(i==dim-1 && j==0){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
		}else if(i==0){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i,j+1);
			liste[1] = point2d(i+1,j);
			liste[2] = point2d(i,j-1);
		}else if(i==dim-1){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i,j-1);
		}else if(j==0){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i+1,j);
		}else if(j==dim-1){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i+1,j);
			liste[2] = point2d(i,j-1);
		}else{
			dimension=4;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i+1,j);
			liste[3] = point2d(i,j-1);
		}
	};


	neighb2diterator(image im, point2d p, unsigned dim){
		//std::cout << "neighb2diterator " << p.i << " " << p.j << std::endl;
		int i = p.i;
		int j = p.j;
		assert(i<dim);
		assert(i>=0);
		assert(j<dim);
		assert(j>=0);
		current = 0;

		if(i==0 && j==0){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i,j+1);
			liste[1] = point2d(i+1,j);
		}else if(i==0 && j==dim-1){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i+1,j);
			liste[1] = point2d(i,j-1);
		}else if(i==dim-1 && j==dim-1){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j-1);
		}else if(i==dim-1 && j==0){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
		}else if(i==0){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i,j+1);
			liste[1] = point2d(i+1,j);
			liste[2] = point2d(i,j-1);
		}else if(i==dim-1){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i,j-1);
		}else if(j==0){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i+1,j);
		}else if(j==dim-1){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i+1,j);
			liste[2] = point2d(i,j-1);
		}else{
			dimension=4;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i+1,j);
			liste[3] = point2d(i,j-1);
		}
	};

	neighb2diterator(image im, point2d p, unsigned dimI, unsigned dimJ){
		//std::cout << "neighb2diterator " << p.i << " " << p.j << std::endl;
		int i = p.i;
		int j = p.j;
		assert(i<dimI);
		assert(i>=0);
		assert(j<dimJ);
		assert(j>=0);
		current = 0;

		if(i==0 && j==0){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i,j+1);
			liste[1] = point2d(i+1,j);
		}else if(i==0 && j==dimJ-1){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i+1,j);
			liste[1] = point2d(i,j-1);
		}else if(i==dimI-1 && j==dimJ-1){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j-1);
		}else if(i==dimI-1 && j==0){
			dimension=2;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
		}else if(i==0){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i,j+1);
			liste[1] = point2d(i+1,j);
			liste[2] = point2d(i,j-1);
		}else if(i==dimI-1){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i,j-1);
		}else if(j==0){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i+1,j);
		}else if(j==dimJ-1){
			dimension=3;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i+1,j);
			liste[2] = point2d(i,j-1);
		}else{
			dimension=4;
			liste = new point2d[dimension];
			liste[0] = point2d(i-1,j);
			liste[1] = point2d(i,j+1);
			liste[2] = point2d(i+1,j);
			liste[3] = point2d(i,j-1);
		}
	};

	~neighb2diterator(){
		//delete liste;
	};

	int getN(){return dimension;};

	int getI(int nn){return i_[nn];};

	int getJ(int nn){return j_[nn];};

	bool hasNext(){
		return (current<dimension);
	}

	point2d& next(){
		current++;
		return liste[current-1];
	}

	void start(){current=0;};
	
private:
	unsigned* i_;
	unsigned* j_;
	point2d* liste;
	unsigned dimension;
	unsigned current;
};*/