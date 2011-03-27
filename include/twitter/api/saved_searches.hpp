#ifndef TWITTER_API_SAVED_SEARCHES_HPP
#define TWITTER_API_SAVED_SEARCHES_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace saved_searches{
				//GET saved_searches
				class saved_searches : public twitter_base{
				public:
					saved_searches(const string_type format)
						: twitter_base("GET","https","api.twitter.com","/1/saved_searches."+format){}
				private:
				};

				//GET saved_searches/show/:id
				class show : public twitter_base{
				public:
					show(const string_type format,const string_type id)
						: twitter_base("GET","https","api.twitter.com","/1/saved_searches/show/"+id+"."+format){}
				private:
				};

				//POST saved_searches/create
				class create : public twitter_base{
				public:
					create(const string_type format,const string_type query="")
						: query_(query), twitter_base("POST","https","api.twitter.com","/1/saved_searches/create."+format){}
					param_type sort() const{
						param_type sort;
						if(!query_.empty()) sort["query"]=query_;
						return sort;
					}
				private:
					const string_type query_;
				};

				//POST saved_searches/destroy/:id
				class destroy : public twitter_base{
				public:
					destroy(const string_type format,const string_type id)
						: twitter_base("DELETE","https","api.twitter.com","/1/saved_searches/destroy/"+id+"."+format){}
				private:
				};
			}//End saved_searches namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
