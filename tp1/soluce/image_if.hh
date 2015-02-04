namespace my
{
	template <typename I, typename F>
	class image_if : public Image< image_if<I,F> >
	{
	public:
		typedef typename F::result_type value_type;

		typedef typename I::domain_type domain_type;
		typedef typename I::point_type point_type;
		typedef typename I::p_iterator_type p_iterator_type;
		typedef typename I::n_iterator_type n_iterator_type;

		image_if(const Image<I>& ima, F f)
		: ima_(ima.exact()),
		f_(f)
		{
		};

		value_type operator()(const point_type& p) const
			{
				if (not f(p))
					std::abort();
				return f_(ima_(p));
			}
	private:
		const I& ima_;
		F f_;
	};

	template <typename D, typename F>
	class domaine_if
	{
	public:
		domaine_if(D& d, F& f){
			dom = d;
			fon = f;
		};

		D getD() {return dom;}

		F getF() {return fon;}
		
	private:
		D& dom;
		F& fon;
	};

	template <typename D, typename F>
	class domaine_if_iterator
	{
	public:
		domaine_if_iterator(D& d, F& f){
			dom = d;
			fon = f;
		};

		void start(){
			p_ = dom.pmin();
		}

		bool is_valid(){
			return p_.row <= dom.pmax().row;
		}

		void next(){
			if (not is_valid())
					std::abort();
			p_.col += 1;
			if (p_.col > dom.pmax().col)
			{
				p_.row += 1;
				p_.col = dom.pmin().col;
			}if(!dom.has(p_) || fon(p_) == false) next();
		}
		
	private:
		D& dom;
		F& fon;
		typename D::point_type p_;
	};

	template <typename I, typename F>
	image_if<I,F>
	make_image_if(const Image<I>& ima, F f)
	{
		return image_if<I,F>(ima, f);
	}
}