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
        cout << "for: " << c << '\n';
    	if (c == '('){
    		st.push(score);
    		score = 0;
    	}
    	else{
            st.show();
    		score = st.pop() + max(score*2,1);
            cout << "score:" << score << '\n';
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