#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cctype>
using namespace std;

string flushleft(int width,vector<string> &words){ // words is a vector
    string boxline = "--";
    for (int a = 0; a<width;++a){
        boxline += '-';
    }
    boxline+="--";
    cout<<boxline<<std::endl; 
    string line;
    int leftover = width;
    int counter = 0;
    for (int i =0 ; i<words.size() ; ++i){
        
        /*cout<<leftover<<std::endl;
        cout<<'x'<<std::endl;
        cout<<words[i].size()<<std::endl;*/
        if (words[i].size() < leftover){ // might need a +1 at length(words[i]) to fix spacing issues.
            if (words[i].size()!=0){
              leftover = leftover - words[i].size()-1; //-1 taking into account spacing
              line += words[i]+ ' ' ; 
              
            }
            
        }
        else { // word too big. Move to next line. And print previous.
            line= "| "+line;
            counter+=1;
            //cout<<counter<<std::endl;
            if (counter ==1 ){
                for (int left = 0; left<leftover+1; left++){
                    line += ' ';
                 }
            } else {
                for (int left = 0; left<leftover; left++){
                    line += ' ';
                 }
            }
           /* for (int left = 0; left<leftover; left++){
                line += ' ';
            }*/
            line = line + "|";
            
           /* cout<<leftover<<std::endl;
            cout<<"x"<<std::endl;
            cout<<words[i].size()<<std::endl;*/
            cout<<line<<std::endl; 
            
            leftover = width-words[i].size();
            line = words[i]+" ";
        }
    }

    line = "| "+line;
    for (int final = 0; final<leftover;final++){
        line+=' ';
    }
    line = line + "|";
    cout<<line<<std::endl;
    cout<<boxline<<std::endl; 
    return "";
}

string flushright(int width, vector<string> &words){
    string boxline = "--";
    for (int a = 0; a<width;++a){
        boxline += '-';
    }
    boxline+="--";
    cout<<boxline<<std::endl; 
    string line;
    int leftover = width;
    int counter = 0;
    string copyline;
    for (int i =0 ; i<words.size() ; ++i){
        
        if (words[i].size() < leftover){ // might need a +1 at length(words[i]) to fix spacing issues.
            if (words[i].size()!=0){
                leftover = leftover - words[i].size()-1; //-1 taking into account spacing
                line += ' '+words[i] ; // when printing might need to -1 the leftover. cause of an extra space.
            }
        }
        else { // word too big. Move to next line
            counter+=1;
            string copyline= line;
            line = "|";
            if (counter == 1){
                for (int first = 0; first<leftover+1;first++){
                    line+= ' ';
                }
            }
            else {
                for (int first = 0; first<leftover;first++){
                    line+= ' ';
                }
            }
            line = line+copyline + " |";
            cout<<line<<std::endl;

            leftover = width- words[i].size();
            line = " " +words[i];

            

        }
    }
    copyline = line;

    line = "|";
    for (int final = 0; final<leftover;final++){
        line+=' ';
    }
    line = line + copyline+ " |";
    cout<<line<<std::endl;
    cout<<boxline<<std::endl;
    return "";
}

vector<string> convert(string line) 
{
    vector<string> words;
    string word = "";
    for ( char i : line) 
    {
        if (i == ' ')
        {
            words.push_back(word);
            word = "";
        }
        else {
            word = word + i;
        }
    }
    words.push_back(word);
    return words;
    
}

vector<char> c_convert(string word){
    string s = word;
 
    vector<char> v(s.begin(), s.end());
 
    return v;

}

    

