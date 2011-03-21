#ifndef TWITTER_API_HELP_HPP
#define TWITTER_API_HELP_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace help{
				//GET help/test
				class test : public twitter_base{
				public:
					test(const string_type format)
						: twitter_base("GET","https","api.twitter.com","/1/help/test."+format){}
				private:
				};
			}//End help namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
