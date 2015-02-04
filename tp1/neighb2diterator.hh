class neighb2diterator
{
public:
	neighb2diterator(point2d p, int dimI, int dimJ){
		//std::cout << "neighb2diterator " << p.i << " " << p.j << std::endl;
		int i = p.i;
		int j = p.j;
		assert(i<dimI);
		assert(i>=0);
		assert(j<dimJ);
		assert(j>=0);
		current = 0;

		if(i==0 && j==0){
			liste.push_back(point2d(i+1,j));
			liste.push_back(point2d(i,j+1));
		}else if(i==0 && j==dimJ-1){
			liste.push_back(point2d(i+1,j));
			liste.push_back(point2d(i,j-1));
		}else if(i==dimI-1 && j==dimJ-1){
			liste.push_back(point2d(i-1,j));
			liste.push_back(point2d(i,j-1));
		}else if(i==dimI-1 && j==0){
			liste.push_back(point2d(i-1,j));
			liste.push_back(point2d(i,j+1));
		}else if(i==0){
			liste.push_back(point2d(i+1,j));
			liste.push_back(point2d(i,j+1));
			liste.push_back(point2d(i,j-1));
		}else if(i==dimI-1){
			liste.push_back(point2d(i-1,j));
			liste.push_back(point2d(i,j+1));
			liste.push_back(point2d(i,j-1));
		}else if(j==0){
			liste.push_back(point2d(i-1,j));
			liste.push_back(point2d(i+1,j));
			liste.push_back(point2d(i,j+1));
		}else if(j==dimJ-1){
			liste.push_back(point2d(i-1,j));
			liste.push_back(point2d(i+1,j));
			liste.push_back(point2d(i,j-1));
		}else{
			liste.push_back(point2d(i-1,j));
			liste.push_back(point2d(i+1,j));
			liste.push_back(point2d(i,j+1));
			liste.push_back(point2d(i,j-1));
		}
	};

	bool hasNext(){
		return (current<liste.size());
	}

	point2d& next(){
		current++;
		return liste[current-1];
	}

	void start(){current=0;};
	
private:
	std::vector<point2d> liste;
	unsigned current;
};