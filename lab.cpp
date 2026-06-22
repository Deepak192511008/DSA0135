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
//Harshad Number
#include <iostream>
using namespace std;
int main() {
    int n, temp, sum = 0;
    cin >> n;
    temp = n;
    while(temp > 0) {
        sum += temp % 10;
        temp /= 10;
    }
    if(n % sum == 0)
        cout << "Harshad Number";
    else
        cout << "Not Harshad Number";
    return 0;
}
----------------
//Swap Without Temporary Variable
#include <iostream>
using namespace std;
int main() {
    int a, b;
    cin >> a >> b;
    a = a + b;
    b = a - b;
    a = a - b;
    cout << a << " " << b;
    return 0;
}
----------------------------------------
//Hollow Square Pattern
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(i==1 || i==n || j==1 || j==n)
                cout<<"* ";
            else
                cout<<"  ";
        }
        cout<<endl;
    }
}
--------------------------------------------------
//Number Pattern
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=i;j++)
            cout<<j<<" ";
        cout<<endl;
    }
}
/*5
1 
1 2 
1 2 3 
1 2 3 4 
1 2 3 4 5 


=== Code Execution Successful ===*/
----------------------------------
//Palindrome Number
#include <iostream>
using namespace std;
int main() {
    int n, temp, rev=0;
    cin >> n;
    temp=n;
    while(temp>0){
        rev=rev*10+temp%10;
        temp/=10;
    }
    if(rev==n)
        cout<<"Palindrome";
    else
        cout<<"Not Palindrome";
}
--------------------------------------------------------
//Sum of Cubes of First n Natural Numbers
#include <iostream>
using namespace std;
int main() {
    int n;
    long long sum=0;
    cin>>n;
    for(int i=1;i<=n;i++)
        sum += i*i*i;
    cout<<sum;
}
------------------------------------------------------
//Binary to Decimal
#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int bin, dec=0, i=0, rem;
    cin>>bin;

    while(bin>0){
        rem=bin%10;
        dec += rem*pow(2,i);
        bin/=10;
        i++;
    }

    cout<<dec;
}
-------------------------------------------------------------
//Palindrome Pattern
#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        for (int j=1;j<=i;j++){
            cout<<j;
        }
        for(int j=i-1;j>=1;j--)
            cout<<j;
        cout<<endl;
    }
}
------------------------------------------
//Hollow Pyramid Pattern
#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=i;j<n;j++)
            cout<<" ";
        for(int j=1;j<=2*i-1;j++){
            if(j==1 || j==2*i-1 || i==n)
                cout<<"*";
            else
                cout<<" ";
        }
        cout<<endl;
    }
}
----------------------------------------------
//Sum of Squares of First n Natural Numbers
#include <iostream>
using namespace std;
int main() {
    int n;
    long long sum=0;
    cin>>n;
    for(int i=1;i<=n;i++)
        sum += i*i;
    cout<<sum;
}
-------------------------------------------------------
//Print All Factors
#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        if(n%i==0)
            cout<<i<<" ";
}
--------------------------------------------------------
//Pyramid Pattern
#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=i;j<n;j++)
            cout<<" ";
        for(int j=1;j<=2*i-1;j++)
            cout<<"*";
        cout<<endl;
    }
}
------------------------------------------------------------
//Power of a Number
#include <iostream>
using namespace std;
int main() {
    int base, exp;
    long long result=1;
    cin>>base>>exp;
    for(int i=1;i<=exp;i++)
        result*=base;
    cout<<result;
}
----------------------------------------------------
//Inverted Pyramid Pattern
#include <iostream>
using namespace std;

int main() {
    int n;
    cin>>n;

    for(int i=n;i>=1;i--){
        for(int j=i;j<n;j++)
            cout<<" ";
        for(int j=1;j<=2*i-1;j++)
            cout<<"*";
        cout<<endl;
    }
}
---------------------------------------------
//Sum of Positive and Negative Numbers
#include <iostream>
using namespace std;

