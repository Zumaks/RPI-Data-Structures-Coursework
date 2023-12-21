#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <cmath>

using namespace std ; 

// Note :  A loop was used to create strings of variable lengths due to an issue with my computer and string(size,char)


// Please begin reading at main and then come back to the functions.


string flush_left(vector <string> b, int char_len) { 
  string new_string;
  int len_tracker = 0;
// Top frame is created 
  int val1 = char_len+4;
  string temp_str1;
  for(int i=0;i<val1;i++) {
      temp_str1 = temp_str1 + "-";
  }
  new_string = new_string + temp_str1 + "\n" + "| ";

// Each word from the vector "b" is iterated through and it's length is compared to the user specified maximum line length

  for(int i=0;i<b.size();i++) {
    len_tracker = len_tracker + b[i].length();
    if (len_tracker > char_len) {
      int val2 = (char_len - (len_tracker - b[i].length() ));
      string temp_str2;
      for(int i=0;i<val2;i++) {
        temp_str2 = temp_str2 + " ";
      }
      new_string = new_string + temp_str2 + " |" +  "\n" + "| " +  b[i] + " ";
      len_tracker = 0;
      len_tracker = len_tracker + b[i].length() + 1;
  }
    else if (len_tracker == char_len) {
      new_string = new_string + b[i] + " |" + "\n" + "| ";
      len_tracker = 0;
    }
    else {
       new_string = new_string + b[i] + " ";
       len_tracker = len_tracker + 1;
    }
  }
  int val3 = char_len - len_tracker;
      string temp_str3;
      for(int i=0;i<val3;i++) {
        temp_str3 = temp_str3 + " ";
      }
  new_string = new_string + temp_str3 + " |";

// Bottom frame is created 
  int val4 = char_len+4;
  string temp_str4;
  for(int i=0;i<val4;i++) {
      temp_str4 = temp_str4 + "-";
  }
  new_string = new_string + "\n" + temp_str4 ;


  return new_string;
}






string flush_right(vector <string> b, int char_len) {
    string new_string;
    int len_tracker = 0;
    vector <string> each_line;
    vector <int> whitespace_num;
    string temp_str;
// Similairly to flush_left, flush_right loops through all words in the vector forming two vectors one of strings containing 
// each line of the box and the other containing the whitespace values calculated in the loop below
    for(int i=0;i<b.size();i++) {
        len_tracker = len_tracker + b[i].length();
        if (len_tracker > char_len) {
            int whitespace = (char_len - (len_tracker - b[i].length()));
            whitespace_num.push_back(whitespace);
            each_line.push_back(temp_str);
            len_tracker = 0;
            len_tracker = len_tracker + b[i].length() + 1;
            temp_str = b[i] + " ";
        }
        else if (len_tracker == char_len) {
            whitespace_num.push_back(0);
            temp_str = temp_str + b[i];
            each_line.push_back(temp_str);
            len_tracker = 0;
            temp_str = "";
          }
        else {
            temp_str = temp_str + b[i] + " ";
            len_tracker = len_tracker + 1;
        }
      }
// Checks to see if there is a left over line not identified by the technique used in the loop above
    if(temp_str.length() != 0 ) { 
      each_line.push_back(temp_str);
      whitespace_num.push_back(char_len - temp_str.length());
    }
    string final_str;

    string topbottom;
    for(int i=0;i<char_len+4;i++) {
      topbottom = topbottom + "-";
  }
// Lastly, the final string is created containing each line of text added to it's corresponding whitespace
    final_str = final_str + topbottom + "\n";
    for(int i=0;i<each_line.size();i++) {
        string white_space;
        for(int z=0;z<whitespace_num[i];z++) {
            white_space = white_space + " ";
        }
        final_str = final_str + "|  " + white_space + each_line[i] + "|" + "\n";
    }
    final_str = final_str + topbottom;
  return final_str;

}




