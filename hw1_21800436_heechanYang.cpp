#include <iostream>
#include <cstring>
#define capacity 31
// #include "MinPriority.h"

using namespace std;

typedef struct{
    string name;
    float score;
}Element;

void printMenu();
char chooseMenu();
Element scanElement();
void insert(Element *a, int &i, Element newElement);
void decreaseScore(Element *a, int count);
int decrease(Element *a, int i, float newScore);
void swap(Element *a, Element *b);
void extractMin(Element *a, int &i);
void minHeapify(Element *a, int size, int i);
void print(Element *a, int size);

int main(){
    Element heap[capacity];
    int count = 0;

    do{
        printMenu();
        switch(toupper(chooseMenu())){
            case 'I':
                insert(heap, count, scanElement());
                break;
            case 'D':
                if(count <= 0){
                    cout << "=> No data to delete" << endl << endl << endl;
                    continue;
                }
                extractMin(heap, count);
                break;
            case 'C':
                if(count <= 0){
                    cout << "=> No data to decrease" << endl << endl << endl;
                    continue;
                }
                decreaseScore(heap, count);
                break;
            case 'P':
                if(count <= 0){
                    cout << "=> No data to print" << endl << endl << endl;
                    continue;
                }
                print(heap, count);
                break;
            case 'Q':
                cout << "=> Thank you, Bye!";
                return 0;
            default:
                cout << "=> no such menu" << endl << endl << endl;
                break;
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
    
    while(1){
        cout << "Enter name of element: ";
        cin >> newElement.name;
        if(newElement.name.length() > 10){
            cout << "=> name too long, size should be below 10" << endl << endl;
        }else{
            break;
        }
    }
    
    cout << "Enter key value of element: ";
    cin >> newElement.score; 

    return newElement;
}

void insert(Element *a, int &i, Element newElement){
    a[++i] = newElement;

    decrease(a, i, newElement.score);

    cout << "=> New element [" << newElement.name << ", " << newElement.score << "] is inserted." << endl << endl << endl;
}

void decreaseScore(Element *a, int count){
    int index;
    float score;

    cout << "Enter index of element: ";
    cin >> index;

    if(index > count){
        cout << "=> no data in index #" << index << endl << endl << endl;
    }else{
        cout << "Enter new key value: ";
        cin >> score;

        if(decrease(a, index, score)==1){
            cout << "=> index #" << index << " element decreased to " << score << endl << endl << endl;
        }
    }
}

int decrease(Element *a, int i, float newScore){
    int index = i;
    
    if(newScore > a[index].score){
        cout << "=> Error : new key is bigger than current key" << endl << endl << endl;;
        return 0;
    }else{
        a[index].score = newScore;
        while(index > 1 && a[index/2].score > a[index].score){
            swap(a[index/2], a[index]);
            index = index/2;
        }
        return 1;
    }
    return 1;
}

void swap(Element *a, Element *b){
    Element tmp = *a;
    *a = *b;
    *b = tmp;
}

void extractMin(Element *a, int &i){
    Element min;
    if(i < 1){
        cout << "=> Error : heap overflow" << endl << endl << endl;
    }else{
        min = a[1];
        a[1] = a[i];
        i--;
        minHeapify(a, i, 1);
    }
    cout << "=> [" << min.name << ", " << min.score << "] is deleted." << endl << endl << endl;
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