int main() {
    int n, num;
    int pos=0, neg=0;

    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>num;

        if(num>0)
            pos+=num;
        else
            neg+=num;
    }

    cout<<"Positive Sum = "<<pos<<endl;
    cout<<"Negative Sum = "<<neg;
}
------------------------------------------------------
//Multiplication Table
#include <iostream>
using namespace std;

int main() {
    int n;
    cin>>n;

    for(int i=1;i<=10;i++)
        cout<<n<<" x "<<i<<" = "<<n*i<<endl;
}
---------------------------------------
//Automorphic Number
#include <iostream>
using namespace std;
int main() {
    int n, sq, temp, digits=0;
    cin>>n;
    sq=n*n;
    temp=n;
    while(temp>0){
        digits++;
        temp/=10;
    }
    int mod=1;
    for(int i=1;i<=digits;i++)
        mod*=10;
    if(sq%mod==n)
        cout<<"Automorphic";
    else
        cout<<"Not Automorphic";
}

#include <iostream>
using namespace std;
int main() {
    int n, sq, m = 1;
    cin >> n;
    sq = n * n;
    for(int t = n; t > 0; t /= 10)
        m *= 10;
    cout << (sq % m == n ? "Automorphic" : "Not Automorphic");
}
------------------------------------------------
//Diamond Pattern
#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=i;j<n;j++) cout<<" ";
        for(int j=1;j<=2*i-1;j++) cout<<"*";
        cout<<endl;
    }
    for(int i=n-1;i>=1;i--){
        for(int j=n;j>i;j--) cout<<" ";
        for(int j=1;j<=2*i-1;j++) cout<<"*";
        cout<<endl;
    }
}
------------------------------------------------------------------
//Decimal ↔ Hexadecimal
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cin>>n;

    cout<<hex<<n;
}
--------------------------------------------------------
//Inverted Right Triangle
#include <iostream>
using namespace std;

int main() {
    int n;
    cin>>n;

    for(int i=n;i>=1;i--){
        for(int j=1;j<=i;j++)
            cout<<"* ";
        cout<<endl;
    }
}
-----------------------------------
//Strong Number
#include <iostream>
using namespace std;
int fact(int n){
    int f=1;
    for(int i=1;i<=n;i++)
        f*=i;
    return f;
}
int main() {
    int n,temp,sum=0;
    cin>>n;
    temp=n;
    while(temp>0){
        sum+=fact(temp%10);
        temp/=10;
    }
    if(sum==n)
        cout<<"Strong Number";
    else
        cout<<"Not Strong Number";
}
---------------------------------------------------
//Frequency of Each Digit
#include <iostream>
using namespace std;
int main() {
    long long n;
    cin>>n;
    int freq[10]={0};
    while(n>0){
        freq[n%10]++;
        n/=10;
    }
    for(int i=0;i<10;i++)
        cout<<i<<" : "<<freq[i]<<endl;
}
-----------------------------------------------------------
//Count Number of Divisors
#include <iostream>
using namespace std;
int main() {
    int n,count=0;
    cin>>n;
    for(int i=1;i<=n;i++)
        if(n%i==0)
            count++;
    cout<<count;
}
--------------------------------------------------------------
//Compound Interest
#include <iostream>
#include <cmath>
using namespace std;
int main() {
    double p,r,t,ci;
    cin>>p>>r>>t;
    ci = p * pow((1+r/100),t) - p;
    cout<<ci;
}
----------------------------------------------------------------
//Reverse Digits
#include <iostream>
using namespace std;
int main() {
    int n,rev=0;
    cin>>n;
    while(n>0){
        rev=rev*10+n%10;
        n/=10;
    }
    cout<<rev;
}
------------------------------------------------------------
//Perfect Number
#include <iostream>
using namespace std;
int main() {
    int n,sum=0;
    cin>>n;
    for(int i=1;i<n;i++)
        if(n%i==0)
            sum+=i;
    if(sum==n)
        cout<<"Perfect Number";
    else
        cout<<"Not Perfect Number";
}
--------------------------------------------------------------
//Fibonacci Series
#include <iostream>
using namespace std;
int main() {
    int n,a=0,b=1,c;
    cin>>n;
    cout<<a<<" "<<b<<" ";
    for(int i=3;i<=n;i++){
        c=a+b;
        cout<<c<<" ";
        a=b;
        b=c;
    }
}
------------------------------------------------------------
//LCM of Two Numbers
#include <iostream>
using namespace std;
int main() {
    int a,b,max;
    cin>>a>>b;
    max=(a>b)?a:b;
    while(true){
        if(max%a==0 && max%b==0){
            cout<<max;
            break;
        }
        max++;
    }
}
----------------------------------------------------------------
//Magic Number
#include <iostream>
using namespace std;
int main() {
    int n,sum=0;
    cin>>n;
    while(n>9){
        sum=0;
        while(n>0){
            sum+=n%10;
            n/=10;
        }
        n=sum;
    }
    if(n==1)
        cout<<"Magic Number";
    else
        cout<<"Not Magic Number";
}
-------------------------------------------------------------------
//Decimal to Binary
#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    int bin[32],i=0;
    while(n>0){
        bin[i]=n%2;
        n/=2;
        i++;
    }
    for(int j=i-1;j>=0;j--)
        cout<<bin[j];
}
------------------------------------------------------------------------
//Average of Given Numbers
#include <iostream>
using namespace std;
int main() {
    int n,num;
    float sum=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>num;
        sum+=num;
    }
    cout<<"Average = "<<sum/n;
}
--------------------------------------------------------------------
//Digital Root
#include<iostream>
using namespace std;
int main(){
    int n,s;
    cin>>n;
    while(n>9){
        s=0;
        for(;n;n/=10)
            s+=n%10;
        n=s;
    }
    cout<<n;
}


