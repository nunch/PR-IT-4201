class dia_matrix : public matrix
{
public:
	dia_matrix(int n, const vector& v){
		assert(n == v.dim());
		i_ = n;
		j_ = n;
		v_ = v;
	};
	~dia_matrix();
	
	int& operator()(int i,int j){
		assert(i<i_ && j<j_);
		if(i==j) return v_[i];
		else return 0;
	}

	int operator()(int i,int j)const{
		assert(i<i_ && j<j_);
		if(i==j) return v_[i];
		else return 0;
	}
private:
	vector v_;
};