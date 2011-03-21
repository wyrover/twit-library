#ifndef HATENA_API_COMMON_HPP
#define HATENA_API_COMMON_HPP

namespace oauth{
	namespace api{
		namespace hatena{
			//はてなお気に入りAPI
			class favorite : public hatena_base{
			public:
				favorite(const string_type& user_id)
					: hatena_base("GET","http","www.hatena.ne.jp","/"+user_id+"/favorites.json"){}
			private:
			};

			namespace friend_info{
				//ともだちイマココ取得(/api/v1/checkins.json)
				class friends : public hatena_base{
				public:
					friends(const string_type& user_id,const string_type& with_annotations="")
						: with_annotations_(with_annotations), hatena_base("GET","http","n.hatena.com","/"+user_id+"/friends.json"){}
					param_type sort() const{
						param_type args;
						if(with_annotations_!="") args["with_annotations"]=with_annotations_;
						return args;
					}
				private:
					const string_type with_annotations_;
				};
					
				//ともだち状態一覧の取得(/fr/all.json)
				class all : public hatena_base{
				public:
					all()
						: hatena_base("GET","http","n.hatena.com","/fr/all.json"){}
				private:
				};
					
				//ともだち状態の変更 (/USERNAME/relation)
				class relation : public hatena_base{
				public:
					relation(const string_type& user_id,const string_type& location,const string_type& operation,const string_type& flid="",const string_type& message="")
						: location_(location), operation_(operation), flid_(flid), message_(message), hatena_base("POST","http","n.hatena.com","/"+user_id+"/relation.json"){}
					param_type sort() const{
						param_type args;
						args["location"]=location_;
						args["operation"]=operation_;
						if(flid_!="") args["flid"]=flid_;
						if(message_!="") args["message"]=message_;
						return args;
					}
				private:
					const string_type location_;
					const string_type operation_;
					const string_type flid_;
					const string_type message_;
				};
					
				//ともだち関係の説明の変更(/USERNAME/relation/label/edit)
				class relation_label : public hatena_base{
				public:
					relation_label(const string_type& user_id,const string_type& label)
						: label_(label), hatena_base("POST","http","n.hatena.com","/"+user_id+"/relation/label/edit"){}
					param_type sort() const{
						param_type args;
						args["label"]=label_;
						return args;
					}
				private:
					const string_type label_;
				};
			}//End friend_info namespace
		}//End hatena namespace
	}//End api namespace
}//End oauth namespace

#endif
