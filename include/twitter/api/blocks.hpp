#ifndef TWITTER_API_BLOCKS_HPP
#define TWITTER_API_BLOCKS_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace blocks{
				//POST blocks/create
				class create : public twitter_base{
				public:
					create(const string_type format,const string_type id)
						: id_(id), twitter_base("POST","https","api.twitter.com","/1/blocks/create."+format){}
					param_type sort() const{
						param_type sort;
						sort["id"]=id_;
						return sort;
					}
				private:
					const string_type id_;
				};

				//POST blocks/destroy
				class destroy : public twitter_base{
				public:
					destroy(const string_type format,const string_type id)
						: id_(id), twitter_base("DELETE","https","api.twitter.com","/1/blocks/destroy."+format){}
					param_type sort() const{
						param_type sort;
						sort["id"]=id_;
						return sort;
					}
				private:
					const string_type id_;
				};

				//GET blocks/exists
				class exists : public twitter_base{
				public:
					exists(const string_type format,const string_type id)
						: id_(id), twitter_base("GET","https","api.twitter.com","/1/blocks/exists."+format){}
					param_type sort() const{
						param_type sort;
						sort["id"]=id_;
						return sort;
					}
				private:
					const string_type id_;
				};

				//GET blocks/blocking
				class blocking : public twitter_base{
				public:
					blocking(const string_type format,const string_type page="")
						: page_(page), twitter_base("GET","https","api.twitter.com","/1/blocks/blocking."+format){}
					param_type sort() const{
						param_type sort;
						if(!page_.empty()) sort["page"]=page_;
						return sort;
					}
				private:
					const string_type page_;
				};

				//GET blocks/blocking/ids
				class blocking_ids : public twitter_base{
				public:
					blocking_ids(const string_type format)
						: twitter_base("GET","https","api.twitter.com","/1/blocks/blocking/ids."+format){}
				private:
				};
			}//End blocks namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
