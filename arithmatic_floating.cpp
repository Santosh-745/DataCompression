#include<iostream>
#include<bits/stdc++.h>
using namespace std;

float generate_tag (string str, vector<float> prob, vector<float> fx){
    float tag = 0.0, temp = 0.0, l, u, pre_l = 0.0, pre_u = 1.0;
    int i;

    for(auto &it: str){        
        i = (int)(it - 96);
        cout<<"\n==> l "<<pre_l<<" || u "<<pre_u; 
        l = pre_l + (pre_u - pre_l) * fx[i-1];
        u = pre_l + (pre_u - pre_l) * fx[i];
        pre_l = l;
        pre_u = u;
    }
    tag = (l + u) / 2;

    return tag;

}

string decipher(float tag, int n, vector<float> prob, vector<float> fx){

    // cout<<" test tag"<<tag;
    int i, xn;
    string ans;
    float l, u, pre_l = 0.0, pre_u = 1.0;
    for(i = 0; i < n; i++){
        // cout<<"\n==> i "<<i;
        for(xn = 1; xn < 5; xn++){
            cout<<"\n==> l "<<pre_l<<" || u "<<pre_u<<" || tag "<< tag; 
            l = pre_l + (pre_u - pre_l) * fx[xn-1];
            u = pre_l + (pre_u - pre_l) * fx[xn];
            if(tag > l && tag < u){
                pre_l = l;
                pre_u = u;
                ans = ans + (char)(xn + 96);
                break;
            }
        }
        cout<<"\n==> Decoded Char "<< (char)(xn + 96);;
    }

    // cout<<" test ans "<<ans ;
    return ans;

}

int main(){

    string str = "acba";
    string de_str;
    float tag = 0.0, temp = 0.0, l, u, pre_l = 0.0, pre_u = 1.0;
    int i, n;
    // vector<float> prob (27, 0);
    // vector<float> fx(27);
    vector<float> prob (5, 0); // use 27 for all alphabets
    vector<float> fx(5);

    fx[0] = 0.0;
    prob[0] = 0.0;
    n = str.length();
    // cout<<"\n n "<<n;
    for(auto &it: str){
        // cout<<" "<<it<<" ";
        i = (int)(it - 96);
        // cout<<" "<<i;
        if(prob[i] == 0.0){   
            prob[i] = ((float)count(str.begin(), str.end(), it) / str.length());
        }
        // cout<<" p "<<prob[i]<<"\n";
    }
    for (i = 1; i < prob.size(); i++)
        fx[i] = fx[i-1] + prob[i];

    // Encoding...
    tag = generate_tag(str, prob, fx);
    cout<<"\n ==> Tag for the string is "<< tag<< "\n";

    // Decoding...
    de_str = decipher(tag, n, prob, fx);
    cout<<"\n ==> Deciphered String is "<< de_str<<"\n";

    return 0; 
}