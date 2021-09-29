#include<bits/stdc++.h>
using namespace std;

int encoder(string str, vector<string> &v)
{
	string tmp_str, ch;
	vector<string> v1;
	int i;

	// permutations...
	v1.push_back(str);
	tmp_str = str;
	for(i=0;i<str.length() - 1;i++){
		tmp_str += tmp_str[0];
		tmp_str.erase(tmp_str.begin());
		v1.push_back(tmp_str);
	}
	sort(v1.begin(), v1.end());
	// for(auto &it : v1)
	// 	cout<<"\n==> "<<it;

	// getiing L...
	tmp_str.clear() ;
	for(auto &it : v1){
		// cout<<"\n"<<it;
		tmp_str += it[it.length()-1];
		// cout<<"\n"<<tmp_str;
		v.push_back(tmp_str);
		tmp_str.clear();
	}

	auto it = find(v1.begin(), v1.end(), str);
	i = it - v1.begin();

	return i;
}

string decoder(vector<string> l, int x) 
{ 
	string str,tmp_str; 
	vector<string> f; 
	map<string, int> m; 
	int i; 

	for(auto &it: l) 
		m[it] = 1; 

	/*
	0  1  2  3   4   5  6  7   8   9  10
	s1 s2 h  t1  t2  h  $  i1  i2  $   e
	*/
	for(i = 0; i < l.size(); i++){ 
		// cout<<"\n l_i "<<l[i]<<" m[l[i]] "<<m[l[i]]; 
		tmp_str = (char)(m[l[i]] + 48);
		m[l[i]] += 1; 
		l[i] += tmp_str;
	} 

	// cout<<"\n"; 
	// for(auto &it: l) 
		// cout<<" "<<it; 

	f = l; 
	sort(f.begin(), f.end()); 

	// cout<<"\n"; 
	// for(auto &it: f) 
	// 	cout<<" "<<it; 

	// original decoding...
	for(i = 0; i < l.size(); i++){ 
		str += f[x][0]; 
		auto it = find(l.begin(), l.end(), f[x]); 
		x = it - l.begin();
		//cout<<"\n"<<str;
	} 
	return str; 
}

int main()
{
	string in_str, de_str;
	int ind;
	vector<string> v;

	in_str = "this_is_burrows_wheeler_transform...";
	cout<<"\n==> Original String ==> "<<in_str;

	// cout<<"\n\n==> Encoding....";
	ind = encoder(in_str, v);
	// cout<<"\n "<<ind<<"\n";
	cout<<"\n==> Encoded ==> ";
	for(auto &it: v)
		cout<<""<<it;

	// cout<<"\n\n==> Decoding....";
	de_str = decoder(v, ind);
	cout<<"\n==> decoded string ==> "<<de_str;

	return 0;

}

/*  a   b   c   d   e  = a,e
	b	c 	d 	e 	a  = b,a
	c 	d 	e 	a 	b  = c,b
	d 	e 	a 	b 	c  = d,c
	e 	a 	b 	c 	d  = e,d 

	0 1 2 3 4 5 6 7 8 9  10
	s s h t t h $ i i $  e
	$ $ e h h i i s s t  t 
 
*/