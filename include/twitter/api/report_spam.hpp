#ifndef TWITTER_API_REPORT_SPAM_HPP
#define TWITTER_API_REPORT_SPAM_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace report_spam{
				//POST report_spam
				class create : public twitter_base{
				public:
					create(const string_type format,const string_type id)
						: id_(id), twitter_base("POST","https","api.twitter.com","/1/report_spam."+format){}
					param_type sort() const{
						param_type sort;
						sort["id"]=id_;
						return sort;
					}
				private:
					const string_type id_;
				};
			}//End report_spam namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
