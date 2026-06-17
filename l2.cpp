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
