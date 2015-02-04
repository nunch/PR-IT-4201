void fillmatrix(matrix& m, int a){
	for(int i=0;i<m.i()*m.j();i++){
		m[i] = a;
	}
}