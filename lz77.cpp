#include<bits/stdc++.h> 	
using namespace std; 

void encoder(string str, vector<vector<int>> &v, int sb_size){
	int cur_i, p1, p2, p3, l, max_l, offset;
	vector<int> tmp_v;
	char ch;

	tmp_v.push_back(0);
	tmp_v.push_back(0);
	tmp_v.push_back(str[0]);
	v.push_back(tmp_v);
	tmp_v.clear();
	
	// for(auto &it : tmp_v)
	// 	cout<<it;
	
	cur_i = 1;
	while(cur_i < str.length()){
		// cout<<"\n\n cur_i"<<cur_i;
		if(cur_i < sb_size)
			p1 = 0;
		else 
			p1 = cur_i - sb_size;

		max_l = 0;
		offset = 0;
		while(p1 < cur_i){
			if(str[p1] == str[cur_i]){
				p2 = cur_i;
				p3 = p1;
				l = 0;
				while(str[p3] == str[p2]){
					p3++;
					p2++;
					l++;
				}
				if(l >= max_l){
					max_l = l;
					offset = cur_i - p1;
				}
				p1 = p3;
			}

			else{
				p1++;
			}
		}
		// cout<<"\n Os "<<offset<<" max_l "<<max_l<<" ch "<<ch;
		
		tmp_v.push_back(offset);
		tmp_v.push_back(max_l);
		if(offset == 0)
			tmp_v.push_back(str[cur_i]);
		else
			tmp_v.push_back(str[cur_i + max_l]);

		v.push_back(tmp_v);
		tmp_v.clear();
		
		cur_i += max_l + 1;
	}
 	// for(auto &it : v)
	 //  	cout<<"\n"<<it[0]<<" "
  //   	  	<<it[1]<<" "<<(char)(it[2]);
}

string decoder(vector<vector<int>> v){
	string str;
	int cur_i, p1, p2, i;

	cur_i = 0;
	for(auto &it: v){
		// cout<<"\n\n cur_i "<<cur_i;
		// cout<<"\n"<<it[0]<<" "<<it[1]<<" "<<(char)(it[2]);
		if(it[0] == 0){
			str += (char)it[2];
			cur_i++;
		}
		else{
			p1 = cur_i - it[0];
			for(i = p1; i < p1 + it[1]; i++)
				str += str[i];
			str += (char)it[2];
			cur_i += it[1] + 1;
		}
	}

	return str;
}

int main() 
{ 
	string in_str, de_str; 
	in_str = "ababcbababaa"; //cabracadabrarrarrad 
	// in_str = "a" ;
	vector<vector<int>> en_v;

	cout<<"Input string "<<in_str;  
	encoder(in_str, en_v, 7);// input string, vector resultant, total window size, search buffer size 
	cout<<"\n==> encoding results ==> ";
	for(auto &it : en_v)
		cout<<" <"<<it[0]<<" "<<it[1]<<" "<<(char)(it[2])<<">,";

	de_str = decoder(en_v); 
	cout<<"\n==> Decoded String is "<<de_str;

	return 0; 
}

// 0 1 2 3 4 5 6 7 8 9 10 11
// a b a b c b a b a b  a  a
// 0 0 a
// 0 0 b
// 2 2 c
// 4 3 a
// 2 2 a

// i = 4
// 0 1 2 3 4 5 6 7 8 9 10 11
// a b a b c b a b a b  a  a 