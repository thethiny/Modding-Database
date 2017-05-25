/**

                    IMPORTANT NOTICES ON HOW I WROTE THE ALGORITHMS

 Completion Time is the moment the process is over with respect to 0, regardless of arrive time
 Total CPU Time is the turnaround of the process, or how long the CPU was running since it arrived till it ended including intermediate processes
 Require CPU Time is Burst Time
 Round Robin Algorithm explained in the function
 For Shortest/Longest Job Time, the calculations will be dynamic according to the CPU time LEFT
   Example, P1 with 8 Burst Time will not interrupt P2 with 4 Burst time in LJF if P1 started 6 units earlier than P2
   Because in such case P1 will need 2 more units to complete, which is less than 4
   This is in Preemptive Scheduling
 Priority will be ignored in cases that it's not used (Notice will be printed)


                            Ridhwan Al-Debsi / U14110128

*/


#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<queue>
#include<stack>
using namespace std;

struct process
{
    int burstTime, arrTime, priority; //User Entered
    int reqTime = 0, startTime = 0, completionTime = 0, totalWaitTime = 0, turnaround = 0, ID; //Calculated
    int runTime = 0;
};

void print(process* p, int x)
{
    //Print the Table
    system("mode con: cols=150 lines=40");
    cout<<left<<setw(8)<<"FCFS"<<setw(16)<<"Arrival Time"<<setw(12)<<"Priority"<<setw(24)<<"Required CPU Time"<<setw(18)<<"Starting Time"<<setw(24)<<"Total CPU Time";
    cout<<setw(24)<<"Total Waiting Time"<<setw(24)<<"Completion Time"<<endl;

    //Display the Processes in order of user input
    for (int j = 0; j < x; j++)
    {
        for (int i = 0; i < x; i++)
        {
            if (p[i].ID == j+1)
            {
                cout<<setw(1)<<"P"<<setw(7)<<p[i].ID;
                cout<<setw(16)<<p[i].arrTime;
                cout<<setw(12)<<p[i].priority;
                cout<<setw(24)<<p[i].burstTime;
                cout<<setw(18)<<p[i].startTime;
                cout<<setw(24)<<p[i].turnaround;
                cout<<setw(24)<<p[i].totalWaitTime;
                cout<<setw(24)<<p[i].completionTime;
                cout<<endl;
                break;
            }
        }
    }

}

void init(int pAmt, process* pro)
{
    for (int i = 0; i < pAmt; i++)
    {
        cout<<"  Process "<<i+1<<endl;
        cout<<"    Burst Time: ";
        cin>>pro[i].burstTime;
        cout<<"    Arrival Time: ";
        cin>>pro[i].arrTime;
        cout<<"    Priority: ";
        cin>>pro[i].priority;
        pro[i].ID=i+1;
    }
}