string full_justify(vector <string> b, int char_len) {
  string new_string;
    int len_tracker = 0;
    vector <vector <string> > each_line;
    vector <string> each_word;
    vector <int> whitespace_num;
    string temp_str;
// The total whitespace is calculated below similairly to how it was done in flush_right and flush_left and a 2D vector is created
// in which each element is a vector containing all the words in one line of the box
    for(int i=0;i<b.size();i++) {
        len_tracker = len_tracker + b[i].length() + 1;
        if (len_tracker > char_len) {
            int whitespace = (char_len - b[i].length() - 1);
            whitespace_num.push_back(whitespace);
            each_line.push_back(each_word);
            len_tracker = 0;
            len_tracker = len_tracker + b[i].length();
            each_word.clear();
            each_word.push_back(b[i]);
        }
        else if (len_tracker == char_len) {
            whitespace_num.push_back(0);
            each_word.push_back(b[i]);
            each_line.push_back(each_word);
            len_tracker = 0;
            each_word.clear();
          }
        else {
            each_word.push_back(b[i]);
        }
      }
    
    if(each_word.size() != 0 ) { 
      each_line.push_back(each_word);
      int total_left_len = 0;
      for(int i =0; i < each_word.size(); i++) {
        total_left_len = total_left_len + each_word[i].length();
      }
      whitespace_num.push_back(char_len - total_left_len);
    }




    string final_str;
// The top frame is created
    string topbottom;
    for(int i=0;i<char_len+4;i++) {
      topbottom = topbottom + "-";
    }
    final_str = final_str + topbottom + "\n";
// The total amount of spaces between words is calculated to know how to divide total whitespace
    for(int i = 0; i < each_line.size(); i++) {
      int num_whitespace;
      if (each_line[i].size() == 1) {
        num_whitespace = 1;
      }
      else {
        num_whitespace = (each_line[i].size() - 1) ;
      }
      string cur_whitespace ;
// Each line is formatted differently depending on it's properties (Whether there is only one word, the numer of spaces is even/odd)
      if (each_line[i].size() == 1) {
        string temp_str;
        for(int z=0;z<whitespace_num[i];z++) {
            cur_whitespace = cur_whitespace + " ";
          }
        temp_str = temp_str + each_line[i][0] +  cur_whitespace;
        final_str = final_str + "| " + temp_str + " |" + "\n";
      }

      else if (whitespace_num[i] % num_whitespace == 0 ) {
// When the number of spaces between words is even, the program simply divides up the whitespace in the same manner
          string temp_str;
          for(int z=0;z<(whitespace_num[i] / num_whitespace);z++) {
            cur_whitespace = cur_whitespace + " ";
          }
          for(int z = 0; z < each_line[i].size(); z++) {
            if(z == (each_line[i].size()-1)) {
              temp_str = temp_str + each_line[i][z];
            }
            else {
              temp_str = temp_str + each_line[i][z] +  cur_whitespace;
            }
            }
      
      final_str = final_str + "| " + temp_str + " |" + "\n";
      }

      else {
// When the whitespace cannot be divided evenly, a vector containing evenly divided whitespace is created following which the
// remainder is used to identify how much extra whitespace is needed and where it is needed
        vector <int> temp_whitespace_left ;
        vector <int> final_whitespace_left ;
        string temp_str;
        int minus_remainder;

        minus_remainder = (whitespace_num[i] % num_whitespace);
        for(int z = 0; z < num_whitespace; z++) {
          temp_whitespace_left.push_back(whitespace_num[i] / num_whitespace);
        }
        for(int z = 0; z < temp_whitespace_left.size(); z++) {
          final_whitespace_left.push_back(temp_whitespace_left[z] + minus_remainder);
          if (minus_remainder == 0) {
            minus_remainder = 0;
          }
          else {
            minus_remainder = minus_remainder - 1;
          }
        }
        for(int z = 0; z < each_line[i].size(); z++) {
          string cur_whitespace;
          for(int y=0;y<final_whitespace_left[z];y++) {
            cur_whitespace = cur_whitespace + " ";
          }
          temp_str = temp_str + each_line[i][z] +  cur_whitespace + " ";
      }
      final_str = final_str + "| " + temp_str + "|" + "\n";
      
    }
    }
    final_str = final_str + topbottom;
  return final_str;

}




int main (int argc, char* argv[]) {
// User input is collected and processed from command line in order to open the associated file
    ifstream text_input;
    text_input.open(argv[1]);
    ofstream MyFile(argv[2]);
    string line;
    vector <string> lines; 
// User specified file is opened and each word is stored into the vector "lines"
    while (text_input) {
      text_input >> line;
      lines.push_back(line);
    }
    lines.pop_back();
    int char_len = stoi(argv[3]);
    string parsed_string;
// The desired form of output is determined through a series of if statements.
    if(strcmp("flush_left",argv[4]) == 0) {
      parsed_string = flush_left(lines,char_len);
    }
    if(strcmp("flush_right",argv[4]) == 0) {
      parsed_string = flush_right(lines,char_len);
    }
    if(strcmp("full_justify",argv[4]) == 0) {
      parsed_string = full_justify(lines,char_len);
    }
// Program generated output is written to a file of user specified title and then closed
    MyFile << parsed_string;
    MyFile.close();
    
}