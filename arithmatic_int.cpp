#include<bits/stdc++.h> 
 
using namespace std; 
 
string encoding(string str, vector<int> cum_count) 
{
    // cout<<"\n in encoding "<<cum_count[0]; 
    string en_str; 
    bitset<8> bin_l, bin_u;     
    int i, b, pre_l, pre_u, l, u, scale3, x, total; 
    pre_l = 0; 
    pre_u = 255; 
    scale3 = 0; 
    total = cum_count.back(); 
    // cout<<"\n total "<<total; 
 
    for(auto &ch : str){ 
        x = (int)(ch - 96); 
        l = pre_l + ( ((pre_u - pre_l + 1) * cum_count[x-1]) / total); 
        u = pre_l + ( ((pre_u - pre_l + 1) * cum_count[x]) / total) - 1; 
         
        // cout<<"\n\n==> l "<<l<<" u "<<u; 
        bin_l = bitset<8>(l);
        bin_u = bitset<8>(u);
        // cout<<"\n==> binl "<<bin_l<<" binu "<<bin_u;
        
        while(bin_l[7] == bin_u[7] || (bin_l[6] == 1 && bin_u[6] == 0) ){
           if(bin_l[7] == bin_u[7]){
                b = bin_u[7];
                en_str = en_str + to_string(b);
                bin_l <<= 1;     // shift l to the left by 1 bit and shift 0 into LSB...
                bin_u <<= 1;       // shift u to the left by 1 bit and shift 1 into LSB...
                bin_u[0] = 1;       
                while(scale3 > 0){
                     en_str += (b==0)?"1":"0";
                     scale3--;
                }
            // cout<<"\n==> binl "<<bin_l<<" binu "<<bin_u;
            }
           if(bin_l[6] == 1 && bin_u[6] == 0){
                bin_l <<= 1;      // shift l to the left by 1 bit and shift 0 into LSB...
                bin_u <<= 1;     // shift u to the left by 1 bit and shift 1 into LSB...
                bin_u[0] = 1;
                bin_u[7] = 1;     // Complementing the msb's of L and U...
                bin_l[7] = 0;
                scale3++;
                // cout<<"\n==> binl "<<bin_l<<" binu "<<bin_u;
            }
        }
        //break; 
        pre_l = bin_l.to_ulong();
        pre_u = bin_u.to_ulong();
        // cout<<"\nend prel "<<pre_l<<" preu "<<pre_u;
    } 
    // cout<<"\n binu at end "<<bin_u;
    
    en_str += to_string(bin_l[7]);
    while(scale3 > 0){
        en_str += '1';
        scale3--; 
    }
    for(i = 6; i >= 0; i--)
        en_str += to_string(bin_l[i]);


    return en_str; 
} 
 
string decoder(string en_str, vector<int> cum_count, int n){

    string de_str;
    bitset<8> bin_l, bin_u, bin_t;     
    int i, k, ind_t, pre_l, pre_u, l, u, t, scale3, total, temp; 
    char x;
    
    pre_l = 0; 
    pre_u = 255; 
    scale3 = 0; 
    total = cum_count.back(); 
    bin_t = bitset<8>(en_str.substr(0,8));
    ind_t = 8; // index for nexxt char from en_stream...
    t = bin_t.to_ulong();

    for(i = 0; i < n; i++){ 


        temp = ((t - pre_l + 1) * total - 1) / (pre_u - pre_l + 1);
        k = 0;
        while(temp >= cum_count[k])
            k++;
        // Decoding charachter...
        x = (char)(k + 96);        
        de_str += x; 
        // cout<<"\n k "<<k<<" x "<<x;

        l = pre_l + ( ((pre_u - pre_l + 1) * cum_count[k-1]) / total); 
        u = pre_l + ( ((pre_u - pre_l + 1) * cum_count[k]) / total) - 1; 
         
        // cout<<"\n\n l "<<l<<" u "<<u; 
        bin_l = bitset<8>(l);
        bin_u = bitset<8>(u);
        // cout<<"\nbinl "<<bin_l<<" binu "<<bin_u<<" bint "<<bin_t;

        while(bin_l[7] == bin_u[7] || (bin_l[6] == 1 && bin_u[6] == 0) ){
           if(bin_l[7] == bin_u[7]){
                bin_l <<= 1;    // shift l to the left by 1 bit and shift 0 into LSB...
                bin_u <<= 1;   // shift u to the left by 1 bit and shift 1 into LSB...
                bin_u[0] = 1;
                bin_t <<= 1;   // shift t to the left by 1 bit 
                bin_t[0] = (int)(en_str[ind_t++]-48);   // and read next bit from received bitstream into LSB...
                // cout<<"\nbinl "<<bin_l<<" binu "<<bin_u<<" bint "<<bin_t;
            }
           if(bin_l[6] == 1 && bin_u[6] == 0){
                bin_l <<= 1;    // shift l to the left by 1 bit and shift 0 into LSB...
                bin_u <<= 1;   // shift u to the left by 1 bit and shift 1 into LSB...
                bin_u[0] = 1;
                bin_t <<= 1;   // shift t to the left by 1 bit 
                bin_t[0] = (int)(en_str[ind_t++]-48);   // and read next bit from received bitstream into LSB...

                bin_u[7] = 1;   // complement (new) MSB of l, u, and t...
                bin_l[7] = 0;
                bin_t[7] = (bin_t[7] == 0) ? 1 : 0;
                // cout<<"\nbinl "<<bin_l<<" binu "<<bin_u<<" bint "<<bin_t;
            }
        }
        //break; 
        pre_l = bin_l.to_ulong();
        pre_u = bin_u.to_ulong();
        t = bin_t.to_ulong();
        // cout<<"\nend binl "<<bin_l<<" binu "<<bin_u<<" bint "<<bin_t;
        // cout<<"\n prel "<<pre_l<<" preu "<<pre_u<<" t "<<t;   

        // break;
    }   

    return de_str;
}

int main() 
{ 
 
    string en_str, de_str; 
    string in_str; 
    // vector<int> count{0,40,1,9,10,32,43,12,30,65,44,11}; 
    vector<int> count{0,40,1,9,10}; 
    vector<int> cum_count;

    // Calculating Cumulative Count....
    cum_count.push_back(0);
    for(int  i = 1; i < count.size(); i++){
       cum_count.push_back(cum_count[i-1] + count[i]);
        // cout<<"\n "<<cum_count[i];
    }

    in_str = "abdcdc"; 
    
    cout<<"\n==> Original string = "<<in_str;
    // Encoding....
    en_str = encoding(in_str, cum_count); 
    cout<<"\n==> encoded stream is ==> "<<en_str; 
 
    // Decoding....
    de_str = decoder(en_str, cum_count, in_str.length());
    cout<<"\n==> decoded stream is ==> "<<de_str; 

   /*bitset<4> b("1010");
    int x = b[1];
    cout<<x;*/

    return 0;  
}