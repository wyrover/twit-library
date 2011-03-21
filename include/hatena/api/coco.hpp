#ifndef HATENA_API_COCO_HPP
#define HATENA_API_COCO_HPP

namespace oauth{
	namespace api{
		namespace hatena{
			namespace coco{
				//イマココ情報JSON
				class info : public hatena_base{
				public:
					info(const string_type& path)
						: hatena_base("GET","http","c.hatena.com",path+".json"){}
				private:
				};
					
				//スポット検索結果JSON
				class nearby : public hatena_base{
				public:
					nearby(const string_type& lat,const string_type& vlong,const string_type& page="")
						: lat_(lat), long_(vlong), page_(page), hatena_base("GET","http","c.hatena.com","/s/nearby.json"){}
					param_type sort() const{
						param_type args;
						args["ll"]=lat_+","+long_;
						if(page_!="") args["page"]=page_;
						return args;
					}
				private:
					const string_type lat_;
					const string_type long_;
					const string_type page_;
				};
					
				//ユーザ情報JSON
				class stats : public hatena_base{
				public:
					stats(const string_type& user_id)
						: hatena_base("GET","http","c.hatena.com","/"+user_id+"/stats.json"){}
				private:
				};
				
				//スポット検索結果JSON(近くのスポット)
				class near_nearby : public hatena_base{
				public:
					near_nearby(const string_type& spot_key,const string_type& page="")
						: page_(page), hatena_base("GET","http","c.hatena.com","/s/"+spot_key+"/nearby.json"){}
					param_type sort() const{
						param_type args;
						if(page_!="") args["page"]=page_;
						return args;
					}
				private:
					const string_type page_;
				};
				
				//スポット検索(/api/v1/spots.json)
				class spots : public hatena_base{
				public:
					spots(const string_type& geolat,const string_type& geolong,const string_type& l="",const string_type& page="",const string_type& present_geolat="",const string_type& present_geolong="",const string_type& q="")
						: geolat_(geolat), geolong_(geolong), l_(l), page_(page), present_geolat_(present_geolat), present_geolong_(present_geolong), q_(q), hatena_base("GET","http","c.hatena.com","/api/v1/spots.json"){}
					param_type sort() const{
						param_type args;
						args["geolat"]=geolat_;
						args["geolong"]=geolong_;
						if(l_!="") args["l"]=l_;
						if(page_!="") args["page"]=page_;
						if(present_geolat_!="") args["present_geolat"]=present_geolat_;
						if(present_geolong_!="") args["present_geolong"]=present_geolong_;
						if(q_!="") args["q"]=util::url::encode(q_);
						return args;
					}
				private:
					const string_type geolat_;
					const string_type geolong_;
					const string_type l_;
					const string_type page_;
					const string_type present_geolat_;
					const string_type present_geolong_;
					const string_type q_;
				};
				
				//スポット検索(/api/v1/spots.json)
				class addspot : public hatena_base{
				public:
					addspot(const string_type& geolat,const string_type& geolong,const string_type& name,const string_type& primarycategoryid,const string_type& vprivate="",const string_type& checkinable_for_friends="")
						: geolat_(geolat), geolong_(geolong), name_(name), primarycategoryid_(primarycategoryid), private_(vprivate), checkinable_for_friends_(checkinable_for_friends), hatena_base("POST","http","c.hatena.com","/api/v1/addspot.json"){}
					param_type sort() const{
						param_type args;
						args["geolat"]=geolat_;
						args["geolong"]=geolong_;
						args["name"]=util::url::encode(name_);
						args["primarycategoryid"]=primarycategoryid_;
						if(private_!="") args["private"]=private_;
						if(checkinable_for_friends_!="") args["checkinable_for_friends"]=checkinable_for_friends_;
						return args;
					}
				private:
					const string_type geolat_;
					const string_type geolong_;
					const string_type name_;
					const string_type primarycategoryid_;
					const string_type private_;
					const string_type checkinable_for_friends_;
				};
				
				//カテゴリー情報取得(/api/v1/categories.json)
				class categories : public hatena_base{
				public:
					categories()
						: hatena_base("GET","http","c.hatena.com","/api/v1/categories.json"){}
				private:
				};
				
