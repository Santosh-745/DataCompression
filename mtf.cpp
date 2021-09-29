#include<bits/stdc++.h>
using namespace std;

void encoder(string str, vector<char> v, vector<int> &v1){
	// v is helper v1 is resultant...
	int i;

	for(auto &ch: str){	
		auto it = find(v.begin(), v.end(), ch);
		i = it - v.begin();
		v1.push_back(i);

		if(i != 0){ // move to front...
			v.erase(v.begin()+i);
			v.insert(v.begin(), ch);
		}
	}
}

string decoder(vector<char> v, std::vector<int> v1){

	string str;
	char ch;

	for(auto &ele: v1){		
		str += v[ele];
		if(ele != 0){
			ch = v[ele];
			v.erase(v.begin()+ele);
			v.insert(v.begin(), ch);
		}
	}

	return str;
}

int main()
{

	string in_str, de_str;
	vector<int> en_v;
	vector<char> v;

	in_str = "this_is_Move_to_front...";
	cout<<"\n==> Original String ==> "<<in_str;
	
	for(auto &it: in_str)
		if(!count(v.begin(), v.end(), it))
			v.push_back(it);
	sort(v.begin(), v.end());

	// for(auto &it: v)
	// 	cout<<" "<<it;

	encoder(in_str, v, en_v);
	cout<<"\n==> Encoded ==> ";
	for(auto &it: en_v)
		cout<<" "<<it;

	de_str = decoder(v, en_v);
	cout<<"\n==> Decoded string ==> "<<de_str;

	return 0;
}