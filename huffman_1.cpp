#include <bits/stdc++.h>

using namespace std;

map<char, string> map_code;
map<string, char> map_decode;


class node{
    public: 
        float freq;
        char symbol;
        string code = "";
        node* left;
        node* right;
};

node* newnode(char symbol, float f, node* l, node* r){
    node *n =  new node();
    n->symbol = symbol;
    n->freq = f;
    n->left = l;
    n->right = r;
    n->code = "";
    return n; 
}

int cmp(node* l, node* r){
    return (l->freq < r->freq);
}

void prepare_tree(vector<node*> &huffman_tree,  map<char, float> &freq, int n){
    
    int i,j; 
    
    node* tmp = NULL; 
    node* tmp1 = NULL; 
    node* tmp2 = NULL; 
    node* tmp3 = NULL; 
    

    for(auto &it: freq){
        tmp = newnode(it.first, it.second, NULL, NULL);
        huffman_tree.push_back(tmp);
    }       

    sort(huffman_tree.begin(), huffman_tree.end(), cmp);

    // Checking sorted or not
    // for(auto &it : huffman_tree ){
    //     cout<<"\n==> "<<it->symbol<<" ==> "<<it->freq;
    // }
    // cout<<"\n";

    while(huffman_tree.size() != 1){
        
        // tsting ....
        // for(i = 0; i < huffman_tree.size(); i++){
        //     cout<<" "<<huffman_tree[i]->freq; 
        // }
        // cout<<"\n";
        tmp1 = huffman_tree[0];
        huffman_tree.erase(huffman_tree.begin());

        tmp2 = huffman_tree[0];
        huffman_tree.erase(huffman_tree.begin());

        tmp3 = newnode('#', tmp1->freq+tmp2->freq, tmp1, tmp2);

        for(j = huffman_tree.size() - 1; j >= 0; j--){
            if(huffman_tree[j]->freq <= tmp3->freq){
                break;
            }
        }

        if(j < huffman_tree.size() - 1)
            huffman_tree.insert(huffman_tree.begin() + j + 1, tmp3);
        else if(j == huffman_tree.size() - 1)
            huffman_tree.push_back(tmp3);

        //testing...    
        // for(int i = 0; i < huffman_tree.size(); i++){
        //     cout<<" "<<huffman_tree[i]->freq; 
        // }
        // cout<<"\n\n";
    }

    // tmp3 = huffman_tree[0];
    // cout<<"\n"<<tmp3->freq<<" "<<tmp3->symbol<<"\n";

}

void set_codes(node* root){
    if(root->left){
        root->left->code = root->code + '0';
        set_codes(root->left);
    }
    if(root->right){
        root->right->code = root->code + '1';
        set_codes(root->right);
    }
    else if(!root->left && !root->right){
        // cout<<"\n==> "<<root->symbol<<" "<<root->code;
        map_code[root->symbol] = root->code;
        map_decode[root->code] = root->symbol;
    }
}

string codeToStr(string str){

    string encoded_txt;
        
    int x = 7;
    int ascii = 0;
    for(char i: str){
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
    cout<<"\n==> encoded txt ==> "<<encoded_txt<<endl;
    
    return encoded_txt;

}

void encode(string mytxt){
    
    // Encoding ...
    string encoded_code;
    string encoded_txt;

    for(char i: mytxt)
        encoded_code = encoded_code + map_code[i];
    
    // cout<<"\n==> encoded_code_size "<<encoded_code.size()<<"\n==> encoded_code "<<encoded_code<<endl;
    encoded_txt = codeToStr(encoded_code);

    // creat and write into file
    ofstream myfile1("compressed.txt");
    myfile1<<encoded_txt;
    myfile1.close();
    // cout<<"\n ==> compressed.txt is ready...";

}

void decode(){
    // Decoding...
    string decoded_code;
    string decoded_txt;
    string my_txt1;
    string temp;

    ifstream myfile2("compressed.txt");
    
    while (getline(myfile2, temp))
        my_txt1 = my_txt1 + temp;

    // cout << my_txt1;
    
    int ascii = 0;
    
    for(char i: my_txt1){
        string tmp;
        tmp = bitset<8>(i).to_string();
        // cout<<"tmp "<<tmp<<'\n';
        decoded_code = decoded_code + tmp;
        // cout<<"decoded_code "<<decoded_code<<'\n';
    }
    // cout<<"\n==> decoded_code "<<decoded_code<<endl;   

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
    // cout<<"\n ==> decompressed.txt is ready...\n";

}

int main()
{
    // node *tmp = newnode('a',10, NULL, NULL);

    // int n = 4;
    // char smbl[] = "abcd";
    // float freq[] = {0.30, 0.3, 0.25, 0.15};

    string mytxt;
    string temp;
    map<char, float> freq;
    vector<node*> huffman_tree;

    string filename = "file.txt";
    ifstream myfile(filename);
    
    while (getline(myfile, temp))
        mytxt = mytxt + temp;
    myfile.close();
    cout << "\n==> Text ==> " <<mytxt;

    for (char i : mytxt)
        freq[i]++;

    int total = mytxt.length();
    for(auto &it : freq){
        it.second = it.second / total; 
    }

   prepare_tree(huffman_tree, freq, freq.size());

    // while(!huffman_tree.empty()){
    //     cout<<" "<<huffman_tree.top()->symbol<<" "<<huffman_tree.top()->freq<<"\n";
    //     huffman_tree.pop();
    // }

    // cout<<"\n\n==> codes ";
    set_codes(huffman_tree[0]);
    cout<<"\n";
    // cout<<tmp->symbol<<" "<<tmp->freq;

    encode(mytxt);
    decode();
}