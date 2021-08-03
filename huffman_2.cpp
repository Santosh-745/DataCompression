#include <bits/stdc++.h>

using namespace std;

class node
{
public:
    string data;
    int count;
    node *left;
    node *right;
};

node *newnode(string s, int x, node *l, node *r)
{
    node *n = new node();
    n->data = s;
    n->count = x;
    n->left = l;
    n->right = r;
    return n;
}

node *nyt = newnode("nyt", 0, NULL, NULL);
map<string, string> m_code;
map<char, int> visited;

void update_count(node *root, string code)
{
    if (code == "")
        root->count += 1;
    else
    {
        node *tmp = root;
        for (auto &i : code)
        {
            tmp->count += 1;
            if (i == '0')
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }
        tmp->count += 1;
    }
}

void update_code(int poz)
{
    //cout<<"\n poz1 "<<poz;
    for (auto &it : m_code)
    {
        if (it.second[poz] == '1')
            it.second[poz] = '0';
        else
            it.second[poz] = '1';
    }
}

void terminater() {}
void check_tree(node *root, int poz)
{
    if (!root->left)
        terminater();
    else
    {
        //cout<<"\n poz "<<" "<<poz<<" "<<root->left->data<<" "<<root->left->count<<" "<<root->right->data<<" "<<root->right->count;
        if (root->left->count > root->right->count)
        {
            node *tmp = root->left;
            root->left = root->right;
            root->right = tmp;
            update_code(poz);
        }
        check_tree(root->left, poz + 1);
        check_tree(root->right, poz + 1);
    }
}

node *update_tree(node *root, char i, int isNew)
{
    //cout<<"\n i "<<i;
    string tmp;
    tmp = i;
    // cout<<"\n tmp "<<tmp;
    // cout<<"\n nyt "<<nyt->data;
    if (!isNew)
    {
        //cout<<"\nhello from if" ;
        update_count(root, m_code[tmp]);
    }
    else
    {
        // cout<<"\nhello from else" ;
        node *tmp1 = newnode("nyt", 0, NULL, NULL);
        node *tmp2 = newnode(tmp, 1, NULL, NULL);
        nyt->data = "*";
        nyt->left = tmp1;
        nyt->right = tmp2;
        update_count(root, m_code["nyt"]);
        nyt = nyt->left;
        //cout<<"\nelse "<<root->left->count;
        m_code[tmp] = m_code["nyt"] + "1";
        m_code["nyt"] += "0";
        //  cout<<"\ntest code tmp "<<m_code[tmp];
    }
    check_tree(root, 0);
    return root;
}

string encode(string s)
{
    node *root;
    root = nyt;
    m_code["nyt"] = "";

    // cout<<nyt->data;
    int e = 4, r = 10, k;
    string ans;
    string tmp;
    // int c = 0;
    for (auto &i : s)
    {
        tmp = i;
        //cout<<"\n c "<<c;
        if (visited[i] == 1)
        {
            //cout<<"\nhello from if";
            //cout<<"\ntesting "<<m_code[tmp];
            ans = ans + m_code[tmp];
            root = update_tree(root, i, 0);
            //cout<<"\n testing encode"<<root->right->data;
        }
        else
        {
            visited[i] = 1;
            k = i - 96;
            // cout<<"\n hello from else "<<i<<" k "<<k;
            if (k <= 2 * r)
            {

                //cout<<"\ntesting k<2r "<<m_code["nyt"]<<" "<<bitset<5>(k-1).to_string();
                ans = ans + m_code["nyt"] + bitset<5>(k - 1).to_string();
            }
            else
            {
                // cout<<"\ntesting "<<m_code["nyt"] + bitset<4>(k-r-1).to_string();
                ans = ans + m_code["nyt"] + bitset<4>(k - r - 1).to_string();
            }
            root = update_tree(root, i, 1);
        }
    }
    return ans;
}

string decode(string en_s)
{
    // cout << "\n"
    //      << "decode " << en_s;
    node *root;
    node *tmp_node;
    root = nyt;
    m_code.clear();
    // cout<<"\n test aize "<<m_code.size();
    m_code["nyt"] = "";

    //cout<<"\n"<<nyt->count;
    int e = 4, r = 10, k;
    char ch;
    string ans = "";
    string tmp;

    tmp_node = root;
    int i = 0;
    while (i < en_s.size())
    {
        // cout << "\n i " << i;
        if (tmp_node == nyt)
        {
            tmp = en_s.substr(i, i + e);
            bitset<4> bits(tmp);
            // cout<<"\n tmp "<<tmp;
            // int c1 = bits.to_ulong(); 
            // cout<<"\n c1 "<<c1<<"\n";

            if (bits.to_ulong() <= r)
            {
                tmp = en_s.substr(i, i + e + 1);
                //cout<<"\n tmp "<<tmp;
                //cout<<"\n ch "<<ch;
                bitset<5> bits(tmp);
                ch = char(bits.to_ulong() + 1 + 96);
                ans = ans + ch;
                i = i + e + 1;
            }
            else
            {
                // cout<<"\nelse parrt";
                ch = char(bits.to_ulong() + r + 1 + 96);
                ans = ans + ch;
                i += e;
            }
            if(i >= en_s.size())
                break;
            root = update_tree(root, ch, 1);
            tmp_node = root;
            //cout<<"\n test "<<root->right->data;
        }
        if (en_s[i] == '0')
            tmp_node = tmp_node->left;
        else
            tmp_node = tmp_node->right;
        i++;
        // cout << "\ncheck befor " << tmp_node->data;
        if (tmp_node != NULL && tmp_node->data != "nyt" && tmp_node->data != "*")
        {
            // cout << "\n visited ";
            ans = ans + tmp_node->data;
            // cout << tmp_node->data;
            ch = tmp_node->data[0];
            root = update_tree(root, ch, 0);
            tmp_node = root;
            // cout << "\ntest1 " << root->left->data;
            // cout<<" "<<i;
        }
        //break;
    }

    //cout<<"\n "<<ans;
    return ans;
}

int main()
{
    string s;
    string en_s;
    string de_s;

    s = "hellobhai"; 
 
    en_s = encode(s); 
    // cout<<"\n root "<<root->count<<"\n"; 
    //cout<<root->left->count; 
    /*for(auto &it : m_code) 
         cout<<it.first<<" "<<it.second<<"\n";*/
    cout<<en_s<<endl;

    de_s = decode(en_s);
    cout << "\n"
         << de_s
         << "\n";

    return 0;
}

 // 0  1  2  3  4  5  6  7  8  9  10  11 
//  0  0  0  0  0  1  0  1  0  0  0   1
//                    |
