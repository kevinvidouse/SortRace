#include <iostream>
#include <string>
#include <time.h>
#include <sys/resource.h>
#include <vector>
using namespace std;


vector<string> merge(vector<string> left, vector<string> right)
{
   vector<string> result;

   while (left.size() > 0 || right.size() > 0) {
      if (left.size() > 0 && right.size() > 0) {
         if (left.front().compare(right.front()) < 0) {
            result.push_back(left.front());
            left.erase(left.begin());
   } 
   else {
            result.push_back(right.front());
            right.erase(right.begin());
         }
      }  else if (left.size() > 0) {
            for (int i = 0; i <left.size(); i++)
               result.push_back(left[i]);
            break;
      }  else if (right.size() > 0) {
            for (int i = 0; i < right.size(); i++)
               result.push_back(right[i]);
            break;
      }
   }
   return result;
}

vector<string> mergeSort(vector<string> & m)
{
   if (m.size() <= 1)
      return m;
 
   vector<string> left, right, result;
   int middle = (m.size()+ 1) / 2;
 
   for (int i = 0; i < middle; i++) {
      left.push_back(m[i]);
   }

   for (int i = middle; i < m.size(); i++) {
      right.push_back(m[i]);
   }
 
   left = mergeSort(left);
   right = mergeSort(right);
   result = merge(left, right);
   m = result;
   return result;
}


void swap(vector<string> & vec, int i, int j)
{
    string tmp = vec[i];
    vec[i] = vec[j];
    vec[j] = tmp;
}
int partition(vector<string> & vec, int low, int high)
{
    int p = low;
    for (int i = p+1; i <= high; ++i)
    {
        if (vec[i].compare(vec[p]) < 0)
        {
            swap(vec, i, p);
            if (i != p+1)
            {
                swap(vec, i, p+1);
            }
            p = p + 1;
        }
    }

    return p;
}

void quicksort(vector<string> & vec, int low, int high) {
    if (low >= high) return;

    int p = partition(vec, low, high);

    quicksort(vec, low, p-1);
    quicksort(vec, p+1, high);
}

void quicksort(vector<string> & vec){
    quicksort(vec, 0, vec.size()-1);
}


double get_cpu_time(){ 
	struct rusage ruse;
	getrusage(RUSAGE_SELF, &ruse);
	return ruse.ru_utime.tv_sec+ruse.ru_utime.tv_usec/1000000.0 + 
         ruse.ru_stime.tv_sec+ruse.ru_stime.tv_usec/1000000.0; 
}

vector<string> generateStringArray(int size){
	char alphabet [] = "abcdefghijklmnopqrstuvwxyz0123456789";
	vector<string> arr;
	while (size > 0){
		size--;
		string filler = "00000000";
		for (int i = 0; i < 8; i++){
			filler[i] = alphabet[rand()%(sizeof(alphabet)-1)];
		}
		arr.push_back(filler);
	}
	return arr;
}

int main(){

for (int arrSize = 2; arrSize<= 10000; arrSize*=2){
	cout<<"arrSize: "<<arrSize<<endl;
	vector<string> unsortedQuick = generateStringArray(arrSize);
	vector<string> unsortedMerge = generateStringArray(arrSize);

	cout<<"created unsorted vectors\n";
	double start, end;

	start = get_cpu_time();
	cout<<"about to mergesort\n";
	mergeSort(unsortedMerge);
	cout<<"done sorting\n";
	end = get_cpu_time();
	cout<<"it took ["<<(end-start)<<"] to sort "<<arrSize<<" strings\n";

/*	for (int i = 0; i < unsortedMerge.size(); i++){
		cout<<unsortedMerge[i]<<endl;
	}
*/

	start = get_cpu_time();
	cout<<"about to quicksort\n";
	quicksort(unsortedQuick);
	cout<<"done sorting\n";
	end = get_cpu_time();
	cout<<"it took ["<<(end-start)<<"] to sort "<<arrSize<<" strings\n";
	cout<<unsortedQuick.size()<<endl;
/*	for (int i = 0; i < unsortedQuick.size(); i++){
		cout<<unsortedQuick[i]<<endl;
	}
*/

}
	return 0;


}

