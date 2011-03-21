#ifndef TWITTER_API_USERS_HPP
#define TWITTER_API_USERS_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace users{
				//GET users/show
				class show : public twitter_base{
				public:
					show(const string_type format,const string_type user_id="",const string_type screen_name="")
						: user_id_(user_id), screen_name_(screen_name), twitter_base("GET","https","api.twitter.com","/1/users/show."+format){}
					param_type sort() const{
						param_type sort;
						if(user_id_!="") sort["user_id"]=user_id_;
						if(screen_name_!="") sort["screen_name"]=screen_name_;
						return sort;
					}
				private:
					const string_type user_id_;
					const string_type screen_name_;
				};

				//GET users/lookup
				class lookup : public twitter_base{
				public:
					lookup(const string_type format,const string_type user_id="",const string_type screen_name="")
						: user_id_(user_id), screen_name_(screen_name), twitter_base("GET","https","api.twitter.com","/1/users/lookup."+format){}
					param_type sort() const{
						param_type sort;
						if(user_id_!="") sort["user_id"]=user_id_;
						if(screen_name_!="") sort["screen_name"]=screen_name_;
						return sort;
					}
				private:
					const string_type user_id_;
					const string_type screen_name_;
				};

				//GET users/search
				class search : public twitter_base{
				public:
					search(const string_type format,const string_type q,const string_type per_page="",const string_type page="")
						: q_(q), per_page_(per_page), page_(page), twitter_base("GET","https","api.twitter.com","/1/users/search."+format){}
					param_type sort() const{
						param_type sort;
						sort["q"]=q_;
						if(per_page_!="") sort["per_page"]=per_page_;
						if(page_!="") sort["page"]=page_;
						return sort;
					}
				private:
					const string_type q_;
					const string_type per_page_;
					const string_type page_;
				};

				//GET users/suggestions
				class suggestions : public twitter_base{
				public:
					suggestions(const string_type format)
						: twitter_base("GET","https","api.twitter.com","/1/users/suggestions."+format){}
				private:
				};

				//GET users/suggestions/:slug
				class suggestions_slug : public twitter_base{
				public:
					suggestions_slug(const string_type format,const string_type slug)
						: twitter_base("GET","https","api.twitter.com","/1/users/suggestions/"+slug+"."+format){}
				private:
				};

				//GET users/profile_image/:screen_name
				class profile_image : public twitter_base{
				public:
					profile_image(const string_type format,const string_type screen_name,const string_type size="")
						: size_(size), twitter_base("GET","https","api.twitter.com","/1/users/profile_image/"+screen_name+"."+format){}
					param_type sort() const{
						param_type sort;
						if(size_!="") sort["size"]=size_;
						return sort;
					}
				private:
					const string_type size_;
				};

			}//End users namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
