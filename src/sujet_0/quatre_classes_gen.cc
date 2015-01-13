#include <iostream>
#include <vector>
#include <cassert>


template <unsigned v1, unsigned v2>
struct equals;

template <unsigned v>
struct equals<v,v>
{
  static void check() {}
};


// concept abstract_algebraic_object
// {
//   unsigned ncells() const;
//   int cell(unsigned i) const;
//   int& cell(unsigned i); // Liskov Substitution Principle (LSP) OK
// };


// concept abstract_vector refines abstract_algebraic_object
// {
//   enum { sdim };
//   unsigned dim() const;
//   int operator[](unsigned i) const; // LSP OK
//   // no write access because it would violate the LSP
// };


// concept abstract_matrix refines abstract_algebraic_object
// {
//   enum { snrows, sncols };
//   unsigned nrows() const;
//   unsigned ncols() const;
//   int operator()(unsigned i, unsigned j) const; // LSP OK
//   // no write access because it would violate the LSP
// };


template <typename T>
struct abstract_algebraic_object
{
  T& itself() { return *(T*)(void*)this; }
  const T& itself() const { return *(const T*)(const void*)this; }
};

template <typename T>
struct abstract_vector : abstract_algebraic_object<T>
{
};

template <typename T>
struct abstract_matrix : abstract_algebraic_object<T>
{
};



template <typename T>
void iota(abstract_algebraic_object<T>& obj_)  // set some dummy values
{
  T& obj = obj_.itself();
  unsigned v = 0;
  for (unsigned i = 0; i < obj.ncells(); ++i)
    obj.cell(i) = ++v;
}


template <typename T>
std::ostream& operator<<(std::ostream& ostr, const abstract_vector<T>& v_)
{
  const T& v = v_.itself();
  const unsigned n = T::sdim;
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
class vector : public abstract_vector< vector<n> >
{
public:

  enum { sdim = n };

  unsigned dim() const
  {
    return n;
  }

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
class one_vector : public abstract_vector< one_vector<n> >
{
public:

  enum { sdim = n };

  unsigned dim() const
  {
    return n;
  }

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



template <typename T>
std::ostream& operator<<(std::ostream& ostr, const abstract_matrix<T>& mat_)
{
  const T& mat = mat_.itself();
  const unsigned n = T::snrows, m = T::sncols;
  for (unsigned i = 0; i < n; ++i)
    {
      for (unsigned j = 0; j < m; ++j)
	ostr << mat(i,j) << ' ';
      ostr << std::endl;
    }
  return ostr;
}



template <unsigned n, unsigned m>
class matrix : public abstract_matrix< matrix<n,m> >
{
public:

  enum { snrows = n, sncols = m };

  unsigned nrows() const
  {
    return n;
  }

  unsigned ncols() const
  {
    return m;
  }

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
class dia_matrix : public abstract_matrix< dia_matrix<n> >
{
public:

  enum { snrows = n, sncols = n };

  unsigned nrows() const
  {
    return n;
  }

  unsigned ncols() const
  {
    return n;
  }

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

template <typename T>
void abstract_fill(abstract_algebraic_object<T>& obj_, int a)
{
  T& obj = obj_.itself();
  for (unsigned i = 0; i < obj.ncells(); ++i)
    obj.cell(i) = a;
}


// matrix * vector

template <typename M, typename V>
vector<M::snrows>
operator*(const abstract_matrix<M>& mat_, const abstract_vector<V>& v_)
{
  equals<M::sncols, V::sdim>::check();

  const M& mat = mat_.itself();
  const V& v = v_.itself();

  const unsigned n = M::snrows, m = M::sncols;

  vector<n> tmp;
  for (unsigned i = 0; i < n; ++i)
    {
      tmp[i] = 0;
      for (unsigned j = 0; j < m; ++j)
	tmp[i] += mat(i,j) * v[j];
    }
  return tmp;
}


template <typename M1, typename M2>
matrix<M1::snrows, M2::sncols>
operator*(const abstract_matrix<M1>& lhs_,
	  const abstract_matrix<M2>& rhs_)
{
  equals<M1::sncols, M2::snrows>::check();

  const M1& lhs = lhs_.itself();
  const M2& rhs = rhs_.itself();

  const unsigned
    n = M1::snrows,
    m = M1::sncols,
    p = M2::sncols;

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


template <unsigned n>
dia_matrix<n> operator*(const dia_matrix<n>& lhs,
			const dia_matrix<n>& rhs)
{
  dia_matrix<n> tmp;
  for (unsigned i = 0; i < n; ++i)
    tmp.cell(i) = lhs.cell(i) * rhs.cell(i);
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

    dia_matrix<3> m2 = m * m;  // NOW works!
    std::cout << m2 << std::endl;
  }
}
