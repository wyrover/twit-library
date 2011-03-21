#ifndef TWITTER_API_NOTIFICATIONS_HPP
#define TWITTER_API_NOTIFICATIONS_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace notifications{
				//POST notifications/follow
				class follow : public twitter_base{
				public:
					follow(const string_type format,const string_type id)
						: id_(id), twitter_base("POST","https","api.twitter.com","/1/notifications/follow."+format){}
					param_type sort() const{
						param_type sort;
						sort["id"]=id_;
						return sort;
					}
				private:
					const string_type id_;
				};

				//POST notifications/leave
				class leave : public twitter_base{
				public:
					leave(const string_type format,const string_type id)
						: id_(id), twitter_base("POST","https","api.twitter.com","/1/notifications/leave."+format){}
					param_type sort() const{
						param_type sort;
						sort["id"]=id_;
						return sort;
					}
				private:
					const string_type id_;
				};
			}//End notifications namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
