
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

void compute_squares(int n, int a[], int b[]){
    for (int i = 0; i < n; ++i)
    {
        *(b+i) = *(a+i)**(a+i);
        //*(a+i);
        cout<<*(b+i)<<" ";
    }

}

int main(){
    int n = 5;
    int a[n] = {1,2,3,4,5};
    int b[n];
    int *ptr = a;
    for (int i = 0; i < n; *ptr=*(a),++i){
        *ptr = *a;
        //cout<<*(a+i)<<" ";
    }
    compute_squares(n,a,b);
}