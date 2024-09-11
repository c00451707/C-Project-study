#include<iostream>
#include<fstream>
#include<cstdlib>
const int SIZE = 60;
using namespace std;

int main() {
    char filename[SIZE];
    ifstream inFile;
    cout << "Enter name of data file: ";
    cin.getline(filename, SIZE);

    inFile.open(filename);
    if (!inFile.is_open()) {
        cout << "Could not open the file " << filename << endl;
        cout << "Program terminating. \n";
        exit(EXIT_FAILURE);
    }
    double value;
    double sum = 0.0;
    int count = 0;
    inFile >> value;
    while (inFile.good()) {
        ++count;
        sum += value;
        inFile >> value;
    }
    if (inFile.eof()) {
        cout << "End of file reached. \n";
    } else if (inFile.fail()) {
        cout << "Input terminated by data dismatch. \n";
    } else {
        cout << "Input terminated for unknow reason. \n";
    }

    if (count == 0) {
        cout << "No data processed. \n";
        inFile.close();
        return 0;
    }

    cout << "Items read: " << count << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << sum / count << endl;

    inFile.close();
    return 0;
}

/*
文件内容：
18 19 18.5 13.5 14（换行符）
16 19.5 20 18 12 18.5（换行符）
17.5（换行符）
有一空行
输出：
Enter name of data file: scores.txt
End of file reached. 
Items read: 12       
Sum: 204.5
Average: 17.0417


文件内容：
18 19 18.5 13.5 14（换行符）
16 19.5 20 18 12 18.5（换行符）
17.5  // 解释：仍然在队列中没有被读取出， 方法good() 指出最后一次读取输入操作是否成功，由于读取 17.5时，没有换行符，inFile.good() 等于 false，跳出while循环了
输出：
Enter name of data file: scores.txt
End of file reached. 
Items read: 11       
Sum: 187
Average: 17
*/