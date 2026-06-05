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
/*Write a program to print the following pattern using nested for loops: 
    *
   ***
  *****
 *******
*********
 *******
  *****
   ***
    *
*/
#include <iostream>
using namespace std;
int main() {
  	int n;
  	cin>>n;
    // Upper Half
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++)
            cout << " ";
        for (int j = 1; j <= 2 * i - 1; j++)
            cout << "*";
        cout << endl;
    }
    // Lower Half
    for (int i = n-1; i >= 1; i--) {
        for (int j = 1; j <= n - i; j++)
            cout << " ";
        for (int j = 1; j <= 2 * i - 1; j++)
            cout << "*";
        cout << endl;
    }
}
-----------------------
/*Write a program to print the following pattern using nested for loops:
    1
   121
  12321
 1234321
123454321*/
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {

        // Print spaces
        for (int j = 1; j <= n - i; j++)
            cout << " ";

        // Print increasing numbers
        for (int j = 1; j <= i; j++)
            cout << j;

        // Print decreasing numbers
        for (int j = i - 1; j >= 1; j--)
            cout << j;

        cout << endl;
    }

    return 0;
}
---------------
  //Write a program to read in an integer and determine if it is a neon number or not.
  #include <iostream>
using namespace std;
int main(){
  int n;
  cin>>n;
  int sq=n*n;
  int t=sq;
  int d;
  int s=0;
  while (sq>0){
    d=sq%10;
    s+=d;
    sq/=10;
  }
  if(s==n){
    cout<<"Neon";
  }
  else{
    cout<<"not neon";
  }
}
------------------
  //Write a program to read in an integer and determine if it is a buzz number or not.
  #include <iostream>
using namespace std;
int main() {
  int n;
  cin >> n;
  if (n % 10 == 7 || n % 7 == 0)
    cout << "Buzz Number";
  else
    cout << "Not a Buzz Number";
  return 0;
}
--------------------
  //Write a program to read in an integer and determine if it is a narcissistic number or not.
  #include <iostream>
#include <cmath>
using namespace std;
int main() {
    int n, temp, digits = 0;
    int sum = 0;
    cin >> n;
    temp = n;
    int t = n;
    while (t > 0) {
        digits++;
        t /= 10;
    }
    t = n;
    while (t > 0) {
        int digit = t % 10;
        sum += pow(digit, digits);
        t /= 10;
    }
    if (sum == n)
        cout << "Narcissistic Number";
    else
        cout << "Not a Narcissistic Number";
}
-------------
  //Write a program to read in an integer and determine if it is a abundant number or not.
  #include <iostream>
using namespace std;
int main() {
    int n, sum = 0;
    cin >> n;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0)
            sum += i;
    }
    if (sum > n)
        cout << "Abundant Number";
    else
        cout << "Not an Abundant Number";
    return 0;
}
------------------
//Write a C++ program to reverse the elements of an array.
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;  	
    int a[n];
    for(int i = 0; i < n; i++)
        cin >> a[i];
  	int len = sizeof(a) / sizeof(a[0]);
    for(int i = len - 1; i >= 0; i--)
        cout << a[i] <<endl;

    return 0;
}
-------------------
  //Write a C++ program to insert an element into an array at a specific position.
  #include <iostream>
using namespace std;
int main() {
    int a[] = {1, 2, 3, 4, 5};
    int n = 5, pos = 3, val = 10;
    for(int i = n; i >= pos; i--) {
        a[i] = a[i - 1];
    }
    a[pos - 1] = val;
    n++;
    for(int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
---------------------------
  //Write a C++ program to delete an element from an array at a specific position.
  
#include <iostream>
using namespace std;
int main() {
    int a[10] = {1, 2, 3, 4, 5};
    int n = 5, pos = 3;
    for(int i = pos - 1; i < n - 1; i++) {
        a[i] = a[i + 1];
    }
    n--;
    for(int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
---------------------
  //Write a C++ program to find the sum of elements in an array.
  #include <iostream>
using namespace std;
int main() {
    int a[] = {1, 2, 3, 4, 5};
    int len = sizeof(a) / sizeof(a[0]);
    int sum = 0;
    for(int i = 0; i < len; i++) {
        sum += a[i];
    }
    cout << sum;
    return 0;
}

--------------------
//Write a C++ program to find the average of elements in an array.
#include <iostream>
using namespace std;
int main() {
    int a[] = {1, 2, 3, 4, 5};
    int len = sizeof(a) / sizeof(a[0]);
    int sum = 0;
    for(int i = 0; i < len; i++) {
        sum += a[i];
    }
    double avg = (double)sum / len;
    cout << avg;
    return 0;
}
--------------
  //Write a C++ program to find the second largest element in an array.
  #include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int a[] = {5, 3, 1, 4, 2};
    int len = sizeof(a) / sizeof(a[0]);
    sort(a, a + len);
    cout<<a[len-2];
    return 0;
}
---------------------
//Write a C++ program to find the number of occurrences of a value in an array.
#include <iostream>
using namespace std;
int main() {
    int a[] = {1, 2, 2, 3, 2, 4, 5};
    int len = sizeof(a) / sizeof(a[0]);
    int key = 2;
    int count = 0;
    for(int i = 0; i < len; i++) {
        if(a[i] == key)
            count++;
    }
    cout << count;
    return 0;
}
-------------------
//Write a C++ program to merge two arrays into a single array.
#include <iostream>
using namespace std;
int main() {
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    int n1 = sizeof(a) / sizeof(a[0]);
    int n2 = sizeof(b) / sizeof(b[0]);
    int c[n1 + n2];
    for(int i = 0; i < n1; i++)
        c[i] = a[i];
    for(int i = 0; i < n2; i++)
        c[n1 + i] = b[i];
    for(int i = 0; i < n1 + n2; i++)
        cout << c[i] << " ";
    return 0;
}
-------------------
  //Write a C++ program to add 2 matrics.
#include <iostream>
using namespace std;
int main() {
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{5, 6}, {7, 8}};
    int c[2][2];
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
---------------
//Write a C++ program to multiply 2 matrics.
#include <iostream>
using namespace std;
int main() {
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{5, 6}, {7, 8}};
    int c[2][2] = {0};
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
---------------
//Write a C++ program find sum of diagonals of the matrics 
#include <iostream>
using namespace std;
int main() {
    int a[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int n = 3;
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += a[i][i]; // main diagonal
    }
    cout << sum;
    return 0;
}
-------------------
//Write a function to compute the factorial of a given integer.
#include <iostream>
using namespace std;
int factorial(int n) {
    int fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}
int main() {
    int n;
    cin >> n;
    cout << "Factorial = " << factorial(n);
    return 0;
}
----------
//Write a function to determine if a given integer is a prime number or not.
#include <iostream>
using namespace std;
string p(int n){
  int c=0;
  for(int i=1;i<=n;i++){
    if (n%i==0){
      c++;
    }
  }
  if(c==2){
    return "prime";
  }
  else
    return "not prime";
}
int main(){
  int n;
  cin>>n;
  cout<<p(n);
}
-----------------------
//Write a function to determine the GCD (greatest common divisor) of two given integers.
#include<iostream>
using namespace std;
int gcd(int a,int b){
  int g=1;
  for(int i=1;i<=a and i<=b;i++){
    if(a%i==0 and b%i==0)
      g=i;
  }
  return g;
}
int main(){
  int a,b;
  cin>>a>>b;
  cout<<gcd(a,b);
}