#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    cout<<(n==0?0:1+(n-1)%9);
}
-------------------------------------------------------------
//Hexadecimal to Decimal conversion
#include<iostream>
using namespace std;
int main(){
    string h;
    int d=0;
    cin>>h;
    for(char c:h){
        d*=16;
        if(c>='0'&&c<='9')
            d+=c-'0';
        else
            d+=toupper(c)-'A'+10;
    }
    cout<<d;
}
----------------------------------------------------
1. Sequence Length
#include <iostream>
using namespace std;

int main() {
    string str;
    getline(cin, str);

    cout << "Length = " << str.length();

    return 0;
}
Output
Input:
Hello World

Output:
Length = 11
2. Sort Array
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    int arr[n];

    for(int i=0;i<n;i++)
        cin >> arr[i];

    sort(arr, arr+n);

    cout<<"Sorted Array: ";

    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";

    return 0;
}
Output
Input:
5
8 2 7 1 4

Output:
Sorted Array:
1 2 4 7 8
3. Anagram
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    string s1,s2;

    cin>>s1>>s2;

    sort(s1.begin(),s1.end());
    sort(s2.begin(),s2.end());

    if(s1==s2)
        cout<<"Anagram";
    else
        cout<<"Not Anagram";

    return 0;
}
Output
Input:
listen
silent

Output:
Anagram
4. Prefix Sum
#include <iostream>
using namespace std;

int main() {
    int n;
    cin>>n;

    int arr[n];

    for(int i=0;i<n;i++)
        cin>>arr[i];

    cout<<"Prefix Sum: ";

    int sum=0;

    for(int i=0;i<n;i++) {
        sum+=arr[i];
        cout<<sum<<" ";
    }

    return 0;
}
Output
Input:
5
1 2 3 4 5

Output:
Prefix Sum:
1 3 6 10 15
5. Second Smallest Element
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin>>n;

    int arr[n];

    for(int i=0;i<n;i++)
        cin>>arr[i];

    sort(arr,arr+n);

    cout<<"Second Smallest = "<<arr[1];

    return 0;
}
Output
Input:
5
8 2 1 7 4

