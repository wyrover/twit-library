#ifndef TWITTER_API_LEGAL_HPP
#define TWITTER_API_LEGAL_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace legal{
				//GET legal/tos
				class tos : public twitter_base{
				public:
					tos(const string_type format)
						: twitter_base("GET","https","api.twitter.com","/1/legal/tos."+format){}
				private:
				};
				
				//GET legal/privacy
				class privacy : public twitter_base{
				public:
					privacy(const string_type format)
						: twitter_base("GET","https","api.twitter.com","/1/legal/privacy."+format){}
				private:
				};
			}//End legal namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
