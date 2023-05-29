// CREATING A TREE OF ANIMALS AND USING QUESTIONS TO DIFFERENTIATE THEM AND ORGANIZE THE TREE
#include "guessingGame.h"

#include <iostream>
#include <string>

using namespace std;

//the structure of every node in the binary tree
struct AnimalNode {
 string guess = ""; //the name of an animal to guess
 string question = ""; //a question to ask the user
 AnimalNode * yesAnswer = nullptr; //pointer to the yes animalNode
 AnimalNode * noAnswer= nullptr; //pointer to the no animalNode
};

//function will go through tree until it reaches a guess node
AnimalNode* guess(AnimalNode * nodePtr){
    //declare all variables
    string ans;

    //base case: if we are at a guess node (its not an empty string), return the guess
    if (nodePtr->guess != ""){
        return nodePtr;
    }

    //otherwise ask the question and get the answer
    cout << nodePtr->question << endl;
    getline(cin, ans);

    //if the first letter of the answer didn't start with a y or n, read in input again
    while (toupper(ans[0]) != 89 && toupper(ans[0]) != 78){
        cout << "Please enter Y or N" << endl;
        getline(cin, ans);
    }

    //if they answered yes, move down that part of the tree
    if (toupper(ans[0]) == 89){
        return guess(nodePtr->yesAnswer);
    }
    //otherwise go down the no part of the tree
    else{
        return guess(nodePtr->noAnswer);
    }
} //guess()

//function will add the new information to the tree
void splitNode(AnimalNode * nodePtr){
    //declare all variables
    string userAnimal, userQuestion,ans;

    //ask all the information and store the answers
    cout << "What animal were you thinking of?" << endl;
    getline(cin,userAnimal);
    cout << "Type a question that would differentiate these two things" << endl;
    getline(cin, userQuestion);
    cout << "For a " << userAnimal << " is the answer 'Y' or 'N'" << endl;
    getline(cin, ans);

    //error processing
    while (toupper(ans[0]) != 89 && toupper(ans[0]) != 78){
        cout << "Please enter Y or N" << endl;
        getline(cin, ans);
    }

    //create the two new animal nodes
    nodePtr->yesAnswer = new AnimalNode;
    nodePtr->noAnswer = new AnimalNode;

    //set the current nodePtr to userQuestion
    nodePtr->question = userQuestion;

    //if the answer was yes
    if(toupper(ans[0]) == 89){
        //go to no pointer and the guess node in the new pointer, set it equal to the current guess
        nodePtr->noAnswer->guess = nodePtr->guess;
        //go to new guess animal node that the yes answer was pointing to and set it equal to the new animal
        nodePtr->yesAnswer->guess = userAnimal;
    }
    //otherwise do the opposite
    else{
        nodePtr->yesAnswer->guess = nodePtr->guess;
        nodePtr->noAnswer->guess = userAnimal;
    }
    //set the current guess to an empty string, because it now has a question
    nodePtr->guess = "";
}//splitNode()

//will delete all the dynamically allocated memory
void deleteTree(AnimalNode *nodePtr){
    //base case
    if (nodePtr == nullptr)
        return;
    //if you are at a leaf node delete the node
    if(nodePtr->yesAnswer == nullptr && nodePtr->noAnswer == nullptr){
        delete nodePtr;
    }
    //otherwise run the program again with the yes answer
    deleteTree(nodePtr->yesAnswer);
    //when there are no yes answers left go through the no answers
    deleteTree(nodePtr->noAnswer);

    //finally delete the root node
    delete nodePtr;
}//delteTree()

int main(){
    //declare all variables
    string ans, keepGoing;
    AnimalNode *rootPtr = new AnimalNode;
    rootPtr->guess = "lizard";

    //Print instructions
    cout << "Think of an animal and hit enter to begin" << endl;
    cin.ignore();

    do{
        //call the guess function and store it in a temporary pointer
        AnimalNode *tempPtr = guess(rootPtr);
        //ask if it's their animal
        cout << "Are you thinking of a " << tempPtr->guess << ": Y or N" << endl;
        getline(cin, ans);

        //error processing
        while (toupper(ans[0]) != 89 && toupper(ans[0]) != 78){
            cout << "Please enter yes or no" << endl;
            getline(cin, ans);
        }

        //if it's not their animal, add their anumal and question to the tree
        if(toupper(ans[0]) == 78){
            splitNode(tempPtr);
        }

        //ask them if they want to play the game again
        cout << "Let me guess your animal again? 'Y' or 'N'" << endl;
        getline(cin, keepGoing);
    }while(toupper(keepGoing[0]) == 89); //run as long as the user says so

    return 0;
} //main()