Output:
Second Smallest = 2
6. Calculate Distance Between Two Points
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float x1,y1,x2,y2;

    cin>>x1>>y1>>x2>>y2;

    float distance;

    distance=sqrt(pow(x2-x1,2)+pow(y2-y1,2));

    cout<<"Distance = "<<distance;

    return 0;
}
Output
Input:
0 0 3 4

Output:
Distance = 5
7. Find Median
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin>>n;

    int arr[n];

    for(int i=0;i<n;i++)
        cin>>arr[i];

    sort(arr,arr+n);

    cout<<"Median = "<<arr[n/2];

    return 0;
}
Output
Input:
5
10 20 30 40 50

Output:
Median = 30
8. All Pairs
#include <iostream>
using namespace std;

int main() {
    int n;
    cin>>n;

    int arr[n];

    for(int i=0;i<n;i++)
        cin>>arr[i];

    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            cout<<"("<<arr[i]<<","<<arr[j]<<")"<<endl;
        }
    }

    return 0;
}
Output
Input:
3
1 2 3

Output:
(1,2)
(1,3)
(2,3)
9. Longest Word
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    string s, w, longest;
    getline(cin, s);

    stringstream ss(s);
    while (ss >> w)
        if (w.size() > longest.size())
            longest = w;

    cout << longest;
}

10. Remove Vowels
#include <iostream>
using namespace std;

int main() {
    string str;

    getline(cin,str);

    for(char ch:str) {
        if(ch!='a'&&ch!='e'&&ch!='i'&&ch!='o'&&ch!='u' &&
           ch!='A'&&ch!='E'&&ch!='I'&&ch!='O'&&ch!='U')
            cout<<ch;
    }

    return 0;
}
Output
Input:
Saveetha

Output:
Svth

11. Matrix Input and Display
#include <iostream>
using namespace std;

int main() {
    int r,c;

    cin>>r>>c;

    int a[r][c];

    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            cin>>a[i][j];

    cout<<"Matrix:"<<endl;

    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }

    return 0;
}
Output
Input:
2 2
1 2
3 4

Output:
Matrix:
1 2
3 4

12. Transpose Matrix
#include <iostream>
using namespace std;

int main() {
    int n;

    cin>>n;

    int a[n][n];

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>a[i][j];

    cout<<"Transpose:"<<endl;

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++)
            cout<<a[j][i]<<" ";
        cout<<endl;
    }

    return 0;
}
Output
Input:
2
1 2
3 4

Output:
Transpose:
1 3
2 4

13. Peak Element
#include <iostream>
using namespace std;

int main() {
    int n;

    cin>>n;

    int a[n];

    for(int i=0;i<n;i++)
        cin>>a[i];

    for(int i=1;i<n-1;i++) {
        if(a[i]>a[i-1] && a[i]>a[i+1]) {
            cout<<"Peak Element = "<<a[i];
            break;
        }
    }

    return 0;
}
Output
Input:
5
1 3 8 4 2

Output:
Peak Element = 8

14. Majority Element
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int a[n], count[101] = {0};

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        count[a[i]]++;
    }

    for (int i = 0; i < 101; i++) {
        if (count[i] > n / 2) {
            cout << "Majority Element = " << i;
            break;
        }
    }

    return 0;
}
Input:
7
2 2 1 2 3 2 2

Output:
Majority Element = 2


15. Union of Two Arrays
#include <iostream>
#include <set>
using namespace std;

int main() {
    int n,m;

    cin>>n;

    set<int> s;

    int x;

    for(int i=0;i<n;i++) {
        cin>>x;
        s.insert(x);
    }

    cin>>m;

    for(int i=0;i<m;i++) {
        cin>>x;
        s.insert(x);
    }

    cout<<"Union: ";

    for(auto i:s)
        cout<<i<<" ";

    return 0;
}
Output
Input:
3
1 2 3
3
2 3 4

Output:
Union:
1 2 3 4



16. Subsequences of String
#include <iostream>
using namespace std;

