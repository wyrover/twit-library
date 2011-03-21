#ifndef TWITTER_CORE_HPP
#define TWITTER_CORE_HPP

#ifndef NO_USE_TWITPIC
#include "twitpic.hpp"
#endif

namespace oauth{
	namespace client{
		template<class Protocol_Type>
		class twitter
			: public virtual oauth::client::client_base<Protocol_Type>
#ifndef NO_USE_TWITPIC
			, public virtual oauth::client::twitpic<Protocol_Type>
#endif
		{
		public:
			twitter(){set_host("api.twitter.com");}
			~twitter(){}
					
			//
			// リクエストトークン取得(オーバーライド)
			//
			res_type oauth_req(){
				return client_base::oauth_req("/oauth/request_token");
			}

			//
			// authorizeのURLを取得(オーバーライド)
			//
			res_type oauth_authorize() const
			{
				return client_base::oauth_authorize("http://api.twitter.com/oauth/authorize");
			}
		
			//
			// アクセストークン取得(オーバーライド)
			// oauth_authorize+ブラウザにより取得できたpinをstd::stringで引数に指定
			//
			res_type oauth_acc(const std::string& pin){
				return client_base::oauth_acc("/oauth/access_token",pin);
			}

#ifndef NO_USE_SSL
			// xAuth認証でアクセストークンを取得
			// user : Account Name (NOT e-mail)
			// pw : Account Password
			res_type xauth(const string_type& user,const string_type& pw)
			{
				//通信用クラス生成
				client_  = new oauth::protocol::https<>(io_service_);

				const string_type method = "POST";
				const string_type path = "/oauth/access_token";
				const string_type url = client_->protocol()+"://"+host_+path;
				
				//xAuthに必要な追加パラメータ
				param_type xauth_info;
				xauth_info["x_auth_mode"] = "client_auth";
				xauth_info["x_auth_password"] = pw;
				xauth_info["x_auth_username"] = user;

				//ヘッダーの作成
				param_type head;
				head["Authorization"] = make_authorization(make_request_signature(method,url,xauth_info));
				head["Content-Type"] = "application/x-www-form-urlencoded";
				
				const auto body = util::map::serialization(xauth_info);

				//通信
				boost::asio::streambuf buffer;
				client_->write(
					host_,
					&make_request(buffer,method,host_,path,head,body)
					);

				string_type res;
				client_->read(res);
				delete client_;
				client_=NULL;

				param_type res_sort = util::map::deserialization(res);
				access_token_ = res_sort["oauth_token"];
				access_token_secret_ = res_sort["oauth_token_secret"];

				return res;
			}
#endif //NO_USE_SSL	
			
			res_type request(const oauth::api::twitter_base *api_type)
			{
				return client_base<Protocol_Type>::request(api_type);
			}
		};
	}//End client namespace
}//End oauth namespace

#endif