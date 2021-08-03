#include<iostream>
#include<cstring>
#include <bits/stdc++.h>

using namespace std;

void terminater(){ cout << "finish..."; }

void fun(int i){
    
    if(i<0)
        terminater();
        else{
            cout<<i<<endl;
    fun(--i);
        }
}

bool cmp(pair<int, int> a, pair<int,int> b){
    return (a.second < b.second);
}


bool isPrefix(string full, string substr){
    return substr == full.substr(0,substr.size());
}

// int main(){

//     // string str;
//     // string s1; 
//     // string s2;
//     // s1 = "abcdef";
//     // s2 = "ab"; 
//     // cout<<" "<<(s1!=s2)<<"\n";
//     // str = s1.substr(s2.size(),s1.size());
//     // cout<<isPrefix("abc","a");
//     // cout<<" \n ==> "<<(str)<<"\n";

//     vector<string> v;
//     v.push_back("a");
//     v.push_back("b");
//     v.push_back("c");
//     v.push_back("d");

//     cout<<"\n "<<v.find("a");


//     // map<int, int> m1;
    
//     // m1[1] = 3;
//     // m1[2] = 2;
//     // m1[3] = 1;
//     // map<int,int> :: iterator iter;
//     // // iter = m1.begin();
//     // // iter++;
//     // // map <int , int> m2 (m1.begin(),iter);
    
//     // vector< pair<int, int> > v(m1.begin(), m1.end());
//     // sort(v.begin(),v.end(),cmp);

//     // for(auto &i : v){
//     //     cout<< i.first<<" "<<i.second<<"\n";
//     // }

//     // map <int , int> m3 (v.begin(),v.end());

//     // for(iter=m3.begin(); iter != m3.end(); iter++){
//     //     cout<< (*iter).first<<" "<<(*iter).second<<"\n";
//     // }
//     // iter = m1.begin();
//     // iter += 1;
//     // cout<<(* iter).first<<endl;
//     // return 0;
 
//     // int a = 3;
//     // a++;
//     // cout<<a<<endl;
    
//     // string s = "heeloo";
//     // cout<<s.length()<<endl;
//     // cout<<char(216)<<'\n';
//     // cout<<int('╪' % 2)<<'\n';
//     // cout<<int('a' % 2)<<'\n';
// }

// int main(int argc, char const *argv[])
// {
//     string decoded_txt;
//     decoded_txt = "Tjis is a example ....";
//     ofstream myfile("decompressed.txt");
//     myfile<<decoded_txt;
//     myfile.close();
//     cout<<"\n ==> decompressed.txt is ready...\n";

// }

void fun(char a[]){
    cout<<a[0]<<"\n";    
}

string asc_char(string str)
{
    string buf;
    stringstream ss(str);

    string ascii_string = "";
    while (ss >> buf)
    {
        while (buf.size() != 8)
        {
            buf += '0';
        }
        bitset<8> bits(buf);
        char c = char(bits.to_ulong());
        int c1 = bits.to_ulong();
        cout<<" c1 "<<c1<<"\n";
        ascii_string += c;
    }

    return ascii_string;
}

int main(){

    cout<<asc_char("100")<<endl;
    // cout<<(char)65<<endl;
    // cout<<(asc_char("00000000") + (char)64);
}

