#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <string>
#include <map>

#include <boost/format.hpp> //Boost.Format用
#include <boost/asio.hpp> //Boost.Asio用ヘッダ

#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>

//Boost.AsioでSSLを使用するために必要(OpenSSL)
#ifndef NO_USE_SSL
#include <boost/asio/ssl.hpp>
#pragma comment(lib, "libeay32MDd.lib")
#pragma comment(lib, "ssleay32MDd.lib")
#endif

#include <stdexcept>

int hex_to_dec(std::string hex)
{
	std::string::size_type i = hex.find(" ");
	if(i!=std::string::npos)
		hex.erase(hex.find(" "));
	boost::algorithm::to_upper(hex);

	int dec=0;
	BOOST_FOREACH(char ch,hex)
	{
		dec*=16;
		switch(ch){
		case '0': dec+=0; break;
		case '1': dec+=1; break;
		case '2': dec+=2; break;
		case '3': dec+=3; break;
		case '4': dec+=4; break;
		case '5': dec+=5; break;
		case '6': dec+=6; break;
		case '7': dec+=7; break;
		case '8': dec+=8; break;
		case '9': dec+=9; break;
		case 'A': dec+=10; break;
		case 'B': dec+=11; break;
		case 'C': dec+=12; break;
		case 'D': dec+=13; break;
		case 'E': dec+=14; break;
		case 'F': dec+=15; break;
		default: throw std::invalid_argument("Invalid Hexadecimal");
		}
	}
	return dec;
}

int dec_to_hex(int dec)
{
	std::string hex;
	while((dec/=16)!=0)
	{
		int i = dec%16;

		switch(i){
		case 0: hex="0"+hex; break;
		case 1: hex="1"+hex; break;
		case 2: hex="2"+hex; break;
		case 3: hex="3"+hex; break;
		case 4: hex="4"+hex; break;
		case 5: hex="5"+hex; break;
		case 6: hex="6"+hex; break;
		case 7: hex="7"+hex; break;
		case 8: hex="8"+hex; break;
		case 9: hex="9"+hex; break;
		case 10: hex="A"+hex; break;
		case 11: hex="B"+hex; break;
		case 12: hex="C"+hex; break;
		case 13: hex="D"+hex; break;
		case 14: hex="E"+hex; break;
		case 15: hex="F"+hex; break;
		default: throw std::invalid_argument("Invalid Decimal");
		}
	}
	return dec;
}

std::string erase_chunk(std::string& data)
{
	std::string ret;
	while(!data.empty())
	{
		int chunk;
		chunk = hex_to_dec(data.substr(0,data.find("\r\n")));
		data.erase(0,data.find("\r\n")+2);

		std::string str;
		while(str.length() < chunk)
		{
			str += data.substr(0,data.find("\r\n"));
			data.erase(0,data.find("\r\n")+2);
		}
		ret += str;
	}

	return data=ret;
}

namespace oauth{
	namespace protocol{
		typedef std::string string_type;
		class protocol_base{
		public:
			protocol_base(boost::asio::io_service& io_service,const string_type protocol): io_service_(io_service),protocol_(protocol){}
			virtual ~protocol_base(){}
			virtual void read(std::string& response){}
			virtual void write(const std::string& host,boost::asio::streambuf *request){}
			string_type protocol() const	{return protocol_;}
			boost::asio::io_service& io_service() const	{return io_service_;}
		protected:
			boost::asio::io_service& io_service_;
		private:
			const string_type protocol_;
		};

		class http : public protocol_base{
		public:
			http(boost::asio::io_service& io_service)
				: protocol_base(io_service,"http"), socket_(io_service_), resolver_(io_service_){}

			void read(std::string& response)
			{
				boost::asio::streambuf buffer;
				boost::system::error_code error;

				//レスポンスの読み取り
				while(boost::asio::read(socket_,buffer,boost::asio::transfer_at_least(1), error));
				response_ = static_cast<std::string>(boost::asio::buffer_cast<const char*>(buffer.data()));

				//チャンクが有るかどうか
				bool chunk = (response_.find("Transfer-Encoding: chunked") != std::string::npos);

				//レスポンスの一行目を解析
				std::istringstream res_stream(response_);
				std::string http_version;
				res_stream >> http_version;
				int status_code;
				res_stream >> status_code;
				std::string status_message;
				res_stream >> status_message;
						
				//レスポンス本文を取り出し
				response_.erase(0,response_.find("\r\n\r\n")+4);

				//区切り削除
				if(chunk)
					response = erase_chunk(response_);
				else
					response = response_;
			}

