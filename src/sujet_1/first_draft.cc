
// image

struct point2d
{
  point2d() {};
  point2d(int row, int col) { this->row = row; this->col = col; }
  int row, col;
};


struct box2d
{
  // ...
  bool has(const point2d& p) const
  { // is p in this box2d?
    // ...
  };
  point2d pmin, pmax;
};



class box2d_iterator
{
public:

  typedef point2d value_type;
  void start() { pcur_ = b_.pmin; }
  bool is_ok() const;
  void next();
  
  value_type value() { return pcur_; } // ou
  operator XXX() const;

private:
  box2d b_;
  point2d pcur_;
};


void test_box2d_iterator(const box2d& b)
{
  box2d_iterator p(b);
  for (p.start(); p.is_ok(); p.next())
    std::cout << p.value() << ' ';
  std::cout << std::endl;

  // b = (pmin=(0,0), pmax=(1,2))
  // output:
  // (0,0), (0,1), (0,2), (1,0), (1,1), (1,2)
}



template <typename T>
class image2d
{
public:

  image2d(unsigned nrows, unsigned ncols)
  {
    assert(nrows != 0 and ncols != 0);
    nrows_ = nrows;
    ncols_ = ncols;
    data_.resize(nrows * ncols);
  };

  // no cpy ctor
  // no op=
  // no dtor

  // read only
  T operator()(const point2d& p) const;
  T operator()(int row, int col) const;

  T& operator()(int row, int col);

  box2d domain() const { return b_; }

private:

  std::vector<T> data_;
  box2d b_;
  // better than unsigned nrows_, ncols_;
};



struct iterator_like
{
  typedef XXX value_type;
  void start();
  bool is_ok() const;
  void next();
  
  value_type value(); // ou
  operator XXX() const;
};


int main()
{

  for (p.start(); p.is_ok(); p.next())
    do_something_with(p.value());

}
