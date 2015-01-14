#include <algorithm>
/*#include <iostream>
#include "point2d.hh"
#include <vector>
#include <cassert>*/
template <typename T>
class image 
{
private:
	unsigned i_;
	unsigned j_;
	std::vector<T> data_;
	T test;
	T isNull;
	int max;
public:

	image(unsigned i, unsigned j){
		i_ = i;
		j_ = j;
		max = i_+j_;
	};

	image(const image<T>& m){
		i_ = m.i();
		j_ = m.j();
		max = i_+j_;
		setIsNull(m.getIsNull());
		for(unsigned i=0;i<i_*j_;i++){
			data_[i] = m[i];
		}
	};

	void setMax(int t) {max = t;};
	int getMax() {return max;};

	void setIsNull(T t) {
		isNull = t;
		if(data_.size()==0) for(int i=0;i<i_*j_;i++) data_.push_back(isNull);
	};
	T getIsNull() const{return isNull;};
	T& getIsNull() {return isNull;};


	void setTest(T t) {test = t;};
	T getTest() {return test;};
	
	unsigned i()const{return i_;};
	unsigned i(){return i_;};

	unsigned j()const{return j_;};
	unsigned j(){return j_;};

	T* data()const{return data_;};
	T* data(){return data_;};


	T operator[](int i) const{
		return data_[i];
	};
	T& operator[](int i){
		return data_[i];
	};

	image<T>& operator=(const image<T>& m){
		i_=m.i();
		j_=m.j();
		setIsNull(m.getIsNull());
		for(int i=0;i<i_*j_;i++){
			data_[i] = m[i];
		}
		return *this;
	};

	T& operator()(const int i, const int j){
		assert(i >= 0 && i < i_);
	    assert(j >= 0 && j < j_);
	 
	    return data_[i*j_+j];
	};

	T& operator()(point2d p){
		int i=p.i;
		int j=p.j;
		//p.affiche();
		//std::cout << i_ << std::endl;
		assert(i >= 0);
		assert(i < i_);
	    assert(j < j_);
	    assert(j >= 0);
	 
	    return data_[i*j_+j];
	};
	

	virtual void fill(T a){
		for (int i=0;i<i_*j_;i++){
			data_[i] = a;
		}
	}

	box2d domain(){
		box2d b(point2d(0,0),point2d(i_,j_));
		return b;
	}

	bool isOk(T t) {return test == t;};

	std::vector<T> values(){
		std::vector<T> vec;
		for(int i=0;i<i_*j_;i++){
			if(data_[i]!=isNull && find(vec.begin(), vec.end(), data_[i]) == vec.end()){
				vec.push_back(data_[i]);
			}
		}
		return vec;
	}

	void affiche(){
		for(int i=0;i<i_;i++){
			std::cout << data_[i*j_+0];
			for(int j=1;j<j_;j++){
				std::cout << "\t" << data_[i*j_+j];
			}
			std::cout << std::endl;
		}
	}
};