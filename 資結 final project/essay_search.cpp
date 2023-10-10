#define FILE_EXTENSION ".txt"
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <locale.h>
#include <set>
#include <time.h>

using namespace std;

// string parser : output vector of strings (words) after parsing
vector<string> word_parse(vector<string> tmp_string){
	vector<string> parse_string;
	for(auto& word : tmp_string){
		string new_str;
    	for(auto &ch : word){
			if(isalpha(ch))
            {
                if(isupper(ch))
                    new_str.push_back(ch + 32);
                else
                    new_str.push_back(ch);
            }
		}
		parse_string.emplace_back(new_str);
	}
	return parse_string;
}

vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if("" == str) return res;
	//先將要切割的字串從string型別轉換為char*型別
	char * strs = new char[str.length() + 1] ; //不要忘了
	strcpy(strs, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while(p) {
		string s = p; //分割得到的字串轉換為string型別
		res.emplace_back(s); //存入結果陣列
		p = strtok(NULL, d);
	}

	return res;
}

class trie {
public:
    class node {
    public:
        node();
        node(int);
        ~node();
        int depth;
        bool is_word;
        unordered_map<char, node*> child;
    };

    trie();
    void insert(std::string);
    bool search(std::string);
    bool search_prefix(std::string);
    void remove(std::string);
    void remove_start_with(std::string);
    vector<std::string> list_start_with(std::string);
    vector<std::string> list_all();
    int max_depth();
    int word_number();

private:
    void push_word_recursive(node*, string, vector<string>*);
    void max_depth_recursive(node*, int*);
    void word_num_recursve(node*, int*);
    node* root;
};

trie::node::node() {
    depth = 0;
    is_word = false;
    child = unordered_map<char, node*>();
}

trie::node::node(int depth): depth(depth) {
    is_word = false;
    child = unordered_map<char, node*>();
}

trie::node::~node() {
    for (std::pair<char, node*> pair : child) {
        delete pair.second;
    }
}

trie::trie() {
    root = new node();
}

void trie::insert(string word) {
    node* n = root;
    for (char c : word) {
        if (n->child.find(c) == n->child.end()) {
            n->child[c] = new node(n->depth + 1);
        }
        n = n->child[c];
    }
    n->is_word = true;
}

bool trie::search(string word) {
    node* n = root;
    for (char c : word) {
        if (n->child.find(c) == n->child.end()) {
            return false;
        }
        n = n->child[c];
    }
    return n->is_word;
}

bool trie::search_prefix(string word) {
    node* n = root;
    for (char c : word) {
        if (n->child.find(c) == n->child.end()) {
            return false;
        }
        n = n->child[c];
    }
    return 1;
}

void trie::remove(string word) {
    node* n = root;
    for (char c : word) {
        if (n->child.find(c) == n->child.end()) {
            return;
        }
        n = n->child[c];
    }
    n->is_word = false;
}

void trie::remove_start_with(string word) {
    node* n = root;
    for (char c : word) {
        if (n->child.find(c) == n->child.end()) {
            return;
        }
        n = n->child[c];
    }
    for (std::pair<char, node*> pair : n->child) {
        delete pair.second;
    }
    n->child = unordered_map<char, node*>();
    n->is_word = false;
}

void trie::push_word_recursive(node* n, std::string word, std::vector<std::string>* list) {
    if (n->is_word) {
        list->push_back(word);
    }
    for (std::pair<char, node*> pair : n->child) {
        push_word_recursive(pair.second, word + pair.first, list);
    }
}

vector<string> trie::list_start_with(string word) {
    node* n = root;
    vector<string> list;
    for (char c : word) {
        if (n->child.find(c) == n->child.end()) {
            return list;
        }
        n = n->child[c];
    }

    push_word_recursive(n, word, &list);
    return list;
}

vector<string> trie::list_all() {
    vector<string> list;
    push_word_recursive(root, "", &list);
    return list;
}

void trie::max_depth_recursive(node* n, int* max) {
    if (n->is_word && n->depth > *max) {
        *max = n->depth;
    }
    for (std::pair<char, node*> pair : n->child) {
        max_depth_recursive(pair.second, max);
    }
}

int trie::max_depth() {
    int max = 0;
    max_depth_recursive(root, &max);
    return max;
}

void trie::word_num_recursve(node* n, int* num) {
    if (n->is_word) {
        *num = *num + 1;
    }
    for (std::pair<char, node*> pair : n->child) {
        word_num_recursve(pair.second, num);
    }
}

int trie::word_number() {
    int num = 0;
    word_num_recursve(root, &num);
    return num;
}

