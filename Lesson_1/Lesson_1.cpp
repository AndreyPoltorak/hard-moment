
#include <fstream>
#include <iostream>
#include <string>
#include <optional>
#include <iomanip>
#include <tuple>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct  Person
{
    string Surname{};
    string Name{};
    optional<string> Patronymic{};
    Person(string sn, string nm, optional<string> ptr)
    {
        Surname = sn;
        Name = nm;
        if(ptr=="-")
        Patronymic = nullopt;
        else
        Patronymic = ptr;
    };
    friend ostream& operator<< (ostream& out, const Person& point);
    friend bool operator== (const Person& lf, const Person& rh);
    friend bool operator< (const Person& lf, const Person& rh);
};

ostream& operator<< (ostream& out, const Person& person)
{
    
    out << right << setw(15) << person.Surname
        << right << setw(15) << person.Name;
    if (person.Patronymic.has_value())
    {
        out << right << setw(15) << person.Patronymic.value();
    }
    else
    {
        out << right << setw(18);
    }
    

    return out;
}

bool operator== (const Person& lf, const Person& rh)
{
    if(lf.Patronymic.has_value() && rh.Patronymic.has_value())
        return tie(lf.Surname, lf.Name, lf.Patronymic.value()) == tie(rh.Surname, rh.Name, rh.Patronymic.value());
    else
        return tie(lf.Surname, lf.Name) == tie(rh.Surname, rh.Name);
}

bool operator< (const Person& lf, const Person& rh)
{
    if (lf.Patronymic.has_value() && rh.Patronymic.has_value())
        return tie(lf.Surname, lf.Name, lf.Patronymic.value()) < tie(rh.Surname, rh.Name, rh.Patronymic.value());
    else
        return tie(lf.Surname, lf.Name) < tie(rh.Surname, rh.Name);
}

struct PhoneNumber {
    int CountryCode{};
    int CityCode{};
    string Number;
    optional<int> ExtensionNumber;
    PhoneNumber(int countcode, int citcode, string num, optional<int> ecod)
    {
        CountryCode = countcode;
        CityCode = citcode;
        Number = num;
        if (ecod == 0)
            ExtensionNumber = nullopt;
        else
            ExtensionNumber = ecod;
    }
    friend ostream& operator<< (ostream& out, const PhoneNumber& point);
    friend bool operator== (const PhoneNumber& lf, const PhoneNumber& rh);
    friend bool operator< (const PhoneNumber& lf, const PhoneNumber& rh);

};

ostream& operator<< (ostream& out, const PhoneNumber& phone)
{
    out <<"   " << left << phone.CountryCode
        <<"("<< phone.CityCode<<")"
        <<phone.Number;
    if (phone.ExtensionNumber.has_value())
    {
        out <<" " << phone.ExtensionNumber.value()<<endl;
    }
    else
    {
        out << endl;
    }


    return out;
}

bool operator== (const PhoneNumber& lf, const PhoneNumber& rh)
{
    if (lf.ExtensionNumber.has_value() && rh.ExtensionNumber.has_value())
        return tie(lf.CountryCode, lf.CityCode, lf.Number, lf.ExtensionNumber.value()) == tie(rh.CountryCode, rh.CityCode, rh.Number,rh.ExtensionNumber.value());
    else
        return tie(lf.CountryCode, lf.CityCode, lf.Number) == tie(rh.CountryCode, rh.CityCode, rh.Number);
}

bool operator< (const PhoneNumber& lf, const PhoneNumber& rh)
{
    if (lf.ExtensionNumber.has_value() && rh.ExtensionNumber.has_value())
        return tie(lf.CountryCode, lf.CityCode, lf.Number, lf.ExtensionNumber.value()) < tie(rh.CountryCode, rh.CityCode, rh.Number, rh.ExtensionNumber.value());
    else
        return tie(lf.CountryCode, lf.CityCode, lf.Number) < tie(rh.CountryCode, rh.CityCode, rh.Number);
}


class PhoneBook {
    vector <pair<Person, PhoneNumber>> Book{};
public:
    PhoneBook(ifstream &file)
    {
        string surname, name, patronymic, number, extensionnumber;
        int countrycode, citycode;
        while (true)
        {
            if (file.eof())
                break;
            file >> surname >> name >> patronymic >> countrycode>> citycode>> number>> extensionnumber;
            Person person(surname, name, patronymic);
            if (extensionnumber == "-")
            {
                PhoneNumber phone(countrycode, citycode, number, 0);
                Book.push_back(pair(person, phone));
            }
                
            else
            {
                PhoneNumber phone(countrycode, citycode, number, stoi(extensionnumber));
                Book.push_back(pair(person, phone));
            }
                

            
        }
    }
    friend ostream& operator<< (ostream& out, const PhoneBook& book );
    void SortByName();
    void SortByPhone();
    tuple <string, string> GetPhoneNumber(string surname);
    void ChangePhoneNumber(Person person, PhoneNumber phone);
};

ostream& operator<< (ostream& out, const PhoneBook& book)
{
    for(auto &P : book.Book )
    {
        out << P.first << P.second;
    }
    return out;
}

void PhoneBook::SortByName() {
    sort(Book.begin(), Book.end(), [](pair<Person, PhoneNumber>& lf,pair<Person, PhoneNumber>& rh)
        {   
            return lf.first < rh.first;
        }
    );
}

void PhoneBook::SortByPhone() {
    sort(Book.begin(), Book.end(), [](pair<Person, PhoneNumber>& lf, pair<Person, PhoneNumber>& rh)
        {
            return lf.second < rh.second;
        }
    );
}

tuple <string, string> PhoneBook::GetPhoneNumber(string surname)
{
    for (auto& P : Book)
    {
        if (P.first.Surname == surname)
        {
            stringstream ss;
            ss << P.second;
            return tuple(ss.str(), "not found");
        }
    }
    return tuple("", "not found");
}

void PhoneBook::ChangePhoneNumber(Person person, PhoneNumber phone)
{
    for (auto& p : Book)
    {
        if (p.first == person)
        {
            p.second = phone;
        }
    }
}

int main()
{
    
    ifstream file("PhoneBook.txt");
    PhoneBook book(file);
    int k = 0;
    
    cout << book;

    cout << "------SortByPhone-------" << endl;
    
    book.SortByPhone();
    cout << book;
    
    cout << "------SortByName--------" << endl;
    book.SortByName();
    cout << book;
    
    cout << "-----GetPhoneNumber-----" << endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона этого    	человека, либо строку с ошибкой
    auto print_phone_number = [&book](const string& surname) {
        cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
            cout << get<1>(answer);
        else
            cout << get<0>(answer);
        cout << endl;
    };

    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");

    cout << "----ChangePhoneNumber----" << endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", nullopt });
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
    cout << book;
}




