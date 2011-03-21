#ifndef TWITTER_API_FAVORITES_HPP
#define TWITTER_API_FAVORITES_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace favorites{
				//GET favorites
				class favorites : public twitter_base{
				public:
					favorites(const string_type format,const string_type id="",const string_type page="")
						: id_(id), page_(page), twitter_base("GET","https","api.twitter.com","/1/favorites"+format){}
					param_type sort() const{
						param_type sort;
						if(id_!="") sort["id"]=id_;
						if(page_!="") sort["page"]=page_;
						return sort;
					}
				private:
					const string_type id_;
					const string_type page_;
				};

				//POST favorites/create/:id
				class create : public twitter_base{
				public:
					create(const string_type format,const string_type id)
						: twitter_base("POST","https","api.twitter.com","/1/favorites/create/"+id+"."+format){}
				private:
				};

				//POST favorites/destroy/:id
				class destroy : public twitter_base{
				public:
					destroy(const string_type format,const string_type id)
						: twitter_base("DELETE","https","api.twitter.com","/1/favorites/destroy/"+id+"."+format){}
				private:
				};
			}//End favorites namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
