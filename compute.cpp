
#include "compute.hpp"
#define LEN 5
using namespace std;

// find start time
void locateInitialDate(std::chrono::system_clock::time_point &start) {
	// go back to last year
	start = start - std::chrono::hours(24*365); // subtract 1 year
    start = start + std::chrono::hours(15);
	time_t start_time = std::chrono::system_clock::to_time_t(start); // transform to time_t
	struct tm *ptm; // transfrom to struct tm
	ptm = gmtime(&start_time);
	start = start + std::chrono::hours((7 - ptm->tm_wday) * 24); // find first Sunday after the start day
	
	// output for checking
	// start_time = std::chrono::system_clock::to_time_t(start); // here we found the start date
	// char *time_str = ctime(&start_time);
	// string res(time_str);
	// res = res.substr(0, res.length() - 1) + " +0000";
	// cout<< "Start date: " << res <<endl;
}

void printTimestamp(std::chrono::system_clock::time_point &start) {
    time_t start_time = std::chrono::system_clock::to_time_t(start); // here we found the start date
    char *time_str = ctime(&start_time);
    string res(time_str);
    res = res.substr(0, res.length() - 1) + " +0000";
    for(char &c : res) {
        c = c == ' ' ? '#' : c;
    }
    // size_t last_colon = res.find_last_of(':');
    // res = res.substr(0, last_colon) + res.substr(last_colon + 3);
    for(int i = 0; i < 50; i ++) {
        cout<< res <<endl;
    }
}



int main(int argc, char * argv[]) {
    // concatenate words that need to display
    string toDisplay = "";
    for(int i = 1; i < argc; i ++) {
        if(i != 1) toDisplay += " ";
        toDisplay += argv[i];
    }
    // cout << toDisplay << endl; 

    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    locateInitialDate(start);

    vector<vector<char>> boxes;
    vector<int> boxCode;
    for(int i = 0; i < toDisplay.length(); i ++) {
        vector<int> boxCode = dict[toDisplay[i]];

        for(int num: boxCode) {
            // add one day 
            // Sunday
            start += std::chrono::hours(24);
            // Monday
            if(rep.find(num) != rep.end()) {
                // already calculated
                boxes.push_back(rep[num]);
                for(auto c : rep[num]) {
                    if(c != ' ') printTimestamp(start);
                    start += std::chrono::hours(24);
                }
                // Saturday
                start += std::chrono::hours(24);
                // Sunday
            }
            else {
                int cur_num = num;
                int counter = 0;
                vector<char> cur_rep;
                while(++counter <= LEN) {
                    if(num%2 == 1) printTimestamp(start);
                    cur_rep.push_back(num%2 == 1 ? '|' : ' ');
                    num = num >> 1;
                    start += std::chrono::hours(24);
                }
                // Saturday
                boxes.push_back(cur_rep);
                rep[cur_num] = cur_rep;
                start += std::chrono::hours(24);
                // Sunday
            }
        }
        boxes.push_back({' ', ' ', ' ', ' ', ' '});
        start += std::chrono::hours(24 * 7);
    }

    // for(int j = 0; j < LEN; j ++) {
    //     for(int i = 0; i < boxes.size(); i ++) {
    //         cout << boxes[i][j];
    //     }
    //     cout<<endl;
    // }
    return 0;
}