#include <iostream>
using namespace std;
int main() {
    // Write C++ code here
    int n;
    cin >> n;
    int a[100];
    int count = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(a[i] == a[j]){
                count++;
            }
        }
    }
    cout << count;
    return 0;
}
