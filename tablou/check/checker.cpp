#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

// ===================
// Problem-specific checker
// ===================
bool check_solution(int N, int S,
                    const vector<vector<int>>& expected,
                    const vector<vector<int>>& contestant) {
    int min1, max1, min2, max2;
    int contestantSum = 0;
    min1 = max1 = expected[0][0];
    min2 = max2 = contestant[0][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            min1 = min(min1, expected[i][j]);
            max1 = max(max1, expected[i][j]);
            min2 = min(min2, contestant[i][j]);
            max2 = max(max2,contestant[i][j]);
            contestantSum += contestant[i][j];
        }

    // TODO: add your real verification properties here
    if(max1 - min1 != max2 - min2) return false;
    if(contestantSum != S) return false;
    map<int, set<int>> L, C;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            int val = contestant[i][j];
            if(L[val].find(i) != L[val].end()) return false;
            L[val].insert(i);
            if(C[val].find(j) != C[val].end()) return false;
            C[val].insert(j);
        }
    return true;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: checker <input_file> <expected_file> <contestant_output_file>\n");
        return 1;
    }

    FILE* fin = fopen(argv[1], "r");    // input file
    FILE* fexp = fopen(argv[2], "r");   // expected solution file
    FILE* fout = fopen(argv[3], "r");   // contestant output file

    if (!fin || !fexp || !fout) {
        fprintf(stderr, "Error opening files\n");
        return 1;
    }

    // ===================
    // Read input
    // ===================
    int N, S;
    if (fscanf(fin, "%d %d", &N, &S) != 2) {
        fprintf(stderr, "Failed to read N and S\n");
        return 1;
    }


    // ===================
    // Read expected solution (used for verification info)
    // ===================
    bool no_solution = false;
    int first_val;
    if (fscanf(fexp, "%d", &first_val) != 1) {
        fprintf(stderr, "Failed to read expected solution\n");
        return 1;
    }
    if(first_val == 0)
    {
        no_solution = true;
    }
    vector<vector<int>> expected(N, vector<int>(N));
    if(no_solution == false)
    {
        expected[0][0] = first_val;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                if(i == 0 && j == 0) continue;
                if (fscanf(fexp, "%d", &expected[i][j]) != 1) {
                    fprintf(stderr, "Failed to read expected solution\n");
                    return 1;
                }
            }
    }

    // ===================
    // Read contestant output
    // ===================
    if (fscanf(fout, "%d", &first_val) != 1) {
        fprintf(stderr, "Failed to read contestant output\n");
        fclose(fin);
        fclose(fexp);
        fclose(fout);
        return 1;
    }
    if(first_val == 0)
    {
        if(no_solution == true)
        {
            fprintf(stderr, "Correct solution!\n");
            printf("1.0\n");
        }
        else
        {
            fprintf(stderr, "Incorrect solution!\n");
            printf("0.0\n");
        }
        fclose(fin);
        fclose(fexp);
        fclose(fout);
        return 0;
    }
    vector<vector<int>> contestant(N, vector<int>(N));
    contestant[0][0] = first_val;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if(i == 0 && j == 0) continue;
            if (fscanf(fout, "%d", &contestant[i][j]) != 1) {
                fprintf(stderr, "Contestant output incomplete or invalid\n");
                printf("0.0\n");  // wrong
                fclose(fin);
                fclose(fexp);
                fclose(fout);
                return 0;
            }
        }

    // ===================
    // Verify solution using expected info
    // ===================
    bool valid = check_solution(N, S, expected, contestant);

    if (valid) {
        fprintf(stderr, "Correct solution!\n");
        printf("1.0\n");
    } else {
        fprintf(stderr, "Incorrect solution!\n");
        printf("0.0\n");
    }

    fclose(fin);
    fclose(fexp);
    fclose(fout);
    return 0;
}
