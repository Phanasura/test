#include <iostream>
#include <math.h>
using namespace std;
int binaryToDecimal(long binarynum)
{
    int decimalnum = 0, temp = 0, remainder;
    while (binarynum!=0)
    {
        remainder = binarynum % 10;
        binarynum = binarynum / 10;
        decimalnum = decimalnum + remainder*pow(2,temp); //1x2^2+0x2^1+1x2^0
        temp++;
    }
    return decimalnum;
}
 
int main()
{
    long binarynum;
    cout<<"Nh?p vào s? nh? phân c?n chuy?n d?i(bao g?m 8 s?): ";
    cin>>binarynum;
 
    cout<<endl<<"S? nh? phân sau khi du?c d?i thành th?p phân là: "<<binaryToDecimal(binarynum);
    cout<<"\n--------------------------------\n";
    cout<<"Chuong trình này du?c dang t?i Freetuts.net";
}

