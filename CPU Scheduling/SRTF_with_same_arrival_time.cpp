//SRTF with same arrival time is similar to SJF with same arrival time

#include<iostream>
#include<iomanip>
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

    public:
        processes()
        {
            process_id=++count;
            burst_time=0;
            turnaround_time=0;
            completion_time=0;
            waiting_time=0;
        }
        void set_data()
        {
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
                    if (proc_arr[j].burst_time>proc_arr[j+1].burst_time)
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
            int time=0;
            for (int i=0; i<num_pro; i++)
            {
                time += proc_arr[i].burst_time;
                proc_arr[i].completion_time = time;
                proc_arr[i].turnaround_time = proc_arr[i].completion_time;
                proc_arr[i].waiting_time = proc_arr[i].turnaround_time - proc_arr[i].burst_time;
            }
        }

        void show_data(processes* proc_arr, int num_pro)
        {
            final_sorting(proc_arr,num_pro);

            int sum_waiting_time=0;
            int sum_turnaround_time=0;

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