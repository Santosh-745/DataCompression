#include<bits/stdc++.h>
using namespace std;


void encoder(string str, map<string, int> m, vector<int> &v){
    int ind, p1;
    string tmp_str;

    p1 = 0;
    ind = m.size() + 1;
    // cout<<"\n==> dictionary extendend for encoding...";
    while(p1 < str.length()){
        tmp_str = str[p1++];
        while(m.count(tmp_str)){
            tmp_str += str[p1++];
        }
        p1--;
        v.push_back(m[tmp_str.substr(0,tmp_str.length() - 1)]);
        m[tmp_str] = ind++;
        // cout<<"\n==> "<<m[tmp_str]<<" : "<<tmp_str;
    }
    // cout<<"\n";
    // for(auto &it: v)
    //     cout<<" "<<it;
       
}


string decoder(vector<int> v, vector<string> de_v){
    string str,tmp_str;
    int p1, tmp_p;

    p1 = 0;
    // cout<<"\n==> dictionary extendend for decoding...";
    for(auto &it: v){
        if(it < de_v.size()){
            str += de_v[it];
        }
        else{
            while(de_v.size() != it + 1){
                tmp_str = str[p1++];
                tmp_p = 0;
                while(count(de_v.begin(), de_v.end(), tmp_str) != 0){
                    if(p1 < str.length())
                        tmp_str += str[p1++];
                   else{
                        tmp_str += tmp_str[tmp_p++];
                        p1++;
                    }
                }
                p1--;
                de_v.push_back(tmp_str);
                // cout<<"\n==> "<<de_v.size()-1<<" : "<<de_v.back();
            }
            str += de_v[it];   
        }
    }
    return str;
}

int main(){
    string in_str, de_str, tmp_str;
    vector<int> en_v;
    vector<string> de_v;
    map<string, int> en_m;
    int ind, i;

    // variable initialization...
    in_str = "wabba$wabba$wabba$wabba$woo$woo";
    // in_str = "ratatatat";
    cout<<"\n==> Original String ==> "<<in_str;
    ind = 1;
    de_v.push_back("");

    // Preparing initial dictionary for encoding and decoding...
    // cout<<"\n==> Intial Dict for encoding...";
    for(auto &i: in_str){
        tmp_str = i;
        if(en_m.count(tmp_str) == 0){
            en_m[tmp_str] = ind++;
            de_v.push_back(tmp_str);
            // cout<<"\n==> "<<(ind - 1) << ": " << de_v.back();
        }
    }
    // for(auto &it: en_m)
    //     cout<<"\n"<<it.first<<" "<<it.second;
    
    // Encoding....
    encoder(in_str, en_m, en_v);
    cout<<"\n==> Encoded result ==> ";
    for(auto &it: en_v)
        cout<<" "<<it;

    // Decoding...
    // cout<<"\n\n==> Intial Dict for decoding...";
    // for(i = 1; i < de_v.size(); i++)
    //     cout<<"\n==> "<<i<<" : "<<de_v[i];
    de_str = decoder(en_v, de_v);
    cout<<"\n==> decoded string ==> "<<de_str;

    return 0;
}