			void write(const std::string& host,boost::asio::streambuf *request)
			{
				boost::asio::ip::tcp::resolver::query query(host,"http");
				boost::asio::ip::tcp::resolver::iterator pos = resolver_.resolve(query);
				boost::asio::ip::tcp::resolver::iterator last;

				boost::system::error_code error = boost::asio::error::host_not_found;
				while(error && pos != last){
							socket_.close();
							socket_.connect(*pos++,error);
				}
				if(error) throw boost::system::system_error(error);
		
				boost::asio::write(socket_, *request);
			}

		protected:
			boost::asio::ip::tcp::socket socket_;
			boost::asio::ip::tcp::resolver resolver_;
			std::string response_;
		};

		class async_http : public protocol_base{
		public:	
			async_http(boost::asio::io_service& io_service)
				: protocol_base(io_service,"http"), socket_(io_service_), resolver_(io_service_){}

			void read(std::string& response)
			{
				bool chunk = (response_.find("Transfer-Encoding: chunked") != std::string::npos);
				
				//レスポンス本文を取り出し
				response_.erase(0,response_.find("\r\n\r\n")+4);

				//区切り削除
				if(chunk)
					response = erase_chunk(response_);
				else
					response = response_;
			}

			void write(const std::string& host,boost::asio::streambuf *request){
				request_ = request;
				boost::asio::ip::tcp::resolver::query query(host, "http");
				resolver_.async_resolve(
					query,
					boost::bind(&async_http::handle_resolve, this, boost::asio::placeholders::error, boost::asio::placeholders::iterator)
					);
			}
			