void sub(string s, string ans, int i) {
    if (i == s.size()) {
        cout << ans << endl;
        return;
    }

    sub(s, ans + s[i], i + 1); // take
    sub(s, ans, i + 1);        // skip
}

int main() {
    string s;
    cin >> s;
    sub(s, "", 0);
}

Output:
abc
ab
ac
a
bc
b
c

17. K-th Position Element
#include <iostream>
using namespace std;

int main()
{
    int n;

    cin>>n;

    int a[n];

    for(int i=0;i<n;i++)
        cin>>a[i];

    int k;

    cin>>k;

    cout<<"Element = "<<a[k-1];

    return 0;
}
Output
Input:
5
10 20 30 40 50
3

Output:
Element = 30

18. Square Matrix Check
#include <iostream>
using namespace std;

int main()
{
    int r,c;

    cin>>r>>c;

    if(r==c)
        cout<<"Square Matrix";
    else
        cout<<"Not Square Matrix";

    return 0;
}
Output
Input:
3 3

Output:
Square Matrix

19. Symmetric Matrix
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int a[n][n];

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> a[i][j];

    bool sym = true;

    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            if(a[i][j] != a[j][i])
                sym = false;

    cout << (sym ? "Symmetric Matrix" : "Not Symmetric");
}
Output
3
1 2 3
2 4 5
3 6 5
Not Symmetric


20. Substring
#include <iostream>
using namespace std;

int main()
{
    string str;

    cin>>str;

    int pos,len;

    cin>>pos>>len;

    cout<<str.substr(pos,len);

    return 0;
}
Output
Input:
SAVEETHA
2 4

Output:
VEET

21. Custom Exception
#include <iostream>
using namespace std;

int main()
{
    try
    {
        throw "Custom Exception Occurred";
    }
    catch(const char* msg)
    {
        cout<<msg;
    }

    return 0;
}
Output
Custom Exception Occurred


22. Account Class
#include <iostream>
using namespace std;

class Account
{
    double balance;

public:
    Account(double b)
    {
        balance=b;
    }

    void display()
    {
        cout<<"Balance = "<<balance;
    }
};

int main()
{
    Account a(5000);

    a.display();

    return 0;
}
Output
Balance = 5000


23. Vehicle Class
#include <iostream>
using namespace std;

class Vehicle
{
public:
    void display()
    {
        cout<<"Vehicle Details";
    }
};

int main()
{
    Vehicle v;

    v.display();

    return 0;
}
Output
Vehicle Details


24. Employee Class
#include <iostream>
using namespace std;

class Employee
{
    int id;
    string name;

public:
    void getData()
    {
        cin>>id>>name;
    }

    void display()
    {
        cout<<id<<" "<<name;
    }
};

int main()
{
    Employee e;

    e.getData();

    e.display();

    return 0;
}
Output
Input:
101 Deepak

Output:
101 Deepak

25. Shape Class (Polymorphism)
#include <iostream>
using namespace std;

class Shape
{
public:
    virtual void area()
    {
        cout<<"Area";
    }
};

class Rectangle : public Shape
{
public:
    void area()
    {
        cout<<"Rectangle Area";
    }
};

int main()
{
    Shape *s;

    Rectangle r;

    s=&r;

    s->area();

    return 0;
}
Output
Rectangle Area


26. Rotated Matrix (90° Clockwise)
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int a[n][n];

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin >> a[i][j];

    cout << "Rotated Matrix:\n";

    for(int i=0;i<n;i++)
    {
        for(int j=n-1;j>=0;j--)
            cout << a[j][i] << " ";

        cout << endl;
    }

    return 0;
}
Output
Input:
3
1 2 3
4 5 6
7 8 9

Output:
7 4 1
8 5 2
9 6 3


27. Boundary Elements of Matrix
#include <iostream>
using namespace std;

