#include <iostream>
#include "list.h"
#include "array.h"

using namespace std;

int main() {
    array arr;

    arr.push(1,1,4);
    arr.push(2,3,1);
    arr.push(4,4,3);
    arr.push(6,2,7);
    arr.show();
    cout << endl;
    cout << arr.get(2,3) << endl;
    cout << arr.get(1,2) << endl;
    cout << arr.get(6,2) << endl;
    cout << arr.get(4,4) << endl;
    list l;
    l.push(1,1);
    l.push(2,2);
    l.push(5,3);
    l.push(4,2);
    l.push(0,8);
    l.show();
    cout << "l[1]: " << l[1] << endl;
    l[1]=4;
    cout << "l[1]: " << l[1] << endl;
    l.show();

    cout << arr[1][1] << endl;
    arr[1][1] = 0;
    cout << arr[1][1] << endl;
    cout << arr[2][3] << endl;
    return 0;
}
