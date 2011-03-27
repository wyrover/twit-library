#ifndef TWITTER_API_DIRECT_MESSAGES_HPP
#define TWITTER_API_DIRECT_MESSAGES_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace direct_messages{
				//GET direct_messages
				class direct_messages : public twitter_base{
				public:
					direct_messages(const string_type format,const string_type since_id="",const string_type max_id="",const string_type count="",const string_type page="")
						: since_id_(since_id), max_id_(max_id), count_(count), page_(page), twitter_base("GET","https","api.twitter.com","/1/direct_messages."+format){}
					param_type sort() const{
						param_type sort;
						if(!since_id_.empty()) sort["since_id"]=since_id_;
						if(!max_id_.empty()) sort["max_id"]=max_id_;
						if(!count_.empty()) sort["count"]=count_;
						if(!page_.empty()) sort["page"]=page_;
						return sort;
					}
				private:
					const string_type since_id_;
					const string_type max_id_;
					const string_type count_;
					const string_type page_;
				};
				
				//GET direct_messages/sent
				class sent : public twitter_base{
				public:
					sent(const string_type format,const string_type since_id="",const string_type max_id="",const string_type count="",const string_type page="")
						: since_id_(since_id), max_id_(max_id), count_(count), page_(page), twitter_base("GET","https","api.twitter.com","/1/direct_messages/sent."+format){}
					param_type sort() const{
						param_type sort;
						if(!since_id_.empty()) sort["since_id"]=since_id_;
						if(!max_id_.empty()) sort["max_id"]=max_id_;
						if(!count_.empty()) sort["count"]=count_;
						if(!page_.empty()) sort["page"]=page_;
						return sort;
					}
				private:
					const string_type since_id_;
					const string_type max_id_;
					const string_type count_;
					const string_type page_;
				};
				
				//POST direct_messages/new
				class new_ : public twitter_base{
				public:
					new_(const string_type format,const string_type user,const string_type text)
						: user_(user), text_(text), twitter_base("POST","https","api.twitter.com","/1/direct_messages/new."+format){}
					param_type sort() const{
						param_type sort;
						sort["user"]=user_;
						sort["text"]=text_;
						return sort;
					}
				private:
					const string_type user_;
					const string_type text_;
				};
				
				//POST direct_messages/destroy/:id
				class destroy : public twitter_base{
				public:
					destroy(const string_type format,const string_type id)
						: twitter_base("DELETE","https","api.twitter.com","/1/direct_messages/destroy/"+id+"."+format){}
				private:
				};
			}//End direct_messages namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
