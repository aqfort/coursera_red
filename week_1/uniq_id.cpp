#include <string>
#include <vector>

using namespace std;

#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a ## b

#define UNIQ_ID CONCAT(var, __COUNTER__)

//#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
//#define UNIQ_ID UNIQ_ID_IMPL(__LINE__)

int main() {
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};
}
