#include <iostream>
#include<algorithm>

using namespace std;

int main()
{
    int input[10]={0},rem=0,sent=0,cap=0,orate=0;
    cout<<"Enter the bucket size: ";
    cin>>cap;
    cout<<"Enter the flowrate: ";
    cin>>orate;
    int i=0,choice;
    do{
        cout<<"Data entered in second "<<i+1<<": ";
        cin>>input[i];
        if(input[i]>cap)
        {
            cout<<"Bucket overflow"<<endl;
            exit(0);
        }
        i++;
        cout<<"Enter 1 for continue 0 for stop: ";
        cin>>choice;
    }while(choice);
    
    int n = i,drop=0,x=0;
    cout<<"Len "<<n<<endl;
    cout<<"\tSecond\t"<<"    Recieved\t"<<"Sent\t"<<"Dropped\t"<<"     Remaining\n";
    for(int i=0;rem||i<n;i++)
    {
        cout<<"\t "<<i+1<<"\t";
        cout<<"\t"<<input[i]<<"\t";
        cout<<" "<<min((input[i]+rem),orate)<<"\t";
        x = input[i]+rem-orate;
        if(x>0)
        {
            if(x>cap)
            {
                rem = cap;
                drop = x-cap;
            }
            else{
                rem = x;
                drop = 0;
            }
        }
        else
        {
            rem = 0;
            drop = 0;
        }
        cout<<"   "<<drop<<"\t";
        cout<<"\t"<<rem<<"\n";
    }
}