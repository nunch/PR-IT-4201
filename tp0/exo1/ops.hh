#include <cassert>
#include <iostream>

vector operator+(int a, const vector& v2){
	vector v(v2);
	for(int i=0;i<v2.dim();i++){
		v[i]+=a;
	}
	return v;
};

vector operator*(int a, const vector& v2){
	vector v(v2);
	for(int i=0;i<v2.dim();i++){
		v[i]*=a;
	}
	return v;
};

matrix operator+(int a, const matrix& m){
	matrix mat(m);
	for(int i=0;i<m.i()*m.j();i++){
		mat[i]+=a;
	}
	return mat;
};

matrix operator*(int a, const matrix& m){
	matrix mat(m);
	for(int i=0;i<m.i()*m.j();i++){
		mat[i]*=a;
	}
	return mat;
};

vector operator+(const vector& v2, int a){
	vector v(v2);
	for(int i=0;i<v2.dim();i++){
		v[i]+=a;
	}
	return v;
};

vector operator*(const vector& v2, int a){
	vector v(v2);
	for(int i=0;i<v2.dim();i++){
		v[i]*=a;
	}
	return v;
};

matrix operator+(const matrix& m, int a){
	matrix mat(m);
	for(int i=0;i<m.i()*m.j();i++){
		mat[i]+=a;
	}
	return mat;
};

matrix operator*(const matrix& m, int a){
	matrix mat(m);
	for(int i=0;i<m.i()*m.j();i++){
		mat[i]*=a;
	}
	return mat;
};

vector operator*(const matrix& m, const vector& v){

	assert(m.j()==v.dim());
	vector vv(v.dim());
	for(int i=0;i<v.dim();i++){
		int res = 0;
		for(int j=0;j<v.dim();j++){
			res += m[i*m.j()+j]*v[j];
		}
		vv[i] = res;
	}
}