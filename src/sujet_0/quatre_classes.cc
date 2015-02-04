#include <iostream>
#include <vector>
#include <cassert>



class abstract_algebraic_object
{
public:

  // cell = a data memory cell (not a mathematical one)
  virtual unsigned ncells() const = 0;
  virtual int cell(unsigned i) const = 0;
  virtual int& cell(unsigned i) = 0; // Liskov Substitution Principle (LSP) OK

  virtual ~abstract_algebraic_object() {}
};


void iota(abstract_algebraic_object& obj)  // set some dummy values
{
  unsigned v = 0;
  for (unsigned i = 0; i < obj.ncells(); ++i)
    obj.cell(i) = ++v;
}


template <unsigned n>
class abstract_vector : public abstract_algebraic_object
{
public:
  unsigned dim() const { return n; }

  virtual int operator[](unsigned i) const = 0; // LSP OK
  // no write access because it would violate the LSP
};


template <> class abstract_vector<0>; // does not exist


template <unsigned n>
std::ostream& operator<<(std::ostream& ostr, const abstract_vector<n>& v)
{
  ostr << '(';
  for (unsigned i = 0; i < n; ++i)
    {
      ostr << v[i];
      if (i + 1 < n)
	ostr << ", ";
    }
  return ostr << ')';
}


template <unsigned n>
class vector : public abstract_vector<n>
{
public:

  unsigned ncells() const
  {
    return n;
  }

  int& cell(unsigned i)  // read/write
  {
    assert(i < n);
    return data_[i];
  }

  int cell(unsigned i) const  // read only
  {
    assert(i < n);
    return data_[i];
  }

  int operator[](unsigned i) const
  {
    assert(i < n);
    return data_[i];
  }

  int& operator[](unsigned i)
  {
    assert(i < n);
    return data_[i];
  }

private:
  int data_[n];
};



template <unsigned n>
class one_vector : public abstract_vector<n>
{
public:

  unsigned ncells() const
  {
    return 1;
  }

  int& cell(unsigned i)  // read/write
  {
    assert(i < n);
    return value_;
  }

  int cell(unsigned i) const  // read only
  {
    assert(i < n);
    return value_;
  }

  int operator[](unsigned i) const
  {
    assert(i < n);
    return value_;
  }

  int& operator[](unsigned i)
  {
    assert(i < n);
    return value_;
  }

private:
  int value_;
};


template <unsigned n, unsigned m>
class abstract_matrix : public abstract_algebraic_object
{
public:

  unsigned nrows() const { return n; }
  unsigned ncols() const { return m; }

  virtual int operator()(unsigned i, unsigned j) const = 0; // LSP OK
  // no write access because it would violate the LSP
};


template <unsigned n> class abstract_matrix<n,0>;
template <unsigned m> class abstract_matrix<0,m>; // do not exist



template <unsigned n, unsigned m>
std::ostream& operator<<(std::ostream& ostr, const abstract_matrix<n,m>& mat)
{
  for (unsigned i = 0; i < n; ++i)
    {
      for (unsigned j = 0; j < m; ++j)
	ostr << mat(i,j) << ' ';
      ostr << std::endl;
    }
  return ostr;
}



template <unsigned n, unsigned m>
class matrix : public abstract_matrix<n,m>
{
public:

  int operator()(unsigned i, unsigned j) const
  {
    assert(i < n and j < m);
    return data_[i * m + j];
  }

  int& operator()(unsigned i, unsigned j)
  {
    assert(i < n and j < m);
    return data_[i * m + j];
  }

  unsigned ncells() const
  {
    return n * m;
  }

  int& cell(unsigned i)  // read/write
  {
    assert(i < ncells());
    return data_[i];
  }

  int cell(unsigned i) const  // read only
  {
    assert(i < ncells());
    return data_[i];
  }

private:

  int data_[n * m];
};


template <unsigned n>
class dia_matrix : public abstract_matrix<n,n>
{
public:

  int operator()(unsigned i, unsigned j) const
  {
    assert(i < n and j < n);
    return i == j ? data_[i] : 0;
  }

  // cannot be implemented:
  // int& operator()(unsigned i, unsigned j);

  unsigned ncells() const
  {
    return n;
  }

  int& cell(unsigned i)  // read/write
  {
    assert(i < ncells());
    return data_[i];
  }

  int cell(unsigned i) const  // read only
  {
    assert(i < ncells());
    return data_[i];
  }

private:

  int data_[n];
};




template <typename T>
void generic_fill(T& obj, int a)
{
  for (unsigned i = 0; i < obj.ncells(); ++i)
    obj.cell(i) = a;
}

void abstract_fill(abstract_algebraic_object& obj, int a)
{
  for (unsigned i = 0; i < obj.ncells(); ++i)
    obj.cell(i) = a;
}


template <unsigned n, unsigned m>
vector<n> operator*(const abstract_matrix<n,m>& mat, const abstract_vector<m>& v)
{
  vector<n> tmp;
  for (unsigned i = 0; i < n; ++i)
    {
      tmp[i] = 0;
      for (unsigned j = 0; j < m; ++j)
	tmp[i] += mat(i,j) * v[j];
    }
  return tmp;
}

template <unsigned n, unsigned m, unsigned p>
matrix<n,p> operator*(const abstract_matrix<n,m>& lhs,
		      const abstract_matrix<m,p>& rhs)
{
  matrix<n,p> tmp;
  for (unsigned i = 0; i < n; ++i)
    for (unsigned j = 0; j < p; ++j)
      {
	unsigned tij = 0;
	for (unsigned k = 0; k < m; ++k)
	  tij += lhs(i,k) * rhs(k,j);
	tmp(i,j) = tij;
    }
  return tmp;
}


int main()
{
  {
    vector<3> v;
    matrix<2,3> m;
    iota(m);

    abstract_fill(v, 1);
    std::cout << v << std::endl;

    std::cout << m * v << std::endl;
    // m * (m * v)  does not work and that's fine...
  }

  {
    dia_matrix<3> m;
    iota(m);
    std::cout << m * m << std::endl;

    // dia_matrix<3> m2 = m * m;    does not work...
  }
}
