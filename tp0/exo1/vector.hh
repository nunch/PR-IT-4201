#include <cassert>

class vector : public truc
{
private:
	int n_;
	int* data_;

public:
	int dim(){
		return n_;
	};

	int dim() const{
		return n_;
	};

	int* data(){
		return data_;
	};

	int* data() const{
		return data_;
	};

	explicit vector(int n){
		n_ = n;
		data_ = new int[n_];
	};

	vector(const vector& v){
		n_ = v.dim();
		data_ = new int[n_];
		for(int i=0;i<n_;i++){
			data_[i] = v.data()[i];
		}
	};

	~vector(){
		delete[] data_;
	};
	
	int& operator[](int i) const{
		return data_[i];
	};
	int& operator[](int i){
		return data_[i];
	};

	vector& operator=(const vector& v2){
		for(int i=0;i<n_;i++){
			data_[i] = v2[i];
		}
		return *this;
	};

	virtual void fill(int a){
		for (int i=0;i<n_;i++){
			data_[i] = a;
		}
	}
};

vector operator+(vector& v1, const vector& v2){
	assert(v1.dim()==v2.dim());
	vector v(v1);
	for(int i=0;i<v1.dim();i++){
		v[i]+=v2[i];
	}
	return v;
};

vector operator-(vector& v1, const vector& v2){
	assert(v1.dim()==v2.dim());
	vector v(v1);
	for(int i=0;i<v1.dim();i++){
		v[i]-=v2[i];
	}
	return v;
};

