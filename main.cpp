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

void init_bohr() {
    Bohr v(0,0);
    bohr.push_back(v);
}


void add_pattern_to_bohr(const std::string& s, int& count) {
    int num = 0;
    for (int i = 0; i<s.length(); i++) {
        char ch = s[i] - 'A';
        if (bohr[num].next_vertex[ch] == -1) {
            Bohr v(num, ch);
            bohr.push_back(v);
            bohr[num].next_vertex[ch] = bohr.size() - 1;
        }
        num = bohr[num].next_vertex[ch];
    }
    bohr[num].flag = true;
    bohr[num].pattern_num.push_back(++count);
}

int get_auto_move(int v, char ch);

int get_suff_link(int v) {
    if (bohr[v].suff_link == -1)
        if (v == 0 || bohr[v].parent == 0)
            bohr[v].suff_link = 0;
        else
            bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].parent), bohr[v].symbol);
    return bohr[v].suff_link;
}

int get_auto_move(int v, char ch) {
    if (bohr[v].auto_move[ch] == -1)
        if (bohr[v].next_vertex[ch] != -1)
            bohr[v].auto_move[ch] = bohr[v].next_vertex[ch];
        else
        if (v == 0)
            bohr[v].auto_move[ch] = 0;
        else
            bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
    return bohr[v].auto_move[ch];
}



void find_all_pos(const std::string& s, std::vector<int>& count, std::vector<int>&pattern_offset_mass, int pat_len, std::vector<std::string>& pat_mass) {
    int u = 0;
    for (size_t i = 0; i < s.size(); i++) {
        u = get_auto_move(u, s[i] - 'A');
        for (int tmp = u; tmp != 0; tmp = get_suff_link(tmp)) {
            if (bohr[tmp].flag) {
                for (int j = 0; j < bohr[tmp].pattern_num.size(); j++) {
                    if ((i + 1 - pattern_offset_mass[bohr[tmp].pattern_num[j] - 1] - pat_mass[bohr[tmp].pattern_num[j] - 1].size() >= 0) && (i + 1 - pattern_offset_mass[bohr[tmp].pattern_num[j] - 1] - pat_mass[bohr[tmp].pattern_num[j] - 1].size() <= s.size() - pat_len)) {
                        count[i + 1 - pattern_offset_mass[bohr[tmp].pattern_num[j] - 1] - pat_mass[bohr[tmp].pattern_num[j] - 1].size()]++;
                        if (count[i + 1 - pattern_offset_mass[bohr[tmp].pattern_num[j] - 1] - pat_mass[bohr[tmp].pattern_num[j] - 1].size()] == pattern_offset_mass.size()) {

                        }
                    }
                }

            }
        }
    }
}

void split_pattern(std::string pattern, char joker, std::vector<std::string>& pat_mas, std::vector<int>& pattern_offset_mas){
    std::string buf = "";
    for (int i = 0; i < pattern.size(); i++) {
        if (pattern[i] == joker){
            if (buf.size() > 0) {
                pat_mas.push_back(buf);
                pattern_offset_mas.push_back(i - buf.size());
                buf = "";
            }
        }
        else {
            buf.push_back(pattern[i]);
            if (i == pattern.size() - 1) {
                pat_mas.push_back(buf);

                pattern_offset_mas.push_back(i - buf.size() + 1);

            }
        }
    }
}

void out(std::vector<int>& count, int pat_counter, int pat_len, std::string& s) {

    for (int i = 0; i < count.size(); i++) {
        if (count[i] == pat_counter) {
            std::cout << i + 1 << "\n";

        }
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

    find_all_pos(text, count, pattern_offset_mass,  pattern.size(),  patt_mass);

    out(count, patt_mass.size(),  pattern.size(), text);
    return 0;
}