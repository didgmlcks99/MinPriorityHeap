#include <iostream>
#define capacity 31
// #include "MinPriority.h"

using namespace std;

typedef struct{
    char name[10];
    float score;
}Element;

void printMenu();
char chooseMenu();
Element scanElement();
void insert(Element *a, int &i, Element newElement);
void decreaseScore(Element *a);
void decrease(Element *a, int i, float newScore);
void swap(Element *a, Element *b);
void extractMin(Element *a, int &i);
void minHeapify(Element *a, int size, int i);
void print(Element *a, int size);

int main(){
    Element heap[capacity];
    int count = 0;

    do{
        printMenu();
        switch(chooseMenu()){
            case 'I':
                insert(heap, count, scanElement());
                break;
            case 'D':
                extractMin(heap, count);
                break;
            case 'C':
                decreaseScore(heap);
                break;
            case 'P':
                print(heap, count);
                break;
            case 'Q':
                cout << "Thank you, Bye!";
                return 0;
        }
    }while(1);

    return 0;
}

void printMenu(){
    cout << "*********** MENU ****************" << endl;
    cout << "I : Insert new element into queue." << endl;
    cout << "D : Delete element with smallest key from queue." << endl;
    cout << "C : Decrease key of element in queue." << endl;
    cout << "P : Print out all elements in queue." << endl;
    cout << "Q : Quit" << endl;
}

char chooseMenu(){
    char input;
    cout << endl << "Choose menu: ";
    cin >> input;

    return input;
}

Element scanElement(){
    Element newElement;
    
    cout << "Enter name of element: ";
    cin >> newElement.name;

    cout << "Enter key value of element: ";
    cin >> newElement.score;

    return newElement;
}

void insert(Element *a, int &i, Element newElement){
    a[++i] = newElement;

    decrease(a, i, newElement.score);

    cout << "New element [" << newElement.name << ", " << newElement.score << "] is inserted." << endl << endl << endl;
}

void decreaseScore(Element *a){
    int index;
    float score;

    cout << "Enter index of element: ";
    cin >> index;

    cout << "Enter new key value: ";
    cin >> score;

    decrease(a, index, score);

    cout << endl << endl << endl;
}

void decrease(Element *a, int i, float newScore){
    int index = i;
    
    if(newScore > a[index].score){
        cout << "Error : new key is bigger than current key" << endl;
    }else{
        a[index].score = newScore;
        while(index > 1 && a[index/2].score > a[index].score){
            swap(a[index/2], a[index]);
            index = index/2;
        }
    }
}

void swap(Element *a, Element *b){
    Element tmp = *a;
    *a = *b;
    *b = tmp;
}

void extractMin(Element *a, int &i){
    Element min;
    if(i < 1){
        cout << "Error : heap overflow";
    }else{
        min = a[1];
        a[1] = a[i];
        i--;
        minHeapify(a, i, 1);
    }
    cout << "[" << min.name << ", " << min.score << "] is deleted." << endl << endl << endl;
}

void minHeapify(Element *a, int size, int i){
    int leftIndex = 2*i;
    int rightIndex = (2*i)+1;

    int smallest;

    if(leftIndex <= size && a[leftIndex].score<a[i].score){
        smallest = leftIndex;
    }else{
        smallest = i;
    }

    if(rightIndex <= size && a[rightIndex].score<a[smallest].score){
        smallest = rightIndex;
    }

    if(smallest != i){
        swap(a[i], a[smallest]);
        minHeapify(a, size, smallest);
    }
}

void print(Element *a, int size){
    for(int i=1; i<=size; i++){
        cout << "[" << a[i].name << ", " << a[i].score << "] ";
    }
    cout << endl << endl << endl;
}