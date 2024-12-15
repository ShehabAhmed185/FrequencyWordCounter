#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;



queue<string>basedParaQue; // this is queue stored based data
queue<string>basedParaQueGlobal; // this is queue stored based global data
string globalFile = "globalData.txt";

class Global {


public:

    
    //////search
    void searchGlobalWord(unordered_map<string, int> frequencies, string word) {
        
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        auto it = frequencies.find(word);
        if (it != frequencies.end()) {
            cout << "The Global frequency of '" << word << "' is: " << it->second << "\n";
        }
        else {
            cout << "Word not found in the paragraph.\n";
        }
    }

    // Function to display the ranking of a word
    void displayGlobalRank(queue<string>q,string word) {
    
        int rank = 0;
        int wordExist = 0;
        while (!q.empty()) {

            rank++;
            if (word == q.front()) {
                cout << "word<" << word << ">has Global rank : " << rank << endl;
                wordExist = 1;
                break;
            }
            q.pop();
        }
        if (wordExist == 0)
            cout << "Word not found in the paragraph.\n";

    }

    bool updateGlobalParagraph(vector<string> vectorHasParagraph, queue<string> &q, string newWord, int indexOfWord, int chooseUpdateWord) {
        // do update : replace word from word user enter it
          //:insert new word in paragraph
          //:delete word user insert it or delete all paragraph words
        queue<string> q2 = q;
        vector<string> v;
        int index = vectorHasParagraph.size() - indexOfWord;
        int realIndex;
        if (chooseUpdateWord == 1) {
            /// update word here
            while (!q.empty())
            {
                v.push_back(q.front());
                q.pop();
            }
            realIndex = v.size() - index;
            v[realIndex-1] = newWord;
            while (!v.empty())
            {
                q.push(v.front());
                v.erase(v.begin());
            }

          
          
       }
        else if (chooseUpdateWord == 2) {
            /// add word here
            while (!q.empty())
            {
                v.push_back(q.front());
                q.pop();
            }

            if (indexOfWord != 0) {
                realIndex = v.size() - index;
                auto it = v.begin() + realIndex - 1;
                v.insert(it, newWord);
            }
            else if (indexOfWord == 0) {
                v.push_back(newWord);

            }
            
            while (!v.empty())
            {
                q.push(v.front());
                v.erase(v.begin());
            }

        }
       

        return true;

    }


    void globalDeleteSentence(queue<string>& queHasParagraph, string wordWantDeleteIt, string fileName) {
        //delete one word user insert it
        // delete all paragraph words

        //// use Data Structures Queue has object basedParaQue because it has All paragraph

        if (true) {
            queue<string> tempQueue;
            queue<string> tempQueue2;
            queue<string> tempQueue3;
            tempQueue = queHasParagraph;
            int count = 0;
            int delWord;
            string frontSentence;
            while (!tempQueue.empty())
            {

                frontSentence = tempQueue.front();
                tempQueue.pop();
                if (frontSentence != wordWantDeleteIt || count > 0) {
                    tempQueue2.push(frontSentence);
                }
                else
                    count++;

            }
            if (count == 0) {
                cout << "sentence not exist in pararaph \n";

            }
            else
                cout << "Sentence '" << wordWantDeleteIt << "' deleted from the frequency list." << "\n \n ";

            tempQueue3 = tempQueue2;
            queHasParagraph = tempQueue2;
            int lineIndex = 0;
            // Remove sentence from the frequency map
            cout << "<<<<< \n";
            while (!tempQueue3.empty()) {
                lineIndex++;
                cout << tempQueue3.front() << " ";
                tempQueue3.pop();
                if (lineIndex > 6) {
                    cout << endl;
                    lineIndex = 0;
                }
            }
            cout << ">>>>> \n";


        }
    }


    queue<string>  globalDeleteSentence(queue<string> &q,queue<string> q2,int number, string fileName, int deleteAll) {
        // delete all paragraph words
        //// use Data Structures Queue has object basedParaQue because it has All paragraph
        
        q = q2;
        return q;
    }




