#include <iostream>
#include <string>
#include <sstream>
using namespace std;
class Stack{
private:
    int top, s[1000];
public:
    Stack(){
        top=-1;
    };
    void push(int element){
        top++;
        s[top]=element;
    }
    int pop(){
        int tem=s[top];
        top--;
        return tem;
        }

    int isEmpty(){
        if(top==-1){
            return true;
        }
        else{
            return false;
        }
    }
};

void SolveA() {
    string s;
    Stack st;
    for (int i = 0; i < 1000; i++) {
        getline(cin, s);
        string cmd;
        int num;
        stringstream ss(s);
        ss >> cmd >> num;
        if (cmd=="pop"){
            if(st.isEmpty()){
                cout<<"false"<<endl;
            }else{
                cout<<st.pop()<<endl;
            }
        }
        if (cmd=="push"){
            st.push(num);
        }
        if(cin.eof()){
            break;
        }
        
    }
}


int main() {
    SolveA();
    return 0;
}

