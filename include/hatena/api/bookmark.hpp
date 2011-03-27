#ifndef HATENA_API_BOOKMARK_HPP
#define HATENA_API_BOOKMARK_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <vector>

namespace oauth{
	namespace api{
		namespace hatena{
			namespace bookmark{
				struct BookMark{
					string_type title;
					string_type url;
					string_type summary;
					BookMark() {}
					BookMark(const string_type& title,const string_type& url,const string_type& summary)
						: title(title), url(url), summary(summary) {}
					BookMark(const BookMark& other)
						: title(other.title), url(other.url), summary(other.summary){}
				};

				namespace atom{
					//ルートAtomエンドポイント
					class atom : public hatena_base{
					public:
						atom()
							: hatena_base("GET","http","b.hatena.ne.jp","/atom"){}
					private:
					};

					//PostURI
					//ブックマークを新規投稿
					class post : public hatena_base{
					public:
						post(BookMark* bookmark)
							: bookmark_(bookmark), hatena_base("POST","http","b.hatena.ne.jp","/atom/post","application/x.atom+xml"){}
						boost::property_tree::ptree xml_ptree() const
						{
							boost::property_tree::ptree pt;
							
							boost::property_tree::ptree& entry = pt.add("entry","");
							entry.put("<xmlattr>.xmlns","http://purl.org/atom/ns#");

							pt.add("entry.title",bookmark_->title);

							boost::property_tree::ptree& link = pt.add("entry.link","");
							link.put("<xmlattr>.rel","related");
							link.put("<xmlattr>.type","text/html");
							link.put("<xmlattr>.href",bookmark_->url);

							boost::property_tree::ptree& summary = pt.add("entry.summary",bookmark_->summary);
							summary.put("<xmlattr>.type","text/plain");
							
							return pt;
						}
					private:
						BookMark* bookmark_;
					};
					
					//EditURI
					//特定のブックマークを参照 (GET)
					class edit_get : public hatena_base{
					public:
						edit_get(string_type eid)
							: hatena_base("GET","http","b.hatena.ne.jp","/atom/edit/"+eid){}
					private:
					};
					
					//EditURI
					//タイトル / コメントの編集 (PUT)
					class edit_put : public hatena_base{
					public:
						edit_put(string_type eid,BookMark* bookmark)
							: bookmark_(bookmark), hatena_base("PUT","http","b.hatena.ne.jp","/atom/edit/"+eid,"application/x.atom+xml"){}
						boost::property_tree::ptree xml_ptree() const
						{
							boost::property_tree::ptree pt;
							
							boost::property_tree::ptree& entry = pt.add("entry","");
							entry.put("<xmlattr>.xmlns","http://purl.org/atom/ns#");

							if(!bookmark_->title.empty())
								pt.add("entry.title",bookmark_->title);
							
							if(!bookmark_->summary.empty())
							{
								boost::property_tree::ptree& summary = pt.add("entry.summary",bookmark_->summary);
								summary.put("<xmlattr>.type","text/plain");
							}
							
							return pt;
						}
					private:
						BookMark* bookmark_;
					};
					
					//EditURI
					//ブックマークの削除 (DELETE)
					class edit_delete : public hatena_base{
					public:
						edit_delete(string_type eid)
							: hatena_base("DELETE","http","b.hatena.ne.jp","/atom/edit/"+eid){}
					private:
					};
					
					//FeedURI
					//投稿されたブックマークのうち最近のエントリをAtomフィードで取得
					class feed : public hatena_base{
					public:
						feed()
							: hatena_base("GET","http","b.hatena.ne.jp","/atom/feed"){}
					private:
					};
					
					//AtomAPI EditURI 
					class edit_url : public hatena_base{
					public:
						edit_url(const string_type& url)
							: url_(url), hatena_base("GET","http","b.hatena.ne.jp","/atom/edit"){}
						param_type sort() const
						{
							param_type args;
							args["url"]=url_;
							return args;
						}
					private:
						const string_type url_;
					};
				}//End atom namespace

				namespace count{
					//シンプルなブックマーク件数取得API 
					class entry : public hatena_base{
					public:
						entry(const string_type& url)
							: url_(url), hatena_base("GET","http","api.b.st-hatena.com","/entry.count"){}
						param_type sort() const
						{
							param_type args;
							args["url"]=url_;
							return args;
						}
					private:
						const string_type url_;
					};

