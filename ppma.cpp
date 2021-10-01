#include <bits/stdc++.h> 
using namespace std; 

void add_cntxt(string cntxt, char ltr, map<string, vector<char>> &l,
		 map<string, vector<int>> &c, map<string, vector<int>> &cc, int cnt, int cum_cnt)
{
	// cout<<"\n cntxt "<<cntxt;
	l[cntxt].push_back(ltr);
	c[cntxt].push_back(cnt);
	cc[cntxt].push_back(cum_cnt);	
}

void add_ltr(string cntxt, char ltr, map<string, vector<char>> &l, 
		   map<string, vector<int>> &c, map<string, vector<int>> &cc)
{
	int i;
	auto it = find(l[cntxt].begin(), l[cntxt].end(), '#');
	i = it - l[cntxt].begin();
	l[cntxt].insert(it, ltr);
	c[cntxt].insert(c[cntxt].begin() + i, 1); // count will be 1 and cum_count remains as esc symbol...
	c[cntxt].push_back(1); // this is for esc symbol...
	cc[cntxt].push_back(cc[cntxt].back() + 1); // this is for new cum_cnt of esc symbol...	
}

int get(string cntxt, char ltr, map<string, vector<char>> &l, map<string, vector<int>> &c)
{
	int i;
	auto it = find(l[cntxt].begin(), l[cntxt].end(), ltr);
	i = it - l[cntxt].begin();
	return c[cntxt][i];
}

void update_cnt(string cntxt, char ltr,  map<string, vector<char>> &l, 
		   map<string, vector<int>> &c, map<string, vector<int>> &cc)
{
	int i, j;
	auto it = find(l[cntxt].begin(), l[cntxt].end(), ltr);
	i = it - l[cntxt].begin();
	c[cntxt][i] += 1; // increamenting cnt of ltr...

	// increamenting cum_cnt of letter and every symbol after it...
	for(j = i; j < c[cntxt].size(); j++){
		cc[cntxt][j] += 1;
	}
}

string encode_utility(int l, int u, int *pre_l, int *pre_u, int *scale3){
	int b;
	string str;
	bitset<8> bin_l, bin_u;
	bin_l = bitset<8>(l); 
	bin_u = bitset<8>(u); 

	cout<<"\n binl "<<bin_l<<" binu "<<bin_u; 
	while(bin_l[7] == bin_u[7] || (bin_l[6] == 1 && bin_u[6] == 0) ){ 
       if(bin_l[7] == bin_u[7]){ 
            b = bin_u[7]; 
            str = str + to_string(b); 
            bin_l <<= 1; 
            bin_u <<= 1; 
            bin_u[0] = 1; 
            while(*scale3 > 0){ 
                 str += (b==0)?"1":"0"; 
                 *scale3 -= 1; 
            } 
            cout<<"\n binl "<<bin_l<<" binu "<<bin_u; 
        } 
       if(bin_l[6] == 1 && bin_u[6] == 0){ 
            bin_l <<= 1; 
            bin_u <<= 1; 
            bin_u[0] = 1; 
            bin_u[7] = 1; 
            bin_l[7] = 0; 
            *scale3 += 1;
             cout<<"\n binl "<<bin_l<<" binu "<<bin_u<<" scale3 "<<scale3; 
        } 
    } 
    //break;  
    *pre_l = bin_l.to_ulong(); 
    *pre_u = bin_u.to_ulong(); 
    cout<<"\n str "<<str;
    return str;
}

