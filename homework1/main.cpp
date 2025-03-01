//File main
//Program:   Creates box of words flushed to the right or left, or full justify.

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cctype>
using namespace std;

//flushes all words to left with extra remaining space on the right.
string flushleft(int width,vector<string> &words, ofstream &outputfile){ 
    string boxline = "--";
    for (int a = 0; a<width;++a){
        boxline += '-'; //prints top box
    }
    boxline+="--";
    outputfile<<boxline<<std::endl; 
    string line;
    int leftover = width;
    int counter = 0;
    for (int i =0 ; i<words.size() ; ++i){
        if (words[i].size() < leftover){ // might need a +1 at length(words[i]) to fix spacing issues.
            if (words[i].size()!=0){
                leftover = leftover - words[i].size()-1; //-1 taking into account spacing
                line += words[i]+ ' '; 
            }
        }
        else { // word too big. Move to next line. And print previous.
            line= "| "+line;
            counter+=1;
            if (counter==1){
                for (int left = 0; left<leftover+1; left++){
                    line += ' ';
                }
            }else{
                for (int left = 0; left<leftover; left++){
                    line += ' ';
                 }
            }
            line = line + "|";
            outputfile<<line<<std::endl;  //outputs line

            leftover = width- words[i].size();
            line = words[i]+" ";

        }
    }
    line = "| "+line;
    for (int final = 0; final<leftover;final++){ //case where last sentence has issues. This block fixes it. (Spacing issues.)
        line+=' ';
    }
    line = line + "|";
    outputfile<<line<<std::endl;
    outputfile<<boxline<<std::endl; 
    return "";
}
//prints all words from right to left. 
string flushright(int width, vector<string> &words, ofstream &outputfile){
    string boxline = "--";
    for (int a = 0; a<width;++a){ 
        boxline += '-';
    }
    boxline+="--";
    outputfile<<boxline<<std::endl; 
    string line;
    int leftover = width;
    int counter = 0;
    string copyline;
    for (int i =0 ; i<words.size() ; ++i){
        if (words[i].size() < leftover){ // more space to add more words in the line.
            if (words[i].size()!=0){
                leftover = leftover - words[i].size()-1; //-1 taking into account spacing
                line += ' '+words[i] ; 
            }
        }
        else { // word too big. Move to next line
            counter+=1;
            string copyline= line;
            line = "|";
            if (counter == 1){
                for (int first = 0; first<leftover+1;first++){
                    line+= ' '; //Fixes error of the extra spacing that is in my vector of words. I have a blank space holding a spot in a vector.
                }
            }
            else {
                for (int first = 0; first<leftover;first++){
                    line+= ' ';
                }
            }
            line = line+copyline + " |";
            outputfile<<line<<std::endl;
            leftover = width- words[i].size();
            line = " " +words[i];
        }
    }
    copyline = line;
    line = "|";
    for (int final = 0; final<leftover;final++){ //prints from right to left.
        line+=' ';
    }
    line = line + copyline+ " |";
    outputfile<<line<<std::endl;
    outputfile<<boxline<<std::endl;
    return "";
}

//converts a line into a vector of words from that line.
vector<string> convert(string line) 
{
    vector<string> words;
    string word = "";
    for (char i : line) // Goes through every word/char in string line. 
    {
        if (i == ' ')//if it finds a space(signifies seperation of characters meaning it finds a word.)
        {
            words.push_back(word); //continues to add word to words vector
            word = ""; //resets word
        }
        else 
        {
            word = word + i; //adds on the character. Creating a word. 
        }
    }
    words.push_back(word);
    return words;
    
}