					//ブックマーク件数を取得したいURLを指定(複数指定可能/50件まで)
					class xmlrpc_url : public hatena_base{
					public:
						xmlrpc_url(const std::vector<string_type>& urls)
							: urls_(urls), hatena_base("GET","http","b.hatena.ne.jp","/xmlrpc","application/x.atom+xml"){}
						boost::property_tree::ptree xml_ptree() const
						{
							boost::property_tree::ptree pt;
							pt.add("methodCall.methodName","bookmark.getCount");

							BOOST_FOREACH(string_type url,urls_)
								pt.add("methodCall.params.param.value.string",url);

							return pt;
						}
					private:
						const std::vector<string_type> urls_;
					};

					//件数を取得したいサイトのURLを指定(複数指定不可)
					class xmlrpc_site : public hatena_base{
					public:
						xmlrpc_site(const string_type& site)
							: site_(site), hatena_base("GET","http","b.hatena.ne.jp","/xmlrpc","application/x.atom+xml"){}
						boost::property_tree::ptree xml_ptree() const
						{
							boost::property_tree::ptree pt;
							pt.add("methodCall.methodName","bookmark.getTotalCount");
							pt.add("methodCall.params.param.value.string",site_);

							return pt;
						}
					private:
						const string_type site_;
					};

					//件数を取得したいASINコードを指定(複数指定可能/50件まで)
					class xmlrpc_asin : public hatena_base{
					public:
						xmlrpc_asin(const std::vector<string_type>& asins)
							: asins_(asins), hatena_base("GET","http","b.hatena.ne.jp","/xmlrpc","application/x.atom+xml"){}
						boost::property_tree::ptree xml_ptree() const
						{
							boost::property_tree::ptree pt;
							pt.add("methodCall.methodName","bookmark.getAsinCount");
							
							BOOST_FOREACH(string_type asin,asins_)
								pt.add("methodCall.params.param.value.string",asin);

							return pt;
						}
					private:
						const std::vector<string_type> asins_;
					};
				}//End count namespace

				namespace entry{
					//エントリー情報を取得するAPI
					class json : public hatena_base{
					public:
						json(const string_type& url)
							: url_(url), hatena_base("GET","http","b.hatena.ne.jp","/entry/json/"){}
						param_type sort() const
						{
							param_type args;
							args["url"]=util::url::encode(url_);
							return args;
						}
					private:
						const string_type url_;
					};

					//情報を絞り高速にエントリー情報を取得するAPI
					class jsonlite : public hatena_base{
					public:
						jsonlite(const string_type& url)
							: url_(url), hatena_base("GET","http","b.hatena.ne.jp","/entry/jsonlite/"){}
						param_type sort() const
						{
							param_type args;
							args["url"]=util::url::encode(url_);
							return args;
						}
					private:
						const string_type url_;
					};
				}//End entry namespace

				//マイブックマーク全文検索API
				class search : public hatena_base{
				public:
					search(const string_type& user_id,const string_type& q,const string_type& of="",const string_type& limit="",const string_type& sort="")
						: q_(q), of_(of), limit_(limit), sort_(sort), hatena_base("GET","http","b.hatena.ne.jp","/"+user_id+"/search/json"){}
					param_type sort() const
					{
						param_type args;
						args["q"]=util::url::encode(q_);
						if(!of_.empty()) args["of"]=of_;
						if(!limit_.empty()) args["limit"]=limit_;
						if(!sort_.empty()) args["sort"]=sort_;
						return args;
					}
				private:
					const string_type q_;
					const string_type of_;
					const string_type limit_;
					const string_type sort_;
				};

				//はてなブックマーク Web Hookはスルー

				namespace feed{
					//Atomフィード
					class atomfeed : public hatena_base{
					public:
						atomfeed(const string_type& user_id,const string_type& tag="",const string_type& date="")
							: tag_(tag), date_(date), hatena_base("GET","http","b.hatena.ne.jp","/"+user_id+"/atomfeed"){}
						param_type sort() const
						{
							param_type args;
							if(!tag_.empty()) args["tag"]=tag_;
							if(!date_.empty()) args["date"]=date_;
							return args;
						}
					private:
						const string_type tag_;
						const string_type date_;
					};
					
					//RSSフィード
					class rss : public hatena_base{
					public:
						rss(const string_type& user_id,const string_type& tag="",const string_type& date="",const string_type& url="")
							: tag_(tag), date_(date), url_(url), hatena_base("GET","http","b.hatena.ne.jp","/"+user_id+"/rss"){}
						param_type sort() const
						{
							param_type args;
							if(!tag_.empty()) args["tag"]=tag_;
							if(!date_.empty()) args["date"]=date_;
							if(!url_.empty()) args["url"]=url_;
							return args;
						}
					private:
						const string_type tag_;
						const string_type date_;
						const string_type url_;
					};
				}//End feed namespace

			}//End bookmark namespace
		}//End hatena namespace
	}//End api namespace
}//End oauth namespace

#endif
