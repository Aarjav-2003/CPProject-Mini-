#include <iostream>       
#include <list>     
#include <string>    
using namespace std;                   /*Cargo Security and Tamper Detection*/
//Base class for Cargo items
class CargoItem {
protected:
    int id;
    string description;
    string content;
public:
    CargoItem(int id, const string& description, const string& content){
        this->id=id;
        this->description=description;
        this->content=content;
    }
    virtual ~CargoItem() {}
    virtual void display() const {
        cout << "ID: " << id << ", Description: " << description << ", Content: " << content << endl;
    }
    virtual void securityApproach() = 0;
    virtual bool tamperDetection() const = 0;
    int getID() const {
        return id; 
    }
};
//Derived class for secured Cargo items
class SecureCargoItem : public CargoItem {
private:
    string secureCode;
public:
    SecureCargoItem(int id, const string& description, const string& content)
        : CargoItem(id, description, content){
            secureCode=""; //Initialize secureCode
        }
    //Implement security measures for secure cargo items
    //For simplicity, let's assume it just sets a security code based on content length
    void securityApproach() override {
        secureCode = to_string(content.length());
    }
    //Implement tamper detection algorithm
    //For simplicity, let's assume tampering is detected if the security code is empty
    bool tamperDetection() const override {
        return secureCode.empty();
    }
    void display() const override {
        cout << "Secured ";
        CargoItem::display();
    }
};
//Class for notification
class InfoNotification {
public:
    //The notification will be received at receiver's side if any stuff is altered somehow so as to inform the user.
    static void showNotification(const CargoItem& item) {
        cout << "Tampering detected in cargo item with ID: " << item.getID() << endl;
        //Implement notification mechanism such as email, SMS, etc.
    }
};
int main() {
    //Creating secure Cargo items
    SecureCargoItem item1(56, "Electronics", "Arduino");
    SecureCargoItem item2(87, "Clothing", "T-Shirts");
    SecureCargoItem item3(32, "Books", "Novels");
    SecureCargoItem item4(12, "Food", "Chocolates");
    SecureCargoItem item5(35, "Tools", "Power Drills");
    SecureCargoItem item6(89, "Paintings", "Canvas, Oil Paints, Frames");
    SecureCargoItem item7(67, "Surgical Instruments", "Scalpels, Sutures");
    SecureCargoItem item8(99, "Lumber", "2X4 Studs");
    //Creating a list to hold CargoItem pointers
    list<CargoItem*> cargoList;
    //Add items to the list
    cargoList.push_back(&item1);
    cargoList.push_back(&item2);
    cargoList.push_back(&item3);
    cargoList.push_back(&item4);
    cargoList.push_back(&item5);
    cargoList.push_back(&item6);
    cargoList.push_back(&item7);
    cargoList.push_back(&item8);
    //Showing the whole database of the Cargo
    cout<<endl<<"The database of the cargo purchases in the stock here is:"<<endl;
    for (auto i : cargoList){
        i->display();
    }
    cout<<endl<<"-----------------------------------------------------------------------------------------------------"<<endl;
    cout<<endl<<"After transferring the cargo purchases to the specified location, the condition is as follows:"<<endl;
    //Iterate over the list and perform security checks
    for (auto item : cargoList) {
        item->securityApproach(); //Apply security measures
        if (item->tamperDetection()) { //Check for tampering
            InfoNotification::showNotification(*item); //Notify if tampering is detected
        }
        else {
            cout << "Product of ID="<<item->getID()<<" is secured." << endl; //Indicate that the item is secured
        }
    }
    cout<<endl;
    return 0;
}