#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int k;
    cout << "Please enter k: " << endl;
    cin >> k;
    
    vector<int> v;
    for(int i = 0; i <= 2*k; i++)
    v.push_back(i);
   
    vector<int> v1;
    for(int i = 0; i <= 2*k; i++)
    v1.push_back(0);
    
    vector<int> vcount;
    
    for( int z = 1; z <= k; z++)
    {
       for (int p = 0; p < z; p++)
       v1[1+p*2] = v[1+z+p];
       
       for (int i = 0; i <= z; i++)
       v1[2*i] = v[i];
       
       for (int j = 0; j < v1.size(); j++)
       if(v1[j] == 0){ v1[j] = j;}
       
       for(int i = 0; i < v.size(); i++)
       v[i] = v1[i];
       
       vcount.push_back(v[1]);
    }
    
    for (int z = k; z >= 1; z--)
    {
       for (int p = 0; p < z; p++)
       v1[1+p*2] = v[1+z+p];
       
       for (int i = 0; i <= z; i++)
       v1[2*i] = v[i];
       
       for (int j = 0; j < v1.size(); j++)
       if(v1[j] == 0){v1[j] = j;}
       
       for(int i = 0; i < v.size(); i++)
       v[i] = v1[i];
       
       vcount.push_back(v[1]);
    }
    
    cout << "The three topmost cards after the complete shuffling is: " << v[1] << ", " << v[2] << ", " << v[3] << endl;
    
    //b
    vector<int> vf;
    for(int i = 0; i <= 2*k; i++)
    vf.push_back(0);
    
    for (int i = 0; i < vcount.size(); i++)
    vf[vcount[i]] = vf[vcount[i]] + 1;
    vf[0] = 0;
    
    int a, b, c;
    int max1, max2, max3;
    int f1, f2, f3;
    a = vf[1]; b = vf[2]; c = vf[3];
    
    if (a >= b){
       if (a >= c){
           if (b >= c){ max1 = a; f1 = 1; max2 = b; f2 = 2; max3 = c; f3 = 3;}
           else{ max1 = a; f1 = 1; max2 = c; f2 = 3; max3 = b; f3 = 2;}
       }
       else{ max1 = c; f1 = 3; max2 = a; f2 = 1; max3 = b; f3 = 2;}
    }
    else{
       if (b >= c){
           if (a >= c){ max1 = b; f1 = 2; max2 = a; f2 = 1; max3 = c; f3 = 3;}
           else{ max1 = b; f1 = 2; max2 = c; f2 = 3; max3 = a; f3 = 1;}
       }
       else{ max1 = c; f1 = 3; max2 = b; f2 = 2; max3 = a; f3 = 1;}
    }
    
    for (int i = 4; i < vf.size(); i++)
    {
       int d = vf[i];
       if (d > max1 ){ max3 = max2; f3 = f2; max2 = max1; f2 = f1; max1 = d; f1 = i;}
       else if (max1 >= d && d > max2){ max3 = max2; f3 = f2; max2 = d; f2 = i;}
       else if (max2 >= d && d > max3){ max3 = d; f3 = i;}
    }
    
    cout << "The three cards that were on top of the stack most frequently during the shuffling are " << f1 << ", " << f2 << ", " << f3 << " [" << max1 << ", " << max2 << ", " << max3 << " times]" << endl;

    //c
    int times = 0;
    for (int i = 0; i < vcount.size(); i++)
    {
        if (vcount[i] == v[1])
        {
            times = i + 1;
            break;
        }
    }
    
    cout << "After " << times << " shuffling the most topmost card was on top for the first time." << endl;
    
    //d
    int f = 0;
    
    for (int i = 0; i < vcount.size(); i++)
    if (vcount[i] == v[1]){f = f + 1;}
    
    cout << "The topmost card was on top for " << f << " times throughout the shuffling." << endl;
    return 0;
}

