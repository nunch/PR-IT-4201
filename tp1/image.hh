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

	void setMax(int t){
		max = t;
	};

	int getMax(){
		return max;
	};

	void setIsNull(T t){
		isNull = t;
		for(int i=0;i<i_*j_;i++){
			data_.push_back(isNull);
		}
	};

	T getIsNull() const{
		return isNull;
	};

	T& getIsNull(){
		return isNull;
	};

	bool isOk(T t){
		return test == t;
	};

	void setTest(T t) {
		test = t;
	};

	T getTest(){
		return test;
	};
	
	image(unsigned i, unsigned j){
		i_ = i;
		j_ = j;
		//data_ = (T*) malloc(i_*j_*sizeof(T));
	};

	image(const image<T>& m){
		i_ = m.i();
		j_ = m.j();
		//data_ = (T*) malloc(i_*j_*sizeof(T));
		setIsNull(m.getIsNull());
		for(unsigned i=0;i<i_*j_;i++){
			data_[i] = m[i];
		}
	};

	box2d domain(){
		box2d b(point2d(0,0),point2d(i_,j_));
		return b;
	}

	
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

	unsigned i()const{return i_;};
	unsigned j()const{return j_;};
	T* data()const{return data_;};
	unsigned i(){return i_;};
	unsigned j(){return j_;};
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
		//data_ = new T[i_*j_];
		for(int i=0;i<i_*j_;i++){
			data_[i] = m[i];
		}
		return *this;
	};
	~image(){
		//delete[] data_;
	};

	virtual void fill(T a){
		for (int i=0;i<i_*j_;i++){
			data_[i] = a;
		}
	}

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
};/*

image operator+(image& m1, const image& m2){
	assert(m1.i()==m2.i());
	assert(m1.j()==m2.j());
	image m(m1);
	for(int i=0;i<m1.i()*m1.j();i++){
		m[i]+=m2[i];
	}
	return m;
};

image operator-(image& m1, const image& m2){
	assert(m1.i()==m2.i());
	assert(m1.j()==m2.j());
	image m(m1);
	for(int i=0;i<m1.i()*m1.j();i++){
		m[i]-=m2[i];
	}
	return m;
};*/
/*#include <algorithm>

class image
{
private:
	unsigned i_;
	unsigned j_;
	int* data_;
public:
	
	image(unsigned i, unsigned j){
		i_ = i;
		j_ = j;
		data_ = (int*) malloc(i_*j_*sizeof(int));
	};

	image(const image& m){
		i_ = m.i();
		j_ = m.j();
		data_ = (int*) malloc(i_*j_*sizeof(int));
		for(unsigned i=0;i<i_*j_;i++){
			data_[i] = m[i];
		}
	};
	
	int& operator()(const int i, const int j){
		assert(i >= 0 && i < i_);
	    assert(j >= 0 && j < j_);
	 
	    return data_[i*j_+j];
	};

	int& operator()(point2d p){
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
/*
	int& operator[](const point2d t){
		assert(t.i >= 0 && t.i  < i_);
	    assert(t.j  >= 0 && t.j < j_);
	 
	    return data_[t.i*j_+t.j];
	};

	unsigned i()const{return i_;};
	unsigned j()const{return j_;};
	int* data()const{return data_;};
	unsigned i(){return i_;};
	unsigned j(){return j_;};
	int* data(){return data_;};

	int operator[](int i) const{
		return data_[i];
	};
	int& operator[](int i){
		return data_[i];
	};

	image& operator=(const image& m){
		i_=m.i();
		j_=m.j();
		data_ = new int[i_*j_];
		for(int i=0;i<i_*j_;i++){
			data_[i] = m[i];
		}
		return *this;
	};
	~image(){
		//delete[] data_;
	};

	virtual void fill(int a){
		for (int i=0;i<i_*j_;i++){
			data_[i] = a;
		}
	}

	std::vector<int> values(){
		std::vector<int> vec;
		for(int i=0;i<i_*j_;i++){
			if(data_[i]!=0 && find(vec.begin(), vec.end(), data_[i]) == vec.end()){
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
};/*

image operator+(image& m1, const image& m2){
	assert(m1.i()==m2.i());
	assert(m1.j()==m2.j());
	image m(m1);
	for(int i=0;i<m1.i()*m1.j();i++){
		m[i]+=m2[i];
	}
	return m;
};

image operator-(image& m1, const image& m2){
	assert(m1.i()==m2.i());
	assert(m1.j()==m2.j());
	image m(m1);
	for(int i=0;i<m1.i()*m1.j();i++){
		m[i]-=m2[i];
	}
	return m;
};*/