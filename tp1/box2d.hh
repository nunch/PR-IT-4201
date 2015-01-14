class box2d
{
public:
	box2d(){};
	box2d(point2d p1_, point2d p2_){
		p1 = p1_;
		p2 = p2_;
		j_ = p2.j-p1.j;
		i_ = p2.i-p1.i;

		for (int i = p1.i; i < p2.i; ++i)
		{
			for (int j = p1.j; j < p2.j; ++j)
			{
				liste.push_back(point2d(i,j));
			}
		}
	};
	~box2d(){};

	std::vector<point2d> getListe(){return liste;};

	int getLast(){return i_*j_;};

	point2d& operator()(point2d p){
		return liste[p.i*j_+p.j];
	};

	point2d& operator[](unsigned i){
		return liste[i];
	};

	bool has(point2d p){
	
		for (int i = p1.i; i < p2.i; ++i)
		{
			for (int j = p1.j; j < p2.j; ++j)
			{
				if(liste[i*j_+j] == p) return true;
			}
		}
		return false;
	}

private:
	std::vector<point2d> liste;
	point2d p1;
	point2d p2;
	int i_;
	int j_;
};