#include <iostream>

using namespace std;

int len_redundant(int data[], int data_len) {
    //2^r >= m + r +1
    int r=0,m=data_len;
    while(pow(2,r) < m+r+1) {
        r++;
    }
    return r;
}

int look_up(int to_return[], int i) {
    
}

int *hamming_gen(int data[], int data_len) {
    int len_redundant=len_redundant(data,data_len);
    int *to_return=new int[data_len+len_redundant];
    int count=0;
    for(int i=0; i<data_len+len_redundant; i++) {
        if(i%2==0) {
            count++;
            to_return[pow(2,i)]=-1;
            to_return[pow(2,i)]=look_up(to_return,i);
            //To continue...
        }
    }
    
}

int main()
{
    int data_len=0;
    cout << "Enter the length of Data\n";
    cin >> data_len;
    cout << "Enter the data bit by bit\n";
    int *data = new int[data_len];
    for(int i=0; i<data_len; i++) {
        cin >> data[i];
    }
    
    
    return 0;
}
