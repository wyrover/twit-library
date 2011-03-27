#ifndef TWITTER_API_SEARCH_HPP
#define TWITTER_API_SEARCH_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace search{
				//GET search
				class search : public twitter_base{
				public:
					search(const string_type format,const string_type q,const string_type callback="",const string_type lang="",const string_type locale="",const string_type rpp="",const string_type page="",const string_type since_id="",const string_type geocode="",const string_type show_user="",const string_type result_type="")
						: q_(q), callback_(callback), lang_(lang), locale_(locale), rpp_(rpp), page_(page), since_id_(since_id), geocode_(geocode), show_user_(show_user), result_type_(result_type), twitter_base("GET","https","search.twitter.com","/search."+format){}
					param_type sort() const{
						param_type sort;
						sort["q"]=q_;
						if(!callback_.empty()) sort["callback"]=callback_;
						if(!lang_.empty()) sort["lang"]=lang_;
						if(!locale_.empty()) sort["locale"]=locale_;
						if(!rpp_.empty()) sort["rpp"]=rpp_;
						if(!page_.empty()) sort["page"]=page_;
						if(!since_id_.empty()) sort["since_id"]=since_id_;
						if(!geocode_.empty()) sort["geocode"]=geocode_;
						if(!show_user_.empty()) sort["show_user"]=show_user_;
						if(!result_type_.empty()) sort["result_type"]=result_type_;
						return sort;
					}
				private:
					const string_type q_;
					const string_type callback_;
					const string_type lang_;
					const string_type locale_;
					const string_type rpp_;
					const string_type page_;
					const string_type since_id_;
					const string_type geocode_;
					const string_type show_user_;
					const string_type result_type_;
				};
			}//End search namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
