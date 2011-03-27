#ifndef TWITTER_API_STATUSES_HPP
#define TWITTER_API_STATUSES_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace statuses{
				//GET statuses/public_timeline
				class public_timeline : public twitter_base{
				public:
					public_timeline(const string_type format)
						: twitter_base("GET","https","api.twitter.com","/1/statuses/public_timeline."+format){}
				private:
				};
				
				//GET statuses/home_timeline
				class home_timeline : public twitter_base{
				public:
					home_timeline(const string_type format,const string_type since_id="",const string_type max_id="",const string_type count="",const string_type page="",const string_type include_rts="true")
						: since_id_(since_id), max_id_(max_id), count_(count), page_(page), include_rts_(include_rts), twitter_base("GET","https","api.twitter.com","/1/statuses/home_timeline."+format){}
					param_type sort() const{
						param_type sort;
						if(!since_id_.empty()) sort["since_id"]=since_id_;
						if(!max_id_.empty()) sort["max_id"]=max_id_;
						if(!count_.empty()) sort["count"]=count_;
						if(!page_.empty()) sort["page"]=page_;
						if(!include_rts_.empty()) sort["include_rts"]=include_rts_;
						return sort;
					}
				private:
					const string_type since_id_;
					const string_type max_id_;
					const string_type count_;
					const string_type page_;
					const string_type include_rts_;
				};
				
				//GET statuses/friends_timeline
				class friends_timeline : public twitter_base{
				public:
					friends_timeline(const string_type format,const string_type since_id="",const string_type max_id="",const string_type count="",const string_type page="",const string_type include_rts="true")
						: since_id_(since_id), max_id_(max_id), count_(count), page_(page), include_rts_(include_rts), twitter_base("GET","https","api.twitter.com","/1/statuses/friends_timeline."+format){}
					param_type sort() const{
						param_type sort;
						if(!since_id_.empty()) sort["since_id"]=since_id_;
						if(!max_id_.empty()) sort["max_id"]=max_id_;
						if(!count_.empty()) sort["count"]=count_;
						if(!page_.empty()) sort["page"]=page_;
						if(!include_rts_.empty()) sort["include_rts"]=include_rts_;
						return sort;
					}
				private:
					const string_type since_id_;
					const string_type max_id_;
					const string_type count_;
					const string_type page_;
					const string_type include_rts_;
				};
				
				//GET statuses/user_timeline
				class user_timeline : public twitter_base{
				public:
					user_timeline(const string_type format,const string_type user_id="",const string_type screen_name="",const string_type since_id="",const string_type max_id="",const string_type count="",const string_type page="",const string_type include_rts="true")
						: user_id_(user_id), screen_name_(screen_name), since_id_(since_id), max_id_(max_id), count_(count), page_(page), include_rts_(include_rts), twitter_base("GET","https","api.twitter.com","/1/statuses/user_timeline."+format){}
					param_type sort() const{
						param_type sort;
						if(!user_id_.empty()) sort["user_id"]=user_id_;
						if(!screen_name_.empty()) sort["screen_name"]=screen_name_;
						if(!since_id_.empty()) sort["since_id"]=since_id_;
						if(!max_id_.empty()) sort["max_id"]=max_id_;
						if(!count_.empty()) sort["count"]=count_;
						if(!page_.empty()) sort["page"]=page_;
						if(!include_rts_.empty()) sort["include_rts"]=include_rts_;
						return sort;
					}
				private:
					const string_type user_id_;
					const string_type screen_name_;
					const string_type since_id_;
					const string_type max_id_;
					const string_type count_;
					const string_type page_;
					const string_type include_rts_;
				};
				
				//GET statuses/mentions
				class mentions : public twitter_base{
				public:
					mentions(const string_type format,const string_type since_id="",const string_type max_id="",const string_type count="",const string_type page="",const string_type include_rts="true")
						: since_id_(since_id), max_id_(max_id), count_(count), page_(page), include_rts_(include_rts), twitter_base("GET","https","api.twitter.com","/1/statuses/mentions."+format){}
					param_type sort() const{
						param_type sort;
						if(!since_id_.empty()) sort["since_id"]=since_id_;
						if(!max_id_.empty()) sort["max_id"]=max_id_;
						if(!count_.empty()) sort["count"]=count_;
						if(!page_.empty()) sort["page"]=page_;
						if(!include_rts_.empty()) sort["include_rts"]=include_rts_;
						return sort;
					}
				private:
					const string_type since_id_;
					const string_type max_id_;
					const string_type count_;
					const string_type page_;
					const string_type include_rts_;
				};
				
				//GET statuses/retweeted_by_me
				class retweeted_by_me : public twitter_base{
				public:
					retweeted_by_me(const string_type format,const string_type since_id="",const string_type max_id="",const string_type count="",const string_type page="")
						: since_id_(since_id), max_id_(max_id), count_(count), page_(page), twitter_base("GET","https","api.twitter.com","/1/statuses/retweeted_by_me."+format){}
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
				
				//GET statuses/retweeted_to_me
				class retweeted_to_me : public twitter_base{
				public:
					retweeted_to_me(const string_type format,const string_type since_id="",const string_type max_id="",const string_type count="",const string_type page="")
						: since_id_(since_id), max_id_(max_id), count_(count), page_(page), twitter_base("GET","https","api.twitter.com","/1/statuses/retweeted_to_me."+format){}
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
				
				//GET statuses/retweets_of_me
				class retweets_of_me : public twitter_base{
				public:
					retweets_of_me(const string_type format,const string_type since_id="",const string_type max_id="",const string_type count="",const string_type page="")
						: since_id_(since_id), max_id_(max_id), count_(count), page_(page), twitter_base("GET","https","api.twitter.com","/1/statuses/retweets_of_me."+format){}
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
				
				//GET statuses/show/:id
				class show : public twitter_base{
				public:
					show(const string_type format,const string_type id)
						: twitter_base("GET","https","api.twitter.com","/1/statuses/show/"+id+"."+format){}
				private:
				};
				
				//POST statuses/update
				class update : public twitter_base{
				public:
					update(const string_type format,const string_type status,const string_type in_reply_to_status_id="",const string_type lat="",const string_type vlong="",const string_type place_id="",const string_type display_coordinates="")
						: status_(status), in_reply_to_status_id_(in_reply_to_status_id), lat_(lat), long_(vlong), place_id_(place_id), display_coordinates_(display_coordinates), twitter_base("POST","https","api.twitter.com","/1/statuses/update."+format){}
					param_type sort() const{
						param_type sort;
						sort["status"]=status_;
						if(!in_reply_to_status_id_.empty()) sort["in_reply_to_status_id"]=in_reply_to_status_id_;
						if((!lat_.empty())&&(!long_.empty())){sort["lat"]=lat_; sort["long"]=long_;}
						if(!place_id_.empty()) sort["place_id"]=place_id_;
						if(!display_coordinates_.empty()) sort["display_coordinates"]=display_coordinates_;
						return sort;
					}
				private:
					const string_type status_;
					const string_type in_reply_to_status_id_;
					const string_type lat_;
					const string_type long_;
					const string_type place_id_;
					const string_type display_coordinates_;
				};

				//POST statuses/destroy/:id
				class destroy : public twitter_base{
				public:
					destroy(const string_type format,const string_type id)
						: twitter_base("POST","https","api.twitter.com","/1/statuses/destroy/"+id+"."+format){}
				private:
				};

				//POST statuses/retweet/:id
				class retweet : public twitter_base{
				public:
					retweet(const string_type format,const string_type id)
						: twitter_base("POST","https","api.twitter.com","/1/statuses/retweet/"+id+"."+format){}
				private:
				};
				
				//GET statuses/retweets/:id
				class retweets : public twitter_base{
				public:
					retweets(const string_type format,const string_type id,const string_type count="")
						: count_(count), twitter_base("GET","https","api.twitter.com","/1/statuses/retweets/"+id+"."+format){}
					param_type sort() const{
						param_type sort;
						if(!count_.empty()) sort["count"]=count_;
						return sort;
					}
				private:
					const string_type count_;
				};
				//GET statuses/:id/retweeted_by
				class retweeted_by : public twitter_base{
				public:
					retweeted_by(const string_type format,const string_type id,const string_type count="",const string_type page="")
						: count_(count), page_(page), twitter_base("GET","https","api.twitter.com","/1/statuses/"+id+"/retweeted_by."+format){}
					param_type sort() const{
						param_type sort;
						if(!count_.empty()) sort["count"]=count_;
						if(!page_.empty()) sort["page"]=page_;
						return sort;
					}
				private:
					const string_type count_;
					const string_type page_;
				};
				
				//GET statuses/:id/retweeted_by/ids
				class retweeted_by_ids : public twitter_base{
				public:
					retweeted_by_ids(const string_type format,const string_type id,const string_type count="",const string_type page="")
						: count_(count), page_(page), twitter_base("GET","https","api.twitter.com","/1/statuses/"+id+"/retweeted_by/ids."+format){}
					param_type sort() const{
						param_type sort;
						if(!count_.empty()) sort["count"]=count_;
						if(!page_.empty()) sort["page"]=page_;
						return sort;
					}
				private:
					const string_type count_;
					const string_type page_;
				};
				
				//GET statuses/friends
				class friends : public twitter_base{
				public:
					friends(const string_type format,const string_type user_id="",const string_type screen_name="",const string_type cursor="")
						: user_id_(user_id), screen_name_(screen_name), cursor_(cursor), twitter_base("GET","https","api.twitter.com","/1/statuses/friends."+format){}
					param_type sort() const{
						param_type sort;
						if(!user_id_.empty()) sort["user_id"]=user_id_;
						if(!screen_name_.empty()) sort["screen_name"]=screen_name_;
						if(!cursor_.empty()) sort["cursor"]=cursor_;
						return sort;
					}
				private:
					const string_type user_id_;
					const string_type screen_name_;
					const string_type cursor_;
				};
				
				//GET statuses/followers
				class followers : public twitter_base{
				public:
					followers(const string_type format,const string_type user_id="",const string_type screen_name="",const string_type cursor="")
						: user_id_(user_id), screen_name_(screen_name), cursor_(cursor), twitter_base("GET","https","api.twitter.com","/1/statuses/followers."+format){}
					param_type sort() const{
						param_type sort;
						if(!user_id_.empty()) sort["user_id"]=user_id_;
						if(!screen_name_.empty()) sort["screen_name"]=screen_name_;
						if(!cursor_.empty()) sort["cursor"]=cursor_;
						return sort;
					}
				private:
					const string_type user_id_;
					const string_type screen_name_;
					const string_type cursor_;
				};
			}//End statuses namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
