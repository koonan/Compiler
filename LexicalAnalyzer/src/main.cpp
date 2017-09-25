#include <iostream>
#include <regex>
#include "Analyzer.h"
#include "Matcher.h"
#include "Parser.h"

using namespace std;

std::map  <std::string, struct automata > automata_table;
std::map<int,std::pair<int, string>> nfa_acceptance_states;
struct automata NFA_automata;
set<string> inputs;
vector<string> possible_inputs;
vector<string> definitions;

int main()
{
    NFA obj;
    DFA inst;
    Matcher match;
    ParserMatcher matcher;
    obj.file_read("Lexical_Rules.txt");
    obj.oring_for_NFA_automata() ;
    match.read_java_file("test_code.txt",inst.dfa(NFA_automata.state));

    Parser p;
    p.file_Reader("cfg.txt");
    p.formulate_first_for_all_non_terminals();
    p.form_follow();
    matcher.print_productions();
    // cout << endl << p.contains("E" , "F Eo") << endl;
    return 0;
}
