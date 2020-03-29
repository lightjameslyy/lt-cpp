#include <vector>

using namespace std;

class KMP {
  private:
    string pat_;
    vector<vector<int>> dp_;

  public:
    explicit KMP(string pat) : pat_(pat) {
        int M = pat_.length();
        dp_ = vector<vector<int>>(M, vector<int>(256, 0));
        // base case
        dp_[0][pat_[0]] = 1; // dp_[0][others] = 0
        int X = 0;           // restart position
        for (int j = 1; j < M; ++j) {
            for (int c = 0; c < 256; ++c) {
                if (pat_[j] == c)
                    dp_[j][c] = j + 1;
                else
                    dp_[j][c] = dp_[X][c];
            }
            X = dp_[X][pat_[j]];
        }
    }

    int search(string txt) {
        int M = pat_.length();
        int N = txt.length();
        // initial state of pat: j = 0
        int j = 0;
        for (int i = 0; i < N; ++i) {
            // state transmission
            j = dp_[j][txt[i]];
            if (j == M)
                return i - M + 1;
        }
        return -1;
    }
};