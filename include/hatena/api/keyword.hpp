#ifndef HATENA_API_BOOKMARK_HPP
#define HATENA_API_BOOKMARK_HPP

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <vector>

namespace oauth{
	namespace api{
		namespace hatena{
			namespace keyword{
				//検索フィードの取得
				class search_feed : public hatena_base{
				public:
					search_feed(const string_type& word,const string_type& page,const string_type& mode)
						: word_(word), page_(page), mode_(mode), hatena_base("GET","http","search.hatena.ne.jp","/keyword"){}
					param_type sort() const{
						param_type args;
						args["ie"]="utf8";
						args["word"]=util::url::encode(word_);
						if(!page_.empty()) args["page"]=page_;
						if(!mode_.empty()) args["mode"]=mode_;
						return args;
					}
				private:
					const string_type word_;
					const string_type page_;
					const string_type mode_;
				};

				//検索フィードの取得
				class keyword_feed : public hatena_base{
				public:
					keyword_feed(const string_type& word,const string_type& mode)
						: word_(word), page_(page), mode_(mode), hatena_base("GET","http","d.hatena.ne.jp","/keyword"){}
					param_type sort() const{
						param_type args;
						args["ie"]="utf8";
						args["word"]=util::url::encode(word_);
						if(!mode_.empty()) args["mode"]=mode_;
						return args;
					}
				private:
					const string_type word_;
					const string_type mode_;
				};
				
				namespace auto_link{
					struct Keywords{
						string_type body;
						string_type score;
						std::vector<string_type> cname;
						string_type a_target;
						string_type a_class;
						string_type mode;
						Keywords() {}
						Keywords(const string_type& body,const string_type& score="",const std::vector<string_type>& cname=std::vector<string_type>(),const string_type& a_target="",const string_type& a_class="",const string_type& mode="")
							: body(body), score(score), cname(cname), a_target(a_target), a_class(a_class), mode(mode) {}
						Keywords(const Keywords& other)
							: body(other.body), score(other.score), cname(other.cname), a_target(other.a_target), a_class(other.a_class), mode(other.mode){}
					};

					//はてなキーワード自動リンクAPI
					class auto_link : public hatena_base{
					public:
						auto_link(const Keywords& keywords)
							: keywords_(keywords), hatena_base("POST","http","d.hatena.ne.jp","/xmlrpc","application/x.atom+xml"){}
						boost::property_tree::ptree xml_ptree() const
						{
							boost::property_tree::ptree pt;
							boost::property_tree::ptree& member;

							pt.add("methodCall.methodname","hatena.setKeywordLink");
							boost::property_tree::ptree& struct_ = pt.add("methodCall.param.value.struct","");
							
							member = struct_.add("<xmlattr>.member","");
							member.add("<xmlattr>.name","body");
							member.add("<xmlattr>.value",keywords_.body);
							
							if(keywords_.score!=""){
								member = struct_.add("<xmlattr>.member","");
								member.add("<xmlattr>.name","score");
								member.add("<xmlattr>.value",keywords_.score);
							}							
							if(keywords_.a_target!=""){
								member = struct_.add("<xmlattr>.member","");
								member.add("<xmlattr>.name","a_target");
								member.add("<xmlattr>.value",keywords_.a_target);
							}
							if(keywords_.a_class!=""){
								member = struct_.add("<xmlattr>.member","");
								member.add("<xmlattr>.name","a_class");
								member.add("<xmlattr>.value",keywords_.a_class);
							}

							if(keywords_.cname.size!=0){
								member = struct_.add("<xmlattr>.member","");
								member.add("<xmlattr>.name","<xmlattr>.cname");

								boost::property_tree::ptree& data = member.add("<xmlattr>.value.array.data","");

								BOOST_FOREACH(string_type keyword,keywords_.cname)
								{
									data.add("<xmlattr>.value.string",keywords_.a_class);
								}
							}
							
							return pt;
						}
					private:
						const Keywords keywords_;
					};
				}//End auto_link namespace
				
				namespace association{
					struct Keywords{
						string_type body;
						string_type score;
						std::vector<string_type> cname;
						string_type a_target;
						string_type a_class;
						string_type mode;
						Keywords() {}
						Keywords(const string_type& body,const string_type& score="",const std::vector<string_type>& cname=std::vector<string_type>(),const string_type& a_target="",const string_type& a_class="",const string_type& mode="")
							: body(body), score(score), cname(cname), a_target(a_target), a_class(a_class), mode(mode) {}
						Keywords(const Keywords& other)
							: body(other.body), score(other.score), cname(other.cname), a_target(other.a_target), a_class(other.a_class), mode(other.mode){}
					};

					//はてなキーワード連想語API
					class association : public hatena_base{
					public:
						association(const std::vector<string_type>& wordlist)
							: wordlist_(wordlist), hatena_base("POST","http","d.hatena.ne.jp","/xmlrpc","application/x.atom+xml"){}
						boost::property_tree::ptree xml_ptree() const
						{
							boost::property_tree::ptree pt;
							
							pt.add("methodCall.methodName","hatena.getSimilarWord");
							boost::property_tree::ptree& member = pt.add("methodCall.param.value.struct.member","");
							boost::property_tree::ptree& data = member.add("<xmlattr>.value.array.data","");
							
							BOOST_FOREACH(string_type word,wordlist_)
							{
								data.add("<xmlattr>.value.string",word);
							}
														
							return pt;
						}
					private:
						const std::vector<string_type> wordlist_;
					};
				}//End association namespace
			}//End keyword namespace
		}//End hatena namespace
	}//End api namespace
}//End oauth namespace

#endif
