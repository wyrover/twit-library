#ifndef HATENA_API_STAR_HPP
#define HATENA_API_STAR_HPP

namespace oauth{
	namespace api{
		namespace hatena{
			namespace star{
					//はてなスターカウントAPI
					class count : public hatena_base{
					public:
						count(const string_type& url)
							: hatena_base("GET","http","s.hatena.ne.jp","/blog.json/"+url){}
					private:
					};
					
			}//End star namespace
		}//End hatena namespace
	}//End api namespace
}//End oauth namespace

#endif
