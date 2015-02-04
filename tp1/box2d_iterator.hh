class box2d_iterator
{
public:
	box2d_iterator(box2d& d){
		current = 0;
		dom = d;
	};
	~box2d_iterator(){};

	bool hasNext(){
		return (current<dom.getLast());
	}

	point2d& next(){
		current++;
		return dom[current-1];
	}

	void start(){current=0;};
	
private:
	box2d dom;
	int current;
};
