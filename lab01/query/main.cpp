#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct Product
{
    string name;
    double price;

    Product() : name(""), price(0.0) {}

    Product(string name, double price)
    {
        this->name = name;
        this->price = price;
    }
};


class Store
{
private:
    vector<Product> products;
    int n;

    void merge(int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<Product> L(n1), R(n2);

        for (int i = 0; i < n1; i++)
            L[i] = this->products[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = this->products[mid + 1 + j];

        int i = 0, j = 0;
        int k = left;

        while (i < n1 && j < n2)
        {
            if (L[i].price <= R[j].price)
            {
                this->products[k] = L[i];
                i++;
            }
            else
            {
                this->products[k] = R[j];
                j++;
            }
            k++;
        }

        // Copy the remaining elements of L[]
        while (i < n1)
        {
            this->products[k] = L[i];
            i++;
            k++;
        }

        // Copy the remaining elements of R[]
        while (j < n2)
        {
            this->products[k] = R[j];
            j++;
            k++;
        }
    }

    void mergeSort(int left, int right)
    {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }

public:
    Store(int n)
    {
        this->n = n;
        products = vector<Product>(n);
    }

    void addProduct(int i, string name, double price)
    {
        products[i] = Product(name, price);
    }

    void sortByPrice()
    {
        mergeSort(0, n - 1);
    }

    void searchByName(string query)
    {
        bool found = false;
        for (int i = 0; i < n; i++)
        {
            // query is a substring of the product name which is case-insensitive
            string name = products[i].name;
            string lowerName = name;
            string lowerQuery = query;

            for (char &c : lowerName)
                c = tolower(c);
                
            for (char &c : lowerQuery)
                c = tolower(c);

            if (lowerName.find(lowerQuery) != string::npos)
            {
                printf("%s %.2lf\n", products[i].name.c_str(), products[i].price);
                found = true;
            }
        }

        if (!found)
            cout << "-- NONE --" << endl;
    }

    void printProducts()
    {
        for (int i = 0; i < n; i++)
            cout << products[i].name << " " << products[i].price << endl;
    }
};


int main() 
{
    Store *store;
    int n;
    string query;

    cin >> n;
    
    store = new Store(n);

    for (int i = 0; i < n; i++)
    {
        string name;
        double price;
        cin >> name >> price;

        store->addProduct(i, name, price); 
    }
    
    cin >> query;

    store->sortByPrice();

    store->searchByName(query);

    return 0;
}
