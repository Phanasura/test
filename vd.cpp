#include <bits/stdc++.h>
using namespace std;
struct Point {
    int x, y;
};
void setio(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  
	cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		//freopen((name + ".out").c_str(), "w", stdout);
	}
}

void readin(){
	
}

void solve(){
	
}

int main(){
	setio("vd");
	readin();
	solve();
	return 0;
}
/*
BAI 01
double s(double x1, double y1, double x2, double y2, double x3, double y3) {
    return abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0;
}
int main() {
    freopen("BAI01.inp","w",stdin);
    freopen("BAI01.out","r",stdout);
    double xa, ya, xb, yb, xc, yc, xm, ym;
    cin >> xa >> ya;
    cin >> xb >> yb;
    cin >> xc >> yc;
    cin >> xm >> ym;
    double S_ABC = s(xa, ya, xb, yb, xc, yc);
    double S_AMB = s(xa, ya, xm, ym, xb, yb);
    double S_BMC = s(xb, yb, xm, ym, xc, yc);
    double S_AMC = s(xa, ya, xm, ym, xc, yc);
    double tongDienTich = S_AMB + S_BMC + S_AMC;
    cout << fixed << setprecision(2) << S_ABC << endl;
    if (abs(S_ABC - tongDienTich) < 1e-6) {
        cout << "TRONG" << endl;
    } else {
        cout << "NGOAI" << endl;
    }
    return 0;
}
*/

/*
twopointline
int main() {
    double A1, B1, C1, A2, B2, C2;
    cin >> A1 >> B1 >> C1;
    cin >> A2 >> B2 >> C2;
    double d = A1 * B2 - A2 * B1;
    double dx = C2 * B1 - C1 * B2;
    double dy = A2 * C1 - A1 * C2;
    if (d != 0) {
        // Có giao di?m
        double x = dx / d;
        double y = dy / d;
        cout << fixed << setprecision(2) << x << " " << y << endl;
    } else if (dx == 0 && dy == 0) {
        // Trùng nhau
        cout << "DUPLICATE" << endl;
    } else {
        // Song song
        cout << "PARALLEL" << endl;
    }
    return 0;
}
*/


/*
Poliar
struct Point {
    int x, y;
};
int main() {
    // Khai báo các bi?n
    int N;
    cin >> N;
    vector<Point> points(N);
    // Ð?c t?a d? c?a các d?nh t? input
    for (int i = 0; i < N; ++i) {
        cin >> points[i].x >> points[i].y;
    }
    // Tính di?n tích b?ng công th?c Shoelace
    double area = 0.0;
    for (int i = 0; i < N; ++i) {
        int j = (i + 1) % N;  // Ch? s? d?nh ti?p theo, quay vòng
        area += points[i].x * points[j].y - points[i].y * points[j].x;
    }
    // Di?n tích tuy?t d?i và chia dôi
    area = abs(area) / 2.0;
    // In di?n tích ra màn hình, làm tròn d?n 2 ch? s? th?p phân
    cout << fixed << setprecision(2) << area << endl;
    return 0;
}
*/





