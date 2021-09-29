#include<bits/stdc++.h>  
  
using namespace std;  
  
string encoding(string str, int n)  
{ 
    // here the n is unique characters in str....
    vector<int> cum_count; 
    string en_str;  
    bitset<8> bin_l, bin_u;      
    int i, b, pre_l, pre_u, l, u, scale3, x, total;  
   
    pre_l = 0;  
    pre_u = 255;  
    scale3 = 0;  
    
    for(i = 0; i < n; i++)
        cum_count.push_back(i);
    total = cum_count.back();
    // cout<<"\n total "<<total;  
    
    for(auto &ch : str){  
        x = (int)(ch - 96);  
        // cout<<"\n\n cum_x-1 "<<cum_count[x-1]
        //  <<" cum_x "<<cum_count[x]
        //  <<" total "<<total;
        l = pre_l + ( ((pre_u - pre_l + 1) * cum_count[x-1]) / total);  
        u = pre_l + ( ((pre_u - pre_l + 1) * cum_count[x]) / total) - 1;  
        
        for(i=x;i<n;i++){
            cum_count[i]++;
        }
        total++;
       // cout<<"\n total "<<total;    
        // cout<<"\n l "<<l<<" u "<<u;  
        bin_l = bitset<8>(l); 
        bin_u = bitset<8>(u); 
        // cout<<"\n binl "<<bin_l
        //  <<" binu "<<bin_u; 
         
        while(bin_l[7] == bin_u[7] || (bin_l[6] == 1 && bin_u[6] == 0) ){ 
           if(bin_l[7] == bin_u[7]){ 
                b = bin_u[7]; 
                en_str = en_str + to_string(b); 
                bin_l <<= 1; 
                bin_u <<= 1; 
                bin_u[0] = 1; 
                while(scale3 > 0){ 
                     en_str += (b==0)?"1":"0"; 
                     scale3--; 
                } 
                // cout<<"\n binl "<<bin_l
                //  <<" binu "<<bin_u; 
            } 
           if(bin_l[6] == 1 && bin_u[6] == 0){ 
                bin_l <<= 1; 
                bin_u <<= 1; 
                bin_u[0] = 1; 
                bin_u[7] = 1; 
                bin_l[7] = 0; 
                scale3++;
                 // cout<<"\n binl "<<bin_l
                 //  <<" binu "<<bin_u
                 //  <<" scale3 "<<scale3; 
            } 
        } 
        //break;  
        pre_l = bin_l.to_ulong(); 
        pre_u = bin_u.to_ulong(); 
        // cout<<"\n end l "<<pre_l
        //  <<" u "<<pre_u;
        // cout<<"\n binl "<<bin_l
         // <<" binu "<<bin_u; 
    }  
    
     
    en_str += to_string(bin_l[7]); 
    while(scale3 > 0){ 
        en_str += '1'; 
        scale3--;  
    } 
    for(i = 6; i >= 0; i--) 
        en_str += to_string(bin_l[i]); 
 
 
    return en_str;  
}  
  
string decoder(string en_str, int n){ 
    vector<int> cum_count; 
    string de_str; 
    bitset<8> bin_l, bin_u, bin_t;      
    int i, j, k, ind_t, pre_l, pre_u, l, u, t, total, temp;  
    char x; 
   
    pre_l = 0;  
    pre_u = 255;
    bin_t = bitset<8>(en_str.substr(0,8)); 
    ind_t = 8; 
    t = bin_t.to_ulong(); 
    //cout<<"\n bin_t "<<bin_t<<" t "<<t; 
 
    for(i = 0; i < 5; i++)
     cum_count.push_back(i);
    total = cum_count.back();
    
    for(i = 0; i < n; i++){  
 
        temp = ((t - pre_l + 1) * total - 1) / (pre_u - pre_l + 1); 
        // cout<<"\n\ntemp "<<temp;
        k = 0; 
        while(temp >= cum_count[k]) 
            k++; 
         
        x = (char)(k + 96);         
        de_str += x;  
        // cout<<"\n k "<<k<<" x "<<x; 
 
        l = pre_l + ( ((pre_u - pre_l + 1) * cum_count[k-1]) / total);  
        u = pre_l + ( ((pre_u - pre_l + 1) * cum_count[k]) / total) - 1;  
          
        // cout<<"\n l "<<l<<" u "<<u;  
        bin_l = bitset<8>(l); 
        bin_u = bitset<8>(u); 
        // cout<<"\n binl "<<bin_l<<" binu "<<bin_u <<" bint "<<bin_t;
   
     for(j=k;j<5;j++){
         cum_count[j]++;
        }
        total++;
   
        while(bin_l[7] == bin_u[7] || (bin_l[6] == 1 && bin_u[6] == 0) ){ 
           if(bin_l[7] == bin_u[7]){ 
                bin_l <<= 1;    // shift l to the left by 1 bit and shift 0 into LSB... 
                bin_u <<= 1;   // shift u to the left by 1 bit and shift 1 into LSB... 
                bin_u[0] = 1; 
                bin_t <<= 1;   // shift t to the left by 1 bit  
                // cout<<"\nind_t "<<ind_t<<" next bit "<<en_str[ind_t];
                bin_t[0] = (int)(en_str[ind_t++]-48);
                // and read next bit from received bitstream into LSB... 
                // cout<<"\n binl "<<bin_l<<" binu "<<bin_u<<" bint "<<bin_t;
            } 
           if(bin_l[6] == 1 && bin_u[6] == 0){ 
                bin_l <<= 1;    // shift l to the left by 1 bit and shift 0 into LSB... 
                bin_u <<= 1;   // shift u to the left by 1 bit and shift 1 into LSB... 
                bin_u[0] = 1; 
                
                bin_t <<= 1;   // shift t to the left by 1 bit  
                // cout<<"\nind_t "<<ind_t<<" next bit "<<en_str[ind_t];
                bin_t[0] = (int)(en_str[ind_t++] - 48);   // and read next bit from received bitstream into LSB... 
 
                bin_u[7] = 1;   // complement (new) MSB of l, u, and t... 
                bin_l[7] = 0; 
                bin_t[7] = (bin_t[7] == 0) ? 1 : 0; 
                // cout<<"\n binl "<<bin_l<<" binu "<<bin_u<<" bint "<<bin_t;
            
            } 
        }  
        // cout<<"\nend binl "<<bin_l<<" binu "<<bin_u<<" bint "<<bin_t;
        pre_l = bin_l.to_ulong();
        pre_u = bin_u.to_ulong(); 
        t = bin_t.to_ulong(); 
        // cout<<"\n prel "<<pre_l<<" preu "<<pre_u<<" t "<<t;   
 
      // break; 
    }    
 
    return de_str; 
} 
 
int main()  
{  
  
    string en_str, de_str;  
    string in_str;  
 
    in_str = "abdc";  

    cout<<"\n==> Original String "<<in_str;
    // we sended the 5 for indicating a to d...
    en_str = encoding(in_str, 5);  
    cout<<"\n==> encoded stream is ==> "<<en_str;  
  
    de_str = decoder(en_str, in_str.length()); 
    cout<<"\n==> decoded stream is ==> "<<de_str;   
 
    return 0;   
}