string encode(string str)
{
	string cntxt_1,cntxt_2, en_str;
	char ltr;
	int i, ind, pre, pre_l, pre_u, l, u, scale3, x, total, cnt_x, cum_cnt_x, k;     
	string output;

	map<char, int> count_0;
	map<char, int> cum_count_0;
	map<char, int> count_1;
	map<char, int> cum_count_1;
	map<string, vector<char>> letrs;
	map<string, vector<int>> cum_count;
	map<string, vector<int>> count;

	// setting up (-1) order count, cum_count...
	// count_1 -> (-1) order count table...
	// cum_count_1 -> (-1) order cum_count table...
	pre = 0;
	for(auto &it : str){
		if(!count_1[it])
		{
			count_1[it] = 1;
			cum_count_1[it] = pre + count_1[it];
			pre = cum_count_1[it];
		}
	}
	count_1['#'] = 1;
	cum_count_1['#'] = pre + 1;
	// for(auto &it: cum_count_1)
	// 	cout<<"\n "<<it.first<<" "<<it.second;
	/*
	l = pre_l + ( ((pre_u - pre_l + 1) * cum_count[x-1]) / total);  
	u = pre_l + ( ((pre_u - pre_l + 1) * cum_count[x]) / total) - 1;  
	*/     
	
	pre_l = 0;
	pre_u = 255;
	scale3 = 0;
	
	// add first char to 0 order tbl
	count_0[str[0]] = 1;
	cum_count_0[str[0]] = 1;

	// add esc to 0 order tbl
	count_0['#'] = 1;
	cum_count_0['#'] = 2;

	// add first char to 1 order tbl with ltr and esc...
	cntxt_1 = str[0];
	add_cntxt(cntxt_1,str[1],letrs,count,cum_count,1,1);
	add_cntxt(cntxt_1,'#',letrs,count,cum_count,1,2);

	// add first two char to 2nd order tbl with esc symbol...
	cntxt_2 = str.substr(0,2);
	// cout<<"\n testing "<<cntxt_2;	
	add_cntxt(cntxt_2,'#',letrs,count,cum_count,1,1);
	// cout<<"\n testing "<<letrs["th"].size();
	
	// cout<<get(cntxt_1,str[1],letrs,cum_count);  // testing get func...
	en_str = "";
	for(ind=2;ind < str.length();ind++)
	{
		ltr = str[ind];
		cntxt_2 = str.substr(ind-2,2);
		cntxt_1 = str[ind-1];
		cout<<"\n\n c_2 = "<<cntxt_2<<"  c_1 = "<<cntxt_1<<"  ltr = "<<ltr;
		
		// if 2nd order context is available or not...
		if(letrs[cntxt_2].size()){
		//if yes then check letter...
			
			if(std::count(letrs[cntxt_2].begin(), letrs[cntxt_2].end(), ltr)){
			// if letter is also there, then encode it and update count...
			
				// l = pre_l + ( ((pre_u - pre_l + 1) * cum_cnt_x_1) / total);  
				// u = pre_l + ( ((pre_u - pre_l + 1) * cum_cnt_x) / total) - 1;
				total = get(cntxt_2, '#', letrs, cum_count);
				cnt_x = get(cntxt_2, ltr, letrs, count);
				cum_cnt_x = get(cntxt_2, ltr, letrs, cum_count);
				k = cum_cnt_x - cnt_x; // cum_cnt(x-1)...

				l = pre_l + (((pre_u - pre_l + 1) * k) / total);
				u = pre_l + (((pre_u - pre_l + 1) * cum_cnt_x) / total) - 1;

				en_str = en_str + encode_utility(l, u, &pre_l, &pre_u, &scale3);
					
				update_cnt(cntxt_2, ltr, letrs, count, cum_count);
			}
			else{
			//if cntxt is there but not the letter then encode esc symbol and add ltr...
				
				total = get(cntxt_2, '#', letrs, cum_count);
				cnt_x = get(cntxt_2, '#', letrs, count);
				cum_cnt_x = total; // x = esc symbol...
				k = cum_cnt_x - cnt_x; // cum_cnt(x-1)...
				
				// cout<<"\n testing cntxt "<<cntxt_2<<" ch "<<ltr;
				// cout<<"\n testing tot "<<total<<" cc "<<cum_cnt_x<<" k "<<k;
				l = pre_l + (((pre_u - pre_l + 1) * k) / total);
				u = pre_l + (((pre_u - pre_l + 1) * cum_cnt_x) / total) - 1;

				en_str = en_str + encode_utility(l, u, &pre_l, &pre_u, &scale3);

				add_ltr(cntxt_2, ltr, letrs, count, cum_count);
				cout<<"\n testing count "<<get(cntxt_2, '#', letrs, cum_count);
			}
		}
		else{

			// if context is not there add it with ltr and esc...
			add_cntxt(cntxt_2,ltr,letrs,count,cum_count,1,1);
			
			// add esc...
			add_cntxt(cntxt_2,'#',letrs,count,cum_count,1,2);

			// now check for 1st order context is available or not...
			if(letrs[cntxt_1].size()){
			//if yes then check ltr...
				

				if(std::count(letrs[cntxt_1].begin(), letrs[cntxt_1].end(), ltr)){
				// if letter is also there, then encode it and update count...
					total = get(cntxt_1, '#', letrs, cum_count);
					cnt_x = get(cntxt_1, ltr, letrs, count);
					cum_cnt_x = get(cntxt_1, ltr, letrs, cum_count);
					k = cum_cnt_x - cnt_x; // cum_cnt(x-1)...

					l = pre_l + (((pre_u - pre_l + 1) * k) / total);
					u = pre_l + (((pre_u - pre_l + 1) * cum_cnt_x) / total) - 1;

					en_str = en_str + encode_utility(l, u, &pre_l, &pre_u, &scale3);
						
					update_cnt(cntxt_1, ltr, letrs, count, cum_count);	
				}
				else{
				//if cntxt is there but not the letter then encode esc symbol and add ltr...
					total = get(cntxt_1, '#', letrs, cum_count);
					cnt_x = get(cntxt_1, '#', letrs, count);
					cum_cnt_x = total; // x = esc symbol...
					k = cum_cnt_x - cnt_x; // cum_cnt(x-1)...
					
					cout<<"\n testing cntxt "<<cntxt_2<<" ch "<<ltr;
					cout<<"\n testing tot "<<total<<" cc "<<cum_cnt_x<<" k "<<k;
					l = pre_l + (((pre_u - pre_l + 1) * k) / total);
					u = pre_l + (((pre_u - pre_l + 1) * cum_cnt_x) / total) - 1;

					en_str = en_str + encode_utility(l, u, &pre_l, &pre_u, &scale3);

					add_ltr(cntxt_1, ltr, letrs, count, cum_count);
				
				}
			}
			else{
				
				// if context is not there add it with ltr and esc...
				add_cntxt(cntxt_1,ltr,letrs,count,cum_count,1,1);
				
				// add esc...
				add_cntxt(cntxt_1,'#',letrs,count,cum_count,1,2);

				// now check for 0 order tbl...
				if(count_0[ltr]){
					
					total = count_0['#'];
					cnt_x = count_0[ltr];
					cum_cnt_x = cum_count_0[ltr];
					k = cum_cnt_x - cnt_x; // cum_cnt(x-1)...

					l = pre_l + (((pre_u - pre_l + 1) * k) / total);
					u = pre_l + (((pre_u - pre_l + 1) * cum_cnt_x) / total) - 1;

					en_str = en_str + encode_utility(l, u, &pre_l, &pre_u, &scale3);

					//update count & cum_count in 0 order table...
					count_0[ltr]++;
					auto it = cum_count_0.find(ltr);
					while(it != cum_count_0.end()){
						cum_count_0[it->first]++;
						it++;
					}
				}
				else{
					// add to 0 order tbl...
					count_0[ltr] = 1;
					cum_count_0[ltr] = cum_count_0['#'];
					cum_count_0['#'] += 1;

					// and encode using -1 order tbl...
					total = count_1['#'];
					cnt_x = count_1[ltr];
					cum_cnt_x = cum_count_1[ltr];
					k = cum_cnt_x - cnt_x; // cum_cnt(x-1)...

					l = pre_l + (((pre_u - pre_l + 1) * k) / total);
					u = pre_l + (((pre_u - pre_l + 1) * cum_cnt_x) / total) - 1;

					en_str = en_str + encode_utility(l, u, &pre_l, &pre_u, &scale3);
				}
			}
		}
	}
	// for(auto &it: letrs){
	// 	cout<<"\n context "<<it.first;
	// 	for(auto &it1: letrs[it.first]){
	// 		cout<<" "<<it1;
	// 	}
	// }

	return en_str;
}

int main() 
{ 
	string en_str;
	string str = "this$is$the";
	cout<<"\n original str "<<str;
	en_str = encode(str);
	cout<<"\n encoded "<<en_str;
}
