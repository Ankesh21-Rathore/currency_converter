#include <iostream>
#include <iomanip>
using namespace std;

// Function to get exchange rate from one currency to another
double getExchangeRate(string from, string to){
     if (from == "SLR") {  // All are correct according to today rate
        if (to == "USD") return 0.0033;
        if (to == "INR") return 0.29;
        if (to == "NPR") return 0.47;
        if (to == "JPY") return 0.49;
        if (to == "PAK") return 0.94;
    }
    else if (from == "INR") {
        if (to == "USD") return 0.011;
        if (to == "SLR") return 3.43;
        if (to == "NPR") return 1.60;
        if (to == "JPY") return 1.67;
        if (to == "PAK") return 3.19;
    } else if (from == "USD")
    {
        if (to == "SLR") return 302.96;
        if (to == "INR") return 88.29;
        if (to == "NPR") return 141.15;
        if (to == "JPY") return 147.88;
        if (to == "PAK") return 284.34;
    } else if (from == "NPR")
    {
        if (to == "USD") return 0.0071;
        if (to == "INR") return 0.63;
        if (to == "SLR") return 2.15;
        if (to == "JPY") return 1.05;
        if (to == "PAK") return 2.01;
    } else if (from == "JPY")
    {  
        if (to == "USD") return 0.0068;
        if (to == "INR") return 0.60;
        if (to == "NPR") return 0.96;
        if (to == "SLR") return 2.05;
        if (to == "PAK") return 1.90;
    } else if (from == "PAK")
    {  
        if (to == "USD") return 0.0035;
        if (to == "INR") return 0.31;
        if (to == "NPR") return 0.50;
        if (to == "JPY") return 0.53;
        if (to == "SLR") return 1.07;
    }
    return -1;  // for invalid
}

bool isValidCurrency(string currency) {
    return currency == "USD" || currency == "INR" || currency == "NPR" || currency == "SLR" || currency == "JPY"|| currency == "PAK";
}

int main() {
    string fromCurrency, toCurrency;
    double amount;

    cout << "Hii, It's Currency Converter " << endl;
    cout << "Supported Currencies: USD, INR, NPR, SLR, JPY, PAK" << endl;

    // to convert
    cout<<"Enter the currency name for convert : ";
    cin>>fromCurrency;

    if (!isValidCurrency(fromCurrency))
    {
        cout<<"Ohh!! you enters invalid currency name : "<<endl;
        return 1;
    }

    // to target
    cout<<"Enter the target currency name: ";
    cin>>toCurrency;

    if (!isValidCurrency(toCurrency))
    {
        cout<<"Ohh!! your target invalid"<<endl;
        return 1;
    }
    if (fromCurrency == toCurrency)
    {
        cout<<"You entred source and target are equal"<<endl;
        return 1;
    }
    
    // Amount 
    cout<<"Enter the amount for convertion : ";
    cin>>amount;
    if (amount<0)
    {
        cout<<"You entered negative number"<<endl;
        return -1;
    }
    

    double rate = getExchangeRate(fromCurrency, toCurrency);
    if (rate == -1) {
        cout << "Conversion rate not available!" << endl;
        return 1;
    }
    
    double convertedAmount = amount * rate;

    cout << fixed << setprecision(2);
    cout << amount << " " << fromCurrency << " = " << convertedAmount << " " << toCurrency << endl;

    
    return 0;
}
