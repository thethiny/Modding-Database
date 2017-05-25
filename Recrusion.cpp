#include<iostream>
#include<stack>
#include<queue>
#include<cstdlib>
#include<ctime>
#include<stdlib.h>
#include<iomanip>
using namespace std;

void printStack(stack<int> s);

void sortStack(stack<int> &s);

void reverseStack(stack<int> &s);

stack<int> mergeStack(stack<int>, stack<int>);

stack<int> mergeSortedStack(stack<int>, stack<int>);

void swapStackElement(stack<int> &, int, int);

stack<int> fillStack(int);

void fnPrint(stack<int> []);

void fnOpCall(stack<int> []);

void fnFill(stack<int> []);

void fnRev(stack<int> []);

void fnMerge(stack<int> []);

void fnMergeSor(stack<int> []);

void fnSwap(stack<int> []);

void fnSort(stack<int> []);

void fnClear(stack<int> []);

void fnInsert(stack<int> []);

bool isSortedStack(stack<int>);

int main()
{
    stack<int> s[5];
    int x,y,z;
    bool t;

    while (!t)
    {
        cout<<"Welcome to Stack Operations..\nStart by filling a stack..\nWhich Stack do you want to Fill (1-5): ";
        cin>>z;
        if (z > 0 && z <6)
            t = true;
        else t = false;
        if (!t)
        {
            system("cls");
            continue;
        }
        cout<<"How many items: ";
        cin>>x;
        switch(z)
        {
            case 1: s[0] = fillStack(x); break;
            case 2: s[1] = fillStack(x); break;
            case 3: s[2] = fillStack(x); break;
            case 4: s[3] = fillStack(x); break;
            case 5: s[4] = fillStack(x); break;
        }

        system("cls");
    }


    fnPrint(s);
    fnOpCall(s);




}

void fnSort(stack<int> s[])
{
    system("cls");
    int x,z;
    bool t;
    while (!t)
    {
        fnPrint(s);
        cout<<"Which Stack do you want to Sort (1-5): ";
        cin>>z;
        if (z > 0 && z <6)
            t = true;
        else t = false;
        if (!t)
        {
            system("cls");
            continue;
        }
        sortStack(s[z-1]);
        reverseStack(s[z-1]);
        system("cls");
    }
    fnOpCall(s);
}

void fnClear(stack<int> s[])
{
    system("cls");
    int x,z;
    bool t;
    while (!t)
    {
        fnPrint(s);
        cout<<"Which Stack do you want to Clear (1-5): ";
        cin>>z;
        if (z > 0 && z <6)
            t = true;
        else t = false;
        if (!t)
        {
            system("cls");
            continue;
        }
        while (!s[z-1].empty())
            s[z-1].pop();
        system("cls");
    }
    fnOpCall(s);

}

bool isSortedStack(stack<int> s)
{
    stack<int> s1 = s;
    sortStack(s1);
    if (s == s1)
        return 1;
    else return 0;
}

void fnFill(stack<int> s[])
{
    system("cls");
    int x,z;
    bool t;
    while (!t)
    {
        fnPrint(s);
        cout<<"Which Stack do you want to Fill (1-5): ";
        cin>>z;
        if (z > 0 && z <6)
            t = true;
        else t = false;
        if (!t)
        {
            system("cls");
            continue;
        }
        cout<<"How many items: ";
        cin>>x;
        switch(z)
        {
            case 1: s[0] = fillStack(x); break;
            case 2: s[1] = fillStack(x); break;
            case 3: s[2] = fillStack(x); break;
            case 4: s[3] = fillStack(x); break;
            case 5: s[4] = fillStack(x); break;
        }

        system("cls");
    }
    fnOpCall(s);
}

void fnRev(stack<int> s[])
{
    system("cls");
    int x,z;
    bool t;
    while (!t)
    {
        fnPrint(s);
        cout<<"Which Stack do you want to Reverse (1-5): ";
        cin>>z;
        if (z > 0 && z <6)
            t = true;
        else t = false;
        if (!t)
        {
            system("cls");
            continue;
        }
        switch(z)
        {
            case 1: reverseStack(s[0]); break;
            case 2: reverseStack(s[1]); break;
            case 3: reverseStack(s[2]); break;
            case 4: reverseStack(s[3]); break;
            case 5: reverseStack(s[4]); break;
        }

        system("cls");
    }
    fnOpCall(s);
}

void fnMerge(stack<int> s[])
{
    system("cls");
    int w,y,z;
    bool t;
        fnPrint(s);
        cout<<"Which 2 Stacks do you want to Merge (1-5): ";
        cin>>z>>y;
        cout<<"Where do you want to store the Merge (1-5): ";
        cin>>w;

        s[w-1] = mergeStack(s[z-1],s[y-1]);

        system("cls");
    fnOpCall(s);

}

