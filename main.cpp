#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>
#define N 50

class Bohr {
public:
    int next_vertex[N];
    std::vector<int> pattern_num;
    bool flag;
    int suff_link;
    int auto_move[N];
    int parent;
    char symbol;
    Bohr(int p, char c) : parent(p), symbol(c) {
        memset(next_vertex, 255, sizeof(next_vertex));
        flag = false;
        suff_link = -1;
        memset(auto_move, 255, sizeof(auto_move));
        pattern_num.resize(0);
    }
};

std::vector<Bohr> bohr;
int cross_count = -1;
bool is_cross = false;
void init_bohr() {
    std :: cout << "Start building the bohr \n";
    std::cout<<"The root is denoted as #"<< std::endl;
    Bohr v(0,-30);
    bohr.push_back(v);
}


void add_pattern_to_bohr(const std::string& s, int& count) {
    int num = 0;
    for (int i = 0; i<s.length(); i++) {
        std :: cout << "Consider the symbol : " << i + 1 <<"th: " << s[i] << "\n";
        char ch = s[i] - 'A';
        if (bohr[num].next_vertex[ch] == -1) {
            Bohr v(num, ch);
            bohr.push_back(v);
            std::cout <<  "A vertex is added to the selection, to which the current symbol of the pattern leads (" << char((v.symbol )+'A') << ") \n";
            bohr[num].next_vertex[ch] = bohr.size() - 1;
        } else{
            std::cout << "The vertex (" << s[i] << ") already exists for the current pattern, you are navigating along it \n";

            num = bohr[num].next_vertex[ch];
        }
    }
    bohr[num].flag = true;
    std::cout << "The vertex to which the transition is made is terminal, the construction of the bohr branch is finished \n";
    bohr[num].pattern_num.push_back(++count);
    std::cout<<"--------------------------------------------------------------------------------------------------------------"<<std::endl;
}

int get_auto_move(int v, char ch);

int get_suff_link(int v) {
    std::cout << "Calculating suffix and end links for vertex: " << char (bohr[v].symbol + 'A')<<std::endl;
    if (bohr[v].suff_link == -1)
        if (v == 0 || bohr[v].parent == 0){
            std :: cout << "Suffix reference points to root(#) \n";
            bohr[v].suff_link = 0;
        }
        else{
            std :: cout << "Follow the parent's suffix link \n";
            std::cout<<"Parent is "<< bohr[v].parent << std::endl;
            bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].parent), bohr[v].symbol);
        }
    return bohr[v].suff_link;
}

int get_auto_move(int v, char ch) {
    std::cout << "Looking for a path from the vertex " << char (bohr[v].symbol + 'A') << " along the edge with the symbol " << char(ch +'A')  << ". \n";
    if (bohr[v].auto_move[ch] == -1)
        if (bohr[v].next_vertex[ch] != -1){
            std :: cout << "Go to the next node with the corresponding character \n";
            bohr[v].auto_move[ch] = bohr[v].next_vertex[ch];
        }
        else
        if (v == 0){
            std :: cout << "The next node with the matching character was not found, go to the root node(#) \n";
            bohr[v].auto_move[ch] = 0;
        }
        else{
            std :: cout << "The next node with the matching character was not found, let's follow the suffix link \n";
            bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
        }
    return bohr[v].auto_move[ch];
}