				//イマココ投稿(/api/v1/checkin.json)
				class checkin : public hatena_base{
				public:
					checkin(const string_type& spot_key,const string_type& body="",const string_type& twitter="",const string_type& mixi="",const string_type& photos_path="",const string_type& photos_name="")
						: key_(spot_key), body_(body), twitter_(twitter), mixi_(mixi), photos_path_(photos_path), photos_name_(photos_name), hatena_base("POST","http","c.hatena.com","/api/v1/checkin.json","multipart/form-data"){}
					std::vector<oauth::content::multipart_form_data> data() const
					{
						std::vector<oauth::content::multipart_form_data> datas;
						
						datas.push_back(oauth::content::multipart_form_data(oauth::content::content_type::Image,"photos",photos_path_,photos_name_));
						datas.push_back(oauth::content::multipart_form_data(oauth::content::content_type::Data,"key",key_));
						
						if(!body_.empty())
							datas.push_back(oauth::content::multipart_form_data(oauth::content::content_type::Data,"body",body_));

						if(!twitter_.empty())
							datas.push_back(oauth::content::multipart_form_data(oauth::content::content_type::Data,"twitter",twitter_));

						if(!mixi_.empty())
							datas.push_back(oauth::content::multipart_form_data(oauth::content::content_type::Data,"mixi",mixi_));

						return std::vector<oauth::content::multipart_form_data>(datas);
					}
				private:
					const string_type key_;
					const string_type body_;
					const string_type twitter_;
					const string_type mixi_;
					const string_type photos_path_;
					const string_type photos_name_;
				};
				
				//イマココ履歴取得(/api/v1/history.json)
				class history : public hatena_base{
				public:
					history(const string_type& name,const string_type& l="",const string_type& page="")
						: name_(name), l_(l), page_(page), hatena_base("GET","http","c.hatena.com","/api/v1/history.json"){}
					param_type sort() const{
						param_type args;
						args["name"]=name_;
						if(l_!="") args["l"]=l_;
						if(page_!="") args["page"]=page_;
						return args;
					}
				private:
					const string_type name_;
					const string_type l_;
					const string_type page_;
				};
				
				//ともだちイマココ取得(/api/v1/checkins.json)
				class checkins : public hatena_base{
				public:
					checkins(const string_type& l="",const string_type& page="")
						: l_(l), page_(page), hatena_base("GET","http","c.hatena.com","/api/v1/checkins.json"){}
					param_type sort() const{
						param_type args;
						if(l_!="") args["l"]=l_;
						if(page_!="") args["page"]=page_;
						return args;
					}
				private:
					const string_type l_;
					const string_type page_;
				};

				namespace timeline{
					struct Image{
						string_type image_path;
						string_type image_name;
						Image() {}
						Image(const string_type& image_path,const string_type& image_name)
							: image_path(image_path), image_name(image_name) {}
						Image(const Image& other)
							: image_path(other.image_path), image_name(other.image_name) {}
					};

					//はてなタイムライン投稿 API
					class post : public hatena_base{
					public:
						post(const string_type& body,const std::vector<Image>& images)
							: body_(body), images_(images), hatena_base("POST","http","h2.hatena.ne.jp","/post.text","multipart/form-data"){}
						std::vector<oauth::content::multipart_form_data> data() const
						{
							std::vector<oauth::content::multipart_form_data> datas;
							datas.push_back(oauth::content::multipart_form_data(oauth::content::content_type::Data,"body",body_));
							
							BOOST_FOREACH(Image image,images_)
								datas.push_back(oauth::content::multipart_form_data(oauth::content::content_type::Image,"image",image.image_path,image.image_name));
							
							return std::vector<oauth::content::multipart_form_data>(datas);
						}
					private:
						const string_type body_;
						const std::vector<Image> images_;
					};

					//タイムラインエントリー一覧ネイティブ API
					class timeline : public hatena_base{
					public:
						timeline(const string_type& page="")
							: page_(page), hatena_base("POST","http","n.hatena.ne.jp","/timeline.json"){}
						param_type sort() const{
							param_type args;
							if(page_!="") args["page"]=page_;
							return args;
						}
					private:
						const string_type page_;
					};
				}//End timeline namespace
			}//End coco namespace
		}//End hatena namespace
	}//End api namespace
}//End oauth namespace

#endif
