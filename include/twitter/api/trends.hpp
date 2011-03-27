#ifndef TWITTER_API_TRENDS_HPP
#define TWITTER_API_TRENDS_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace trends{
				//GET trends
				class trends : public twitter_base{
				public:
					trends()
						: twitter_base("GET","https","api.twitter.com","/1/trends.json"){}
				private:
				};

				//GET trends/current
				class current : public twitter_base{
				public:
					current(const string_type exclude="")
						: exclude_(exclude), twitter_base("GET","https","api.twitter.com","/1/trends/current.json"){}
					param_type sort() const{
						param_type sort;
						if(!exclude_.empty()) sort["exclude"]=exclude_;
						return sort;
					}
				private:
					const string_type exclude_;
				};

				//GET trends/daily
				class daily : public twitter_base{
				public:
					daily(const string_type year="",const string_type month="",const string_type day="",const string_type exclude="")
						: date_(year+"-"+month+"-"+day), exclude_(exclude), twitter_base("GET","https","api.twitter.com","/1/trends/daily.json"){}
					param_type sort() const{
						param_type sort;
						if(!date_.empty()) sort["date"]=date_;
						if(!exclude_.empty()) sort["exclude"]=exclude_;
						return sort;
					}
				private:
					const string_type date_;
					const string_type exclude_;
				};

				//GET trends/weekly
				class weekly : public twitter_base{
				public:
					weekly(const string_type year="",const string_type month="",const string_type day="",const string_type exclude="")
						: date_(year+"-"+month+"-"+day), exclude_(exclude), twitter_base("GET","https","api.twitter.com","/1/trends/weekly.json"){}
					param_type sort() const{
						param_type sort;
						if(!date_.empty()) sort["date"]=date_;
						if(!exclude_.empty()) sort["exclude"]=exclude_;
						return sort;
					}
				private:
					const string_type date_;
					const string_type exclude_;
				};

				//GET trends/available
				class available : public twitter_base{
				public:
					available(const string_type format,const string_type lat="",const string_type vlong="")
						: lat_(lat), long_(vlong), twitter_base("GET","https","api.twitter.com","/1/trends/available."+format){}
					param_type sort() const{
						param_type sort;
						if((!lat_.empty())&&(!long_.empty())){
							sort["lat"]=lat_;
							sort["long"]=long_;
						}
						return sort;
					}
				private:
					const string_type lat_;
					const string_type long_;
				};

				//GET trends/location(:woeid)
				class location : public twitter_base{
				public:
					location(const string_type format,const string_type woeid)
						: twitter_base("GET","https","api.twitter.com","/1/trends/"+woeid+"."+format){}
				private:
				};
			}//End trends namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
