#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;

void SolveC(){
    string s;
    int score = 0;
    Stack st;
    cin >> s;
    for(char c:s){
        cout << "for:" << c << '\n';
    	if (c == '('){
    		st.push(score);
            st.show();
    		score = 0;
            cout << "score = 0" << '\n';
    	}
    	else{
            st.show();
            int popped = st.pop();
            cout << "score = " << popped << "+" << "max(" << score*2 << ",1)"  << " = ";
    		score = popped + max(score*2,1);
            cout << score << '\n';
            st.show();
    	}
    }
    cout << score;
    /* your code starts here */
}

int main() {
    SolveC();
    return 0;
}