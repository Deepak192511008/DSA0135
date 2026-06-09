//1
#include <iostream>
using namespace std;
class Department{
private:
    int deptId;
    int n;
    int marks[100];
public:
    static int totalDepartments;
    void input(){
        cout << "\nEnter Department ID: ";
        cin >> deptId;
        cout << "Enter Number of Students: ";
        cin >> n;
        if (n > 100)
            n = 100;
        if (n > 0){
            cout << "Enter Marks:\n";
            for (int i = 0; i < n; i++)
                cin >> marks[i];
        }
    }
    int getTopperMark(){
        if (n == 0)
            return -1;
        int top = marks[0];
        for (int i = 1; i < n; i++){
            if (marks[i] > top)
                top = marks[i];
        }
        return top;
    }
    double getPassPercentage(){
        if (n == 0)
            return 0;
        int pass = 0;
        for (int i = 0; i < n; i++){
            if (marks[i] >= 40)
                pass++;
        }
        return (pass * 100.0) / n;
    }
    void displayDepartmentResult(){
        cout << "\nDepartment " << deptId;
        if (n == 0){
            cout << "\nNo Students in Department\n";
            return;
        }
        cout << "\nTopper Mark = " << getTopperMark();
        cout << "\nPass Percentage = " << getPassPercentage() << "%\n";
    }
};
int Department::totalDepartments = 0;
int main(){
    int d;
    cout << "Enter Number of Departments: ";
    cin >> d;
    Department dept[50];   // Array of Objects
    int overallTopper = -1;
    int overallDept = -1;
    for (int i = 0; i < d; i++){
        dept[i].input();
        Department::totalDepartments++;
        int deptTop = dept[i].getTopperMark();
        if (deptTop > overallTopper){
            overallTopper = deptTop;
            overallDept = i + 1;
        }
    }
    cout << "\n===== DEPARTMENT RESULTS =====\n";
    for (int i = 0; i < d; i++){
        dept[i].displayDepartmentResult();
    }
    cout << "\n===== UNIVERSITY TOPPER =====\n";
    if (overallTopper == -1){
        cout << "No Students in University\n";
    }
    else{
        cout << "Overall Topper Mark = "
             << overallTopper
             << "\nDepartment Number = "
             << overallDept << endl;
    }
    cout << "\nTotal Departments Processed = "
         << Department::totalDepartments << endl;
    return 0;
}
//Output
/*

TEST CASE 1 (Normal Case)

Input:
2
101
3
75 80 90
102
4
60 45 35 85

Output:
Department 101
Topper Mark = 90
Pass Percentage = 100%

Department 102
Topper Mark = 85
Pass Percentage = 75%

Overall Topper Mark = 90
Department Number = 1


TEST CASE 2 (Empty Department)

Input:
1
101
0

Output:
No Students in Department
No Students in University


TEST CASE 3 (All Students Fail)

Input:
1
101
5
10 20 30 35 39

Output:
Topper Mark = 39
Pass Percentage = 0%


TEST CASE 4 (Equal Top Marks)

Input:
1
101
4
95 95 80 70

Output:
Topper Mark = 95
Pass Percentage = 100%


TEST CASE 5 (Single Student)

Input:
1
101
1
100

Output:
Topper Mark = 100
Pass Percentage = 100%
Overall Topper Mark = 100


TIME COMPLEXITY

Best Case:
O(1)
(One department with one student)

Average Case:
O(N)
(N = Total number of students)

Worst Case:
O(N)
(All student marks must be traversed)

SPACE COMPLEXITY

O(N)
(for storing student marks)

*/

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

