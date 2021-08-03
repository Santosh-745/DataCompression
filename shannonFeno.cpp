#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

map<char, string> map_code;
map<string, char> map_decode;

int cmp(pair<char, int> a, pair<char, int> b){
    return (a.second > b.second);
}

void terminater(){}

void set_code(vector<pair<char, int>> &counter, int total)
{
    // testing ...
    // cout<<"Size "<<counter.size()<<" total "<< total <<endl;
    
    // for(auto &i : counter){
    //     cout<< i.first<<" "<<i.second<<"\n";
    // }
    // map<char,string> :: iterator iter1;
    // for(iter1=code.begin(); iter1 != code.end(); iter1++){
    //     cout<< (*iter1).first<<" "<<(*iter1).second<<"\n";
    // }

    if (counter.size() == 1){
        terminater();
    }
    else
    {
        int min_diff = 10000, s1, s2, t1, t2;
        char point;

        s1 = 0;
        s2 = total;
        
        vector<pair<char, int>>::iterator i;
        for (i = counter.begin(); i!=counter.end();i++)
        {
            s1 = s1 + (* i).second;
            s2 = s2 - (*i).second;
            // cout <<" s1 "<< s1 << " s2 "<<s2 <<" s1-s2 "<< s1 - s2 << endl;
            if (min_diff > (s1 - s2))
            {
                min_diff = s1 - s2;
                point = (* (++i)).first;
                t1 = s1;
                t2 = s2;
                i--;
            }
        }
        // cout << point << min_diff << endl;
        
        for (i = counter.begin(); (*i).first != point; i++)
        {
            char key = (* i).first;
            
            // cout<<"Key "<<key<<endl;
            map_code[key] = map_code[key] + '0';
        }
        vector<pair<char, int>>::iterator i_1;
        i_1 = i;
        while (i != counter.end())
        {
            char key = (* i).first;
            // cout<<"Key "<<key<<endl;
            map_code[key] = map_code[key] + '1';
            i++;
        }

        // cout<<(* i_1).first<<endl;
        vector<pair<char, int>> left(counter.begin(), i_1);
        vector<pair<char, int>> right(i_1, counter.end());
        
        // for(auto &i: left){
        //     cout<< "left "<<i.first<<" "<<i.second<<"\n";
        // }
        // for(auto &i: right){
        //     cout<< "right "<<i.first<<" "<<i.second<<"\n";
        // }
        
        set_code(left, t1);
        set_code(right, t2);
    }
}

int main(int argc, char const *argv[])
{

    // creat and write into file
    // ofstream myfile("file.txt");
    // myfile<< "Hello its Sam here...";
    // myfile.close();

    int total;
    string filename;
    string mytxt;
    string temp;
    
    filename = argv[1];
    ifstream myfile(filename);
    
    while (getline(myfile, temp))
    {
        mytxt = mytxt + temp;
    }
    cout << "\n==> Text ==> " <<mytxt;
    total = mytxt.length();
    cout << endl;
    myfile.close();

    map<char, int> counter;

    for (char i : mytxt)
    {
        counter[i]++;
    }

    vector<pair<char, int>> counter_v(counter.begin(), counter.end());
    sort(counter_v.begin(), counter_v.end(), cmp);

    // Checking count...
    // for (auto &i: counter_v)
    //     cout << i.first << " " << i.second << "\n";

    set_code(counter_v, total);

    cout<<"==> Codes\n";
    for (auto &i : map_code){
        map_decode[i.second] = i.first;
        cout << "==> "<<i.first << " " << i.second << "\n";
    }

    // cout<<"\ndecoded map \n";
    // for (auto &i: map_decode){
    //     cout << i.first << " " << i.second << "\n";
    // }

    // Encoding ...
    string encoded_code;
    string encoded_txt;

    for(char i: mytxt){
        encoded_code = encoded_code + map_code[i];
    }
    // cout<<"encoded_code_size "<<encoded_code.size()<<"\nencoded_code "<<encoded_code<<endl;

    int x = 7;
    int ascii = 0;
    for(char i: encoded_code){
        if(x < 0){
            //    cout<<"ascii "<<ascii<<endl;
            encoded_txt = encoded_txt + char(ascii);
            ascii = 0;
            x = 7; 
        }
        ascii = ascii + ((int)pow(2,x) * ((int)(i) - 48));
        // cout<<"ascii "<<ascii<<" pow "<<pow(2,x)<<" i "<<i<<endl;
        x--;
    }
    // for last ascii value ...
    encoded_txt = encoded_txt + char(ascii);
    // printig ...
    cout<<"\n==> encoded txt "<<encoded_txt<<endl;
    
    // creat and write into file
    ofstream myfile1("compressed.txt");
    myfile1<<encoded_txt;
    myfile1.close();
    cout<<"\n ==> compressed.txt is ready...";

    // Decoding...
    string decoded_code;
    string decoded_txt;
    string my_txt1;
    ifstream myfile2("compressed.txt");
    
    while (getline(myfile2, temp))
    {
        my_txt1 = my_txt1 + temp;
    }
    // cout << my_txt1;


    ascii = 0;
    
    for(char i: my_txt1){
        string tmp;
        tmp = bitset<8>(i).to_string();
        // cout<<"tmp "<<tmp<<'\n';
        decoded_code = decoded_code + tmp;
        // cout<<"decoded_code "<<decoded_code<<'\n';
    }
    // cout<<"\nencoded_code "<<encoded_code<<endl;
    // cout<<"\ndecoded_code "<<decoded_code<<endl;   

    string tmp;
    for(char i: decoded_code){
        tmp = tmp + i;
        if (map_decode.count(tmp)){
            decoded_txt = decoded_txt + map_decode[tmp];
            tmp.erase();
        }
    }
    cout<<"\n==> decoded txt ==> "<<decoded_txt<<"\n";
    
    // creat and write into file
    ofstream myfile3("decompressed.txt");
    myfile3<<decoded_txt;
    myfile3.close();
    cout<<"\n ==> decompressed.txt is ready...\n";

    return 0;
}