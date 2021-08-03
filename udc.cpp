#include <iostream>
#include <string>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

bool isPrefix(string full, string substr){
    return substr == full.substr(0,substr.size());
}

int main(){
    
    int n,i,flag = 0;
    string key;
    string value;
    string s1;
    string s2;
    string ds; // dangling suffix
    map <string, string> codes;

    // codes.insert({"0","a"});
    // codes.insert({"10","b"});
    // codes.insert({"110","c"});
    // codes.insert({"101","d"});

    // taking inputs...
    cout<<"\n==> No. of codewords Codewords ==> ";
    cin>>n;

    for(i = 0; i < n;i++){
    //    cout<<"==> Enter the charachter "<<i+1<<"==> ";
    //    cin>>value;
       cout<<"==> Enter the codeword "<<i+1<<"==> ";
       cin>>key;
       codes.insert({key, value});
    }

    // for(auto &it : codes){
    //     cout<<"\n==> codes "<<it.second<<" "<<it.first;
    // }
    cout<<"\n";

    for(auto &it: codes){
        for(auto &it1: codes){
            if(it1.first != it.first){
                if(isPrefix(it.first, it1.first)){
                    s1 = it.first;
                    s2 = it1.first;
                    ds = s1.substr(s2.size(),s1.size());
                    if(codes.count(ds)){
                        flag = 1;
                        cout<<"==> This code is not Uniquely decodable...";
                        break;
                    }
                }
            }
        }
        if(flag == 1) break;
    }
    if(flag == 0)
        cout<<"==> This code is Uniquely Decodable...\n";

}