string fulljustify(int width,vector<string> &words){
    string boxline = "--";//+('-'*width)+"--";
    for (int a = 0; a<width;++a){
        boxline += '-';
    }
    boxline+="--";
    cout<<boxline<<std::endl; 
    string line;
    int leftover = width;
    for (int i =0 ; i<words.size() ; ++i){
        
        bool longword = false;
        if (words[i].size()>width){ //long word and another word before it.
            longword = true;
            if (leftover< width){
                for (int i = 0; i<leftover;i++){// 
                    line+=" ";
                }
                cout<<"| "<<line<<"|"<<std::endl;
                line = "";
            }
        }
        if (words[i].size() < leftover && longword == false){ // might need a +1 at length(words[i]) to fix spacing issues.
            //longword = false;
            leftover = leftover - words[i].size()-1; //-1 taking into account spacing
            line += words[i]+ ' ' ; // when printing might need to -1 the leftover. cause of an extra space.
        }
        else if (longword == true){//Word is bigger than the width of the input. need a dash-
            //cout<<leftover<<std::endl;
            
            vector<char> lword = c_convert(words[i]);
            //cout<<"HERE"<<std::endl;
           // longword = true; //might not need this.
            int count=0;
            for (int let = 0; let <lword.size() ;let++){  //lword.size = 35
                count +=1;
                if (count < width){
                    line+=lword[let];
                }
                else{
                    //cout<<let<<std::endl;
                    let--;
                    count = 0;
                    line+="-";
                    cout<<"| "<<line<<" |"<<std::endl;
                    line = "";
                    
                }
            }
            line += " ";
            if (i==words.size()-1){
                leftover = width - line.size();
                for (int h = 0; h<leftover;h++){
                    line+=" ";
              }
           // cout<<line<<" |"<<std::endl;
            }
            leftover = leftover - line.size()-1;
            
        }
        else{ 
            string newline;
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
                cout<<print<<std::endl;
            } else{
                if (longword == false){
                    for (int i = 0; i < str.size()-1; i++){
                        bar = "";
                        for (int x = 0; x<spacing+1; x++){
                            if (i != str.size()-2){
                                bar+=' ';
                            }
                        }
                        newline += str[i]+bar;
                    }
                    
                    print = "| " + newline + " |";
                    cout<<print<<std::endl;
                }
            }
            leftover = width- words[i].size();
            line = words[i]+" ";
            
            


        }
         
    }//last sentence.
    for (int s = 0; s<leftover-1;s++){
        line+=" ";
    }
    cout<<"| "<<line<<" |"<<std::endl;
    cout<<boxline<<std::endl;
   return "";
}

    

string printvector(int width, vector<string> &words){
    for (int i = 0; i< words.size();++i){
        cout<<words[i]<<std::endl;
        cout<<words[i].size()<<std::endl;
    }
    return "";
}

int main(int argc, char* argv[]){
    if (argc != 5){
        cerr<<"Error occured. Did not provide 4 arguments"<<std::endl;
        return 0;
    }
    ifstream myfile(argv[1]);
   // ofstream outfile(argv[2]);  
    int width = stoi(argv[3]);
    string flush = argv[4];
    string text;
    vector<string> sentences;
    while (getline(myfile,text)){
        sentences.push_back(text); // create a vector of all words  
    }
    
    vector<string> words = convert(sentences[0]); //Here I am creating one vector that includes all the words from every sentence
    if (sentences.size() >1){                     // in the file.
        for (int index = 1; index < sentences.size(); index++){
            vector<string> helper = convert(sentences[index]);
            for (int h = 0; h<helper.size();h++){
                words.insert(words.end(),helper[h]);
            }
            
        } // words now has every word of every line in a text.
    }
    
    if (flush == "flush_left") {
        flushleft(width,words); 
    } else if (flush == "flush_right") {
        flushright(width,words);
    } else if (flush == "full_justify"){
        fulljustify(width,words);
    } else if (flush=="vector"){
        printvector(width,words);
     
    }
}








/*
string fulljustify(int width,vector<string> &words, ofstream &outputfile){
    string boxline = "--";//+('-'*width)+"--";
    for (int a = 0; a<width;++a){
        boxline += '-';
    }
    boxline+="--";
    outputfile<<boxline<<std::endl; 
    string line;
    int leftover = width;
    

    for (int i =0 ; i<words.size() ; ++i){
        if (words[i].size() <= leftover){ // might need a +1 at length(words[i]) to fix spacing issues.
            if (words[i].size()!=0){
                leftover = leftover - words[i].size()-1; //-1 taking into account spacing
                line += words[i]+ ' ' ; // when printing might need to -1 the leftover. cause of an extra space.
            }
        }
        else { // word too big. Move to next line

            string newline;
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
                for (int i = 0; i < str.size()-1; i++){
                    bar = "";
                    for (int x = 0; x<spacing+1; x++){
                        if (i!=str.size()-2){
                            bar+= ' ';
                        }
                    }
                    newline += str[i]+bar;
                }
                print = "| " + newline + " |";
                outputfile<<print<<std::endl;
            }
        
            leftover = width- words[i].size()-1;
            line = words[i]+" ";


            if (words.size() - 1 == i){ // If it is the last word.
                
                line = "| "+words[i];
                for (int left = 0; left<=leftover; left++){
                    line += ' ';
                }
                line = line+ " |";
                outputfile<<line<<std::endl;
            }


        }
         
    }
    outputfile<<boxline<<std::endl;
    return "";
    }
    */