double FCFS()
{
    int numberOfProcesses;
    process *p;

    cout<<"First Come First Serve Algorithm:\n\n";

    cout<<"Fill out the following details: ";
    cout<<"\n    Processes amount: ";
    cin>>numberOfProcesses;

    p = new process[numberOfProcesses];

    init(numberOfProcesses, p);

    //Selection Sort
    for (int i = 0; i < numberOfProcesses -1; i++)
    {
        int k = i;
        process temp;
        for (int j = i; j < numberOfProcesses; j++)
        {
            if (p[k].arrTime > p[j].arrTime)
            {
                k = j;
            }
        }
        if (k != i)
        {
            temp = p[k];
            p[k] = p[i];
            p[i] = temp;
        }
    }
    for(int i = 0; i < numberOfProcesses; i++)
    {
        if (i == 0)
        {
            p[i].startTime = p[i].arrTime;
        }
        else if (i > 0)
        {
            if (p[i-1].startTime + p[i-1].burstTime > p[i].arrTime)
                p[i].startTime = p[i-1].turnaround + p[i-1].arrTime;
            else
                p[i].startTime = p[i].arrTime;
        }


        p[i].totalWaitTime = p[i].startTime - p[i].arrTime;
        p[i].turnaround = p[i].totalWaitTime + p[i].burstTime;
        p[i].completionTime = p[i].turnaround + p[i].arrTime;
    }

    print(p, numberOfProcesses);
}
double PSp(int numberOfProcesses, process *p)
{
    double avg = 0;
    int time = 0, tos = 0;
    bool done = 0;
    process *q, *temp, **stack;

    stack = new process*[numberOfProcesses];


    //Selection Sort
    for (int i = 0; i < numberOfProcesses -1; i++)
    {
        int k = i;
        process temp;
        for (int j = i; j < numberOfProcesses; j++)
        {
            if (p[k].arrTime > p[j].arrTime)
            {
                k = j;
            }
        }
        if (k != i)
        {
            temp = p[k];
            p[k] = p[i];
            p[i] = temp;
        }
    }

    while(!done)
    {
        for (int i = 0; i < numberOfProcesses; i++)
        {
            //If it arrives, add it to the stack
            if (p[i].arrTime == time)
            {
                stack[tos] = &p[i];
                tos++;
            }
        }

        if (tos > 0) //If stack has elements
        {
            q = stack[tos-1]; //Current process is the one in the stack
            tos--;

        }
        else
        {
            time++;
            continue;
        }
        for (int i = 0; i < tos ; i++) //Find the next process to start
        {
            if (stack[i]->priority > q->priority) ///Search for the Highest Priority
            {
                temp = q;
                q = stack[i];
                stack[i] = temp;
            }
            else if (stack[i]->priority == q->priority) ///If Equal Priority, prefer the first arrival
            {
                if (stack[i]->arrTime < q->arrTime)
                {
                    temp = q;
                    q = stack[i];
                    stack[i] = temp;
                }
            }

        }

        if (q->runTime < q->burstTime) //If job not finished
        {
            if (q->runTime == 0) //If it never worked before, then it just started
                q->startTime = time;
            q->runTime++;
        }

        //All stacks in Queue are waiting
        for (int i = 0; i < tos; i++)
            stack[i]->totalWaitTime++;

        //After it works, put it back into the queue
        if (q->runTime < q->burstTime)
        {
            stack[tos] = q;
            tos++;
        }



        //If all processes are done, exit
        done = 1;
        for (int i = 0; i < numberOfProcesses; i++)
        {
            if (p[i].runTime < p[i].burstTime) //If process isn't done
                done = 0;
        }


        //Next CPU Cycle
        time++;

        //Completion Time
        for (int i = 0; i < numberOfProcesses; i++)
        {
            if (p[i].runTime == p[i].burstTime && p[i].completionTime == 0 && p[i].burstTime > 0)
                p[i].completionTime = time;

        }
    }

    for (int i = 0; i < numberOfProcesses; i++)
    {
        p[i].turnaround = p[i].totalWaitTime + p[i].burstTime;
        avg += p[i].totalWaitTime;
    }

    print(p, numberOfProcesses);
    avg /= double(numberOfProcesses);
    cout<<endl<<"The Average Waiting Time is: "<<avg<<" units."<<endl;
    return avg;
}

double PSn()
{
    //NonPremptive Here
}

