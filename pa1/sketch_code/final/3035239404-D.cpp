#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

void SolveD () {
    /* your code starts here */
    std::vector<string> v;
    std::vector<string>::iterator it;
    string inp;
    string s;
    string inp2;
    int c;
    getline(cin, inp2);
    c = stoi(inp2);
    getline(cin, inp);
    stringstream ss;
    ss << inp;
    while(ss >> s){
    	it = find(v.begin(), v.end(), s);
    	if(it != v.end()){
    		c--;
    	}else{
    		v.push_back(s);
    	}

    }
    cout << c;
}
int main() {
    SolveD();
    return 0;
}