		private:
			//async_resolve後ハンドル
			void handle_resolve(const boost::system::error_code& err,boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
			{
				if(!err)
				{
					//正常
					boost::asio::ip::tcp::endpoint endpoint= *endpoint_iterator;
					socket_.async_connect(
						endpoint,
						boost::bind(&async_http::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator)
						);

				}
				else throw std::invalid_argument("Error: "+err.message());
			}

			//async_connect後ハンドル
			void handle_connect(const boost::system::error_code& err,boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
			{
				if(!err)
				{
					//正常接続
					boost::asio::async_write(
					socket_,
					*request_,
					boost::bind(&async_http::handle_write_request, this, boost::asio::placeholders::error)
					);
				}
				else if(endpoint_iterator != boost::asio::ip::tcp::resolver::iterator())
				{
					//接続ミス
					socket_.close();
					boost::asio::ip::tcp::endpoint endpoint= *endpoint_iterator;
					socket_.async_connect(
						endpoint,
						boost::bind(&async_http::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator)
						);

				}
				else throw std::invalid_argument("Error: "+err.message());
			}

			//async_write後ハンドル
			void handle_write_request(const boost::system::error_code& err)
			{
				if(!err)
				{
					//正常送信
					boost::asio::async_read_until(
					socket_,
					response_stream_,
					"\r\n",
					boost::bind(&async_http::handle_read_status, this, boost::asio::placeholders::error)
					);
				}
				else throw std::invalid_argument("Error: "+err.message());
			}

			//async_read_until後ハンドル
			void handle_read_status(const boost::system::error_code& err)
			{
				if(!err)
				{
					//正常送信
					std::istream response_stream(&response_stream_);
					//レスポンスチェック
					std::string http_version;
					response_stream >> http_version;
					unsigned int status_code;
					response_stream >> status_code;
					std::string status_message;
					response_stream >> status_message;
			
					if (!response_stream || http_version.substr(0, 5) != "HTTP/")
					{
						throw std::invalid_argument("Invalid response");
					}

					boost::asio::async_read_until(
						socket_,
						response_stream_,
						"\r\n\r\n",
						boost::bind(&async_http::handle_read_header, this, boost::asio::placeholders::error)
						);
				}
				else throw std::invalid_argument("Error: "+err.message());
			}

			//handle_read_status後ハンドル
			void handle_read_header(const boost::system::error_code& err)
			{
				if(!err)
				{
					//正常送信
					std::istream response_stream(&response_stream_);
					//レスポンスチェック
					std::string header;
					while (std::getline(response_stream, header) && header != "\r")
						std::cout << header << "\n";
					std::cout << "\n";
			
					// Write whatever content we already have to output.
					if (response_stream_.size() > 0)
					response_ = static_cast<std::string>(boost::asio::buffer_cast<const char*>(response_stream_.data()));
			
					// Start reading remaining data until EOF.
					boost::asio::async_read(
						socket_,
						response_stream_,
						boost::asio::transfer_at_least(1),
						boost::bind(&async_http::handle_read_content, this, boost::asio::placeholders::error)
						);			
				}
				else throw std::invalid_argument("Error: "+err.message());
			}

			//handle_read_header後ハンドル
			void handle_read_content(const boost::system::error_code& err)
			{
				if(!err)
				{
				response_ = static_cast<std::string>(boost::asio::buffer_cast<const char*>(response_stream_.data()));
			
					boost::asio::async_read(
						socket_,
						response_stream_,
						boost::asio::transfer_at_least(1),
						boost::bind(&async_http::handle_read_content,
						this,
						boost::asio::placeholders::error)
						);
				}
				else if (err != boost::asio::error::eof)
				{
					std::cout << "Error: " << err << "\n";
				}
			}

			boost::asio::streambuf *request_;
			boost::asio::ip::tcp::socket socket_;
			boost::asio::ip::tcp::resolver resolver_;
			std::string response_;
			boost::asio::streambuf response_stream_;
		};

#ifndef NO_USE_SSL
		template<boost::asio::ssl::context_base::method SSL_TYPE = boost::asio::ssl::context::sslv23>
		class https : public protocol_base{
		public:
			https(boost::asio::io_service& io_service)
				: protocol_base(io_service,"https"), ctx_(io_service_,SSL_TYPE), socket_(io_service_,ctx_), resolver_(io_service_){}

			void read(std::string& response)
			{
				boost::asio::streambuf buffer;
				boost::system::error_code error;

				//レスポンスの読み取り
				while(boost::asio::read(socket_,buffer,boost::asio::transfer_at_least(1), error));
				response_ = static_cast<std::string>(boost::asio::buffer_cast<const char*>(buffer.data()));

				bool chunk = (response_.find("Transfer-Encoding: chunked") != std::string::npos);

				//レスポンスの一行目を解析
				std::istringstream res_stream(response_);
				std::string http_version;
				res_stream >> http_version;
				int status_code;
				res_stream >> status_code;
				std::string status_message;
				res_stream >> status_message;
					
				//レスポンス本文を取り出し
				response_.erase(0,response_.find("\r\n\r\n")+4);

				//区切り削除
				if(chunk)
					response = erase_chunk(response_);
				else
					response = response_;
			}

			void write(const std::string& host,boost::asio::streambuf *request)
			{
				boost::asio::ip::tcp::resolver::query query(host,"https");
				boost::asio::ip::tcp::resolver::iterator pos = resolver_.resolve(query);
				boost::asio::ip::tcp::resolver::iterator last;

				boost::system::error_code error = boost::asio::error::host_not_found;
				while(error && pos != last){
					socket_.lowest_layer().close();
					socket_.lowest_layer().connect(*pos++,error);
					socket_.handshake(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::client); //ハンドシェイクする
				}
				if(error) throw boost::system::system_error(error);
		
				boost::asio::write(socket_, *request);
			}

		private:
			boost::asio::ssl::context ctx_;
			boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
			boost::asio::ip::tcp::resolver resolver_;
			std::string response_;
		};

		template<boost::asio::ssl::context_base::method SSL_TYPE = boost::asio::ssl::context::sslv23>
		class async_https : public protocol_base{
		public:
			async_https(boost::asio::io_service& io_service)
				: protocol_base(io_service,"https"), ctx_(io_service,SSL_TYPE), socket_(io_service_,ctx_), resolver_(io_service_){}
	
			void read(std::string& response)
			{
				bool chunk = (response_.find("Transfer-Encoding: chunked") != std::string::npos);
				
				//レスポンス本文を取り出し
				response_.erase(0,response_.find("\r\n\r\n")+4);

				//区切り削除
				if(chunk)
					response = erase_chunk(response_);
				else
					response = response_;
			}

			void write(const std::string& host,boost::asio::streambuf *request){
				request_ = request;
				boost::asio::ip::tcp::resolver::query query(host, "https");
				resolver_.async_resolve(
					query,
					boost::bind(&async_https::handle_resolve, this, boost::asio::placeholders::error, boost::asio::placeholders::iterator)
					);
			}	
	
		private:
			//async_resolve後ハンドル
			void handle_resolve(const boost::system::error_code& err,boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
			{
				if(!err)
				{
					//正常
					boost::asio::ip::tcp::endpoint endpoint= *endpoint_iterator;
					socket_.lowest_layer().async_connect(
						endpoint,
						boost::bind(&async_https::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator)
						);

				}
				else throw std::invalid_argument("Error: "+err.message());
			}

			//async_connect後ハンドル
			void handle_connect(const boost::system::error_code& err,boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
			{
				if(!err)
				{
					//正常接続
					socket_.async_handshake(
						boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::client,
						boost::bind(&async_https::handle_handshake, this, boost::asio::placeholders::error)
						);		
				}
				else if(endpoint_iterator != boost::asio::ip::tcp::resolver::iterator())
				{
					//接続ミス
					socket_.lowest_layer().close();
					boost::asio::ip::tcp::endpoint endpoint= *endpoint_iterator;
					socket_.lowest_layer().async_connect(
						endpoint,
						boost::bind(&async_https::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator)
						);

				}
				else throw std::invalid_argument("Error: "+err.message());
			}

			//async_handshake後ハンドル
			void handle_handshake(const boost::system::error_code& err)
			{
				if(!err)
				{
					//正常ハンドシェイク
					boost::asio::async_write(
					socket_,
					*request_,
					boost::bind(&async_https::handle_write_request, this, boost::asio::placeholders::error)
					);
				}
				else throw std::invalid_argument("Error: "+err.message());
			}

			//async_write後ハンドル
			void handle_write_request(const boost::system::error_code& err)
			{
				if(!err)
				{
					//正常送信
					boost::asio::async_read_until(
					socket_,
					response_stream_,
					"\r\n",
					boost::bind(&async_https::handle_read_status, this, boost::asio::placeholders::error)
					);
				}
				else throw std::invalid_argument("Error: "+err.message());
			}

			//async_read_until後ハンドル
			void handle_read_status(const boost::system::error_code& err)
			{
				if(!err)
				{
					//正常送信
					std::istream response_stream(&response_stream_);
					//レスポンスチェック
					std::string http_version;
					response_stream >> http_version;
					unsigned int status_code;
					response_stream >> status_code;
					std::string status_message;
					response_stream >> status_message;
			
					if (!response_stream || http_version.substr(0, 5) != "HTTP/")
					{
						throw std::invalid_argument("Invalid response");
					}

					boost::asio::async_read_until(
						socket_,
						response_stream_,
						"\r\n\r\n",
						boost::bind(&async_https::handle_read_header, this, boost::asio::placeholders::error)
						);
				}
				else throw std::invalid_argument("Error: "+err.message());
			}

			//handle_read_status後ハンドル
			void handle_read_header(const boost::system::error_code& err)
			{
				if(!err)
				{
					//正常送信
					std::istream response_stream(&response_stream_);
					//レスポンスチェック
					std::string header;
					while (std::getline(response_stream, header) && header != "\r")
						std::cout << header << "\n";
					std::cout << "\n";
			
					// Write whatever content we already have to output.
					if (response_stream_.size() > 0)
					response_ = static_cast<std::string>(boost::asio::buffer_cast<const char*>(response_stream_.data()));
			
					// Start reading remaining data until EOF.
					boost::asio::async_read(
						socket_,
						response_stream_,
						boost::asio::transfer_at_least(1),
						boost::bind(&async_https::handle_read_content, this, boost::asio::placeholders::error)
						);			
				}
				else throw std::invalid_argument("Error: "+err.message());
			}

			//handle_read_header後ハンドル
			void handle_read_content(const boost::system::error_code& err)
			{
				if(!err)
				{
				response_ = static_cast<std::string>(boost::asio::buffer_cast<const char*>(response_stream_.data()));
			
					boost::asio::async_read(
						socket_,
						response_stream_,
						boost::asio::transfer_at_least(1),
						boost::bind(&async_https::handle_read_content,
						this,
						boost::asio::placeholders::error)
						);
				}
				else if (err != boost::asio::error::eof)
				{
					std::cout << "Error: " << err << "\n";
				}
			}

			boost::asio::ssl::context ctx_;
			boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
			boost::asio::ip::tcp::resolver resolver_;
			boost::asio::streambuf *request_;
			boost::asio::streambuf response_stream_;
			std::string response_;
		};
#endif
	}//End protocol namespace
}//End oauth namespace

#endif