//2
#include<iostream>
using namespace std;
class Election{
private:
    int regions,candidates;
    int votes[50][100];
public:
    static int totalRegions;
    void input(){
        cout<<"Enter Number of Regions: ";
        cin>>regions;
        cout<<"Enter Number of Candidates: ";
        cin>>candidates;
        if(regions>50)
            regions=50;
        if(candidates>100)
            candidates=100;
        for(int i=0;i<regions;i++){
            cout<<"\nEnter Votes for Region "<<i+1<<":\n";
            for(int j=0;j<candidates;j++){
                cin>>votes[i][j];
                if(votes[i][j]<0)
                    votes[i][j]=0;
            }
        }
        totalRegions=regions;
    }
    void regionalWinners(){
        cout<<"\n===== REGIONAL RESULTS =====\n";
        for(int i=0;i<regions;i++){
            int maxVotes=votes[i][0];
            int winner=0,tie=0;
            for(int j=1;j<candidates;j++){
                if(votes[i][j]>maxVotes){
                    maxVotes=votes[i][j];
                    winner=j;
                    tie=0;
                }
                else if(votes[i][j]==maxVotes){
                    tie=1;
                }
            }
            cout<<"Region "<<i+1<<" : ";
            if(tie)
                cout<<"Tie";
            else
                cout<<"Winner = Candidate "<<winner+1;
            cout<<endl;
        }
    }
    void overallWinner(){
        int totalVotes[100]={0};
        for(int i=0;i<regions;i++){
            for(int j=0;j<candidates;j++){
                totalVotes[j]+=votes[i][j];
            }
        }
        int maxVotes=totalVotes[0];
        int winner=0,tie=0;
        for(int j=1;j<candidates;j++){
            if(totalVotes[j]>maxVotes){
                maxVotes=totalVotes[j];
                winner=j;
                tie=0;
            }
            else if(totalVotes[j]==maxVotes){
                tie=1;
            }
        }
        cout<<"\n===== OVERALL RESULT =====\n";
        if(tie)
            cout<<"Overall Election Result : Tie";
        else
            cout<<"Overall Winner = Candidate "<<winner+1
                <<" with "<<maxVotes<<" votes";
        cout<<"\nTotal Regions Processed = "
            <<Election::totalRegions<<endl;
    }
};
int Election::totalRegions=0;
int main(){
    Election e;
    e.input();
    e.regionalWinners();
    e.overallWinner();
    return 0;
}
//Output
/*

TEST CASE 1 (Normal Case)

Input:
3
3
100 80 60
90 120 70
110 100 50

Output:
Region 1 : Winner = Candidate 1
Region 2 : Winner = Candidate 2
Region 3 : Winner = Candidate 1

Overall Winner = Candidate 1 with 300 votes


TEST CASE 2 (Regional Tie)

Input:
1
3
100 100 50

Output:
Region 1 : Tie
Overall Election Result : Tie


TEST CASE 3 (Overall Tie)

Input:
2
2
100 50
50 100

Output:
Region 1 : Winner = Candidate 1
Region 2 : Winner = Candidate 2
Overall Election Result : Tie


TEST CASE 4 (All Zero Votes)

Input:
2
3
0 0 0
0 0 0

Output:
Region 1 : Tie
Region 2 : Tie
Overall Election Result : Tie


TEST CASE 5 (Invalid Votes)

Input:
1
3
100 -50 200

Output:
Region 1 : Winner = Candidate 3
Overall Winner = Candidate 3 with 200 votes

(-50 is converted to 0)


TIME COMPLEXITY

Best Case:
O(R × C)
(Need to scan all votes at least once)

Average Case:
O(R × C)

Worst Case:
O(R × C)

Where:
R = Number of Regions
C = Number of Candidates


SPACE COMPLEXITY

O(R × C)

For storing the 2D votes array.

*/
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//3
#include<iostream>
#include<string>
using namespace std;
class Product{
private:
    string pname;
    float price;
    int qty;

public:
    void input(){
        cout<<"Enter Product Name: ";
        cin>>pname;
        cout<<"Enter Price: ";
        cin>>price;
        cout<<"Enter Quantity Sold: ";
        cin>>qty;
    }
    float calculateSales(){
        return price*qty;
    }
    string getName(){
        return pname;
    }
    void display(){
        cout<<"\nProduct Name : "<<pname;
        cout<<"\nPrice : "<<price;
        cout<<"\nQuantity Sold : "<<qty;
        cout<<"\nSales : "<<calculateSales()<<endl;
    }
};
class Store{
private:
    int storeId;
    int n;
    Product p[100];
public:
    static float overallSales;
    void input(){
        cout<<"\nEnter Store ID: ";
        cin>>storeId;
        cout<<"Enter Number of Products: ";
        cin>>n;
        if(n>100)
            n=100;
        for(int i=0;i<n;i++){
            cout<<"\nProduct "<<i+1<<endl;
            p[i].input();
        }
    }
    float calculateStoreSales(){
        float total=0;
        for(int i=0;i<n;i++)
            total+=p[i].calculateSales();
        overallSales+=total;
        return total;
    }
    void displayStoreDetails(){
        cout<<"\n===== Store "<<storeId<<" =====\n";
        for(int i=0;i<n;i++)
            p[i].display();
        cout<<"Store Total Sales : "<<calculateStoreSales()<<endl;
    }
    float getStoreSales(){
        float total=0;
        for(int i=0;i<n;i++)
            total+=p[i].calculateSales();
        return total;
    }
    int getProductCount(){
        return n;
    }
    Product getProduct(int index){
        return p[index];
    }
    int getStoreId(){
        return storeId;
    }
};
float Store::overallSales=0;
int main(){
    int stores;
    cout<<"Enter Number of Stores: ";
    cin>>stores;
    Store s[50];
    for(int i=0;i<stores;i++)
        s[i].input();
    int bestStore=0;
    float maxStoreSales=s[0].getStoreSales();
    string bestProduct;
    float maxProductSales=-1;
    cout<<"\n===== STORE DETAILS =====\n";
    for(int i=0;i<stores;i++){
        s[i].displayStoreDetails();
        float storeSales=s[i].getStoreSales();
        if(storeSales>maxStoreSales){
            maxStoreSales=storeSales;
            bestStore=i;
        }
        for(int j=0;j<s[i].getProductCount();j++){
            Product temp=s[i].getProduct(j);
            if(temp.calculateSales()>maxProductSales){
                maxProductSales=temp.calculateSales();
                bestProduct=temp.getName();
            }
        }
    }
    cout<<"\n===== RETAIL CHAIN REPORT =====\n";
    cout<<"Overall Sales : "<<Store::overallSales<<endl;
    cout<<"Best Performing Store : Store "<<s[bestStore].getStoreId()<<endl;
    cout<<"Best Selling Product : "<<bestProduct<<endl;
    cout<<"Highest Product Revenue : "<<maxProductSales<<endl;
    return 0;
}
//Output