    // Function to count word frequencies
    unordered_map<string, int> globalCountFrequencies(queue<string> words) {
        unordered_map<string, int> frequencies;
        queue<string> q = words;

        while (!q.empty()) {
            frequencies[q.front()] = 0;
            q.pop();
        }
        unordered_map<string, int> ::iterator it;
        while (!words.empty()) {
            it = frequencies.find(words.front());
            if (it != frequencies.end())
                frequencies[words.front()]++;
            words.pop();
        }
        return frequencies;


    }


  



};
// this function read data from file and stored it in a based queue 
queue<string> readFile(string file_name) {
    string file_word;
    fstream input;
    int i = 0;
    input.open(file_name);
    if (input.is_open()) {
        while (!input.eof()) {
            input >> file_word;
            basedParaQue.push(file_word);
            file_word.clear();
        }
        input.close();
    }
    input.open(globalFile);
    if (input.is_open()) {
        while (!input.eof()) {
            input >> file_word;
            basedParaQueGlobal.push(file_word);
            file_word.clear();
        }
        input.close();
    }

    return basedParaQue;
}

//write updated data from datastructer to file
bool writeFile(queue < string> queWriteInFile, string fileName) {
    fstream myFile;
    int lineIndex = 0;
    queue < string> queWriteInGlobalFile = queWriteInFile;
    myFile.open(fileName, ios::out);    //ios::out = clear data then write in file  // ios app = save old data
    if (myFile.is_open()) {

        while (!queWriteInFile.empty())
        {
            lineIndex++;
            myFile << queWriteInFile.front() << " ";
            queWriteInFile.pop();
            if (lineIndex >= 8) {
                myFile << endl;
                lineIndex = 0;
            }
        }

        myFile.close();

    }

    ///write in global file
    myFile.open(globalFile, ios::app);    //ios::out = clear data then write in file  // ios app = save old data
    if (myFile.is_open()) {

        while (!queWriteInGlobalFile.empty())
        {
            lineIndex++;
            myFile << queWriteInGlobalFile.front() << " ";
            queWriteInGlobalFile.pop();
            if (lineIndex >= 8) {
                myFile << endl;
                lineIndex = 0;
            }
        }

        myFile.close();
        return true;
    }
    return true;
}


// Function to count word frequencies
unordered_map<string, int> countFrequencies(queue<string> words) {
    unordered_map<string, int> frequencies;
    queue<string> q = words;

    while (!q.empty()) {
        frequencies[q.front()] = 0;
        q.pop();
    }
    unordered_map<string, int> ::iterator it;
    while (!words.empty()) {
        it = frequencies.find(words.front());
        if (it != frequencies.end())
            frequencies[words.front()]++;
        words.pop();
    }
    return frequencies;


}


string searchWord(unordered_map<string, int> frequencies) {
    string word;
    cout << "Enter a word to search: ";
    cin >> word;
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    auto it = frequencies.find(word);
    if (it != frequencies.end()) {
        cout << "The Local frequency of '" << word << "' is: " << it->second << "\n";
    }
    else {
        cout << "Word not found in the paragraph.\n";
    }
    return word;
}


//
// Function to display the ranking of a word
void displayRank(queue<string>q,string word) {
    
    int rank = 0;
    int wordExist = 0;
    while (!q.empty()) {

        rank++;
        if (word == q.front()) {
            cout << "word<" << word << ">has local rank : " << rank << endl;
            wordExist = 1;
            break;
        }
        q.pop();
    }
    if (wordExist == 0)
        cout << "Word not found in the paragraph.\n";

}

