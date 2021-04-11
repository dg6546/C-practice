#include <iostream>
#include <string>

using namespace std;

class Stack{
private:
    int size;
    int array[1000];
public:
    Stack(){ //constructor
        size = -1;
        for (int i = 0; i < 1000; i++){
            array[i] = -1;
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

    void show(){
        string s = "";
        for(int i = 0; i < size+1; i++){
            s += to_string(array[i]);
            s += " ";
        }
        cout << "Stack: "<< s << '\n';
    }
};

void SolveC(){
    string s;
    int score = 0;
    Stack st;
    cin >> s;
    for(char c:s){
    	if (c == '('){
    		st.push(score);
    		score = 0;
    	}
    	else{
    		score = st.pop() + max(score*2,1);
    	}
    }
    cout << score;
    /* your code starts here */
}

int main() {
    SolveC();
    return 0;
}