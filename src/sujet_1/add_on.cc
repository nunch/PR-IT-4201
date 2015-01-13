
template <typename T>
class set_image2d
{
public:
  
  T operator()(const point2d& p) const
  {
    assert(D_.find(p) != D_.end());
    return data_[p];
  }
private:
  std::set<point2d> D_;
  std::map<point2d,T> data_;
};

point2d operator+(const point2d& p1, const point2d& p2)
{
}


class neighb2d
{
  //...
  std::vector<point2d> dpoint2d_; // (-1,0), (0,-1), (0,1), (1,1)
};


class neighb2d_iterator
{
public:
  neighb2d_iterator(const std::vector<point2d>& neighb2d);
  void center_at(const point2d& p_center)
  {
    p_center_ = p_center;
  }
  void start() { i_ = 0; }
  void next() { ++i_; }
  bool is_ok() const { return i < neighb2d_.size(); }
  point2d value() const
  {
    return p_center_ + neighb2d_[i];
  }
private:
  std::vector<point2d> neighb2d_; // (-1,0), (0,-1), (0,1), (1,1)
  point2d p_center_;
  unsigned i_;
};

// p = (2,3)
// i -> start (1,3), next (2,2)  next (2,4), next (3,3), not is_ok


// 
// while q is not empty
// , p <- q.pop()
// , for all n in N(p)

{
  std::vector<point2d> N; // ... (-1,0), (0,-1), (0,1), (1,1)
  neighb2d_iterator n(N);
  
  while (not q.empty())
    {
      point2d p = q.front();
      q.pop();
      n.center_at(p);
      for (n.start(); n.is_ok(); n.next())
	;
    }

}
