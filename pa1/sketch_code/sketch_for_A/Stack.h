#include <iostream>

class Stack{
private:
    int size;
    char array[1000];
public:
    Stack(){ //constructor
        size = -1;
        for (int i = 0; i < 1000; i++){
            array[i] = 0;
        }
    }
    void push(int element){
        array[++size] = element;
    }

    int pop(){
        if (!isEmpty()){
            return array[size--];
        }else{
            return -1;
        }
    }

    int isEmpty(){
        if (size <= -1){
            return 1;
        }else{
            return 0;
        }
    }
};