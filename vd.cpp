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

/*
void lines(Point P, Q, A,B,C){
	A = P.y-Q.y;
	B=Q.x - P .x;
	C = -(A*P.x + B*P.y) // C=X1Y2 - X2 Y1
}

void dist(Point A, B ){
return sqrt((B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y));
}

bool isCollinear(int x1, int y1, int x2, int y2, int x3, int y3) {
    // S? d?ng công th?c (X1 - X2) * (Y1 - Y3) = (X1 - X3) * (Y1 - Y2)
    return (x1 - x2) * (y1 - y3) == (x1 - x3) * (y1 - y2);
}



struct Point {
    double x, y;
};

// Hàm tính tích có hu?ng c?a 2 vector AB và AM
double crossProduct(Point A, Point B, Point M) {
    return (B.x - A.x) * (M.y - A.y) - (B.y - A.y) * (M.x - A.x);
}

// Hàm tính kho?ng cách t? di?m M d?n du?ng th?ng di qua A và B
double distanceToLine(Point A, Point B, Point M) {
    double numerator = abs((B.y - A.y) * M.x - (B.x - A.x) * M.y + B.x * A.y - B.y * A.x);
    double denominator = sqrt(pow(B.y - A.y, 2) + pow(B.x - A.x, 2));
    return numerator / denominator;
}

// Hàm ki?m tra v? trí c?a M và in ra k?t qu?
void checkPosition(Point A, Point B, Point M) {
    double cross = crossProduct(A, B, M);
    
    if (cross == 0) {
        cout << "M n?m trên du?ng th?ng di qua A và B." << endl;
    } else if (cross > 0) {
        cout << "M n?m phía bên trái c?a du?ng th?ng." << endl;
    } else {
        cout << "M n?m phía bên ph?i c?a du?ng th?ng." << endl;
    }
    
    double distance = distanceToLine(A, B, M);
    cout << "Kho?ng cách t? M d?n du?ng th?ng: " << distance << endl;
}


int ccw(Point A, Point B, Point C)
{ double t=(B.x-A.x)*(C.y-A.y) - (B.y-A.y)*(C.x-A.x);
if (t>0) return 1; //quay trai
if (t<0) return -1; //quay phai
return 0; //thang hang
}



#Tích vô hu?ng (tích ch?m)
int tichvh(Point u, Point v)
{
return (u.x*v.x + u.y*v.y);
}
Tích chéo
int tichc(Point u, Point v)
{
return (u.x*v.y - u.y*v.x);
}


#Goc
double goc(Point A)
{
double t = atan2(A.y,A.x);
if (t<0) t = t + 2 * acos(-1);
return t;
}


#S tam giac
double sTriangle(Point A, Point B, Point C)
{
double s=(B.x-A.x)*(C.y-A.y)-(B.y-A.y)*(C.x-A.x);
return abs(s/2);  #S := sqrt((p-a)*(p-b)*(p-c)*p);
}
#duong cao tam giac
double dist2(Point A, Point B, Point C)
{
return 2*sTriangle(A,B,C)/dist(A,B);
}

*/


