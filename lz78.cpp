#include<bits/stdc++.h>
using namespace std;

void encoder(string str, vector<vector<int>> &v){
    map<string, int> m; 
    int p1, ind;
    string tmp_str;
    vector<int> tmp_v;

    tmp_v.push_back(0);
    tmp_v.push_back(str[0]);
    v.push_back(tmp_v);
    tmp_v.clear();
    tmp_str = str[0];
    m[tmp_str] = 1;

    p1 = 1;
    ind = 2;
    while(p1 < str.length()){
        tmp_str = str[p1++];
        while(m.count(tmp_str)){
            tmp_str += str[p1++];
        }
        
        if(tmp_str.length() == 1)
            tmp_v.push_back(0);
        else{
            tmp_v.push_back(m[tmp_str.substr(0,tmp_str.length()-1)]);
        }
        tmp_v.push_back(tmp_str.back());
        v.push_back(tmp_v);
        tmp_v.clear();

        m[tmp_str] = ind++;
        //cout<<"\n "<<v.back()[0]<<" "<<(char)v.back()[1]<<" "<<m[tmp_str];
    }
    // for(auto &it: v){
    //     cout<<"\n "<<it[0]<<" "<<(char)it[1];
    // }
}

string decoder(vector<vector<int>> v){
    vector<string> m;
    string str,tmp_str;

    m.push_back("");
    for(auto &it: v){
        if(it[0] == 0){
            tmp_str = (char)it[1];
            m.push_back(tmp_str);
            str += (char)it[1];
        }
        else{
            tmp_str = m[it[0]] + (char)it[1];
            str += tmp_str;
            m.push_back(tmp_str);
        }
    }
    return str;
}

int main(){
    string in_str, de_str;
    vector<vector<int>> en_v;

    // in_str = "abcdabcabcdaabcabce";
    in_str = "this_is_lz78....";
    cout<<"\n==> Original String ==> "<<in_str;
    //in_str = "abcdabca";
    encoder(in_str, en_v);
    cout<<"\n==>";
    for(auto &it: en_v)
        cout<<" ["<<it[0]<<" "<<(char)it[1]<<"],";

    de_str = decoder(en_v);
    cout<<"\n==> decoded string ==> "<<de_str;

    return 0;
}