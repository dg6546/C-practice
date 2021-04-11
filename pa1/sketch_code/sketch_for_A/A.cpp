#include <iostream>
#include <string>
#include <sstream>


using namespace std;


class Stack{
private:
    int size;
    int array[1000];
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





void SolveA() {
    string s;
    string temp;
    string out = "";
    string op = "";
    string data_temp = "-1";
    Stack *st = new Stack();
    stringstream ss;
    bool error = false;
    int pop_temp;
    int data;
    for (int i = 0; i < 1000; i++) {
        getline(cin, s);
        //cout << s << '\n';
            ss << s;
            ss >> op >> data_temp;
        ss.str( std::string() );
        ss.clear();
        data = stoi(data_temp); //convert input data into integer
        //cout << op<<" + " << data << '\n';
        if (op =="push"){
            st->push(data);
        }
        else if (op == "pop"){
            pop_temp = st->pop();
            if (pop_temp == -1){
                out += "false ";
                error = true;
            }else{
                out += to_string(pop_temp) + " ";
            }
        }
        if ( cin.eof() || error )
            break;
    }
    cout << out << '\n';
}

int main() {
    SolveA();
    return 0;
}