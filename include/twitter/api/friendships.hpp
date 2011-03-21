#ifndef TWITTER_API_FRIENDSHIPS_HPP
#define TWITTER_API_FRIENDSHIPS_HPP

namespace oauth{
	namespace api{
		namespace twitter{
			namespace friendships{
				//POST friendships/create
				class create : public twitter_base{
				public:
					create(const string_type format,const string_type id,const string_type follow="")
						: id_(id), follow_(follow), twitter_base("POST","https","api.twitter.com","/1/friendships/create."+format){}
					param_type sort() const{
						param_type sort;
						sort["id"]=id_;
						if(follow_!="") sort["follow"]=follow_;
						return sort;
					}
				private:
					const string_type id_;
					const string_type follow_;
				};
				
				//POST friendships/destroy
				class destroy : public twitter_base{
				public:
					destroy(const string_type format,const string_type id)
						: id_(id), twitter_base("DELETE","https","api.twitter.com","/1/friendships/destroy."+format){}
					param_type sort() const{
						param_type sort;
						sort["id"]=id_;
						return sort;
					}
				private:
					const string_type id_;
				};
				
				//GET friendships/exists
				class exists : public twitter_base{
				public:
					exists(const string_type format,const string_type user_a,const string_type user_b)
						: user_a_(user_a), user_b_(user_b), twitter_base("GET","https","api.twitter.com","/1/friendships/exists."+format){}
					param_type sort() const{
						param_type sort;
						sort["user_a"]=user_a_;
						sort["user_b"]=user_b_;
						return sort;
					}
				private:
					const string_type user_a_;
					const string_type user_b_;
				};
				
				//GET friendships/show
				class show : public twitter_base{
				public:
					//採取引数をfalseにするとuser_idでの確認も可能。標準はスクリーンネーム。
					show(const string_type format,const string_type source,const string_type target,const bool use_screen_name=true)
						: source_(source), target_(target), use_screen_name_(use_screen_name), twitter_base("GET","https","api.twitter.com","/1/friendships/show."+format){}
					param_type sort() const{
						param_type sort;
						if(use_screen_name_==true)
						{
							sort["source_screen_name"]=source_;
							sort["target_screen_name"]=target_;
						}
						else
						{
							sort["source_id"]=source_;
							sort["target_id"]=target_;
						}

						return sort;
					}
				private:
					const string_type source_;
					const string_type target_;
					const bool use_screen_name_;
				};
				
				//GET friendships/incoming
				class incoming : public twitter_base{
				public:
					incoming(const string_type format,const string_type cursor="")
						: cursor_(cursor), twitter_base("GET","https","api.twitter.com","/1/friendships/incoming."+format){}
					param_type sort() const{
						param_type sort;
						if(cursor_!="") sort["cursor"]=cursor_;
						return sort;
					}
				private:
					const string_type cursor_;
				};
				
				//GET friendships/outgoing
				class outgoing : public twitter_base{
				public:
					outgoing(const string_type format,const string_type cursor="")
						: cursor_(cursor), twitter_base("GET","https","api.twitter.com","/1/friendships/outgoing."+format){}
					param_type sort() const{
						param_type sort;
						if(cursor_!="") sort["cursor"]=cursor_;
						return sort;
					}
				private:
					const string_type cursor_;
				};				
			}//End direct_messages namespace
		}//End twitter namespace
	}//End api namespace
}//End oauth namespace

#endif
