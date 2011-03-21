#ifndef HATENA_CORE_HPP
#define HATENA_CORE_HPP

namespace oauth{
	namespace client{
		//
		// はてなサービス用のOAuthクラス
		// リクエストトークン/アクセストークン所得時にSSL通信、
		// 普通のAPIを走らせるときにTCP通信を使用するように
		// OAuth::Wraper::TCPとOAuth::Wraper::SSLを派生し、調節をしている
		//
		class hatena : public oauth::client::client_base<oauth::protocol::https<>>, public oauth::client::client_base<oauth::protocol::http>
		{
		public:
			typedef oauth::client::client_base<oauth::protocol::https<>> https;
			typedef oauth::client::client_base<oauth::protocol::http> http;

			hatena(){	}
			~hatena(){}
			// リクエストトークン取得(オーバーライド)
			// スコープを引数にする必要があります
			// スコープを以下のように置き換え、複数のスコープを使用する場合は'&'で繋いでください(順不同)
			res_type oauth_req(std::string scope)
			{
				set_host("www.hatena.com");
		
				param_type add;
				add["oauth_callback"]="oob";
				add["scope"] = util::url::encode(scope);
				return https::oauth_req("/oauth/initiate",add);
			}

			//
			// authorizeのURLを取得(オーバーライド)
			//
			std::string oauth_authorize() const
			{
				return https::oauth_authorize("https://www.hatena.ne.jp/oauth/authorize");
			}

			//
			// アクセストークン取得(オーバーライド)
			// oauth_authorize+ブラウザにより取得できたpinをstd::stringで引数に指定
			//
			int oauth_acc(const std::string& pin)
			{
				set_host("www.hatena.com");

				const std::string path = "/oauth/token";

				auto res = https::oauth_acc(path,pin);

				return 0;
			}

			//基本的なAPIはすべて動かせるはず
			res_type request(const string_type& host,const string_type& method,const string_type& path,param_type& add_arg=param_type())
			{
				http::set_host(host);
				return http::request(method,path,add_arg);
			}

			//基本的なAPIはすべて動かせるはず
			res_type request(const string_type& host,const string_type& method,const string_type& path,const std::vector<oauth::content::multipart_form_data>& data)
			{
				http::set_host(host);
				return http::request(method,path,data);
			}
			
		};
	}//End client namespace
}//End oauth namespace

#endif
