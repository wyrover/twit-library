#ifndef TWITTER_API_FRIENDS_FOLLOWERS_HPP
#define TWITTER_API_FRIENDS_FOLLOWERS_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace friends{
				//GET friends/ids
				class ids : public twitter_base{
				public:
					ids(const string_type format,const string_type id,const string_type cursor="")
						: id_(id), cursor_(cursor), twitter_base("GET","https","api.twitter.com","/1/friends/ids."+format){}
					param_type sort() const{
						param_type sort;
						sort["id"]=id_;
						if(cursor_!="") sort["cursor"]=cursor_;
						return sort;
					}
				private:
					const string_type id_;
					const string_type cursor_;
				};
			}//End friends namespace

			namespace followers{
				//GET followers/ids
				class ids : public twitter_base{
				public:
					ids(const string_type format,const string_type id,const string_type cursor="")
						: id_(id), cursor_(cursor), twitter_base("GET","https","api.twitter.com","/1/friends/ids."+format){}
					param_type sort() const{
						param_type sort;
						sort["id"]=id_;
						if(cursor_!="") sort["cursor"]=cursor_;
						return sort;
					}
				private:
					const string_type id_;
					const string_type cursor_;
				};
			}//End followers namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
