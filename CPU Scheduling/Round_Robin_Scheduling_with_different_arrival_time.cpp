#include<iostream>
#include<iomanip>
#include<queue>
using namespace std;

class processes
{
    private:
        int process_id;
        int arrival_time;
        int burst_time;
        int turnaround_time;
        int completion_time;
        int waiting_time;
        static int count;
        static int time_quanta;
        bool in_queue;

    public:
        processes()
        {
            process_id=++count;
            arrival_time=0;
            burst_time=0;
            turnaround_time=0;
            completion_time=0;
            waiting_time=0;
            in_queue=false;
        }
        void set_data()
        {
            cout << "Enter arrival time for process " << process_id << ": " ;
            cin >> arrival_time;
            cout << "Enter burst time for process " << process_id << ": " ;
            cin >> burst_time;
            cout << endl;
        }

        void sort_processes(processes* proc_arr, int num_pro)
        {
            for (int i=1; i<=num_pro-1; i++)
            {
                bool flag=true;
                for (int j=0; j<=num_pro-1-i; j++)
                {
                    if (proc_arr[j].arrival_time>proc_arr[j+1].arrival_time)
                    {
                        flag=false;
                        swap(proc_arr[j],proc_arr[j+1]);
                    }
                }
                if (flag==true)
                    break;
            }
        }

        void final_sorting(processes* proc_arr, int num_pro)
        {
            for (int i=1; i<=num_pro-1; i++)
            {
                bool flag=true;
                for (int j=0; j<=num_pro-1-i; j++)
                {
                    if (proc_arr[j].process_id>proc_arr[j+1].process_id)
                    {
                        flag=false;
                        swap(proc_arr[j],proc_arr[j+1]);
                    }
                }
                if (flag==true)
                    break;
            }
        }

        void calculate_values(processes* proc_arr, int num_pro)
        {
            int remaining_time[num_pro];

            for (int i=0; i<num_pro; i++)
                remaining_time[i]=proc_arr[i].burst_time;

            int time=0;
            time += proc_arr[0].arrival_time;

            queue <int> q;
            q.push(0);
            proc_arr[0].in_queue=true;

            int complete=0;

            while (complete<num_pro)
            {
                bool remaining=true;
                if (!q.empty())
                {
                    int pro_ind=q.front();
                    q.pop();
                    proc_arr[pro_ind].in_queue=false;

                    if (remaining_time[pro_ind]>time_quanta)
                    {
                        time+=time_quanta;
                        remaining_time[pro_ind]-=time_quanta;
                        remaining=true;
                    }

                    else
                    {
                        time+=remaining_time[pro_ind];
                        remaining_time[pro_ind]=0;
                        proc_arr[pro_ind].completion_time=time;
                        proc_arr[pro_ind].turnaround_time=proc_arr[pro_ind].completion_time-proc_arr[pro_ind].arrival_time;
                        proc_arr[pro_ind].waiting_time=proc_arr[pro_ind].turnaround_time-proc_arr[pro_ind].burst_time;
                        complete++;
                        remaining=false;
                    }

                    for (int i=0; i<num_pro; i++)
                    {
                        if (proc_arr[i].arrival_time<=time && remaining_time[i]!=0 && !proc_arr[i].in_queue && i!=pro_ind)
                        {
                            q.push(i);
                            proc_arr[i].in_queue=true;
                        }
                    }

                    if (remaining==true)
                    {
                        q.push(pro_ind);
                        proc_arr[pro_ind].in_queue=true;
                    }
                }
                else
                {
                    for (int i=0; i<num_pro; i++)
                    {
                        if (remaining_time[i]!=0)
                        {
                            time = proc_arr[i].arrival_time;
                            q.push(i);
                            proc_arr[i].in_queue=true;
                            break;
                        }
                    }
                }
                
            }
        }

        void show_data(processes* proc_arr, int num_pro)
        {
            final_sorting(proc_arr,num_pro);

            int sum_waiting_time=0;
            int sum_turnaround_time=0;

            cout << "Time Quanta for processes is " << time_quanta << endl << endl;

            cout << setw(20) << "Process ID" << setw(20) << "Arrival Time" << setw(20) << "Burst Time" << setw(20) <<  "Completion Time" << setw(20) << "Turnaround Time" << setw(20) << "Waiting Time" << endl;
            for (int i=0; i<num_pro; i++)
            {
                cout << setw(20) << proc_arr[i].process_id << setw(20) << proc_arr[i].arrival_time << setw(20) << proc_arr[i].burst_time << setw(20) << proc_arr[i].completion_time << setw(20) << proc_arr[i].turnaround_time << setw(20) << proc_arr[i].waiting_time << endl ;

                sum_waiting_time+=proc_arr[i].waiting_time;
                sum_turnaround_time+=proc_arr[i].turnaround_time;
            }   

            cout << "Average Waiting Time: " << float(sum_waiting_time)/float(num_pro) << endl;
            cout << "Average Turnaround Time: " << float(sum_turnaround_time)/float(num_pro) << endl;
        }
};

int processes::count=0;
int processes::time_quanta=2;

int main()
{
    int num_pro;

    cout << "Enter number of processes: ";
    cin >> num_pro;

    cout << endl;

    processes *proc_arr = new processes[num_pro];

    for (int i=0; i<num_pro; i++)
    {
        proc_arr[i].set_data();
    }

    processes temp_pro;

    temp_pro.sort_processes(proc_arr,num_pro);
    temp_pro.calculate_values(proc_arr,num_pro);
    temp_pro.show_data(proc_arr,num_pro);

    delete[] proc_arr;    

    return 0;
}