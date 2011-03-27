#ifndef TWITTER_API_GEO_HPP
#define TWITTER_API_GEO_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace geo{
				//GET geo/nearby_places
				class nearby_places : public twitter_base{
				public:
					nearby_places(const string_type lat="",const string_type vlong="",const string_type query="",const string_type ip="",const string_type granularity="",const string_type accuracy="",const string_type max_results="")
						: lat_(lat), long_(vlong), query_(query), ip_(ip), granularity_(granularity), accuracy_(accuracy), max_results_(max_results), twitter_base("GET","https","api.twitter.com","/1/geo/nearby_places.json"){}
					param_type sort() const{
						param_type sort;
						if(!lat_.empty()) sort["lat"]=lat_;
						if(!long_.empty()) sort["long"]=long_;
						if(!query_.empty()) sort["query"]=query_;
						if(!ip_.empty()) sort["ip"]=ip_;
						if(!granularity_.empty()) sort["granularity"]=granularity_;
						if(!accuracy_.empty()) sort["accuracy"]=accuracy_;
						if(!max_results_.empty()) sort["max_results"]=max_results_;
						return sort;
					}
				private:
					const string_type lat_;
					const string_type long_;
					const string_type query_;
					const string_type ip_;
					const string_type granularity_;
					const string_type accuracy_;
					const string_type max_results_;
				};
				
				//GET geo/search
				class search : public twitter_base{
				public:
					search(const string_type lat="",const string_type vlong="",const string_type query="",const string_type ip="",const string_type granularity="",const string_type accuracy="",const string_type max_results="",const string_type contained_within="",const string_type attribute_street_address="",const string_type callback="")
						: lat_(lat), long_(vlong), query_(query), ip_(ip), granularity_(granularity), accuracy_(accuracy), max_results_(max_results), contained_within_(contained_within), attribute_street_address_(attribute_street_address), callback_(callback), twitter_base("GET","https","api.twitter.com","/1/geo/search.json"){}
					param_type sort() const{
						param_type sort;
						if(!lat_.empty()) sort["lat"]=lat_;
						if(!long_.empty()) sort["long"]=long_;
						if(!query_.empty()) sort["query"]=query_;
						if(!ip_.empty()) sort["ip"]=ip_;
						if(!granularity_.empty()) sort["granularity"]=granularity_;
						if(!accuracy_.empty()) sort["accuracy"]=accuracy_;
						if(!max_results_.empty()) sort["max_results"]=max_results_;
						if(!contained_within_.empty()) sort["contained_within"]=contained_within_;
						if(!attribute_street_address_.empty()) sort["attribute:street_address"]=attribute_street_address_;
						if(!callback_.empty()) sort["callback"]=callback_;
						return sort;
					}
				private:
					const string_type lat_;
					const string_type long_;
					const string_type query_;
					const string_type ip_;
					const string_type granularity_;
					const string_type accuracy_;
					const string_type max_results_;
					const string_type contained_within_;
					const string_type attribute_street_address_;
					const string_type callback_;
				};
				
				//GET geo/similar_places
				class similar_places : public twitter_base{
				public:
					similar_places(const string_type lat,const string_type vlong,const string_type name,const string_type contained_within="",const string_type attribute_street_address="",const string_type callback="")
						: lat_(lat), long_(vlong), name_(name), contained_within_(contained_within), attribute_street_address_(attribute_street_address), callback_(callback), twitter_base("GET","https","api.twitter.com","/1/geo/similar_places.json"){}
					param_type sort() const{
						param_type sort;
						sort["lat"]=lat_;
						sort["long"]=long_;
						if(!name_.empty()) sort["name"]=name_;
						if(!contained_within_.empty()) sort["contained_within"]=contained_within_;
						if(!attribute_street_address_.empty()) sort["attribute:street_address"]=attribute_street_address_;
						if(!callback_.empty()) sort["callback"]=callback_;
						return sort;
					}
				private:
					const string_type lat_;
					const string_type long_;
					const string_type name_;
					const string_type contained_within_;
					const string_type attribute_street_address_;
					const string_type callback_;
				};
				
				//GET geo/reverse_geocode
				class reverse_geocode : public twitter_base{
				public:
					reverse_geocode(const string_type lat,const string_type vlong,const string_type accuracy="",const string_type granularity="",const string_type max_results="",const string_type callback="")
						: lat_(lat), long_(vlong), accuracy_(accuracy), granularity_(granularity), max_results_(max_results), callback_(callback), twitter_base("GET","https","api.twitter.com","/1/geo/reverse_geocode.json"){}
					param_type sort() const{
						param_type sort;
						sort["lat"]=lat_;
						sort["long"]=long_;
						if(!accuracy_.empty()) sort["accuracy"]=accuracy_;
						if(!granularity_.empty()) sort["granularity"]=granularity_;
						if(!max_results_.empty()) sort["max_results"]=max_results_;
						if(!callback_.empty()) sort["callback"]=callback_;
						return sort;
					}
				private:
					const string_type lat_;
					const string_type long_;
					const string_type accuracy_;
					const string_type granularity_;
					const string_type max_results_;
					const string_type callback_;
				};
				
				//GET geo/id/:place_id
				class id : public twitter_base{
				public:
					id(const string_type place_id)
						: twitter_base("GET","https","api.twitter.com","/1/geo/id/"+place_id+".json"){}
				private:
				};
				
				//POST geo/place
				class place : public twitter_base{
				public:
					place(const string_type name,const string_type contained_within,const string_type token,const string_type lat,const string_type vlong,const string_type attribute_street_address="",const string_type callback="")
						: name_(name), contained_within_(contained_within), token_(token), lat_(lat), long_(vlong), attribute_street_address_(attribute_street_address), callback_(callback), twitter_base("POST","https","api.twitter.com","/1/geo/place.json"){}
					param_type sort() const{
						param_type sort;
						sort["name"]=name_;
						sort["contained_within"]=contained_within_;
						sort["token"]=token_;
						sort["lat"]=lat_;
						sort["long"]=long_;
						if(!attribute_street_address_.empty()) sort["attribute:street_address"]=attribute_street_address_;
						if(!callback_.empty()) sort["callback"]=callback_;
						return sort;
					}
				private:
					const string_type name_;
					const string_type contained_within_;
					const string_type token_;
					const string_type lat_;
					const string_type long_;
					const string_type attribute_street_address_;
					const string_type callback_;
				};				
			}//End geo namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