//creates vector of characters.
vector<char> c_convert(string word){
    string s = word;
 
    vector<char> v(s.begin(), s.end()); //creates vector of all characters in the word.
 
    return v;

}

    
//full justify.
string fulljustify(int width,vector<string> &words, ofstream &outputfile){
    string boxline = "--";
    for (int a = 0; a<width;++a){ // top of boxline
        boxline += '-';
    }
    boxline+="--";
    outputfile<<boxline<<std::endl; 
    string line;
    int leftover = width;
    for (int i =0 ; i<words.size() ; ++i){ //goes through every word in the vector
        
        bool longword = false; // is the word a long word?
        if (words[i].size()>width){ 
            longword = true;//a longword
            if (leftover< width){
                for (int i = 0; i<leftover;i++){
                    line+=" ";
                }
                outputfile<<"| "<<line<<"|"<<std::endl; //prints long word with a word placed after it.
                line = "";
            }
        }
        if (words[i].size() < leftover && longword == false){ // 
            //longword = false;
            leftover = leftover - words[i].size()-1; //-1 taking into account spacing
            line += words[i]+ ' ' ; // when printing might need to -1 the leftover. cause of an extra space.
        }
        else if (longword == true){//Word is bigger than the width of the input. need a dash-
            vector<char> lword = c_convert(words[i]); //vector of characters in the long word.
            int count=0;
            for (int let = 0; let <lword.size() ;let++){  //lword.size = 35
                count +=1;
                if (count < width){
                    line+=lword[let];
                }
                else{
                    let--; 
                    count = 0;
                    line+="-";
                    outputfile<<"| "<<line<<" |"<<std::endl;  //prints long word with dash.
                    line = "";
                    
                }
            }
            line += " ";
            if (i==words.size()-1){
                leftover = width - line.size(); //this if statement makes sure that the last part of the long word in the last sentence is placed 
                for (int h = 0; h<leftover;h++){// correctly. So that the | is placed correctly.
                    line+=" ";
              }
            }
            leftover = leftover - line.size()-1; 
            
        }
        else{ 
            string newline;  //Printing of regular words.
            string bar;
            string print;
            vector<string> str = convert(line);
            int length = width - line.size()+1;
            int spacing = length/(str.size()-2);
            if ((str.size()-1)>length){// takes care of sentences where some words have extra space and some words do not. 
                for (int j = 0; j < str.size()-1; ++j){
                    bar = "";
                    if (length>0){ // Words that have the extra space 
                        length-=1;
                        bar = "  ";
                    } else {  // Words that do not have the extra space
                        bar = " ";
                        }
                    newline += str[j]+bar;
                }
                print = "| "+newline+"|";
                outputfile<<print<<std::endl;
            } else{
                if (longword == false){ 
                    for (int i = 0; i < str.size()-1; i++){
                        bar = "";
                        for (int x = 0; x<spacing+1; x++){ //spacing of words when there is space leftover.
                            if (i != str.size()-2){
                                bar+=' ';
                            }
                        }
                        newline += str[i]+bar;
                    }
                    
                    print = "| " + newline + " |";
                    outputfile<<print<<std::endl;
                }
            }
            leftover = width- words[i].size(); //subtracts leftover spaces from size of word and space.
            line = words[i]+" ";
            
            


        }
         
    }//last sentence.
    for (int s = 0; s<leftover-1;s++){
        line+=" ";
    }
    outputfile<<"| "<<line<<" |"<<std::endl;
    outputfile<<boxline<<std::endl;
   return "";
}   


//main function.
int main(int argc, char* argv[]){
    if (argc != 5){
        cerr<<"Error occured. Did not provide 4 arguments"<<std::endl; //error. Sent to error terminal.
        return 0;
    }
    ifstream myfile(argv[1]);
    ofstream outfile(argv[2]);  //intaking the arguments
    int width = stoi(argv[3]);
    string flush = argv[4];
    string text;
    vector<string> sentences; //vector of all the sentences in the file.
    while (getline(myfile,text)){
        sentences.push_back(text); // create a vector of all words  
    }
    
    vector<string> words = convert(sentences[0]); //Here I am creating one vector that includes all the words from every sentence
    if (sentences.size() >1){                     // in the file.
        for (int index = 1; index < sentences.size(); index++){
            vector<string> helper = convert(sentences[index]);
            for (int h = 0; h<helper.size();h++){  //combines multiple vectors together.
                words.insert(words.end(),helper[h]);
            }
            
        } // words now has every word of every line in a text.
    }
    
    if (flush == "flush_left") {
        flushleft(width,words,outfile); 
    } else if (flush == "flush_right") {
        flushright(width,words,outfile);  //prints correct thing that user wants.
    } else if (flush == "full_justify"){  
        fulljustify(width,words,outfile);
    } else return 0;
}