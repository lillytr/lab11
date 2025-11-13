#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Matrix {
private:
    int size;
    int** data;

public:
    Matrix(int n = 0) {
        size = n;
        if (size > 0) {
            data = new int*[size];
            for (int i = 0; i < size; i++)
                data[i] = new int[size];
        } else data = nullptr;
    }

    Matrix(const Matrix &other) {
        size = other.size;
        data = new int*[size];
        for (int i = 0; i < size; i++) {
            data[i] = new int[size];
            for (int j = 0; j < size; j++)
                data[i][j] = other.data[i][j];
        }
    }

    ~Matrix() {
        if (data) {
            for (int i = 0; i < size; i++)
                delete[] data[i];
            delete[] data;
        }
    }

    void readFromFile(ifstream &fin) {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                fin >> data[i][j];
    }

    void display() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++)
                cout << setw(6) << data[i][j];
            cout << endl;
        }
        cout << endl;
    }

    Matrix operator+(const Matrix &other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    Matrix operator*(const Matrix &other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < size; k++)
                    result.data[i][j] += data[i][k] * other.data[k][j];
            }
        return result;
    }

    void diagonalSums() const {
        int mainSum = 0, secondarySum = 0;
        for (int i = 0; i < size; i++) {
            mainSum += data[i][i];
            secondarySum += data[i][size - i - 1];
        }
        cout << "Main diagonal sum: " << mainSum << endl;
        cout << "Secondary diagonal sum: " << secondarySum << endl << endl;
    }

    void swapRows(int r1 = 0, int r2 = 1) const {
        if (r1 < 0 || r2 < 0 || r1 >= size || r2 >= size) {
            cout << "Invalid row indices." << endl;
            return;
        }
        Matrix temp = *this;
        for (int j = 0; j < size; j++)
            swap(temp.data[r1][j], temp.data[r2][j]);
        temp.display();
    }

    void swapColumns(int c1 = 0, int c2 = 1) const {
        if (c1 < 0 || c2 < 0 || c1 >= size || c2 >= size) {
            cout << "Invalid column indices." << endl;
            return;
        }
        Matrix temp = *this;
        for (int i = 0; i < size; i++)
            swap(temp.data[i][c1], temp.data[i][c2]);
        temp.display();
    }

    void updateElement(int r = 0, int c = 0, int value = 100) {
        if (r < 0 || c < 0 || r >= size || c >= size) {
            cout << "Invalid indices." << endl;
            return;
        }
        data[r][c] = value;
        display();
    }
};

int main() {
    string filename;
    cout << "Enter input filename: ";
    cin >> filename;

    ifstream fin(filename);
    if (!fin) {
        cerr << "Error: cannot open file " << filename << endl;
        return 1;
    }

    int N;
    fin >> N;
    Matrix A(N), B(N);
    A.readFromFile(fin);
    B.readFromFile(fin);

    cout << "\nMatrix A:" << endl;
    A.display();
    cout << "Matrix B:" << endl;
    B.display();

    cout << "Matrix A + B:" << endl;
    Matrix sum = A + B;
    sum.display();

    cout << "Matrix A * B:" << endl;
    Matrix prod = A * B;
    prod.display();

    cout << "Diagonal sums of A:" << endl;
    A.diagonalSums();

    cout << "Swap rows in A:" << endl;
    A.swapRows(0, 1);

    cout << "Swap columns in A:" << endl;
    A.swapColumns(0, 1);

    cout << "Update element in A:" << endl;
    A.updateElement(1, 1, 99);

    fin.close();
    return 0;
}
