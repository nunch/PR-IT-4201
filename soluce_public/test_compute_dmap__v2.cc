#include "image2d.hh"
#include "image_if.hh"
#include "helper.hh"
#include "compute_dmap__v2.hh"




int main()
{
  using namespace my;

  box2d b(4, 5);

  bool_t msk_dta[]   = {0, 0, 0, 0, 1,
			1, 1, 1, 1, 0,
			0, 0, 0, 1, 1,
			1, 1, 1, 0, 1};

  unsigned lab_dta[] = {0, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			2, 0, 0, 0, 0};

  image2d<bool_t> msk(b);
  msk.fill(msk_dta);
  msk.debug_print();
  // gives:
  //
  // 0 0 0 0 1 
  // 1 1 1 1 0 
  // 0 0 0 1 1 
  // 1 1 1 0 1 

  image2d<unsigned> lab(b); // this is the "seed" label image
  lab.fill(lab_dta);
  lab.debug_print();
  // gives:
  //
  // 0 0 0 0 0 
  // 1 0 0 0 0 
  // 0 0 0 0 0 
  // 2 0 0 0 0 

  image_if<image2d<unsigned>, image2d<bool_t> > image = make_image_if(lab, msk);
  fancy_print(image, b);
  // gives:
  //
  //         0
  // 1 0 0 0  
  //       0 0
  // 2 0 0   0


  {
    image2d<unsigned> dmap = compute_dmap__v2(lab);
    dmap.debug_print();
    // gives:
    // 
    // 1 2 3 4 5
    // 0 1 2 3 4
    // 1 2 3 4 5
    // 0 1 2 3 4


    // THIS RESULT IS CORRECT BUT...  THIS IS *NOT* WHAT WE WANT!  :-(

    //fancy_print( make_image_if(dmap, msk), b );
    image_if<image2d<unsigned>, image2d<bool_t> > image2 = make_image_if(dmap, msk);
    //fancy_print(image2.getF(),image2.getF().domain());
    //image = make_image_if(dmap, msk)
    fancy_print(image2,b);

    //fancy_print(image2.getIma(),b);
    //fancy_print(dmap,b);


    //std::cout << "msk\n" << image2.getF()*/msk << std::endl;
    //std::cout << image2.getF() << std::endl;
    //std::cout << image << std::endl;
    // gives:
    //
    //         5 
    // 0 1 2 3   
    //       4 5 
    // 0 1 2   4 
    //std::cout << msk << std::endl;
    //std::cout << image.domain() << std::endl;
    //domaine_if<box2d,image2d<bool_t> > d(image.domain());
    //domaine_if_iterator<box2d,image2d<bool_t> > p(d);
    //std::cout << image.getF()<< std::endl;
    
    // WE WANT TO COMPUTE THE DISTANCE MAP *WITHIN* THE MASK:
    //compute_dmap__COMPUTE THE DISTANCE MAP *WITHIN* THE MASK:
    //compute_dmap__COMPUTE THE DISTANCE MAP *WITHIN* THE MASK:
    //compute_dmap__v2v2COMPUTE THE DISTANCE MAP *WITHIN* THE MASK:
    //compute_dmap__v2v2(make_image_if(lab, msk));
    //fancy_print(lab,b);
    //fancy_print(msk,b);
    fancy_print( compute_dmap__v2v2(make_image_if(lab, msk)), b );
    // gives:
    //
    //         4294967295 <- this value is MAX, i.e., unsigned(-1)
    // 0 1 2 3   
    //       4 5 
    // 0 1 2   6 

    // THAT IS THE *EXPECTED* RESULT  :-)
  }


  {
    helper f(lab);
    fancy_print(compute_dmap__v2(make_image_if(lab, msk),f),b);//, f);//.remove_if();

    //dmap.debug_print();
    // gives:
    //
    // 0 0 0 0 4294967295 
    // 0 1 2 3 0 
    // 0 0 0 4 5 
    // 0 1 2 0 6 

    f.iz.debug_print(); // 'iz' means "influence zone" of a seed
    // gives:
    //
    // 0 0 0 0 0 <- this pixel cannot be reached from a seed
    // 1 1 1 1 0 
    // 0 0 0 1 1 
    // 2 2 2 0 1

    f.prev.debug_print();
    // gives:
    //
    // (0,0) (0,1) (0,2) (0,3) (0,4) 
    // (1,0) (1,0) (1,1) (1,2) (1,4) 
    // (2,0) (2,1) (2,2) (1,3) (2,3) 
    // (3,0) (3,0) (3,1) (3,3) (2,4) 
    f.next.debug_print();
  }

}
