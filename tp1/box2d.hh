class box2d
{
public:
	box2d(){};
	box2d(point2d p1, point2d p2){
		i_ = p2.i;
		j_ = p2.j;
		liste = new point2d[i_*j_];

		for (int i = p1.i; i < i_; ++i)
		{
			for (int j = p1.j; j < j_; ++j)
			{
				liste[i*j_+j] = point2d(i,j);
			}
		}
	};
	~box2d(){};

	point2d* getListe(){return liste;};

	unsigned getLast(){return i_*j_;};

	point2d& operator()(point2d p){
		return liste[p.i*j_+p.j];
	};

	point2d& operator[](unsigned i){
		return liste[i];
	};

	bool isIn(point2d p){
		for (int i = 0; i < i_; ++i)
		{
			for (int j = 0; j < j_; ++j)
			{
				if(liste[i*j_+j] == p) return true;
			}
		}
		return false;
	}

private:
	point2d* liste;
	unsigned i_;
	unsigned j_;
};
/*#include "point2d.hh"
#include "image.hh"

class box2d
{
public:
	box2d(){};
	box2d(image im){
		i_ = im.i();
		j_ = im.j();
		liste = new point2d[i_*j_];

		for (int i = 0; i < i_; ++i)
		{
			for (int j = 0; j < j_; ++j)
			{
				liste[i*j_+j] = point2d(i,j);
			}
		}
	};
	~box2d(){};

	point2d* getListe(){return liste;};

	unsigned getLast(){return i_*j_;};

	point2d& operator()(point2d p){
		return liste[p.i*j_+p.j];
	};

	point2d& operator[](unsigned i){
		return liste[i];
	};

private:
	point2d* liste;
	unsigned i_;
	unsigned j_;
};*/