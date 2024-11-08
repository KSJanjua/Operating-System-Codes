#include<iostream>
using namespace std;

int main()
{
    int num_pro;
    int num_reso;

    cout << "Enter number of processes: " ;
    cin >> num_pro;

    cout << "Enter types of Resources available? ";
    cin >> num_reso;

    cout << endl;

    int maximum[num_pro][num_reso];
    int allocated[num_pro][num_reso];
    int need[num_pro][num_reso];
    int available[num_reso];

    cout << "***********Maximum need of Resources for each process***********" << endl << endl ;
    for (int i=0; i<num_pro; i++)
    {
        for (int j=0; j<num_reso; j++)
        {
            cout << "Enter maximum number of instances of resource " << j+1 << " requested by process " << i+1 << ": ";
            cin >> maximum[i][j];
        }
        cout << endl;
    }

    cout << "***********Resources of each type allocated to each process***********" << endl << endl ;
    for (int i=0; i<num_pro; i++)
    {
        for (int j=0; j<num_reso; j++)
        {
            cout << "Enter number of instances of resource " << j+1 << " allocated to process " << i+1 << ": ";
            cin >> allocated[i][j];
        }
        cout << endl;
    }

    cout << "***********Instances of each resource type available after allocation***********" << endl << endl ;
    for (int i=0; i<num_reso; i++)
    {
        cout << "Enter number of instances of resource " << i+1 << " available after allocation: " ;
        cin >> available[i];
    }

    for (int i=0; i<num_pro; i++)
    {
        for (int j=0; j<num_reso; j++)
            need[i][j]=maximum[i][j]-allocated[i][j];
    }

    int safe_sequence[num_pro]={0};
    int completed[num_pro]={0};
    int index=0;

    bool found;

    do
    {
        found=false;
        for (int i=0; i<num_pro; i++)
        {
            if (completed[i]==0)
            {
                bool can_execute=true;
                for (int j=0; j<num_reso; j++)
                {
                    if (need[i][j]>available[j])
                    {
                        can_execute=false;
                        break;
                    }
                }

                if (can_execute)
                {
                    safe_sequence[index++]=i+1;
                    completed[i]=1;
                    for (int j=0; j<num_reso; j++)
                    {
                        available[j]+=allocated[i][j];
                        allocated[i][j]=0;
                        need[i][j]=0;
                    }
                    found=true;
                }
            }
        }
    }
    while (found && index<num_pro);

    if (index==num_pro)
    {
        cout << "Safe sequence is: " << endl ;
        for (int i=0; i<num_pro-1; i++)
            cout << "P" << safe_sequence[i] << "  ->  " ;
        cout << "P" << safe_sequence[num_pro-1] ;
    }
    else
    {
        cout << "Safe sequence does not exist." << endl;
    }

    return 0;
}