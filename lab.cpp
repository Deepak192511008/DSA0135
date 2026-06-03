//Write a program to read in two integers and perform the following operations on them: addition, subtraction, multiplication, division, and modulo.
#include<iostream>
using namespace std;
int main(){
  int a,b;
  cin>>a>>b;
  cout<<"Addition = "<<a+b<<" Subtraction = "<<a-b<<" Multiplication = "<<a*b<<" Division = "<<a/b<<endl;
}
------------
//Write a program to read in three integers and compute the average of the three numbers. Use the assignment operator to store the result in a variable.
#include<iostream>
using namespace std;
int main(){
  int a,b,c;
  cin>>a>>b>>c;
  cout<<"average = "<<(a+b+c)/3<<endl;
}
----------------
//Write a program to read in two integers and determine if they are equal or not.
#include<iostream>
using namespace std;
int main(){
  int a,b;
  cin>>a>>b;
  if(a==b){
    cout<<"They are equal"<<endl;
  }else{
    cout<<"Not equal";
  }
}

--------------------
//Write a program to read in two integers and use the conditional operator to determine which number is greater.
#include<iostream>
using namespace std;
int main(){
  int a,b;
  cin>>a>>b;
  int greater = (a>b)?a:b;
  cout<<greater;
}
-------------
//Write a program to read in two integers and swap their values using the bitwise XOR ope
#include<iostream>
using namespace std;
int main(){
  int a,b;
  cin>>a>>b;
  a=a^b;
  b=a^b;
  a=a^b;
  cout<<"a="<<a<<"b="<<b<<endl;
}
----------
// Write a program to read in a floating-point number and round it to the nearest integer using the floor and ceil functions.
#include <iostream>
#include <cmath>
using namespace std;
int main() {
    double num;
    cout << "Enter a floating-point number: ";
    cin >> num;
    int rounded;
    if (num - floor(num) < 0.5)
        rounded = floor(num);
    else
        rounded = ceil(num);
    cout << "Rounded value: " << rounded;
    return 0;
}
-----------
//Write a program to read in three integers and determine which one is the maximum using the ternary conditional operator.
#include <iostream>
using namespace std;
int main() {
    int num1, num2, num3;   
    cin >> num1 >> num2 >> num3;    
    int maxResult = (num1 > num2) ? ((num1 > num3) ? num1 : num3) : ((num2 > num3) ? num2 : num3);
  	cout << "The maximum value is: " << maxResult << endl;
    return 0;
}
-----------
  //rite a program to read in an integer and print the factorial of that number using a for loop.
  #include<iostream>
using namespace std;
int main(){
  int fact=1;
  int num;
  cin>>num;
  for(int i=1;i<=num;i++){
    fact=fact*i;
  }
  cout<<"factorial = "<<fact<<endl;
}
----------------
//Write a program to read in an integer and determine if it is a prime number or not using a for loop.
#include <iostream>
using namespace std;
int main() {
    int n, i,c=0;
    cin >> n;
    for (i = 1; i <= n; i++) {
        if (n % i == 0)
            c++;
    }
    if (c==2)
        cout << "Prime";
    else
        cout << "Not Prime";
    return 0;
}
------------------
  //Write a program to read in an integer and print the Fibonacci series up to that number using a for loop
#include <iostream>
using namespace std;
int main(){
  int n;
  cin>>n;
  int a=0,b=1;
  for(int i=0;i<=n;i++){
    cout<<a<<" ";
    int c=a+b;
    a=b;
    b=c;
  }
}
--------------------
//Write a program to read in an integer and print the sum of all its digits using a while loop.
#include <iostream>
using namespace std;
int main() {
    int n, sum = 0;
    cin >> n;
    while (n != 0) {
        sum = sum + (n % 10);
        n = n / 10;
    }
    cout << "Sum of digits = " << sum;
    return 0;
}
------
//Write a program to read in an integer and determine if it is a palindrome or not using a while loop.
#include <iostream>
using namespace std;
int main(){
  int n;
  cin>>n;
  int t=n;  
  int r=0;
  while (n>0){
    r=r*10+n%10;
    n=n/10;
  }
  if(r==t){
    cout<<"palindrome";
  }
  else{
    cout<<"not palindrome";
  }
}
-------------
//Write a program to read in two integers and compute their greatest common divisor using a do-while loop.
#include <iostream>
using namespace std;
int main() {
    int a, b, r;
    cin >> a >> b;
    do {
        r = a % b;
        a = b;
        b = r;
    } while (b != 0);
    cout << "GCD = " << a;
}
------------
// Write a program to read in an integer and determine if it is an Armstrong number or not.
#include <iostream>
using namespace std;
int main(){
  int n,s=0,t,d,r=0;
  cin>>n;
  t=n;
  while (n>0){
    d=n%10;
    s+=d*d*d;
    n=n/10;
  }
  if (s==t){
    cout <<"arm";
  }
  else{
    cout<<"no arm";
  }
}
----------------
//Write a program to read in an integer and determine if it is a perfect number or not.
#include <iostream>
using namespace std;
int main() {
    int n, sum = 0;
    cin >> n;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0)
            sum += i;
    }
    if (sum == n)
        cout << "Perfect Number";
    else
        cout << "Not a Perfect Number";
}
--------------
//Write a program to read in an integer and determine if it is a strong number or not.
#include <iostream>
using namespace std;
int main() {
    int n, temp, digit, sum = 0;
    cin >> n;
    temp = n;
    while (n > 0) {
        digit = n % 10;
        int fact = 1;
        for (int i = 1; i <= digit; i++)
            fact *= i;
        sum += fact;
        n /= 10;
    }
    if (sum == temp)
        cout << "Strong Number";
    else
        cout << "Not a Strong Number";
}
-----------------
// Write a program to read in an integer and determine if it is a happy number or not.
#include <iostream>
using namespace std;
int main() {
    int n, sum, digit;
    cin >> n;
    while (n != 1 && n != 4) {
        sum = 0;
        while (n > 0) {
            digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        n = sum;
    }
    if (n == 1)
        cout << "Happy Number";
    else
        cout << "Not a Happy Number";
}
------------------
  //Write a program to read in an integer and determine if it is a Harshad number or not.
#include <iostream>
using namespace std;
int main() {
    int n, temp, digit, sum = 0;
    cin >> n;
    temp = n;
    while (n > 0) {
        digit = n % 10;
        sum += digit;
        n /= 10;
    }
    if (temp % sum == 0)
        cout << "Harshad Number";
    else
        cout << "Not a Harshad Number";
}
------------------
  /*Write a program to print the following pattern using nested for loops:

*
**
***
****
******/
#include<iostream>
using namespace std;
int main(){
  int n;
  cin>>n;
  for (int i=0;i<n;i++){
    for (int j=0;j<=i;j++){
      cout<<"*";
    }
    cout<<endl;
  }
}
-------------------
/*Write a program to print the following pattern using nested for loops:

1
22
333
4444
55555*/
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cout << i;
        }
        cout << endl;
    }

    return 0;
}
---------------------
