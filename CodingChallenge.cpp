//1
#include <iostream>
using namespace std;
class Dept{
public:
    int n,m[100];
    void in(){
        cout<<"Enter number of students: ";
        cin>>n;
        cout<<"Enter student marks: ";
        for(int i=0;i<n;i++)
            cin>>m[i];
    }
    int top(){
        if(n==0) return -1
        int mx=m[0];
        for(int i=1;i<n;i++)
            if(m[i]>mx)
                mx=m[i];
        return mx;
    }
    float pass(){
        int c=0;
        for(int i=0;i<n;i++)
            if(m[i]>=40)
                c++;
        return (float)c*100/n;
    }
};
int main(){
    cout<<"Enter number of departments: ";
    int d;
    cin>>d;
    Dept a[10];
    for(int i=0;i<d;i++){
        cout<<"\nDepartment "<<i+1<<endl;
        a[i].in();
    }
    int om=-1,od=-1;
    // A. Topper in each department, overall topper, pass percentage
    cout<<"\n--- Result ---\n";
    for(int i=0;i<d;i++){
        int t=a[i].top();
        cout<<"Department "<<i+1<<endl;
        cout<<"Topper Marks = "<<t<<endl;
        cout<<"Pass Percentage = "<<a[i].pass()<<"%"<<endl;
        if(t>om){
            om=t;
            od=i+1;
        }
    }
    cout<<"\nOverall University Topper Marks = "<<om<<endl;
    cout<<"Department = "<<od<<endl;
    // B. Edge Cases
    // Empty department
    // Equal marks
    // All students failing
    return 0;
}

//Output
/*Enter number of departments: 3

Department 1
Enter number of students: 5
Enter student marks: 12
34
65
34
21

Department 2
Enter number of students: 6
Enter student marks: 34
45
67
89
43
43

Department 3
Enter number of students: 5
Enter student marks: 12
21
34
54
44

--- Result ---
Department 1
Topper Marks = 65
Pass Percentage = 20%
Department 2
Topper Marks = 89
Pass Percentage = 83.3333%
Department 3
Topper Marks = 54
Pass Percentage = 40%

Overall University Topper Marks = 89
Department = 2
*/

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

//2
#include <iostream>
using namespace std;
int main(){
    cout<<"Enter number of regions and candidates: ";
    int r,c;
    cin>>r>>c;
    int t[100]={0};
    // A. Find winner in each region
    for(int i=0;i<r;i++){
        cout<<"\nEnter votes for Region "<<i+1<<": ";
        int mx=0,w=0;
        for(int j=0;j<c;j++){
            int v;
            cin>>v;
            t[j]+=v;
            if(v>mx){
                mx=v;
                w=j+1;
            }
        }
        cout<<"Region "<<i+1<<" Winner = Candidate "<<w<<endl;
    }
    // B. Find overall winner
    int mx=0,w=0;
    for(int i=0;i<c;i++){
        if(t[i]>mx){
            mx=t[i];
            w=i+1;
        }
    }
    cout<<"\nOverall Winner = Candidate "<<w<<endl;
    // C. Total votes of each candidate
    cout<<"\nTotal Votes:"<<endl;
    for(int i=0;i<c;i++)
        cout<<"Candidate "<<i+1<<" = "<<t[i]<<endl;
    // D. Edge Cases
    // Tie votes
    // Zero votes
    // Invalid negative votes
    return 0;
}

//Output
/*Enter number of regions and candidates: 3
5

Enter votes for Region 1: 12
32
5
86
67
Region 1 Winner = Candidate 4

Enter votes for Region 2: 54
4
34
45
34
Region 2 Winner = Candidate 1

Enter votes for Region 3: 23
56
66
74
3
Region 3 Winner = Candidate 4

Overall Winner = Candidate 4

Total Votes:
Candidate 1 = 89
Candidate 2 = 92
Candidate 3 = 105
Candidate 4 = 205
Candidate 5 = 104
*/
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//3
#include <iostream>
using namespace std;
class P{
public:
    string n;
    float p;
    int q;
    float sale(){
        return p*q;
    }
};
int main(){
    cout<<"Enter number of stores: ";
    int s;
    cin>>s;
    float all=0,mxp=0,mxs=0;
    string bp;
    int bs=0;
    // A, B, C
    for(int i=0;i<s;i++){
        cout<<"\nEnter number of products in Store "<<i+1<<": ";
        int n;
        cin>>n;
        float ts=0;
        cout<<"Enter ProductName Price Quantity:"<<endl;
        for(int j=0;j<n;j++){
            P x;
            cin>>x.n>>x.p>>x.q;
            float sale=x.sale();
            ts+=sale;
            if(sale>mxp){
                mxp=sale;
                bp=x.n;
            }
        }
        cout<<"Store "<<i+1<<" Sales = "<<ts<<endl;
        all+=ts;
        if(ts>mxs){
            mxs=ts;
            bs=i+1;
        }
    }
    cout<<"\nOverall Sales = "<<all<<endl;
    cout<<"Best Store = "<<bs<<endl;
    cout<<"Best Product = "<<bp<<endl;
    // D. Edge Cases
    // Zero quantity
    // Same sales value
    // Empty store
    return 0;
}

//Output

/*Enter number of stores: 2

Enter number of products in Store 1: 4
Enter ProductName Price Quantity:
soap 25 50
maggie 50 78
rice 50 120
pen 10 150
Store 1 Sales = 12650

Enter number of products in Store 2: 3
Enter ProductName Price Quantity:
food 120 35
drinks 100 100
shampoo 35 140
Store 2 Sales = 19100

Overall Sales = 31750
Best Store = 2
Best Product = drinks
*/
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
