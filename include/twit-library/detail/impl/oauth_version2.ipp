#ifndef TWIT_LIB_DETAIL_OAUTH_VER_2_IPP
#define TWIT_LIB_DETAIL_OAUTH_VER_2_IPP

#include <map>
#include <boost/assign.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <boostconnect/client.hpp>
#include "../oauth_version2.hpp"
#include "../../keys/key_version2.hpp"
#include "../../utility.hpp"

namespace oauth{
namespace detail{

oauth_version2::oauth_version2(const boost::shared_ptr<Key_Type> &key, const boost::shared_ptr<bstcon::client> &client)
{
    key_ = key;
    client_ = client;
}
oauth_version2::~oauth_version2(){}

const std::string oauth_version2::authorization_request_uri(const std::string& uri, const std::string& response_type, const std::string& redirect_uri, const std::string& scope, const std::string& state)
{
    Param_Type param = boost::assign::map_list_of
        ("client_id"     ,key_->get_client_id())
        ("response_type" ,response_type);

    if(!redirect_uri.empty()) param["redirect_uri"] = redirect_uri; //MAY
    if(!scope.empty())        param["scope"] = scope;               //Option
    if(!state.empty())        param["state"] = state;               //Option
        
    return uri + "?" + generator_.urlencode(param);
}

void oauth_version2::code_to_access_token(const std::string& uri, const std::string& code, const std::string& redirect_uri)
{
    oauth::utility::uri_parser uri_parsed(uri);

    Param_Type param = boost::assign::map_list_of
        ("client_id",key_->get_client_id())
        ("client_secret",key_->get_client_secret())
        ("redirect_uri",redirect_uri)
        ("code",code)
        ("grant_type","authorization_code");
    
    auto request = boost::make_shared<bstcon::request>("POST", uri_parsed.get_path(), generator_.urlencode(param));
    boost::assign::insert(request->header)
        ("Content-Length", std::to_string(request->body.length()))
        ("Content-Type: ", "application/x-www-form-urlencoded");
    
    (*client_)(
        uri_parsed.get_host(),
        [request, this](bstcon::connection_type::connection_base::connection_ptr connection, boost::system::error_code ec)
        {
            connection->send(*request, boost::bind(&oauth_version2::set_access_token, this, _1, _2));
        });
        
    return;
}

void oauth_version2::set_access_token(const boost::shared_ptr<bstcon::response> response, const boost::system::error_code& ec)
{
    if(ec) return;
    if(200 <= response->status_code && response->status_code < 300)
    {
        const Param_Type parsed = parser_.urlencode(response->body);
        key_->set_access_token(parsed.at("access_token"));
    }
    return;
}

} // namespace detail
} // namespace oauth

#endif
//http://openid-foundation-japan.github.com/draft-ietf-oauth-v2.ja.html#user-authorization