void checkout(int u, int i, const std::string& s, std::vector<int>& count, std::vector<int>&pattern_offset_mass, int pat_len, std::vector<std::string>& pat_mass,  std::string pattern){
    for (int tmp = u; tmp != 0; tmp = get_suff_link(tmp)) {
        if (bohr[tmp].flag) {
            for (int j = 0; j < bohr[tmp].pattern_num.size(); j++) {
                if ((i + 1 - pattern_offset_mass[bohr[tmp].pattern_num[j] - 1] - pat_mass[bohr[tmp].pattern_num[j] - 1].size() >= 0) && (i + 1 - pattern_offset_mass[bohr[tmp].pattern_num[j] - 1] - pat_mass[bohr[tmp].pattern_num[j] - 1].size() <= s.size() - pat_len)) {
                    std::cout << "Terminal vertex," << "subpattern =" << pat_mass[bohr[tmp].pattern_num[j] - 1] << "Number of matched subpatterns" << count[i + 1 - pattern_offset_mass[bohr [ tmp].pattern_num [j] - 1] - pat_mass[bohr[tmp].pattern_num[j] - 1] .size ()] <<
                              "from" << pattern_offset_mass.size () << ". \n";
                    count[i + 1 - pattern_offset_mass[bohr[tmp].pattern_num[j] - 1] - pat_mass[bohr[tmp].pattern_num[j] - 1].size()]++;

                    if (count[i + 1 - pattern_offset_mass[bohr[tmp].pattern_num[j] - 1] - pat_mass[bohr[tmp].pattern_num[j] - 1].size()] == pattern_offset_mass.size()) {
                        std :: cout << "Found pattern in text \n";
                        if (cross_count != -1 && i - cross_count < pattern.size() + pattern.length()) {
                            is_cross = true;
                        }
                        cross_count = i - pattern.length();
                        std::cout << i - pattern.length() + 1 << "\n";
                    }
                }
            }

        }
    }
    std::cout<<"The current suffix link points to the root, read the next character of the text.\n";
    std::cout<<"--------------------------------------------------------------------------------------------------------------"<<std::endl;
}

void find_all_pos(const std::string& s, std::vector<int>& count, std::vector<int>&pattern_offset_mass, int pat_len, std::vector<std::string>& pat_mass, std::string pattern) {
    int u = 0;
    for (size_t i = 0; i < s.size(); i++) {
        std::cout << "Consider the line with the current position: ";
        for (int j = 0; j < s.length(); j++)
            if (j == i)
                std::cout << "'" << s[j] << "'";
            else
                std::cout << s[j];
        std::cout<<std::endl;
        u = get_auto_move(u, s[i] - 'A');
        checkout(u, i, s, count, pattern_offset_mass,  pat_len,  pat_mass, pattern );
    }
}

void split_pattern(std::string pattern, char joker, std::vector<std::string>& pat_mas, std::vector<int>& pattern_offset_mas){
    std::cout << "Break the original pattern by jokers, into subpatterns. \n";
    std::string buf = "";
    for (int i = 0; i < pattern.size(); i++) {
        if (pattern[i] == joker){
            if (buf.size() > 0) {
                pat_mas.push_back(buf);
                std::cout << "Found a new subpattern: " << buf << "\n";
                pattern_offset_mas.push_back(i - buf.size());
                buf = "";
            }
        }
        else {
            buf.push_back(pattern[i]);
            if (i == pattern.size() - 1) {

                std::cout << "Found a new subpattern:" << buf << "\n";
                pat_mas.push_back(buf);

                pattern_offset_mas.push_back(i - buf.size() + 1);
                std::cout << "Starting index in the original pattern:" << i - buf.size () + 1 << "\n";
            }
        }
    }
}

void out(std::vector<int>& count, int pat_counter, std::string& s, std::string pattern) {

    for (int i = 0; i < count.size(); i++) {
        if (count[i] == pat_counter) {
            std::cout << i + 1 << "\n";

        }
    }
    std::cout<<"The number of vertices in the automate: " <<bohr.size()<<std::endl;
    std::cout<<"A list of found patterns that overlap with other found patterns in the search bar";
    if (!is_cross)
        std::cout<<" , empty"<< std::endl;
    else{
        std::cout<<":\n";
        std::cout<<pattern<<std::endl;
    }
}

int main()
{
    init_bohr();
    std::string text;
    std::string pattern;
    std::vector<int> pattern_offset_mass;
    char joker;
    std::cin >> text >> pattern >> joker;
    std::vector<int> count(text.size(), 0);
    std::vector<std::string> patt_mass;
    split_pattern(pattern, joker, patt_mass, pattern_offset_mass);
    int k = 0;
    for (auto pat : patt_mass) {
        add_pattern_to_bohr(pat, k);
    }

    find_all_pos(text, count, pattern_offset_mass,  pattern.size(),  patt_mass, pattern );

    out(count, patt_mass.size(), text, pattern);
    return 0;
}