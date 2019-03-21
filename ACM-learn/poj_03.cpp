// 1011
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;

typedef vector<int> Vector_Int;
typedef vector<bool> Vector_Bool;

bool dfs(const Vector_Int &part_length, Vector_Bool &use_of_parts, 
            int choose_id, int left_length, int done_number, 
            const int dest_length, const int dest_number_sticks)
{
    // used to debug
    // cout << "part_length: " << endl;
    // for(Vector_Int::const_iterator iter = part_length.cbegin(); 
    //     iter != part_length.cend(); iter++)
    // {
    //     cout << *iter << " ";
    // }
    // cout << endl;
    // cout << "use_of_parts: " << endl;
    // for(Vector_Bool::iterator iter = use_of_parts.begin(); iter != use_of_parts.end(); iter++)
    // {
    //     cout << *iter << " ";
    // }
    // cout << endl << endl;cout << "part_length: " << endl;
    // for(Vector_Int::const_iterator iter = part_length.cbegin(); 
    //     iter != part_length.cend(); iter++)
    // {
    //     cout << *iter << " ";
    // }
    // cout << endl;
    // cout << "use_of_parts: " << endl;
    // for(Vector_Bool::iterator iter = use_of_parts.begin(); iter != use_of_parts.end(); iter++)
    // {
    //     cout << *iter << " ";
    // }
    // cout << endl << endl;

    int n = part_length.size();
    if(part_length[choose_id] > left_length)    // left part is too long
    {
        return false;
    }
    else if(part_length[choose_id] == left_length)  // compltete a stick
    {
        done_number++;
        if(done_number == dest_number_sticks)    // mission compltete
        {
            return true;
        }
        // try all unsued stick
        int id = 0;
        while(use_of_parts[id])
            id++;
        use_of_parts[id] = true;
        if(dfs(part_length, use_of_parts, id, dest_length, done_number, 
            dest_length, dest_number_sticks))
        {
            return true;
        }
        else
        {
            use_of_parts[id] = false;
            return false;
        }
    }
    else    // length of this part is less than left_length
    {
        // try all unused stick
        int last_search_length = -1;
        for(int id = choose_id + 1; id < n; id++)
        {
            if(!use_of_parts[id] && last_search_length != part_length[id])
            {
                use_of_parts[id] = true;
                if(dfs(part_length, use_of_parts, id, left_length - part_length[choose_id], 
                    done_number, dest_length, dest_number_sticks))
                // get a possible result
                {
                    return true;
                }
                else
                {
                    last_search_length = part_length[id];
                    use_of_parts[id] = false;
                }
            }
        }
    }
    return false;
}

bool compute(const Vector_Int &part_length, 
    const int dest_length, const int dest_number_sticks)
{
    int n = part_length.size();
    Vector_Bool use_of_parts(n, false);
    use_of_parts[0] = true;
    return dfs(part_length, use_of_parts, 0, dest_length, 0, 
        dest_length, dest_number_sticks);
}

int main()
{
    int n;
    Vector_Int parts;
    parts.reserve(64);
    while(cin >> n && n > 0)
    {
        parts.resize(n);
        int sum = 0;
        int min_stick_length = 50;
        for(int i = 0; i < n; i++)
        {
            cin >> parts[i];
            sum += parts[i];
        }
        sort(parts.begin(), parts.end(), greater<int>());
        // for(Vector_Int::iterator iter = parts.begin(); iter != parts.end(); iter++)
        // {
        //     cout << *iter << " ";
        // }
        bool done = false;
        for(int length = parts[0]; 2*length <= sum; length++)
        {
            if(sum % length != 0)   // assure all sticks have the same length
            {
                continue;
            }
            int num_of_sticks = sum/length;

            // debug
            // cout << "sum: " << sum << ", num_of_sticks: " << num_of_sticks 
            //     << ", stick length: " << length << endl;

            if(compute(parts, length, num_of_sticks))
            {
                cout << length << endl;
                done = true;
                break;
            }
        }
        if(!done)
            cout << sum << endl;        // only one stick
    }
    return 0;
}