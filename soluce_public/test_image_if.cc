#include "image_if.hh"


int main()
{
  using namespace my;

  box2d b(2, 3);

  bool_t msk_dta[] = {
          0, 0, 1,
		      1, 0, 0};
  image2d<bool_t> msk(b);
  msk.fill(msk_dta);
  fancy_print(msk, b);

  image2d<int> ima(b);
  debug_iota(ima);
  fancy_print(ima, b);

  fancy_print(make_image_if(ima, msk),b);
  image_if<image2d<int>, image2d<bool_t> > image = make_image_if(ima, msk);
  domaine_if<box2d,image2d<bool_t> > d(image.domain());
  domaine_if_iterator<box2d,image2d<bool_t> > p(d);
  //image(point2d(0,0));
  for_all(p) {
    std::cout << p;
    image(p)=5;
  }
  std::cout << std::endl;
  fancy_print(image,b);


}