void displayParagraph(queue<string>que) {

    int i = 1;
    int count = 0;
    while (!que.empty())
    {
        cout << i << ") " << que.front() << "       ";
        que.pop();
        i++;
        count++;
        if (count > 5) {
            cout << endl;
            count = 0;
        }
    }

}
// Function to update the paragraph -> one word
bool updateParagraph(vector<string>& vectorHasParagraph, string newWord, int indexOfWord, int chooseUpdateWord) {
    // do update : replace word from word user enter it
      //:insert new word in paragraph
      //:delete word user insert it or delete all paragraph words
    if (chooseUpdateWord == 1) {
        /// update word here
        vectorHasParagraph.at(indexOfWord - 1) = newWord;

    }
    else if (chooseUpdateWord == 2) {
        /// add word here
        if (indexOfWord != 0) {
            auto it = vectorHasParagraph.begin() + indexOfWord - 1;
            vectorHasParagraph.insert(it, newWord);
        }
        else if (indexOfWord == 0) {
            vectorHasParagraph.push_back(newWord);
        }
        else
            return false;
    }

    return true;

}

// Function to update the paragraph -> many words
bool updateParagraph(vector<string>& vectorHasParagraph, string newWord[10], int arr[10], int indexUpdateArr, int chooseUpdateWord) {
    // do update : replace word from word user enter it
      //:insert new word in paragraph
      //:delete word user insert it or delete all paragraph words
    if (chooseUpdateWord == 1) {
        /// update word here
        for (size_t i = 0; i < indexUpdateArr; i++)
        {
            vectorHasParagraph.at(arr[i] - 1) = newWord[i];
        }

    }
    else if (chooseUpdateWord == 2) {
        /// add words here
        /*auto it = vectorHasParagraph.begin() + indexOfWord - 1;
        vectorHasParagraph.insert(it, newWord);
        */
        auto it = vectorHasParagraph.begin();
        for (size_t i = 0; i < indexUpdateArr; i++)
        {
            it = vectorHasParagraph.begin() + arr[i] - 1;
            vectorHasParagraph.insert(it, newWord[i]);
        }

    }
    return true;

}


void deleteSentence(queue<string>& queHasParagraph, string wordWantDeleteIt, string fileName) {
    //delete one word user insert it
    // delete all paragraph words

    //// use Data Structures Queue has object basedParaQue because it has All paragraph

    if (true) {
        queue<string> tempQueue;
        queue<string> tempQueue2;
        queue<string> tempQueue3;
        tempQueue = queHasParagraph;
        int count = 0;
        int delWord;
        string frontSentence;
        while (!tempQueue.empty())
        {

            frontSentence = tempQueue.front();
            tempQueue.pop();
            if (frontSentence != wordWantDeleteIt || count > 0) {
                tempQueue2.push(frontSentence);
            }
            else
                count++;

        }
        if (count == 0) {
            cout << "sentence not exist in pararaph \n";

        }
        else
            cout << "Sentence '" << wordWantDeleteIt << "' deleted from the frequency list." << "\n \n ";

        tempQueue3 = tempQueue2;
        queHasParagraph = tempQueue2;
        int lineIndex = 0;
        // Remove sentence from the frequency map
        cout << "<<<<< \n";
        while (!tempQueue3.empty()) {
            lineIndex++;
            cout << tempQueue3.front() << " ";
            tempQueue3.pop();
            if (lineIndex > 6) {
                cout << endl;
                lineIndex = 0;
            }
        }
        cout << ">>>>> \n";


    }

}



queue<string>  deleteSentence(queue<string>& queHasParagraph, string wordWantDeleteIt, string fileName, int deleteAll) {
    // delete all paragraph words
    //// use Data Structures Queue has object basedParaQue because it has All paragraph
    queue<string> queDelete;
    queDelete = queHasParagraph;
    while (!queHasParagraph.empty()) {
        queHasParagraph.pop();
    }
    queHasParagraph.push(" ");
    return queDelete;
}


bool compareBySecond(const pair<std::string, int>& a, const pair<std::string, int>& b)
{
    return a.second > b.second;
}

void sortTextFreq(const string& filename) {
    unordered_map<string, int> textMap;
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Error: Unable to open input file." << endl;
        return;
    }
    string word;
    while (inputFile >> word) {
        textMap[word]++;
    }


    inputFile.close();


    vector<pair<string, int>> textVector(textMap.begin(), textMap.end());


    sort(textVector.begin(), textVector.end(), compareBySecond);


    cout << "Sorted words according to frequency:" << endl;
    for (const auto& it : textVector) {
        cout << it.first << ": " << it.second << " occurrences" << endl;
    }
}