double PS()
{
    char c;
    double avg;
    int numberOfProcesses;
    process *p;

    cout<<"Priorty Scheduling Algorithm:\n";
    cout<<"Preemptive (Y) or Non-Preemptive (N)(default)? ";
    cin>>c;
    cout<<"\nFill out the following details: (Priority will be ignored)";
    cout<<"\n    Processes amount: ";
    cin>>numberOfProcesses;

    p = new process[numberOfProcesses];

    init(numberOfProcesses, p);

    system("cls");

    if (c == 'Y' || c =='y')
        avg = PSp(numberOfProcesses, p);
    else avg = PSn();

    return avg;

}
double SJF()
{
    int numberOfProcesses, time = 0, tos = 0;
    bool done = 0;
    process *p, *q, *temp, **stack;

    cout<<"Shortest Job First Algorithm:\n\n";

    cout<<"Fill out the following details: (Priority will be ignored)";
    cout<<"\n    Processes amount: ";
    cin>>numberOfProcesses;

    p = new process[numberOfProcesses];
    stack = new process*[numberOfProcesses];

    init(numberOfProcesses, p);

    //Selection Sort
    for (int i = 0; i < numberOfProcesses -1; i++)
    {
        int k = i;
        process temp;
        for (int j = i; j < numberOfProcesses; j++)
        {
            if (p[k].arrTime > p[j].arrTime)
            {
                k = j;
            }
        }
        if (k != i)
        {
            temp = p[k];
            p[k] = p[i];
            p[i] = temp;
        }
    }

    while(!done)
    {
        for (int i = 0; i < numberOfProcesses; i++)
        {
            //If it arrives, add it to the stack
            if (p[i].arrTime == time)
            {
                stack[tos] = &p[i];
                tos++;
            }
        }

        if (tos > 0) //If stack has elements
        {
            q = stack[tos-1]; //Current process is the one in the stack
            tos--;

        }
        else
        {
            time++;
            continue;
        }
        for (int i = 0; i < tos ; i++) //Find the next process to start
        {
            if (stack[i]->burstTime - stack[i]->runTime < q->burstTime - q->runTime) ///Higher Priority is given to the process with the Shortest REMAINING time
            {
                temp = q;
                q = stack[i];
                stack[i] = temp;
            }
            else if (stack[i]->burstTime - stack[i]->runTime == q->burstTime - q->runTime)
            {
                if (stack[i]->arrTime < p->arrTime) ///Higher Priority to first arrival if equal times
                {
                    temp = q;
                    q = stack[i];
                    stack[i] = temp;
                }
            }

        }

        if (q->runTime < q->burstTime) //If job not finished
        {
            if (q->runTime == 0) //If it never worked before, then it just started
                q->startTime = time;
            q->runTime++;
        }

        //All stacks in Queue are waiting
        for (int i = 0; i < tos; i++)
            stack[i]->totalWaitTime++;

        //After it works, put it back into the queue
        if (q->runTime < q->burstTime)
        {
            stack[tos] = q;
            tos++;
        }



        //If all processes are done, exit
        done = 1;
        for (int i = 0; i < numberOfProcesses; i++)
        {
            if (p[i].runTime < p[i].burstTime) //If process isn't done
                done = 0;
        }

        //Next CPU Cycle
        time++;

        //Completion Time
        for (int i = 0; i < numberOfProcesses; i++)
        {
            if (p[i].runTime == p[i].burstTime && p[i].completionTime == 0 && p[i].burstTime > 0)
                p[i].completionTime = time;

        }
    }

    for (int i = 0; i < numberOfProcesses; i++)
        p[i].turnaround = p[i].burstTime + p[i].totalWaitTime;


    print(p, numberOfProcesses);

}
double LJF()
{
    int numberOfProcesses, time = 0, tos = 0;
    bool done = 0;
    process *p, *q, *temp, **stack;

    cout<<"Longest Job First Algorithm:\n\n";

    cout<<"Fill out the following details: (Priority will be ignored)";
    cout<<"\n    Processes amount: ";
    cin>>numberOfProcesses;

    p = new process[numberOfProcesses];
    stack = new process*[numberOfProcesses];

    init(numberOfProcesses, p);

    //Selection Sort
    for (int i = 0; i < numberOfProcesses -1; i++)
    {
        int k = i;
        process temp;
        for (int j = i; j < numberOfProcesses; j++)
        {
            if (p[k].arrTime > p[j].arrTime)
            {
                k = j;
            }
        }
        if (k != i)
        {
            temp = p[k];
            p[k] = p[i];
            p[i] = temp;
        }
    }

    while(!done)
    {
        for (int i = 0; i < numberOfProcesses; i++)
        {
            //If it arrives, add it to the stack
            if (p[i].arrTime == time)
            {
                stack[tos] = &p[i];
                tos++;
            }
        }


        if (tos > 0) //If stack has elements
        {
            q = stack[tos-1]; //Current process is the one in the stack
            tos--;

        }
        else ///No Processes Arrived or all that arrived are done
        {
            time++; //Next CPU Cycke
            continue;
        }
        for (int i = 0; i < tos ; i++) //Find the next process to start
        {
            if (stack[i]->burstTime - stack[i]->runTime > q->burstTime - q->runTime) ///Higher priority is given to the process with the Longest REMAINING time
            {
                temp = q;
                q = stack[i];
                stack[i] = temp;
            }
            else if (stack[i]->burstTime - stack[i]->runTime == q->burstTime - q->runTime) ///Higher Priority to first arrival if equal job time left
            {
                if (stack[i]->arrTime < q->arrTime)
                {
                    temp = q;
                    q = stack[i];
                    stack[i] = temp;
                }
            }

        }

        if (q->runTime < q->burstTime) //If job not finished
        {
            if (q->runTime == 0) //If it never worked before, then it just started
                q->startTime = time;
            q->runTime++;
        }

        //All stacks in Queue are waiting
        for (int i = 0; i < tos; i++)
            stack[i]->totalWaitTime++;

        //After it works, put it back into the queue
        if (q->runTime < q->burstTime)
        {
            stack[tos] = q;
            tos++;
        }


        //If all processes are done, exit
        done = 1;
        for (int i = 0; i < numberOfProcesses; i++)
        {
            if (p[i].runTime < p[i].burstTime) //If process isn't done
                done = 0;
        }

            cout<<"\nCurrent Time: "<<time;



        //Next CPU Cycle
        time++;

        //Completion Time
        for (int i = 0; i < numberOfProcesses; i++)
        {
            if (p[i].runTime == p[i].burstTime && p[i].completionTime == 0 && p[i].burstTime > 0)
                p[i].completionTime = time;

        }


    }


    for (int i = 0; i < numberOfProcesses; i++)
        p[i].turnaround = p[i].burstTime + p[i].totalWaitTime;


    print(p, numberOfProcesses);


}
double RR()
{
    int numberOfProcesses, quantum, *bursts, time;
    bool done;
    process *p;

    cout<<"Round Robin Algorithm:\n\n";
    /** If a process uses its quantum, then another process arrives, the new process gets the turn.
            Example: P1 Burst 8 Arrive 0, P2 Burst 2 Arrive 4, Quantum 4
            P1 will use its Quantum Twice, then P2 will arrive, then P2 will use its Quantum

            A few test cases are noted:

                Burst   Arrival
            P1  5       0
            P2  5       3       Quantum1 = 2
            P3  5       4       Quantum2 = 3
            P4  5       7

            Results:
                Quantum1
                Start   Wait    Completion
            P1  0       6       11
            P2  4       10      15
            P3  6       10      15
            P4  8       8       13

                Quantum2
                Start   Wait    Completion
            P1  0       9       14
            P2  3       8       13
            P3  6       9       14
            P4  9       8       13

            ____________________
                Burst   Arrival Start   Wait    Completion
            P1  3       0       0       0       3
            P2  4       4       4       0       4       Quantum = 2
            P3  5       10      10      0       5
            P4  6       16      16      0       6

    */
    cout<<"Fill out the following details: (Priority will be ignored)";
    cout<<"\n    Processes amount: ";
    cin>>numberOfProcesses;
    cout<<"    Quantum Time: ";
    cin>>quantum;

    p = new process[numberOfProcesses];
    bursts = new int[numberOfProcesses];

    init(numberOfProcesses, p);

    //Selection Sort
    for (int i = 0; i < numberOfProcesses -1; i++)
    {
        int k = i;
        process temp;
        for (int j = i; j < numberOfProcesses; j++)
        {
            if (p[k].arrTime > p[j].arrTime)
            {
                k = j;
            }
        }
        if (k != i)
        {
            temp = p[k];
            p[k] = p[i];
            p[i] = temp;
        }
    }

    for (int i = 0; i < numberOfProcesses; i++)
    {
        bursts[i] = p[i].burstTime;
    }

    //Loop until all bursts are finished
    time = p[0].arrTime;
    cout<<"Time at start is "<<time<<endl;
    while(!done)
    {
        done = 0;
        for (int i = 0; i < numberOfProcesses; i++)
        {
            //cout<<"Info\n    "<<bursts[i]<<" == "<<p[i].burstTime<<" && "<<time<<" >= "<<p[i].arrTime<<endl;
            if (bursts[i] == p[i].burstTime && time >= p[i].arrTime) //First time here
            {
                p[i].startTime = time;
                //cout<<i+1<<"Started at "<<time<<endl;
            }
            if (bursts[i] > 0 && p[i].arrTime <= time)
            {
                time += quantum;
                bursts[i] -= quantum;
                if (bursts[i] < 0)
                time += bursts[i];

                for (int j = 0; j < numberOfProcesses; j++)
                {
                    cout<<"        "<<j<<" != "<<i<<" && "<<bursts[j]<<" > 0 && "<<p[j].arrTime<<" <= "<<time<<endl;
                    if (j != i && bursts[j] > 0 && p[j].arrTime < time)
                    {
                        p[j].totalWaitTime += quantum;
                        if (bursts[i] < 0)
                            p[j].totalWaitTime += bursts[i];


                        cout<<"P"<<i+1<<" added to P"<<j+1<<" to become "<<p[j].totalWaitTime<<endl;
                    }
                }
            }


        }
        //system("pause");

        done = 0;
        for (int i = 0; i < numberOfProcesses; i++)
        {
            //if you arrived and are still working
            if (time >= p[i].arrTime && bursts[i] >0)
                {
                    done = 1;
                }
        }

        if (!done)
            time++;



        //check if all are = 0
        done = 1;
        for (int i = 0; i < numberOfProcesses; i++)
        {
            if (bursts[i] > 0)
                {
                    done = 0;
                    break;
                }
        }
    }

    for (int i = 0; i < numberOfProcesses; i++)
    {
        p[i].totalWaitTime -= p[i].arrTime%quantum;
        p[i].turnaround = p[i].totalWaitTime + p[i].burstTime;
        p[i].completionTime = p[i].turnaround + p[i].arrTime;
    }

    print(p, numberOfProcesses);

}

int main()
{
    double time;
    string alg;
    Retry: //Note, all of them have no avg time yet
    cout<<" Enter the Abbreviation of the Name of the Algorithm: ";
    cout<<"\n ====================================================";
    cout<<"\n FCFS: First Come First Serve"; //Working
    cout<<"\n PS: Priority Scheduling"; //Working Need Testing Need NonPremtive
    cout<<"\n SJF: Shortest Job First"; //Working Need Testing Need NonPremtive
    cout<<"\n LJF: Longest Job First"; //Need Testing Need Non Premtive
    cout<<"\n RR: Round Robin:"; //Working
    cout<<"\n ====================================================";
    cout<<"\n\nChoice: ";
    cin>>alg;
    system("cls");

    //Normalize Capitalization
    for (int i = 0; i < alg.length(); i++)
            alg[i] = toupper(alg[i]);

    //Function Calls
    if (alg == "FCFS")
        time = FCFS();
    else if (alg == "PS")
        time = PS();
    else if (alg == "SJF")
        time = SJF();
    else if (alg == "LJF")
        time = LJF();
    else if (alg == "RR")
        time = RR();
    else
    {
        cout<<"Invalid Option... Retry input\n\n";
        goto Retry;
    }
}
