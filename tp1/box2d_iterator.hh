class box2d_iterator
{
public:
	box2d_iterator(box2d& d){
		current = 0;
		begin=0;
		end = d.getLast();
		dom = d;
		//std::cout << "end " << end << std::endl;
	};
	~box2d_iterator(){};

	bool hasNext(){
		return (current<end);
	}

	point2d& next(){
		current++;
		return dom[current-1];
	}

	void start(){current=0;};
	
private:
	box2d dom;
	unsigned current;
	unsigned begin;
	unsigned end;
};

/*class box2d_iterator
{
public:
	box2d_iterator(box2d& d){
		current = 0;
		begin=0;
		end = d.getLast();
		dom = d;
		//std::cout << "end " << end << std::endl;
	};
	~box2d_iterator(){};

	bool hasNext(){
		return (current<end);
	}

	point2d& next(){
		current++;
		return dom[current-1];
	}

	void start(){current=0;};
	
private:
	box2d dom;
	unsigned current;
	unsigned begin;
	unsigned end;
};*/