#include "Parser.h"
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
#include<vector>

using namespace std;

ParserMatcher::ParserMatcher()
{
    //ctor
}

vector<string>ParserMatcher::get_productions()
{
    Matcher matcher ;
    Parser parser;
    vector<pair<string, string>>  input ;
    string str;
    string stack_top;
    string producticon ;

    pair<string,string >entry;
    vector<string>output;

    bool error =0 ;
    stack <string>production_stack ;

    //str = get_next_token();

    input = matcher.tokens;


    production_stack.push("$");
    production_stack.push(start_symbol);
    int index =0 ;
    while(!production_stack.empty())
    {
        vector <string> temp ;
        stack_top = production_stack.top();
        production_stack.pop();
        //Non Terminal
        if (!all_strings[stack_top]  &&  stack_top.compare("$")!=0 )
        {

            if(all_strings[input.at(index).first] || input.at(index).first.compare("$")==0)
            {

                entry.first =stack_top;
                entry.second =input.at(index).first;
                producticon = production_table[entry];

                cout << stack_top << " satckTop " << endl;
                cout << input.at(index).first << " input" << endl;
                cout << producticon << " production" << endl<<endl;

                if(!producticon.empty() )
                {


                    output.push_back(producticon);
                    str = producticon;
                    std::istringstream iss(str);
                    for(std::string str; iss >> str; )
                        temp.push_back(str);


                    if(temp.at(0).compare(EPSILON)!=0 &&temp.at(0).compare("sync")!=0 )
                    {
                        str = temp.at(0);
                        for(int i = temp.size() -1 ; i >= 0 ; i -- )
                        {
                            str = temp.at(i);
                            cout <<temp.at(i)<< "pushtostack"<<endl;
                            production_stack.push(temp.at(i));
                        }
                    }

                    else if(temp.at(0).compare("sync")==0)
                    {
                        output.push_back("ERROR SYNCH");
                        error = 1 ;
                    }
                    else if(temp.at(0).compare(EPSILON)==0)
                    {
                        output.push_back(temp.at(0));
                    }

                }
                ////////////////////////////////////////////////////////////////Error should be hanled
                else
                {
                    output.push_back("ERROR NO PRODUCTION");
                    index++;
                    production_stack.push(stack_top);
                    error = 1;
                }

            }

        }
        //Terminal
        else  if(all_strings[stack_top] ||  stack_top.compare("$")==0)

        {
            cout << stack_top << "satckTop " << endl;
            cout << input.at(index).first << "input" << endl;
            if(stack_top.compare(input.at(index).first)==0 )
            {
                cout << "Match : "+ stack_top + ", " << input.at(index).first<< endl;
                index++;

                // cout << stack_top << "matched\n";
            }

            else
            {
                output.push_back("ERROR MISSINNG IN STACK : "+ stack_top);
                error = 1;
                cout << "ERROR MISSINNG IN STACK : "+ stack_top << endl;
            }
        }

        //    }
    }
    if(error)
    {
        output.push_back("ACCEPTED WITH ERROR");
    }
    else
    {
        output.push_back("ACCEPTED");
    }
    cout <<endl<<endl;

    return output ;
}


void ParserMatcher::print_productions()
{
    vector<string> output = get_productions();
    cout <<"\\----------------------------- PRODUCTIONS-------------------------------\\" << endl;
    for(int i = 0; i < output.size(); i++){
        cout << "=>> " << output[i] << endl;
    }
}
