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
