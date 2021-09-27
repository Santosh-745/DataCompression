#include <bits/stdc++.h> 
using namespace std; 

void add(string cntxt, char ltr, map<string, vector<char>> &l,
		 map<string, vector<int>> &c, map<string, vector<int>> &cc, int cnt, int cum_cnt)
{
	l[cntxt].push_back(ltr);
	c[cntxt].push_back(cnt);
	cc[cntxt].push_back(cum_cnt);	
}

int get(string cntxt, char ltr, map<string, vector<char>> &l, map<string, vector<int>> &c)
{
	int i;
	auto it = find(l[cntxt].begin(), l[cntxt].end(), ltr);
	i = it - l[cntxt].begin();
	return c[cntxt][i];
}

string encode(string str)
{
	string cntxt_1,cntxt_2;
	char ltr;
	int ind, pre;
	string output;

	unordered_map<char, int> count_0;
	unordered_map<char, int> cum_count_0;
	unordered_map<char, int> count_1;
	unordered_map<char, int> cum_count_1;
	map<string, vector<char>> letrs;
	map<string, vector<int>> cum_count;
	map<string, vector<int>> count;

	pre = 0;
	for(auto &it : str){
		if(!count_1[it])
		{
			count_1[it] = 1;
			cum_count_1[it] = pre + count_1[it];
			pre = cum_count_1[it];
		}
	}
	/*for(auto &it: cum_count_1)
		cout<<"\n "<<it.first<<" "<<it.second;

	l = pre_l + ( ((pre_u - pre_l + 1) * cum_count[x-1]) / total);  
	u = pre_l + ( ((pre_u - pre_l + 1) * cum_count[x]) / total) - 1;  
	*/     
	
	// add first char to 0 order tbl
	count_0[str[0]] = 1;
	cum_count_0[str[0]] = 1;

	// add esc to 0 order tbl
	count_0['#'] = 1;
	cum_count_0['#'] = 2;

	// add first char to 1 order tbl with ltr and esc...
	cntxt_1 = str[0];
	add(cntxt_1,str[1],letrs,count,cum_count,1,1);
	add(cntxt_1,'#',letrs,count,cum_count,1,2);

	// add first two char to 2nd order tbl with esc symbol...
	cntxt_2 = str[0] + str[1];
	add(cntxt_2,'#',letrs,count,cum_count,1,1);

	// cout<<get(cntxt_1,str[1],letrs,cum_count);  // testing get func...

	for(ind=2;ind < str.length();ind++)
	{
		ltr = str[ind];
		cntxt_2 = str.substr(ind-2,2);
		cntxt_1 = str[ind-1];
		
		// if 2nd order context is available or not...
		if(ltrs[cntxt_2].size()){
		//if yes then check letter...
		
			if(count(letrs[cntxt_2].begin(), letrs[cntxt_2].end(), ltr)){
			// if letter is also there, then encode it and update count...
				
			}
			else{
			//if cntxt is there but not the letter then encode esc symbol and add ltr...

			}
		}
		else{
			// if context is not there add it with ltr and esc...
			add(cntxt_2,ltr,letrs,count,cum_count,1,1);
			
			// add esc...
			add(cntxt_2,'#',letrs,count,cum_count,1,2);

			// now check for 1st order context is available or not...
			if(ltrs[cntxt_1].size()){
			//if yes then check ltr...
				
				if(count(letrs[cntxt_1].begin(), letrs[cntxt_1].end(), ltr)){
				// if letter is also there, then encode it and update count...

				}
				else{
				//if cntxt is there but not the letter then encode esc symbol and add ltr...

				}
			}
			else{
				// if context is not there add it with ltr and esc...
				add(cntxt_1,ltr,letrs,count,cum_count,1,1);
				
				// add esc...
				add(cntxt_1,'#',letrs,count,cum_count,1,2);

				// now check for 0 order tbl...
				if(count_0[ltr]){

				}
				else{
				// add to 0 order tbl...


					// and encode using -1 order tbl...
					

				}
			}
		}
	}

	return output;
}

int main() 
{ 
	string en_str;
	string str = "this$is";
	en_str = encode(str);
}
