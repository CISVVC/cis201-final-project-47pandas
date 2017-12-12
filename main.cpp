/*
 * dev Nathan Emigh
 * Email: 47pandas@gmail.com 
 * Professor: Tonning
 * Description: This program reads in a text file, creates an index of all the words, removes duplicates, counts how many times the words occurs and what lines they occur on.
*/

#include <iostream>  
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

struct Word
{
    std::vector<int> line;
    std::string word;
    int word_count = 1;
};

void remove_punctuation(std::string &p)
{
    p.erase(std::remove_if (p.begin (), p.end (), ispunct), p.end());
}

void make_lowercase(std::string &p)
{
   for(int i = 0;i < p.size();i++)
   {
      p[i] = tolower(p[i]);
   }
}

int find(std::string werdz, std::vector<Word> bloop)
{
   for(int i = 0; i < bloop.size();i++)
   {
      if(werdz == bloop[i].word)
      {
         return i;
      }
   }
  return -1;
}

std::vector<Word> extract_database (std::string &p)
{
    std::vector<Word> words;
    int lines = 1;
    while(p.length() > 1)
    {
        int e = p.find(' ');
        int new_line = p.find('\n');
        
        if(e + 1 <= p.length())
        {
            Word w;
            w.line.push_back(lines);
              
            if(new_line < e && new_line != -1)
            {
               w.word = p.substr(0, new_line);
               lines++;
	    }
            else
            {
               w.word = p.substr(0, e);         
            }

            int location = find(w.word, words);
            
            if(location == -1)
            {
               words.push_back(w);
            }
            else
            {
               words[location].word_count++;
               
               words[location].line.push_back(lines);
            }

            if(new_line < e && new_line != -1)
            {
               p.erase(0, new_line + 1);
            }
            else if(e != -1)
            {
                 p.erase(0, e + 1);
            }
            else
            {
                break;
            }
        }
     
    }
    words[words.size() - 1].word.erase(std::remove(words[words.size() - 1].word.begin(), words[words.size() - 1].word.end(), '\n'), words[words.size() - 1].word.end());
    return words;
}

std::string stream2string()
{
   std::string s;
   std::string stotal;
   
   std::ifstream in;
   in.open("alice.txt");

   while(!in.eof())
   {
      getline(in, s);
      stotal += s + "\n";
   }

in.close();
return stotal;
}

int main()
{
    std::string input;
    input = stream2string();
    std::map<std::string, Word > testinghere;
    make_lowercase(input);
    remove_punctuation(input);
   // make_lowercase(input);
   // std::cout << input << std::endl;
   
    std::vector<Word> words = extract_database(input);
   
    for(int i = 0;i < words.size(); i++)
    {   
       std::string l;
       for(int j = 0; j < words[i].line.size();j++)
       {
          l += std::to_string(words[i].line[j]) + ", ";
       }
       std::cout << words[i].word << " Word count: " << words[i].word_count << " Lines: " << l << std::endl;
    }

    return 0;
 }
