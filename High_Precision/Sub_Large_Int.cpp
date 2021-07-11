# include <iostream>
# include <vector>
 // C = A - B
using namespace std;

const int N = 1e6 + 10;

bool cmp(vector <int> &A, vector <int> &B){
	if (A.size() != B.size()) return A.size() > B.size();
	for (int i = A.size() - 1; i >= 0; --i){
		if (A[i] != B[i])
			return A[i] > B[i];
	}
	return true;
}

vector <int> sub(vector <int> &A, vector <int> &B){
	if (cmp(A, B) == false)
		return sub(A, B);
	
	vector <int> C;
	int t = 0;
	for (int i = 0; i < A.size(); ++i){
		t += A[i];
		if (i < B.size()) t -= B[i];
		C.push_back((t + 10) % 10);
		if (t < 0)
			t = -1;
		else
			t = 0 ;
	}
	
	while (C.size() > 1 && C.back() == 0) C.pop_back();
	
	return C;
}
int main(){
	string a, b;
	vector <int> A, B, C;
	
	cin >> a >> b;
	for (int i = a.size() - 1; i >= 0; --i) A.push_back(a[i] - '0');
	for (int i = b.size() - 1; i >= 0; --i) B.push_back(b[i] - '0');
	
	bool cmpAB = cmp(A, B);
	
	if (cmpAB)
		C = sub(A, B);
	else
		C = sub(B, A);
	
	if (!cmpAB) printf("-");
	
	for (int i = C.size() - 1; i >= 0; --i) printf("%d", C[i]);
	
	return 0;
}
