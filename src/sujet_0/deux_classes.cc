#include <iostream>
#include <vector>
#include <cassert>


class vector
{
public:

  explicit vector(unsigned n)
  {
    assert(n != 0); // precondition
    n_ = n;
    data_ = new int[n];
  }

  vector(const vector& rhs)
  {
    assert(rhs.dim() != 0);
    n_ = rhs.n_;
    data_ = new int[n_];
    for (unsigned i = 0; i < n_; ++i)
      data_[i] = rhs.data_[i];
  }

  vector& operator=(const vector& rhs)
  {
    assert(rhs.dim() == this->dim());
    if (&rhs == this)
      return *this;
    n_ = rhs.n_;
    data_ = new int[n_];
    for (unsigned i = 0; i < n_; ++i)
      data_[i] = rhs.data_[i];
    return *this;
  }

  ~vector()
  {
    delete[] data_;
    data_ = 0; // safety
  }

  unsigned dim() const
  {
    return n_;
  }

  int operator[](unsigned i) const
  {
    assert(i < n_);
    return data_[i];
  }

  int& operator[](unsigned i)
  {
    assert(i < n_);
    return data_[i];
  }


  // not a solution:

  void fill(int a)
  {
    std::cout << "code dedicated to vector" << std::endl;
  }


  // soluce: unique interface

  unsigned ncells() const
  {
    return n_;
  }

  int& cell(unsigned i)  // read/write
  {
    assert(i < n_);
    return data_[i];
  }

  int cell(unsigned i) const  // read only
  {
    assert(i < n_);
    return data_[i];
  }

  // end of the unique interface

private:
  unsigned n_;
  int* data_;
};


std::ostream& operator<<(std::ostream& ostr, const vector& v)
{
  ostr << '(';
  for (unsigned i = 0; i < v.dim(); ++i)
    {
      ostr << v[i];
      if (i + 1 < v.dim())
	ostr << ", ";
    }
  return ostr << ')';
}



class matrix
{
public:

  matrix(unsigned n, unsigned m)
  {
    assert(n != 0 and m != 0);
    n_ = n;
    m_ = m;
    data_.resize(n * m);
  }

  unsigned nrows() const
  {
    return n_;
  }

  unsigned ncols() const
  {
    return m_;
  }

  int operator()(unsigned i, unsigned j) const
  {
    assert(i < n_ and j < m_);
    return data_[i * m_ + j];
  }

  int& operator()(unsigned i, unsigned j)
  {
    assert(i < n_ and j < m_);
    return data_[i * m_ + j];
  }

  void iota()  // set some dummy values
  {
    unsigned v = 0;
    for (unsigned i = 0; i < ncells(); ++i)
      cell(i) = ++v;
  }

  // not a solution:

  void fill(int a)
  {
    std::cout << "code dedicated to matrix" << std::endl;
  }


  // soluce: unique interface

  unsigned ncells() const
  {
    return n_ * m_;
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

  // end of the unique interface

private:

  std::vector<int> data_; // so there is no need to define a cpy ctor, an op=, and a dtor
  unsigned n_, m_;
};



template <typename T>
void fill(T& obj, int a)
{
  for (unsigned i = 0; i < obj.ncells(); ++i)
    obj.cell(i) = a;
}


template <typename T>
void fill_bad(T& obj, int a)
{
  obj.fill(a); // writing two methods is cheating...
}


vector operator*(const matrix& m, const vector& v)
{
  vector tmp(m.nrows());
  for (unsigned i = 0; i < m.nrows(); ++i)
    {
      tmp[i] = 0;
      for (unsigned j = 0; j < m.ncols(); ++j)
	tmp[i] += m(i,j) * v[j];
    }
  return tmp;
}


int main()
{
  vector v(3);
  matrix m(2,3);
  m.iota();

  fill(v, 1);
  std::cout << v << std::endl;

  std::cout << m * v << std::endl;
}
