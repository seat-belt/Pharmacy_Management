#include <iostream>
#include <unordered_map>
#include <list>
#include <fstream> 
#include <cstring>

using namespace std;
//
bool userLogin()
{
    string username, password, un, pw; //last two are comparison string
    cout << "Enter username :";
    cin >> username;
    

    cout << "Enter password :";
    cin >> password;

    ifstream read("C:\\Users\\AFRIN\\Desktop\\dsa_reg\\" + username + ".txt");
    getline(read, un);  
    getline(read, pw);

    //comparison

    if (un == username && pw == password)
    {
        return true;   //that the user is valid and can log in
    }
    else
    {
        return false;
    }
}

bool adminLogin()
{
    string password, pw; 

    cout << "Enter password to login as admin:";
    cin >> password;

    ifstream read("C:\\Users\\AFRIN\\Desktop\\dsa_reg\\ADMIN.txt");
    getline(read, pw); 

    //comparison

    if (pw == password)
    {
        return true;   
    }
    else
    {
        return false;
    }
}

//
class medicineType{
public:
    int choice; 
    void take_order(const string &inputName, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void view_medicines(medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void add(int num, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void deleteMed(const string &inputName, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void update(const string &inputName, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void viewCart(medicineType type, const list<unordered_map<std::string, std::string>>& medsList, list<unordered_map<std::string, std::string>> cart);
    void generateBill(list<unordered_map<std::string, std::string>> cart);
    void menu(int choice, medicineType medicine, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void exit();
    medicineType();
};

medicineType::medicineType()= default;

//method for taking medicine orders
void medicineType::take_order(const string &inputName, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    int count = 0;
    for (const unordered_map<string, string>&med : medsList)
    {
        if(med.at("Name") == inputName) {
            string inputQuantity;
            cout << "Enter quantity of " << inputName << " to order: " << endl;
            cin >> inputQuantity;
            int q = stoi(med.at("Quantity"));

            if(q>= stoi(inputQuantity)){
                q = q - stoi(inputQuantity);
                unordered_map<string, string> medicineMap;          //hashmap of a medicine
                medicineMap["Name"] = med.at("Name");
                medicineMap["Expiry"] = med.at("Expiry");
                medicineMap["Cost"] = med.at("Cost");
                medicineMap["Quantity"] = to_string(q);
                medsList.remove(med);
                medsList.push_back(medicineMap);        //reducing the quantity of total medicines from the medicines list
                medicineMap["Quantity"] = std::to_string(stoi(inputQuantity));
                cart.push_back(medicineMap);           //medicine is added to cart
                count++;
                cout << inputName << " has been added to your cart " << endl;
                break;
            }
            else{
                cout << "Insufficient amount of " << inputName << " in current medicine stock" << endl;
                break;
            }
        }
    }
    if(count == 0){
        cout << inputName << " is not in the pharmacy!" << std::endl;
    }
    menu(choice,type, medsList, cart);
}

//method for viewing all the medicines present in the pharmacy
void medicineType::view_medicines(medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    cout << "Medicines present in the pharmacy stock:" << endl;
    for (const unordered_map<string, string>&med : medsList)
    {
        string n = med.at("Name");
        string e = med.at("Expiry");
        string c = med.at("Cost");
        string q = med.at("Quantity");
        cout << "Name: " << n << ", " << "Expiry date: " << e << ", " << "Cost: " << c << ", " << "Quantity: " << q << endl;
    }
    menu(choice, type, medsList, cart);
}

//method to add new medicines to the pharmacy's stock of medicines
void medicineType::add(int num, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    string name, expiry, quantity, cost;
    for(int i = 1; i <= num; i++){
        cout << "New medicine" << endl;
        cout << "Enter name: " << endl;
        cin >> name;
        cout << "Enter expiry date: " << endl;
        cin >> expiry;
        cout << "Enter quantity: " << endl;
        cin >> quantity;
        cout << "Enter cost: " << endl;
        cin >> cost;

        unordered_map<string, string> medicineMap;       //hashmap of a medicine
        medicineMap["Name"] = name;
        medicineMap["Expiry"] = expiry;
        medicineMap["Cost"] = cost;
        medicineMap["Quantity"] = quantity;

        medsList.push_back(medicineMap);
    }
    cout << "Medicines added successfully!" << endl;
    menu(choice, type, medsList, cart);
}

//method to remove medicines from the pharmacy's medicine stock
void medicineType::deleteMed(const string &inputName, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    int count = 0;
    for (const unordered_map<string, string>&med : medsList)
    {
        if(med.at("Name") == inputName) {
            medsList.remove(med);      //removing the medicine from list of medicines
            count++;
            cout << "Successfully deleted " << inputName << " from list of medicines" << endl;
            break;
        }
    }
    if(count == 0){
        cout << inputName << " is not in the pharmacy!" << std::endl;
    }
    menu(choice, type, medsList, cart);
}

//method to update the pharmacy's current medicines data
void medicineType::update(const string &inputName, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    int count = 0;
    for (const unordered_map<string, string>&med : medsList)
    {
        string newName, newExpiry, newCost, newQuantity;
        if(med.at("Name") == inputName) {
            cout << "Enter new name of medicine: " << endl;
            cin >> newName;
            cout << "Enter new expiry date of medicine: " << endl;
            cin >> newExpiry;
            cout << "Enter new cost of medicine: " << endl;
            cin >> newCost;
            cout << "Enter new quantity of medicine: " << endl;
            cin >> newQuantity;
            medsList.remove(med);

            unordered_map<string, string> medicineMap;    //hashmap of a medicine
            medicineMap["Name"] = newName;
            medicineMap["Expiry"] = newExpiry;
            medicineMap["Cost"] = newCost;
            medicineMap["Quantity"] = newQuantity;

            medsList.push_back(medicineMap);     //updated data is added to list of medicines
            count++;
            cout << count << std::endl;
            cout << "Successfully updated!" << endl;
            break;
        }
    }
    if(count == 0){
        cout << inputName << " is not in the pharmacy!" << std::endl;
    }
    menu(choice, type, medsList, cart);
}

//to exit the pharmacy
void medicineType::exit() {
    exit();
}

//to view all the medicines which have been added to cart
void medicineType::viewCart(medicineType type, const list<unordered_map<std::string, std::string>>& medsList, list<unordered_map<std::string, std::string>> cart) {
    cout << "CART:" << endl;
    for (const unordered_map<string, string>&med : cart)
    {
        string n = med.at("Name");
        string e = med.at("Expiry");
        string c = med.at("Cost");
        string q = med.at("Quantity");
        cout << "Name: " << n << ", " << "Expiry date: " << e << ", " << "Cost: " << c << ", " << "Quantity: " << q << endl;
    }
    menu(choice,type, medsList, cart);
}

void medicineType::generateBill(list<unordered_map<std::string, std::string>> cart) {
    cout << "BILL:" << endl;
    
}

//menu to display all the operations which can be performed
void medicineType::menu(int choice, medicineType medicine, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    int menu;
    
    cout << "MENU:" << endl;
    
    cout << "1. For ordering medicines" <<endl;
    cout << "2. For viewing cart" <<endl;
    cout << "3. For viewing all medicines" <<endl;
    if(choice==3){
    cout << "4. For adding new medicines" <<endl;
    cout << "5. For deleting any medicines" <<endl;
    cout << "6. For updating current medicines" <<endl;
    }
    cout << "x To exit" <<endl;
    cout << "Enter choice: ";
    cin >> menu;

    string inputName;

    switch(menu){
        case 1:
        {
            cout << "Enter name of medicine to order: " << endl;
            cin >> inputName;
            medicine.take_order(inputName, medicine, medsList, cart);
            break;
        }
        case 2:
        {
            medicine.viewCart(medicine, medsList, cart);
            break;
        }
        case 3:
        {
            medicine.view_medicines(medicine, medsList, cart);
            break;
        }
        if(choice==3){
        case 4:
        {
            int num;
            cout << "How many medicines would you like to add: " << endl;
            cin >> num;
            medicine.add(num, medicine, medsList, cart);
            break;
        }
        case 5:
        {
            cout << "Enter name of medicine to delete: " << endl;
            cin >> inputName;
            medicine.deleteMed(inputName, medicine, medsList, cart);
            break;
        }
        case 6:
        {
            cout << "Enter name of medicine to update: " << endl;
            cin >> inputName;
            medicine.update(inputName, medicine, medsList, cart);
            break;
        }
        }
        case 'x':
        {
            cout << "Thank you!" << endl;
            medicine.exit();
            break;
        }
        default:
        {
            cout << "Please enter a valid option number" << endl;
        }
    }
}

int main() {
    int choice;
    string username, password;

    cout << "1 : Register \n2 :Login\n3 :Login as admin\nYour choice :";
    cin >> choice;
    if (choice == 1)
    {
        

        cout << "select a username :";
        cin >> username;
        cout << "select a password :";
        cin >> password;

        //

        ofstream file;
        file.open("C:\\Users\\AFRIN\\Desktop\\dsa_reg\\" + username + ".txt");
        file<<username<<endl<<password; 
        file.close();

    
    main();
    }

    else if(choice==2)
    {
       bool status =userLogin();

       if(!status) 
       {
          cout<<"Invalid user name password \n"<<endl;
          //system("PAUSE");
          return 0;
       }
       else 
       {
           cout<<"Successfully Logged in \n"<<endl;
          // system("pause");
          // return 1;
       }
    }
    else if(choice==3){
        bool status =adminLogin();

         if(!status) 
       {
          cout<<"Invalid user name password \n"<<endl;
          //system("PAUSE");
          return 0;
       }
       else 
       {
           cout<<"Successfully Logged in\n"<<endl;
           //system("pause");
          // return 1;
       }

    }
    //

    medicineType medicine2;
    list<unordered_map<string, string>> medicines;
    list<unordered_map<string, string>> cart;
    medicine2.menu(choice,medicine2, medicines, cart);
}