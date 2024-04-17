#include <iostream>
using namespace std;
class qui
{
    public:
    int x;
    int y;
    int juli_2(const qui &q)
    {
       // cout << q.x << endl;
        int ret=(this->x - q.x) * (this->x - q.x) + (this->y - q.y) * (this->y - q.y);
       // cout << ret;
        return ret;
    }
};

int main()
{
    int n;
    cin >> n;
    qui dian[n];
    int jvli[n][n];
    for (int i = 0; i < n; i++)
    {
        cin >> dian[i].x >> dian[i].y;
        for (int j = 0; j < i; j++)
        {
            
            jvli[j][i] = dian[i].juli_2(dian[j]);
            jvli[i][j] = jvli[j][i];
           // cout <<"dian[i].x=="<<dian[i].x<<" " <<dian[i].juli_2(dian[j]) <<"\n";
        }
    }
    for (int i = 0; i < n; i++)
    {
        int max = -1;
        int count = -1;
        for (int j = n - 1; j >= 0; j--)
        {
            if (j != i)
            {
                if (jvli[i][j] >= max || max == -1)
                {
                    max = jvli[i][j];
                    count = j;
                }
            }
        }
        cout << count+1 << "\n";
    }
    return 0;
}