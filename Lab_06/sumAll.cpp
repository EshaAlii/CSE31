#include<iostream>

using namespace std;

int main(){
    int number;
    int even_sum = 0;
    int odd_sum = 0;
    int temp;
    
    while (number != 0){
        cout << "Please enter a number: ";
        cin >> number;

        temp = number;

        if (number%2 == 0){
            even_sum = even_sum + number;
        }
        else{
            odd_sum = odd_sum + number;
        }
    }

    cout << "Even sum: " << even_sum << endl;
    cout << "Odd sum: " << odd_sum << endl;

    return 0;

}