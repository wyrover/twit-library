#ifndef TWITTER_API_LIST_HPP
#define TWITTER_API_LIST_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace user{
				namespace lists{
					//POST :user/lists(POST lists)
					class lists_post : public twitter_base{
					public:
						lists_post(const string_type format,const string_type user,const string_type name,const string_type mode="",const string_type description="")
							: name_(name), mode_(mode), description_(description), twitter_base("POST","https","api.twitter.com","/1/"+user+"/lists."+format){}
						param_type sort() const{
							param_type sort;
							sort["name"]=name_;
							if(!mode_.empty()) sort["mode"]=mode_;
							if(!description_.empty()) sort["description"]=description_;
							return sort;
						}
					private:
						const string_type name_;
						const string_type mode_;
						const string_type description_;
					};

					//POST :user/lists/:id(POST list id)
					class lists_id_post : public twitter_base{
					public:
						lists_id_post(const string_type format,const string_type user,const string_type id,const string_type name="",const string_type mode="",const string_type description="")
							: name_(name), mode_(mode), description_(description), twitter_base("POST","https","api.twitter.com","/1/"+user+"/lists/"+id+"."+format){}
						param_type sort() const{
							param_type sort;
							if(!name_.empty()) sort["name"]=name_;
							if(!mode_.empty()) sort["mode"]=mode_;
							if(!description_.empty()) sort["description"]=description_;
							return sort;
						}
					private:
						const string_type name_;
						const string_type mode_;
						const string_type description_;
					};

					//GET :user/lists(GET lists)
					class lists_get : public twitter_base{
					public:
						lists_get(const string_type format,const string_type user,const string_type cursor="")
							: cursor_(cursor), twitter_base("GET","https","api.twitter.com","/1/"+user+"/lists."+format){}
						param_type sort() const{
							param_type sort;
							if(!cursor_.empty()) sort["cursor"]=cursor_;
							return sort;
						}
					private:
						const string_type cursor_;
					};

					//GET :user/lists/:id(GET list id)
					class lists_id_get : public twitter_base{
					public:
						lists_id_get(const string_type format,const string_type user,const string_type id)
							: twitter_base("GET","https","api.twitter.com","/1/"+user+"/lists/"+id+"."+format){}
					private:
					};

					//DELETE :user/lists/:id(DELETE list id)
					class lists_id_delete : public twitter_base{
					public:
						lists_id_delete(const string_type format,const string_type user,const string_type id)
							: twitter_base("DELETE","https","api.twitter.com","/1/"+user+"/lists/"+id+"."+format){}
					private:
					};

					//GET :user/lists/:id/statuses(GET list statuses)
					class lists_id_status : public twitter_base{
					public:
						lists_id_status(const string_type format,const string_type user,const string_type id,const string_type since_id="",const string_type max_id="",const string_type per_page="",const string_type page="")
							:  since_id_(since_id), max_id_(max_id), per_page_(per_page), page_(page), twitter_base("GET","https","api.twitter.com","/1/"+user+"/lists/"+id+"/statuses."+format){}
						param_type sort() const{
							param_type sort;
							if(!since_id_.empty()) sort["since_id"]=since_id_;
							if(!max_id_.empty()) sort["max_id"]=max_id_;
							if(!per_page_.empty()) sort["per_page"]=per_page_;
							if(!page_.empty()) sort["page"]=page_;
							return sort;
						}
					private:
						const string_type since_id_;
						const string_type max_id_;
						const string_type per_page_;
						const string_type page_;
					};
					
					//GET :user/lists/memberships(GET list memberships)
					class lists_memberships : public twitter_base{
					public:
						lists_memberships(const string_type format,const string_type user,const string_type cursor="")
							:  cursor_(cursor), twitter_base("GET","https","api.twitter.com","/1/"+user+"/lists/memberships."+format){}
						param_type sort() const{
							param_type sort;
							if(!cursor_.empty()) sort["cursor"]=cursor_;
							return sort;
						}
					private:
						const string_type cursor_;
					};

					//GET :user/lists/subscriptions(GET list subscriptions)
					class lists_subscriptions : public twitter_base{
					public:
						lists_subscriptions(const string_type format,const string_type user,const string_type cursor="")
							:  cursor_(cursor), twitter_base("GET","https","api.twitter.com","/1/"+user+"/lists/subscriptions."+format){}
						param_type sort() const{
							param_type sort;
							if(!cursor_.empty()) sort["cursor"]=cursor_;
							return sort;
						}
					private:
						const string_type cursor_;
					};
					
					//GET :user/:list_id/members(GET list members)
					class list_members_get : public twitter_base{
					public:
						list_members_get(const string_type format,const string_type user,const string_type list_id,const string_type cursor="")
							:  cursor_(cursor), twitter_base("GET","https","api.twitter.com","/1/"+user+"/"+list_id+"/members."+format){}
						param_type sort() const{
							param_type sort;
							if(!cursor_.empty()) sort["cursor"]=cursor_;
							return sort;
						}
					private:
						const string_type cursor_;
					};
					
					//POST :user/:list_id/members(POST list members)
					class list_members_post : public twitter_base{
					public:
						list_members_post(const string_type format,const string_type user,const string_type list_id,const string_type id="")
							:  id_(id), twitter_base("POST","https","api.twitter.com","/1/"+user+"/"+list_id+"/members."+format){}
						param_type sort() const{
							param_type sort;
							if(!id_.empty()) sort["id"]=id_;
							return sort;
						}
					private:
						const string_type id_;
					};
					
					//POST :user/:list_id/create_all(POST list create_all)
					class list_create_all : public twitter_base{
					public:
						list_create_all(const string_type format,const string_type user,const string_type list_id,const string_type user_id="",const string_type screen_name="")
							:  user_id_(user_id), screen_name_(screen_name), twitter_base("POST","https","api.twitter.com","/1/"+user+"/"+list_id+"/create_all."+format){}
						param_type sort() const{
							param_type sort;
							if(!user_id_.empty()) sort["user_id"]=user_id_;
							if(!screen_name_.empty()) sort["screen_name"]=screen_name_;
							return sort;
						}
					private:
						const string_type user_id_;
						const string_type screen_name_;
					};
					
					//DELETE :user/:list_id/members(DELETE list members)
					class list_members_delete : public twitter_base{
					public:
						list_members_delete(const string_type format,const string_type user,const string_type list_id,const string_type id="")
							:  id_(id), twitter_base("DELETE","https","api.twitter.com","/1/"+user+"/"+list_id+"/members."+format){}
						param_type sort() const{
							param_type sort;
							if(!id_.empty()) sort["id"]=id_;
							return sort;
						}
					private:
						const string_type id_;
					};
					
					//GET :user/:list_id/members/:id(GET list members id)
					class list_members_id : public twitter_base{
					public:
						list_members_id(const string_type format,const string_type user,const string_type list_id,const string_type id)
							: twitter_base("GET","https","api.twitter.com","/1/"+user+"/"+list_id+"/members/"+id+"."+format){}
					private:
					};
					
					//GET :user/:list_id/subscribers(GET list subscribers)
					class list_subscribers_get : public twitter_base{
					public:
						list_subscribers_get(const string_type format,const string_type user,const string_type list_id,const string_type cursor="")
							:  cursor_(cursor), twitter_base("GET","https","api.twitter.com","/1/"+user+"/"+list_id+"/subscribers."+format){}
						param_type sort() const{
							param_type sort;
							if(!cursor_.empty()) sort["cursor"]=cursor_;
							return sort;
						}
					private:
						const string_type cursor_;
					};

					//POST :user/:list_id/subscribers(POST list subscribers)
					class list_subscribers_post : public twitter_base{
					public:
						list_subscribers_post(const string_type format,const string_type user,const string_type list_id)
							: twitter_base("POST","https","api.twitter.com","/1/"+user+"/"+list_id+"/subscribers."+format){}
					private:
					};

					//DELETE :user/:list_id/subscribers(DELETE list subscribers)
					class list_subscribers_delete : public twitter_base{
					public:
						list_subscribers_delete(const string_type format,const string_type user,const string_type list_id)
							: twitter_base("DELETE","https","api.twitter.com","/1/"+user+"/"+list_id+"/subscribers."+format){}
					private:
					};
				}//End lists namespace
			}//End user namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
