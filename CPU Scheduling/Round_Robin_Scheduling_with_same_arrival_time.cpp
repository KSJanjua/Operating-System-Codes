#include<iostream>
#include<iomanip>
#include<queue>
using namespace std;

class processes
{
    private:
        int process_id;
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
            burst_time=0;
            turnaround_time=0;
            completion_time=0;
            waiting_time=0;
            in_queue=false;
        }
        void set_data()
        {
            cout << "Enter burst time for process " << process_id << ": " ;
            cin >> burst_time;
            cout << endl;
        }

        void calculate_values(processes* proc_arr, int num_pro)
        {
            int remaining_time[num_pro];
            queue <int> q;

            for (int i=0; i<num_pro; i++)
            {
                remaining_time[i]=proc_arr[i].burst_time;
                q.push(i);
                proc_arr[0].in_queue=true;
            }
                

            int time=0;
            int complete=0;

            while (complete<num_pro)
            {
                if (!q.empty())
                {
                    int pro_ind=q.front();
                    q.pop();
                    proc_arr[pro_ind].in_queue=false;

                    if (remaining_time[pro_ind]>time_quanta)
                    {
                        time+=time_quanta;
                        remaining_time[pro_ind]-=time_quanta;
                        q.push(pro_ind);
                        proc_arr[pro_ind].in_queue=true;
                    }

                    else
                    {
                        time+=remaining_time[pro_ind];
                        remaining_time[pro_ind]=0;
                        proc_arr[pro_ind].completion_time=time;
                        proc_arr[pro_ind].turnaround_time=proc_arr[pro_ind].completion_time;
                        proc_arr[pro_ind].waiting_time=proc_arr[pro_ind].turnaround_time-proc_arr[pro_ind].burst_time;
                        complete++;
                    }
                }
            }
        }

        void show_data(processes* proc_arr, int num_pro)
        {
            int sum_waiting_time=0;
            int sum_turnaround_time=0;

            cout << "Time Quanta for processes is " << time_quanta << endl << endl;

            cout << setw(20) << "Process ID" << setw(20) << "Burst Time" << setw(20) <<  "Completion Time" << setw(20) << "Turnaround Time" << setw(20) << "Waiting Time" << endl;
            for (int i=0; i<num_pro; i++)
            {
                cout << setw(20) << proc_arr[i].process_id << setw(20) << proc_arr[i].burst_time << setw(20) << proc_arr[i].completion_time << setw(20) << proc_arr[i].turnaround_time << setw(20) << proc_arr[i].waiting_time << endl ;

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
        proc_arr[i].set_data();

    processes temp_pro;

    temp_pro.calculate_values(proc_arr,num_pro);
    temp_pro.show_data(proc_arr,num_pro);

    delete[] proc_arr;    

    return 0;
}