void fnMergeSor(stack<int> s[])
{
    system("cls");
    int w,y,z;
    bool t,t2;
    stack<int> s1,s2;
        fnPrint(s);
        cout<<"Which 2 Stacks do you want to Merge Sort (1-5): ";
        cin>>z>>y;
        cout<<"Where do you want to store the Merge (1-5): ";
        cin>>w;
        s1 = s[z-1];
        s2 = s[y-1];
        sortStack(s1);
        sortStack(s2);
        s[w-1] = mergeSortedStack(s1,s2);

        system("cls");
    fnOpCall(s);
}

void fnSwap(stack<int> s[])
{
    system("cls");
    int w,x,y;
    bool t;
        fnPrint(s);
        cout<<"What element would you like to swap with what (Element A swapped with B): ";
        cin>>x>>y;
        cout<<"In which Stack should the swap occur (1-5): ";
        cin>>w;
        swapStackElement(s[w-1],x,y);

        system("cls");
    fnOpCall(s);

}

void fnInsert(stack<int> s[])
{
    int x,w;
    system("cls");
    fnPrint(s);
    cout<<"What Element would you like to insert: ";
    cin>>x;
    cout<<"Into which Stack should it be inserted (1-5): ";
    cin>>w;

    reverseStack(s[w-1]);
    s[w-1].push(x);
    reverseStack(s[w-1]);

    system("cls");
    fnOpCall(s);
}

void fnOpCall(stack<int> s[])
{
    int x;
    bool t;
        system("cls");
        fnPrint(s);
        cout<<"What operation would you like to perform (1-7): ";
        cout<<"\n1:Fill a Stack";
        cout<<"\n2:Reverse a Stack";
        cout<<"\n3:Merge Two Stacks";
        cout<<"\n4:Merge Two Sorted Stacks";
        cout<<"\n5:Swap an element in a Stack";
        cout<<"\n6:Sort a Stack";
        cout<<"\n7:Clear a Stack";
        cout<<"\n8:Insert into a Stack";
        cout<<endl;
        cin>>x;

    switch(x)
    {
    case 1:fnFill(s); break;
    case 2:fnRev(s); break;
    case 3:fnMerge(s); break;
    case 4:fnMergeSor(s); break;
    case 5:fnSwap(s); break;
    case 6:fnSort(s); break;
    case 7:fnClear(s); break;
    case 8:fnInsert(s); break;
    }



}

void fnPrint(stack<int> s[])
{
    cout<<"Your Stacks:\n";
    for (int i = 0; i < 5; i++)
    {
        cout<<"Stack "<<i+1<<"("<<right<<setw(3)<<setfill('0')<<s[i].size()<<"): ";
        printStack(s[i]);
        cout<<endl;
    }
    cout<<endl;
}

stack<int> fillStack(int x)
{
    srand(time(0));
    stack<int> s;

    for (int i = 0; i < x; i++)
        s.push(rand()%50);

    return s;
}

void printStack(stack<int> s)
{
    int size = s.size();
    for (int i = 0; i < size; i++)
    {
        cout<<s.top()<<" ";
        s.pop();
    }

}

void sortStack(stack<int> &s)
{
    stack<int> s1,s2;
    int size = s.size();
    if (s.size() > 1)
    {
        for (int i = 0; i < size; i++)
        {
            s1.push(s.top());
            s.pop();

            while (!s2.empty())
                s2.pop(); //Clear the stack
            while (!s.empty())
            {
                if (s.top() < s1.top())
                {
                    s2.push(s1.top());
                    s1.pop();
                    s1.push(s.top());
                }
                else
                {
                    s2.push(s.top());
                }
                s.pop();
            }
            s = s2;
        }
        s = s1;
    }

}

void reverseStack(stack<int> &s)
{
    stack<int> s1;
    int size = s.size();

    for (int i = 0; i < size; i++)
    {
        s1.push(s.top());
        s.pop();
    }
    s = s1;

}

stack<int> mergeStack(stack<int> s1, stack<int> s2)
{
    stack<int> s = s1;

    while(!s2.empty())
    {
        s.push(s2.top());
        s2.pop();
    }

    return s;

}

stack<int> mergeSortedStack(stack<int> s1, stack<int> s2)
{

    stack<int> s;
    while(!s1.empty() && !s2.empty())
    {
        if (s1.top() > s2.top())
        {
            s.push(s1.top());
            s1.pop();
        }
        else
        {
            s.push(s2.top());
            s2.pop();
        }
    }
    if (s1.empty())
    {
        while (!s2.empty())
        {
            s.push(s2.top());
            s2.pop();
        }
    }
    else
    {
        while (!s1.empty())
        {
            s.push(s1.top());
            s1.pop();
        }
    }
    return s;
}

void swapStackElement(stack<int> &s, int x, int y)
{
    stack<int> s1;

    while(!s.empty())
    {
        if (s.top() == x)
            s1.push(y);
        else s1.push(s.top());
        s.pop();
    }

    reverseStack(s1);
    s = s1;

}


