class point2d
{
public:
	explicit point2d(unsigned i_, unsigned j_){
		i=i_;
		j=j_;
	};
	explicit point2d (){
		point2d(0,0);
	}
	~point2d(){};

	void affiche(){
		std::cout << "i = " << i << "\tj = "<< j <<std::endl;
	};

	bool operator==(point2d p){
		return i==p.i && j==p.j;
	}
	unsigned i;
	unsigned j;
	
};