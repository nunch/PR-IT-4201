#include <cassert>

class matrix : public truc
{
private:
	unsigned i_;
	unsigned j_;
	int* data_;
public:
	
	matrix(unsigned i, unsigned j){
		i_ = i;
		j_ = j;
		data_ = new int[i*j];
	};

	matrix(const matrix& m){
		i_ = m.i();
		j_ = m.j();
		data_ = new int[i_*j_];
		for(unsigned i=0;i<i_*j_;i++){
			data_[i] = m[i];
		}
	};
	
	int& operator()(const int i, const int j){
		assert(i >= 0 && i < i_);
	    assert(j >= 0 && j < j_);
	 
	    return data_[i*j_+j];
	};

	unsigned i()const{return i_;};
	unsigned j()const{return j_;};
	int* data()const{return data_;};
	unsigned i(){return i_;};
	unsigned j(){return j_;};
	int* data(){return data_;};

	int& operator[](int i) const{
		return data_[i];
	};
	int& operator[](int i){
		return data_[i];
	};

	matrix& operator=(const matrix& m){
		i_=m.i();
		j_=m.j();
		for(int i=0;i<i_*j_;i++){
			data_[i] = m[i];
		}
		return *this;
	};
	~matrix(){
		delete[] data_;
	};

	virtual void fill(int a){
		for (int i=0;i<i_*j_;i++){
			data_[i] = a;
		}
	}
};

matrix operator+(matrix& m1, const matrix& m2){
	assert(m1.i()==m2.i());
	assert(m1.j()==m2.j());
	matrix m(m1);
	for(int i=0;i<m1.i()*m1.j();i++){
		m[i]+=m2[i];
	}
	return m;
};

matrix operator-(matrix& m1, const matrix& m2){
	assert(m1.i()==m2.i());
	assert(m1.j()==m2.j());
	matrix m(m1);
	for(int i=0;i<m1.i()*m1.j();i++){
		m[i]-=m2[i];
	}
	return m;
};