int main(int argc, char *argv[])
{
    clock_t start, end_time;
    start = clock();

    // INPUT :
	// 1. data directory in data folder
	// 2. number of txt files
	// 3. output route

    string data_dir = argv[1] + string("/");
	string query = string(argv[2]);
	string output = string(argv[3]);

	// Read File & Parser Example


	trie t[10000];
	trie t_reverse[10000];
	vector<string> directory(10000);

    int how_many_txt = 0;
    string file, title_name, tmp;
    fstream fi;
    ofstream fout;
    char buf[128], buffer[128];
    for(int i = 0; i < data_dir.size(); i++)
        buffer[i] = data_dir[i];
    sprintf(buf, "%s%d.txt", buffer, how_many_txt);
    fi.open(buf, ios::in);
	while(fi.is_open())
    {

        vector<string> tmp_string;

        // GET TITLENAME
        getline(fi, title_name);
        directory[how_many_txt] = title_name;

        // GET TITLENAME WORD ARRAY
        tmp_string = split(title_name, " ");

        vector<string> title = word_parse(tmp_string);
        for(auto &word : title){
            t[how_many_txt].insert(word);

            reverse(word.begin(), word.end());
            t_reverse[how_many_txt].insert(word);
        }

        // GET CONTENT LINE BY LINE
        while(getline(fi, tmp)){

            // GET CONTENT WORD VECTOR
            tmp_string = split(tmp, " ");

            // PARSE CONTENT
            vector<string> content = word_parse(tmp_string);

            for(auto &word : content){
                t[how_many_txt].insert(word);

                reverse(word.begin(), word.end());
                t_reverse[how_many_txt].insert(word);
            }
        }

        // CLOSE FILE
        fi.close();

        how_many_txt++;
        sprintf(buf, "%s%d.txt", buffer, how_many_txt);
        fi.open(buf, ios::in);
    }
    //cout << how_many_txt << endl;


    string whole_line;

    fi.open(query, ios::in);
    fout.open(output, ios::out);
    while(getline(fi, whole_line))
    {
        //cout << endl << whole_line << endl;

        int now_pos = 0;
        int len = whole_line.size();
        int and_or_mode = 0; // 0是無, 1是且, 2是或
        bool total_result[10000] = {0};

        while(now_pos < len)
        {
            // 且
            if(whole_line[now_pos] == '+')
            {
                now_pos += 2;
                and_or_mode = 1;
            }

            // 或
            else if(whole_line[now_pos] == '/')
            {
                now_pos += 2;
                and_or_mode = 2;
            }

            // 完整搜尋
            else if(whole_line[now_pos] == '"')
            {
                int right_boundry;
                for(right_boundry = now_pos + 1; right_boundry < len; right_boundry++)
                    if(whole_line[right_boundry] == '"')
                        break;

                string test;
                test = whole_line.substr(now_pos + 1, right_boundry - now_pos - 1);
                //fout << "-> " << test << endl;

                now_pos = right_boundry + 2;



                transform(test.begin(), test.end(), test.begin(), ::tolower);

                bool result[10000] = {0};
                for(int i = 0; i < how_many_txt; i++)
                {
                    if(t[i].search(test))
                    {
                        result[i] = 1;
                        //cout << i << endl;
                    }

                }

                // 進行合併
                if(and_or_mode == 0)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i];
                }
                else if(and_or_mode == 1)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i] && total_result[i];
                }
                else if(and_or_mode == 2)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i] || total_result[i];
                }


                //keep_search = 0;
            }

            // suffix 搜尋
            else if(whole_line[now_pos] == '*')
            {
                int right_boundry;
                for(right_boundry = now_pos + 1; right_boundry < len; right_boundry++)
                    if(whole_line[right_boundry] == '*')
                        break;

                string test;
                test = whole_line.substr(now_pos + 1, right_boundry - now_pos - 1);
                //fout << "-> " << test << endl;

                now_pos = right_boundry + 2;


                transform(test.begin(), test.end(), test.begin(), ::tolower);
                reverse(test.begin(), test.end());

                bool result[10000] = {0};
                for(int i = 0; i < how_many_txt; i++)
                {
                    if(t_reverse[i].search_prefix(test))
                    {
                        result[i] = 1;
                        //cout << i << endl;
                    }

                }

                // 進行合併
                if(and_or_mode == 0)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i];
                }
                else if(and_or_mode == 1)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i] && total_result[i];
                }
                else if(and_or_mode == 2)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i] || total_result[i];
                }


                //keep_search = 0;
            }

            // prefix 搜尋
            else
            {
                int right_boundry;
                for(right_boundry = now_pos; right_boundry < len; right_boundry++)
                    if( whole_line[right_boundry] == ' ' )
                        break;

                string test;
                test = whole_line.substr(now_pos, right_boundry - now_pos);
                //fout << "-> " << test << endl;

                now_pos = right_boundry + 1;


                transform(test.begin(), test.end(), test.begin(), ::tolower);

                bool result[10000] = {0};
                for(int i = 0; i < how_many_txt; i++)
                {
                    if(t[i].search_prefix(test))
                    {
                        result[i] = 1;
                        //cout << i << endl;
                    }

                }

                // 進行合併
                if(and_or_mode == 0)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i];
                }
                else if(and_or_mode == 1)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i] && total_result[i];
                }
                else if(and_or_mode == 2)
                {
                    for(int i = 0; i < how_many_txt; i++)
                        total_result[i] = result[i] || total_result[i];
                }


                //keep_search = 0;
            }

        }

        // 最終輸出
        int all_zero = 1;
        for(int i = 0; i < how_many_txt; i++)
            if(total_result[i])
            {
                fout << directory[i] << "\n";
                all_zero = 0;
            }

        if(all_zero)
            fout << "Not Found!" << "\n";

    }
    fi.close();
    fout.close();

    end_time = clock();
    cout << (double) (end_time - start) / CLOCKS_PER_SEC << " S" << endl;
}


// 1. UPPERCASE CHARACTER & LOWERCASE CHARACTER ARE SEEN AS SAME.
// 2. FOR SPECIAL CHARACTER OR DIGITS IN CONTENT OR TITLE -> PLEASE JUST IGNORE, YOU WONT NEED TO CONSIDER IT.
//    EG : "AB?AB" WILL BE SEEN AS "ABAB", "I AM SO SURPRISE!" WILL BE SEEN AS WORD ARRAY AS ["I", "AM", "SO", "SURPRISE"].
// 3. THE OPERATOR IN "QUERY.TXT" IS LEFT ASSOCIATIVE
//    EG : A + B / C == (A + B) / C

//

//////////////////////////////////////////////////////////
