#ifndef HATENA_API_DIARY_HPP
#define HATENA_API_DIARY_HPP

namespace oauth{
	namespace api{
		namespace hatena{
			namespace diary{
				struct Diary{
					string_type title;
					string_type content;
					string_type updated;
					Diary() {}
					Diary(const string_type& title,const string_type& content,const string_type& updated="")
						: title(title), content(content), updated(updated) {}
					Diary(const Diary& other)
						: title(other.title), content(other.content), updated(other.updated){}
				};

				namespace atom{
					//サービス文書
					class atom : public hatena_base{
					public:
						atom(const string_type& user_id)
							: hatena_base("GET","http","d.hatena.ne.jp","/"+user_id+"/atom"){}
					private:
					};
					
					//日記エントリー一覧の取得
					class blog_get : public hatena_base{
					public:
						blog_get(const string_type& user_id,const string_type& page="")
							: page_(page), hatena_base("GET","http","d.hatena.ne.jp","/"+user_id+"/atom/blog"){}
						param_type sort() const{
							param_type args;
							if(page_!="") args["page"]=page_;
							return args;
						}
					private:
						const string_type page_;
					};
					
					//日記エントリーの投稿
					class blog_post : public hatena_base{
					public:
						blog_post(const string_type& user_id,const Diary* diary)
							: diary_(diary), hatena_base("POST","http","d.hatena.ne.jp","/"+user_id+"/atom/blog","application/x.atom+xml"){}
						boost::property_tree::ptree xml_ptree() const
						{
							boost::property_tree::ptree pt;
							
							boost::property_tree::ptree& entry = pt.add("entry","");
							entry.put("<xmlattr>.xmlns","http://purl.org/atom/ns#");

							pt.add("entry.title",diary_->title);

							boost::property_tree::ptree& content = pt.add("entry.content",diary_->content);
							content.put("<xmlattr>.type","text/html");

							if(!diary_->updated.empty()){
								pt.add("entry.updated",diary_->updated);
							}

							return pt;
						}
					private:
						const Diary* diary_;
					};
					
					//日記エントリーの取得
					class blog_entry_get : public hatena_base{
					public:
						blog_entry_get(const string_type& user_id,const string_type& date,const string_type& entry_id)
							: hatena_base("GET","http","d.hatena.ne.jp","/"+user_id+"/atom/blog/"+date+"/"+entry_id){}
					private:
					};
					
					//日記エントリーの編集
					class blog_entry_put : public hatena_base{
					public:
						blog_entry_put(const string_type& user_id,const string_type& date,const string_type& entry_id,const Diary* diary)
							: diary_(diary), hatena_base("PUT","http","d.hatena.ne.jp","/"+user_id+"/atom/blog/"+date+"/"+entry_id,"application/x.atom+xml"){}
						boost::property_tree::ptree xml_ptree() const
						{
							boost::property_tree::ptree pt;
							
							boost::property_tree::ptree& entry = pt.add("entry","");
							entry.put("<xmlattr>.xmlns","http://purl.org/atom/ns#");

							pt.add("entry.title",diary_->title);

							boost::property_tree::ptree& content = pt.add("entry.content",diary_->content);
							content.put("<xmlattr>.type","text/html");

							if(!diary_->updated.empty()){
								pt.add("entry.updated",diary_->updated);
							}

							return pt;
						}
					private:
						const Diary* diary_;
					};
					
					//日記エントリーの削除
					class blog_entry_delete : public hatena_base{
					public:
						blog_entry_delete(const string_type& user_id,const string_type& date,const string_type& entry_id)
							: hatena_base("DELETE","http","d.hatena.ne.jp","/"+user_id+"/atom/blog/"+date+"/"+entry_id){}
					private:
					};
					
					//下書きの投稿
					class blog_draft_post : public hatena_base{
					public:
						blog_draft_post(const string_type& user_id,const Diary* diary)
							: diary_(diary), hatena_base("POST","http","d.hatena.ne.jp","/"+user_id+"/atom/draft/","application/x.atom+xml"){}
						boost::property_tree::ptree xml_ptree() const
						{
							boost::property_tree::ptree pt;
							
							boost::property_tree::ptree& entry = pt.add("entry","");
							entry.put("<xmlattr>.xmlns","http://purl.org/atom/ns#");

							pt.add("entry.title",diary_->title);

							boost::property_tree::ptree& content = pt.add("entry.content",diary_->content);
							content.put("<xmlattr>.type","text/html");

							if(!diary_->updated.empty()){
								pt.add("entry.updated",diary_->updated);
							}

							return pt;
						}
					private:
						const Diary* diary_;
					};
					
					//日記エントリーの編集
					class blog_draft_put : public hatena_base{
					public:
						blog_draft_put(const string_type& user_id,const string_type& entry_id,const Diary* diary)
							: diary_(diary), hatena_base("PUT","http","d.hatena.ne.jp","/"+user_id+"/atom/draft/"+entry_id,"application/x.atom+xml"){}
						boost::property_tree::ptree xml_ptree() const
						{
							boost::property_tree::ptree pt;
							
							boost::property_tree::ptree& entry = pt.add("entry","");
							entry.put("<xmlattr>.xmlns","http://purl.org/atom/ns#");

							pt.add("entry.title",diary_->title);

							boost::property_tree::ptree& content = pt.add("entry.content",diary_->content);
							content.put("<xmlattr>.type","text/html");

							if(!diary_->updated.empty()){
								pt.add("entry.updated",diary_->updated);
							}

							return pt;
						}
					private:
						const Diary* diary_;
					};
					
					//下書きの公開
					class blog_draft_publish : public hatena_base{
					public:
						blog_draft_publish(const string_type& user_id,const string_type& entry_id)
							: hatena_base("PUT","http","d.hatena.ne.jp","/"+user_id+"/atom/draft/"+entry_id){}
						std::map<string_type,string_type> header() const{
							param_type head;
							head["X-HATENA-PUBLISH"] = "1";
							return head;
						}
					private:
					};
					
					//下書きの削除
					class blog_draft_delete : public hatena_base{
					public:
						blog_draft_delete(const string_type& user_id,const string_type& entry_id)
							: hatena_base("DELETE","http","d.hatena.ne.jp","/"+user_id+"/atom/draft/"+entry_id){}
					private:
					};
				}//End atom namespace
				
				namespace comment{
					//コメントURL数取得API
					class urlcount : public hatena_base{
					public:
						urlcount(const std::vector<string_type>& urls)
							: urls_(urls), hatena_base("GET","http","d.hatena.ne.jp","/api/comment/urlcount"){}
						param_type sort() const{
							param_type args;

							bool first = true;
							BOOST_FOREACH(string_type url,urls_)
							{
								if(first==true)
								{
									args["url"]=util::url::encode(url);
									first = false;
								}
								else args["url"]+=("&url="+util::url::encode(url));
							}

							return args;
						}
					private:
						const std::vector<string_type> urls_;
					};
				}//End comment namespace
			}//End diary namespace
		}//End hatena namespace
	}//End api namespace
}//End oauth namespace

#endif
