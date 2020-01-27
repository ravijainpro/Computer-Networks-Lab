#include <iostream>

using namespace std;

//If generator polynomial is of length n then append (n-1) zeros in the data at the end.

int EXOR(int x, int y) {
    if((x==1 && y==1) || (x==0 && y==0)) {
        return 0;
    }
    else {
        return 1;
    }
}

int *encoder(int data[], int generator[], int generator_len, int data_len) {
    int data_cpy[data_len+generator_len-1];
    for(int k=0; k<data_len+generator_len-1; k++) {
        data_cpy[k]=data[k];
    }
    while(true) {
        int pos=0;
        int i;    
        for(i=0; i<data_len; i++) {
            if(data_cpy[i]==1) {
                pos=i;
                 break;
            }
        }
        if(i==data_len) {
            break;
        }
        for(int j=0; j<generator_len; j++) {
            data_cpy[pos]=EXOR(data_cpy[pos],generator[j]);
            pos++;
        }
        
    }
    for(int k=data_len; k<data_len+generator_len-1; k++) {
        cout << "\n"<< data[k]<<"\n";
        data[k]=data_cpy[k];
    }
    return data;
}

int decoder(int data[], int generator[], int generator_len, int data_len) {
    while(true) {
        int pos=0;
        int i;    
        for(i=0; i<data_len; i++) {
            if(data[i]==1) {
                pos=i;
                 break;
            }
        }
        if(i==data_len) {
            break;
        }
        for(int j=0; j<generator_len; j++) {
            data[pos]=EXOR(data[pos],generator[j]);
            pos++;
        }
    }
    int check=0;
    for(int k=0; k<data_len+generator_len-1; k++) {
        if(data[k]==1) {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int generator_len, data_len;
    cout << "Enter Generator Length\n";
    cin >> generator_len;
    int *generator = new int[generator_len];
    cout << "Enter generator\n";
    for(int i=0; i<generator_len; i++) {
        cin >> generator[i];
    }
    cout << "Enter Data Length\n";
    cin >> data_len;
    int *data = new int[data_len+generator_len-1];
    cout << "Enter Data\n";
    for(int i=0; i<data_len+generator_len-1; i++) {
        int temp;
        if(i<data_len) {
            cin >> temp;
            while(temp!=0 && temp!=1) {
                cout << "Invalid Bit Entered..Re-enter the correct value: \n";
                cin >> temp;
            }
            data[i]=temp;
        }
        else {
            data[i]=0;
        }
    }
    int *encoded_data=new int[data_len+generator_len-1];
    encoded_data=encoder(data, generator, generator_len, data_len);
    cout << "Encoded data value is: ";
    for(int i=0; i<data_len+generator_len-1; i++) {
        cout << encoded_data[i];
    }
    if(decoder(encoded_data, generator, generator_len, data_len)==1) {
        cout << "\nReceived data is good to go!!\n";
    }
    else {
        cout << "\nReceived data is corroupted!!\n";
    }
    return 0;
}
