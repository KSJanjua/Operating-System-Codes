#include<iostream>
#include<string>
#include<limits.h>
using namespace std;

class memory
{
    private:
        int block_size;
        int available;
        static int count;
        int block_ID;
    
    public:
        memory()
        {
            block_size=0;
            available=1;
            block_ID=++count;
        }

        memory(int block_size, int available=1)
        {
            this->block_size=block_size;
            this->available=available;
            block_ID=++count;
        }

        void set_data()
        {
            cout << "Enter block size of block " << block_ID << ": " ;
            cin >> block_size;
            cout << "Memory block available? (1 for YES/0 for NO): " ;
            cin >> available;
        }  

        friend class process;
};

class process
{
    private:
        int process_size;
        int allocated;
        static int count;
        int pro_ID;
    
    public:
        process()
        {
            process_size=0;
            allocated=0;
            pro_ID=++count;
        }

        process(int process_size)
        {
            this->process_size=process_size;
            allocated=0;
            pro_ID=++count;
        }

        void set_data()
        {
            cout << "Enter process size of process " << pro_ID << ": " ;
            cin >> process_size;
        }

        void best_fit_memory_alloc(memory* memo_arr, int num_blo)
        {
            int min=INT_MAX;
            int ID=-1;
            for (int j=0; j<num_blo; j++)
            {
                if (memo_arr[j].block_size>process_size && memo_arr[j].available==1)
                {
                    if (min>memo_arr[j].block_size)
                    {
                        min=memo_arr[j].block_size;
                        ID=j;
                    }
                }
            }
            if (ID!=-1)
            {
                allocated=memo_arr[ID].block_ID;
                memo_arr[ID].available=0;
            }
        
        }

        void display_data()
        {
            if (allocated!=0)
            {
                cout << "Process " << pro_ID << " with size " << process_size << " has been allocated block no. " << allocated << endl;
                return; 
            }
            cout << "No memory block allocated to process " << pro_ID ;            
        }
};

int memory::count=0;
int process::count=0;

int main()
{
    int num_pro;
    int num_blo;

    cout << "Enter number of processes: " ;
    cin >> num_pro;

    cout << "Enter number of blocks: " ;
    cin >> num_blo;

    cout << endl;

    process* proc_arr;
    proc_arr = new process[num_pro];

    memory* memo_arr;
    memo_arr = new memory[num_blo];

    for (int i=0; i<num_pro; i++)
    {
        (proc_arr+i)->set_data();
    }

    cout << endl;

    for (int i=0; i<num_blo; i++)
    {
        (memo_arr+i)->set_data();
    }

    cout << endl;

    for (int i=0; i<num_pro; i++) 
        (proc_arr+i)->best_fit_memory_alloc(memo_arr, num_blo);

    for (int i=0; i<num_pro; i++)
        (proc_arr+i)->display_data();

    return 0;
}