/*

TEST CASE 1 (Normal Case)

Input:
2

101
2
Pen
10
20
Book
50
10

102
2
Pencil
5
50
Bag
500
5

Output:
Store 101 Total Sales = 700
Store 102 Total Sales = 2750

Overall Sales = 3450
Best Performing Store = 102
Best Selling Product = Bag
Highest Product Revenue = 2500


TEST CASE 2 (Single Store, Single Product)

Input:
1

101
1
Pen
10
5

Output:
Store 101 Total Sales = 50

Overall Sales = 50
Best Performing Store = 101
Best Selling Product = Pen
Highest Product Revenue = 50


TEST CASE 3 (Store with No Products)

Input:
1

101
0

Output:
Store 101 Total Sales = 0

Overall Sales = 0
Best Performing Store = 101


TEST CASE 4 (Product with Zero Quantity)

Input:
1

101
2
Pen
10
0
Book
50
5

Output:
Pen Sales = 0
Book Sales = 250

Store Total Sales = 250

Overall Sales = 250
Best Selling Product = Book


TEST CASE 5 (Equal Revenue Products)

Input:
1

101
2
Pen
100
10
Book
50
20

Output:
Pen Sales = 1000
Book Sales = 1000

Store Total Sales = 2000

Best Selling Product = Pen
(First encountered product is selected)


TEST CASE 6 (All Sales Zero)

Input:
1

101
3
A
10
0
B
20
0
C
30
0

Output:
Overall Sales = 0
Highest Product Revenue = 0


TIME COMPLEXITY

Best Case:
O(S × P)
(One store with one product)

Average Case:
O(S × P)

Worst Case:
O(S × P)

Where:
S = Number of Stores
P = Number of Products per Store
*/
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