int main()
{
    int r,c;
    cin>>r>>c;

    int a[r][c];

    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            cin>>a[i][j];

    cout<<"Boundary Elements:\n";

    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            if(i==0 || j==0 || i==r-1 || j==c-1)
                cout<<a[i][j]<<" ";
        }
    }

    return 0;
}
Output
3 3
1 2 3 4 5 6 7 8 9
Boundary Elements:
1 2 3 4 6 7 8 9 

28. Count Occurrences
#include <iostream>
using namespace std;

int main()
{
    int n,key,count=0;

    cin>>n;

    int a[n];

    for(int i=0;i<n;i++)
        cin>>a[i];

    cin>>key;

    for(int i=0;i<n;i++)
    {
        if(a[i]==key)
            count++;
    }

    cout<<"Count = "<<count;

    return 0;
}
Output
Input:
5
1 2 3 2 2
2

Output:
Count = 3

29. Subarray
#include <iostream>
using namespace std;

int main()
{
    int n;

    cin>>n;

    int a[n];

    for(int i=0;i<n;i++)
        cin>>a[i];

    cout<<"Subarrays:\n";

    for(int i=0;i<n;i++)
    {
        for(int j=i;j<n;j++)
        {
            for(int k=i;k<=j;k++)
                cout<<a[k]<<" ";

            cout<<endl;
        }
    }

    return 0;
}
output
3
1 2 3
Subarrays:
1 
1 2 
1 2 3 
2 
2 3 
3 

30. Triplets
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin>>n;

    int a[n];

    for(int i=0;i<n;i++)
        cin>>a[i];

    cout<<"Triplets:\n";

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            for(int k=j+1;k<n;k++)
            {
                cout<<"("
                    <<a[i]<<","
                    <<a[j]<<","
                    <<a[k]<<")"<<endl;
            }
        }
    }

    return 0;
}
Output
Input:
4
1 2 3 4

Output:
(1,2,3)
(1,2,4)
(1,3,4)
(2,3,4)


31. Inversion Count
#include <iostream>
using namespace std;

int main()
{
    int n,count=0;

    cin>>n;

    int a[n];

    for(int i=0;i<n;i++)
        cin>>a[i];

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(a[i]>a[j])
                count++;
        }
    }

    cout<<"Inversions = "<<count;

    return 0;
}
Output
Input:
5
5 4 3 2 1

Output:
Inversions = 10


33. Rectangle Class
#include <iostream>
using namespace std;

class Rectangle
{
    int length,breadth;

public:

    Rectangle(int l,int b)
    {
        length=l;
        breadth=b;
    }

    int area()
    {
        return length*breadth;
    }
};

int main()
{
    Rectangle r(10,5);

    cout<<"Area = "<<r.area();

    return 0;
}
Output
Area = 50


34. Appliance Class
#include <iostream>
using namespace std;

class Appliance
{
public:
    void display()
    {
        cout<<"Home Appliance";
    }
};

int main()
{
    Appliance a;

    a.display();

    return 0;
}
Output
Home Appliance

35. Device Class
#include <iostream>
using namespace std;

class Device
{
public:
    void show()
    {
        cout<<"Electronic Device";
    }
};

int main()
{
    Device d;

    d.show();

    return 0;
}
Output
Electronic Device

36. Animal Class
#include <iostream>
using namespace std;

class Animal
{
public:
    void sound()
    {
        cout<<"Animal Sound";
    }
};

int main()
{
    Animal a;

    a.sound();

    return 0;
}
Output
Animal Sound

Merge Two Arrays
#include <iostream>
using namespace std;

int main()
{
    int n,m;

    cin>>n;

    int a[n];

    for(int i=0;i<n;i++)
        cin>>a[i];

    cin>>m;

    int b[m];

    for(int i=0;i<m;i++)
        cin>>b[i];

    cout<<"Merged Array: ";

    for(int i=0;i<n;i++)
        cout<<a[i]<<" ";

    for(int i=0;i<m;i++)
        cout<<b[i]<<" ";

    return 0;
}
Output
Input:
3
1 2 3
3
4 5 6

Output:
Merged Array:
1 2 3 4 5 6