int main() {
    Global gl;
    queue<string>que;
    vector<string>vec;
    string type;
    string fileName;
    int wantExit = 1;



    cout << "Enter a paragraph (or 'file' to read from a file): ";
    getline(cin, type);

    if (type == "file") {
        cout << "Enter path of your paragraph file \n";
        getline(cin, fileName);
        que = readFile(fileName); // here paragraph word return from readFile function and stored in object que
    }
    else {
        string paragraph;
        cout << "Enter your paragraph \n";
        getline(cin, paragraph);
    }
    queue<string>q1;
    queue<string>q2;
    q1 = basedParaQueGlobal;
    q2 = basedParaQueGlobal;
    queue<string> q = que;
    while (!q.empty())
    {
        basedParaQueGlobal.push(q.front());
        q.pop();
    }

    // searchWord(frequencies);
     //displayRank(que);
    int choice;
    string wordBeDelete;
    int chooseDeleteWord;
    int chooseUpdateWord;
    int indexOfWord;
    int oneWordOrMore;
    string updateWord;
    int indexUpdateArr;
    int indexWordArr[10];
    string newWordArr[10];
    string wordSearch;
    string word;
    int numOfDelete = que.size();
    int chooseGlobal;
    int chooseGlobalSorted;


    unordered_map<string, int> frequencies;
    unordered_map<string, int> globalFrequencies;

    do {
        cout << "\nMenu:\n";
        cout << "1. Display word frequencies\n";
        cout << "2. Search for a word\n";
        cout << "3. Display the ranking of a word\n";
        cout << "4. Update the paragraph\n";
        cout << "5. Delete sentences\n";
        cout << "6. Display Sorted Paragraph\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: \n";
        cin >> choice;
        cout << "\n \n";
        frequencies = countFrequencies(que);
        globalFrequencies = gl.globalCountFrequencies(basedParaQueGlobal);

        switch (choice) {
        case 1:
            cout << "if want display frequencies of local words press 1, for global frequencies press 2 \n\n";
            cin >> chooseGlobal;
            if (chooseGlobal == 1) {
                cout << frequencies.begin()->first;
                for (auto itr = frequencies.begin(); itr != frequencies.end(); itr++) {
                    cout << itr->first << " -> " << itr->second << endl;
                }
            }
            else {
                    cout << globalFrequencies.begin()->first;
                    for (auto itr = globalFrequencies.begin(); itr != globalFrequencies.end(); itr++) {
                        cout << itr->first << " -> " << itr->second << endl;
                }
            }
            break;
        case 2:
            wordSearch=  searchWord(frequencies);
            gl.searchGlobalWord(globalFrequencies, wordSearch);
            break;
        case 3:
            cout << "Enter word you want display rank \n";
            cin >> word;
            displayRank(que,word);
            gl.displayGlobalRank(basedParaQueGlobal,word);
            break;
        case 4:
            cout << "If Want Update {Paragraph} press 1 ,want add word in {Paragraph} press 2  \n";
            cin >> chooseUpdateWord;
            if (chooseUpdateWord == 1) {
                /// update word here
                cout << "\n If want update one word press 1 , want Update many words press 2\n\n ";
                cin >> oneWordOrMore;


                displayParagraph(que);

                /// insert Paragraph from que to vec
                while (!que.empty())
                {
                    vec.push_back(que.front());
                    que.pop();
                }


                if (oneWordOrMore == 1) {
                    cout << "\n \n \n";
                    cout << "\n \n \n";
                    cout << "Enter index of word you want Update it \n \n";
                    cin >> indexOfWord;
                    cout << "Enter new Word of word you want Update it \n \n";
                    cin >> updateWord;


                    updateParagraph(vec, updateWord, indexOfWord, chooseUpdateWord);
                    gl.updateGlobalParagraph(vec, basedParaQueGlobal, updateWord, indexOfWord, chooseUpdateWord);

                }
                else if (oneWordOrMore == 2) {
                    cout << "\n\nEnter num of word you want update \n\n";
                    cin >> indexUpdateArr;
                    for (size_t i = 0; i < indexUpdateArr; i++)
                    {
                        cout << i + 1 << ") Enter Index of Word you want update \n\n";
                        cin >> indexWordArr[i];
                    }

                    for (size_t i = 0; i < indexUpdateArr; i++)
                    {
                        cout << i + 1 << ") Enter Update Word arranged  \n\n";
                        cin >> newWordArr[i];
                    }

                    updateParagraph(vec, newWordArr, indexWordArr, indexUpdateArr, chooseUpdateWord);

                }


                /// insert Paragraph from vec to que
                while (!vec.empty())
                {
                    que.push(vec.front());
                    vec.erase(vec.begin());
                }


                ////// here end of update 
            }


            else if (chooseUpdateWord == 2) {
                ///start add words here
                cout << "\n\n If Want add one word press 1 ,want add many words  press 2  \n";
                cin >> oneWordOrMore;
                // chooseUpdateWord
                // 
                  //add one word
                displayParagraph(que);

                while (!que.empty())
                {
                    vec.push_back(que.front());
                    que.pop();
                }
                if (oneWordOrMore == 1) {


                    cout << "\n \n \n";
                    cout << "\n \n \n";
                    cout << "Enter index of word you want add before it if want add in End press 0\n \n";
                    cin >> indexOfWord;
                    cout << "Enter new Word of word you want add before it \n \n";
                    cin >> updateWord;
                    updateParagraph(vec, updateWord, indexOfWord, chooseUpdateWord);


                    /// insert Paragraph from vec to que


                }
                else if (oneWordOrMore == 2) {
                    // add many words
                    cout << "\n\nEnter num of word you want update \n\n";
                    cin >> indexUpdateArr;
                    for (size_t i = 0; i < indexUpdateArr; i++)
                    {
                        cout << i + 1 << ") Enter Index of Word you want update \n\n";
                        cin >> indexWordArr[i];
                    }

                    for (size_t i = 0; i < indexUpdateArr; i++)
                    {
                        cout << i + 1 << ") Enter Update Word arranged  \n\n";
                        cin >> newWordArr[i];
                    }

                    updateParagraph(vec, newWordArr, indexWordArr, indexUpdateArr, chooseUpdateWord);



                }


                while (!vec.empty())
                {
                    que.push(vec.front());
                    vec.erase(vec.begin());
                }

                /////end of add words
            }
            /// <summary>
            /// /end of case 4
            /// </summary>
            /// <returns></returns>
            break;

        case 5:
            displayParagraph(que);
            cout << "\n\n";
            cout << "If Want delete one Word press 1 ,want delete many word press 2  \n";
            cin >> chooseDeleteWord;
            if (chooseDeleteWord == 1) {
                cout << "Enter word you want delete it \n";
                cin >> wordBeDelete;
                deleteSentence(que, wordBeDelete, fileName);
                gl.globalDeleteSentence(basedParaQueGlobal, wordBeDelete, fileName);
            }
            else if (chooseDeleteWord == 2) {
                deleteSentence(que, wordBeDelete, fileName, 1);
                gl.globalDeleteSentence(basedParaQueGlobal,q2, numOfDelete,fileName, 1);
                cout << "Paragraph Deleted successfully \n \n";
            }
            else
                cout << "Wrong input \n\n";

            break;

        case 6:

            cout << "If want display local Sorted Frequencise press 1 , for global Frequencise press 2 \n\n";
            cin >> chooseGlobalSorted;
            if(chooseGlobalSorted == 1)
            sortTextFreq(fileName);
            else
           // gl.globalSortTextFreq(globalFile);
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);
    writeFile(que, fileName);

    fileName = "";
    while (!que.empty()) {
        que.pop();
    }

    return 0;
}