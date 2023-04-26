#include <cstring>
#include <iostream>
#include<string.h>
#include<conio.h>
#include<math.h>
#include<fstream>
#include <cstdio>

using namespace std;

class item{
	
	char name[20], id[7];
	int price, qty;
	
	public:
		
		item(){
		}
		
		item(int p, int q){
			this->price = p;
			this->qty = q;
		}
		
		item(char *n, char *ID, int price, int qty){
			strcpy(name,n);
			this->price = price;
			this->qty = qty;
			strcpy(id,ID);
		}
		
		setName(char n[]){
			strcpy(name,n);
		}
		char* getName(){
			return name;
		}
		
		setId(char ID[]){
			strcpy(id,ID);
		}
		char* getId(){
			return id;
		}
		
		setPrice(int price){
			this->price = price;
		}
		int getPrice(){
			return price;
		}
		
		setQty(int qty){
			this->qty = qty;
		}
		int getQty(){
			return qty;
		}
		
		disp(){
			cout << endl << name << "\t\t" << id << "\t\t" << qty << "\t\t\t" << price;
		}
		
		int idcmp(string temp){
			if (temp == id){
				return 0;
			}
			else {
				return 1;
			}
		}
		
		refill(int addqty){
			qty = qty + addqty;
		}
		
		reduce(int redqty){
			qty = qty - redqty;
		}
		
};



class Supplier {
	
	ofstream fout;
	ifstream fin;
	fstream fio;
	
	string id;
	string password;
	
	public:
		
		Supplier(){
		
		}
		
		displayitems(){
			int i=1;
			cout<<"\nNAME\t\tID\t\tSTOCK AVAILABLE\t\tPRICE";
			fin.open("supplieritems.dat",ios::in|ios::binary);
			item readitem;
			cout << endl;
		    while(!fin.eof()){

				fin.read((char*)&readitem,sizeof(readitem));

				if(!fin.eof()){
			    	if(fin.tellg()<0){
						i=0;
						break;
					}
//					if (fin.is_open()){
//   						cout << "Done !" << endl;
//					}
			    readitem.disp();
		    }}
		    if(i==0){
				cout<<"\n\tNo record exist";
				getch();
		    }
		    fin.close();
		    getch();
		}
		
		addnewitem(){
			char name[20], id[7];
			int qty, price;
			
			cout << "Enter the name: ";
			cin >> name;
			fflush(stdin);
			cout << "Enter the id: ";
			cin>>id;
			fflush(stdin);
			cout << "Enter price: ";
			cin >> price;
			cout << "Enter quantity: ";
			cin >> qty;
			
			item add = item(name, id, price, qty);
			fout.open("supplieritems.dat",ios_base::app | ios_base::in);
			if (fout.is_open()){
   				cout << "Done !" << endl;
			}
			fout.write((char*)&add,sizeof(add));
			fout.close();
		}
		
		void refill(){
			system("cls");
			displayitems();
			system("cls");
			char temp_id[7];
			item temp_item;
			int qty;
			int i = 0;
			long pointerposition = 0;
//			system("cls");
			cout << "\n\nEnter the item's id: ";
			cin >> temp_id;
			cout << "\n\nEnter quantity: \n"<<endl;
			cin >> qty;
			fio.open("supplieritems.dat",ios::binary|ios::out|ios::in);
		    while(fio){
			    pointerposition = fio.tellp();
			    fio.read((char*)&temp_item,sizeof(temp_item));
			    if(temp_item.idcmp(temp_id)==0){
					temp_item.refill(qty);
					fio.seekp(pointerposition);
					fio.write((char*)&temp_item,sizeof(temp_item));
					i = 1;
					break;
			    }
		    }
		    if(i != 1){
		    	cout<<"\n\n!!Record not found!!";
			}
			fio.close();
		    system("cls");
		    getch;
			displayitems();
			getch;
		}
		
		void reduce(){
			system("cls");
			displayitems();
			system("cls");
			char temp_id[7];
			item temp_item;
			int qty;
			int i = 0;
			long pointerposition = 0;
//			system("cls");
			cout << "\n\nEnter the item's id: ";
			cin >> temp_id;
			cout << "\nEnter quantity: \n"<<endl;
			cin >> qty;
			fio.open("supplieritems.dat",ios::binary|ios::out|ios::in);
		    while(fio){
			    pointerposition = fio.tellp();
			    fio.read((char*)&temp_item,sizeof(temp_item));
			    if(temp_item.idcmp(temp_id)==0){
					temp_item.reduce(qty);
					fio.seekp(pointerposition);
					fio.write((char*)&temp_item,sizeof(temp_item));
					i = 1;
					break;
			    }
		    }
		    if(i != 1){
		    	cout<<"\n\n!!Record not found!!";
			}
			fio.close();
		    system("cls");
		    getch;
			displayitems();
			getch;
		}
		
		item sell(){
			system("cls");
			displayitems();
			system("cls");
			char temp_id[7];
			item temp_item;
			int qty;
			int i = 0;
			long pointerposition = 0;
//			system("cls");
			cout << "\n\nEnter the item's id: ";
			cin >> temp_id;
			cout << "\nEnter quantity: \n"<< endl;
			cin >> qty;
			fio.open("supplieritems.dat",ios::binary|ios::out|ios::in);
		    while(fio){
			    pointerposition = fio.tellp();
			    fio.read((char*)&temp_item,sizeof(temp_item));
			    if(temp_item.idcmp(temp_id)==0){
					temp_item.reduce(qty);
					fio.seekp(pointerposition);
					fio.write((char*)&temp_item,sizeof(temp_item));
					i = 1;
					break;
			    }
		    }
		    
			fio.close();
			if (i == 1){
		    	return temp_item;
			}
		    else if(i != 1){
		    	cout<<"\n\n!!Record not found!!";
		    	item garbage = item(-1, -1);
		    	return garbage;
			}
		}
	
		void removeitem(){
			system("cls");
			item temp;
			int i = 0;
			displayitems();
			system("cls");
		    char temp_id[7];
//		    cout<<"\n\t\t\t\tDelete Record";
		    cout<<"\n\nEnter the id of the product you want to remove: ";
		    cin >> temp_id;
		    fout.open("temp.dat",ios_base::app | ios_base::in);
		    fin.open("supplieritems.dat",ios::in|ios::binary);
		    while(!fin.eof()){
			fin.read((char*)&temp,sizeof(temp));
			if(!fin.eof()){
				if(temp.idcmp(temp_id) == 0){    			// add in the id class 
					temp.disp();
					cout<<"\nRecord deleted";
					i++;
			    }
			    else{
					fout.write((char*)&temp,sizeof(temp));
		    	}
				}
			}
		    if(i == 0){
		    	cout<<"\nRecord doesn't exist'!!";
		    }
		    fin.close();
		    fout.close();
		    int j = remove("supplieritems.dat");
		    int z = rename("temp.dat","supplieritems.dat");
		}
		
};


class Retailer {
	
	ofstream fout;
	ifstream fin;
	fstream fio;

	public:
		
		Retailer(){
		
		}
		
		displayitems(){
			int i = 1;
			cout << "ITEMS IN SHOP:" << endl ;
			cout<<"\nNAME\t\tID\t\tSTOCK AVAILABLE\t\tPRICE";
			fin.open("retaileritems.dat",ios::in|ios::binary);
			item readitem;
			cout << endl;
		    while(!fin.eof()){

				fin.read((char*)&readitem,sizeof(readitem));

				if(!fin.eof()){
			    	if(fin.tellg()<0){
						i=0;
						break;
					}
//					if (fin.is_open()){
//   						cout << "Done !" << endl;
//					}
			    readitem.disp();
		    }}
		    if(i==0){
				cout<<"\n\tNo record exist";
				getch();
		    }
		    fin.close();
		    getch();
		}
		
		void addnewitem(){			
			Supplier s;
			item add = s.sell();
			if (add.getPrice() == -1){
				return;
			}
			
			fout.open("retaileritems.dat",ios_base::app | ios_base::in);
//			if (fout.is_open()){
//   				cout << "Done !" << endl;
//			}
			fout.write((char*)&add,sizeof(add));
			fout.close();
		}
		
		item sell(){
			system("cls");
			displayitems();
			system("cls");
			char temp_id[7];
			item temp_item;
			int qty;
			int i = 0;
			long pointerposition = 0;
//			system("cls");
			cout << "\n\nEnter the item's id: ";
			cin >> temp_id;
			cout << "\nEnter quantity: \n"<< endl;
			cin >> qty;
			fio.open("retaileritems.dat",ios::binary|ios::out|ios::in);
		    while(fio){
			    pointerposition = fio.tellp();
			    fio.read((char*)&temp_item,sizeof(temp_item));
			    if(temp_item.idcmp(temp_id)==0){
					temp_item.reduce(qty);
					fio.seekp(pointerposition);
					fio.write((char*)&temp_item,sizeof(temp_item));
					i = 1;
					break;
			    }
		    }
		    
			fio.close();
			if (i == 1){
		    	return temp_item;
			}
		    else if(i != 1){
		    	cout<<"\n\n!!Record not found!!";
		    	item garbage = item( -1, -1);
		    	return garbage;
			}
		}
		
		void refill(){
			system("cls");
			displayitems();
			system("cls");
			char temp_id[7];
			item temp_item;
			int qty;
			int i = 0;
			long pointerposition = 0;
//			system("cls");
			cout << "\n\nEnter the item's id: ";
			cin >> temp_id;
			cout << "\n\nEnter quantity: \n"<<endl;
			cin >> qty;
			fio.open("retaileritems.dat",ios::binary|ios::out|ios::in);
		    while(fio){
			    pointerposition = fio.tellp();
			    fio.read((char*)&temp_item,sizeof(temp_item));
			    if(temp_item.idcmp(temp_id)==0){
					temp_item.refill(qty);
					fio.seekp(pointerposition);
					fio.write((char*)&temp_item,sizeof(temp_item));
					i = 1;
					break;
			    }
		    }
		    if(i != 1){
		    	cout<<"\n\n!!Record not found!!";
			}
			fio.close();
		    system("cls");
		    getch;
			displayitems();
			getch;
		}
		
		void reduce(){
			system("cls");
			displayitems();
			system("cls");
			char temp_id[7];
			item temp_item;
			int qty;
			int i = 0;
			long pointerposition = 0;
//			system("cls");
			cout << "\n\nEnter the item's id: ";
			cin >> temp_id;
			cout << "\nEnter quantity: \n"<<endl;
			cin >> qty;
			fio.open("retaileritems.dat",ios::binary|ios::out|ios::in);
		    while(fio){
			    pointerposition = fio.tellp();
			    fio.read((char*)&temp_item,sizeof(temp_item));
			    if(temp_item.idcmp(temp_id)==0){
					temp_item.reduce(qty);
					fio.seekp(pointerposition);
					fio.write((char*)&temp_item,sizeof(temp_item));
					i = 1;
					break;
			    }
		    }
		    if(i != 1){
		    	cout<<"\n\n!!Record not found!!";
			}
			fio.close();
		    system("cls");
		    getch;
			displayitems();
			getch;
		}
		
		void removeitem(){
			system("cls");
			item temp;
			int i = 0;
			displayitems();
			system("cls");
		    char temp_id[7];
//		    cout<<"\n\t\t\t\tDelete Record";
		    cout<<"\n\nEnter the id of the product you want to remove: ";
		    cin >> temp_id;
		    fout.open("temp.dat",ios_base::app | ios_base::in);
		    fin.open("retaileritems.dat",ios::in|ios::binary);
		    while(!fin.eof()){
			fin.read((char*)&temp,sizeof(temp));
			if(!fin.eof()){
				if(temp.idcmp(temp_id) == 0){    			// add in the id class 
					temp.disp();
					cout<<"\nRecord deleted";
					i++;
			    }
			    else{
					fout.write((char*)&temp,sizeof(temp));
		    	}
				}
			}
		    if(i == 0){
		    	cout<<"\nRecord doesn't exist'!!";
		    }
		    fin.close();
		    fout.close();
		    int j = remove("retaileritems.dat");
		    int z = rename("temp.dat","retaileritems.dat");
		}
		
};

class PersonData{
	
	private:
		
		string lastName;     // The person's last name
		string firstName;    // The person's first name
		string address;      // The person's address
		string phone;        // The person's phone number
		
	public:
		
		PersonData(string ln, string fn, string addr, string ph){ 
			lastName = ln;
		    firstName = fn;
		    address = addr;
		    phone = ph;
		}
		
		PersonData(){
			lastName = "";
		    firstName = "";
		    address = "";
		    phone = "";
		}
		
		void setLastName(string ln)
		  { lastName = ln; }
		void setFirstName(string fn)
		  { firstName = fn; }
		void setAddress(string addr)
		  { address = addr; }
		void setPhone(string ph)
		  { phone = ph; }
		
		string getLastName() 
		  { return lastName; }
		string getFirstName()
		  { return firstName; }
		string getAddress() 
		  { return address; }
		string getPhone() const
		  { return phone; }
};

 
class Customer : public PersonData{

	private:

		int customerNumber;             // Customer number
	    int purchasesAmount;         // Holds the amount of a customer's purchases
	    double discountLevel;           // Holds the customer's discount level
		int points;
	    
	public:
	
		Customer(string ln, string fn, string addr, string ph, int cn, double pa, double dl, int points): PersonData(ln, fn, addr, ph){
			customerNumber = cn;
			purchasesAmount = pa;
			discountLevel = dl;
			this->points = points;
		}
	
		Customer() : PersonData(){
	   		customerNumber = 0;
			purchasesAmount = 0; 
			discountLevel = 0;
			points = 0;
		}
		
		Customer( Customer &o){
			this->customerNumber = o.customerNumber;
			this->purchasesAmount = o.purchasesAmount;
			this->discountLevel = o.discountLevel;
			this->points = o.points;
			setFirstName(o.getFirstName());
			setLastName(o.getLastName());
			setPhone(o.getPhone());
			setAddress(o.getAddress());
		}
		
		void Addnew(){
			cout<<"=================Sign up======================\n\n";
			string fname,lname,add;
			ofstream fout;
			string phone;
			int cn;
			cout<<"Enter first name: ";
			cin>>fname;
			cout<<"Enter last name: ";
			cin>>lname;
			cout<<"Enter address: ";
			cin>>add;
			cout<<"Enter phone: ";
			fflush(stdin);
		    cin>>phone;
		    cout<<"Enter customer number: ";
		    fflush(stdin);
			cin>>cn;
		    Customer c;
		    c = Customer(lname,fname,add,phone,cn, 0.0, 0.0 ,0);
		    fout.open("customeraccounts.dat",ios_base::app | ios_base::in);
			if (fout.is_open()){
   				cout << endl << "Registration done!" << endl;
			}
			fout.write((char*)&c,sizeof(c));
			fout.close();
			system("cls");
			fflush(stdin);
			string username, password;
			cout << "Enter username: ";
			fflush(stdin);
			getline(cin,username);
			fflush(stdin);
			cout << "Enter password: ";
			getline(cin,password);
		    fout.open("customer.txt",ios_base::app | ios_base::out);
//			if (fout.is_open()){
//   				cout << endl << "Registration done!" << endl;
//			}
			fout << username << "\t" << password << endl;
			fout.close();
		}
		
		   
	   	void setCustomerNumber(int cn){
			customerNumber = cn;
		}
	    
	   	int getCustomerNumber(){
			return customerNumber;
		}
	     
	    void setPurchasesAmount(double p){ 
			purchasesAmount = p;
	        determineDiscountLevel(); 
		}
		
	    double getPurchasesAmount(){ 
			return purchasesAmount; 
		}
		
	    double getDiscountLevel(){ 
		    determineDiscountLevel();
	        return discountLevel; 
		}
		
		void determineDiscountLevel(){
		    if (purchasesAmount >= 2000)
		    	discountLevel = 0.10;
		    else if (purchasesAmount >= 1500)
		        discountLevel = 0.07;
		    else if (purchasesAmount >= 1000)
		        discountLevel = 0.06;
		    else if (purchasesAmount >= 500)
		        discountLevel = 0.05;
		}
		
		void Displaydetails(){
			system("cls");
			
			cout << "Your account details: \n\nFirst Name: " << getFirstName() << "\nLast Name: "<< getLastName() <<"\nAddress:"<< getAddress()<<"\nPhone:"<< getPhone()<<"\nCustomer number:"<<getCustomerNumber()<<"\n"
			<<"Purchase amount:"<< getPurchasesAmount()<<"\nDiscount level:"<< getDiscountLevel()<< endl ;
		}
		
		
	    void addPurchase(double p){ 
			purchasesAmount += p;
		}
		
		addPoints(int amount){
			if (amount > 5000){
				points= points + 20; 
			}
			else if (amount > 2500){
				points = points + 10;
			}
			else if (amount > 1250){
				points = points + 5;
			}
			else if (amount > 500){
				points = points + 2;
			}
			else if (amount > 0){
				points = points + 1;
			}
		}
		
		void setPoints(int p){
			points = p;
		}
	    
	   	int getPoints(){
			return points;
		}
		
		Buy(){
			Retailer r;
			
			item bought = r.sell();
			addPurchase(bought.getPrice() * (1-getDiscountLevel()));
			addPoints(bought.getPrice());
			
			int bill = 0;
			int i, n;
			cout << "Enter the number of items you want to buy: ";
			cin >> n;
			for (i = 0;i < n;i++){
				item bought = r.sell();
				bill = bill + bought.getPrice();
			}
			addPurchase(bill * (1-getDiscountLevel()));
			addPoints(bought.getPrice());
			
			cout << "\n\nBill for these items: " << bill;
		} 
		
		Displayitems(){
			Retailer r;
			r.displayitems();
		}
		
}; 

Customer CustomerFinder(int cust_number){
	
	ifstream fin;
	
	Customer find;
	fin.open("customeraccounts.dat", ios::in);
	while(!fin.eof()){
		fin.read((char*)&find, sizeof(find));
		if (find.getCustomerNumber() == cust_number){
			fin.close();
			return find;
		}
	}
	
}

int PasswordChecker(int choice, char* name, char* password){
	
	switch (choice){
		case 1:
			{
			ifstream myfile;
			char*word; char*word2;
			myfile.open("supplier.txt",ios::in);
			char str[30];
			
			while(!myfile.eof()){
				myfile.getline(str, 30);
				
				word = strtok(str,"\t");
				word2 = strtok(NULL,"\t");
				
				if (strcmp(name,word) == 0 && strcmp(password,word2) == 0){
					return 1;
				}
			}
			break;
		}
		case 2:
			{
			
			ifstream myfile;
			char*word; char*word2;
			myfile.open("retailer.txt",ios::in);
			char str[30];
			
			while(!myfile.eof()){
				myfile.getline(str, 30);
				
				word = strtok(str,"\t");
				word2 = strtok(NULL,"\t");
				
				if (strcmp(name,word) == 0 && strcmp(password,word2) == 0){
					return 1;
				}
			}
			break;
		}
		case 3:
			{
			
			ifstream myfile;
			char*word; char*word2;
			myfile.open("customer.txt",ios::in);
			char str[30];
			
			while(!myfile.eof()){
				myfile.getline(str, 30);
				
				word = strtok(str,"\t");
				word2 = strtok(NULL,"\t");
				
				if (strcmp(name,word) == 0 && strcmp(password,word2) == 0){
					return 1;
				}
			}
			break;
		}
	}
}


int main(){
	
	char user[10],pass[10];
	int i,j;
	ofstream fout;
	
	
	cout<<"\n\n\n\n\n\n\n\n\n\n\n \t\t\t|============ WELCOME TO INVENTORY MANAGEMENT ============|";
	getch();
	system("cls");
	cout<<"\n\t\t   INVENTORY MANAGEMENT SYSTEM\n";	
	cout<<"=============================================================";
	cout<<"\n\n\t\t   1. Supplier Menu\n\n\t\t   2. Retailer Menu\n\n\t\t   3. Customer Menu";
	cout<<"\n\n=============================================================\n";
	cout<<"\n\nEnter Your Choice:";
	cin >> j;
	switch (j){
		case 1:
			{
				Supplier s;
				system("cls");
				cout<<"\n\n\n\n\n\n\n\t\t\t\t\tEnter the username letter by letter: ";
				cin >> user;
			    cout<<"\n\t\t\t\t\tEnter the password letter by letter: ";
			    cin >> pass;
				
				if(PasswordChecker(1,user,pass) == 1){
					cout << "Access Granted";
				    system("cls");
					suppliermenu:
					system("cls");
					cout<<"=================================================================";
					cout<<"\n\n\t\t\t    SUPPLIER MENU\n1. Add new product\n2. Display stock\n3. Refill stock\n4.Reduce any stock\n5. Remove an item\n6. Exit";
					cout<<"\n\n\n==========================END OF MENU=============================";
					cout<<"\n\n Enter your Choice :\t";
					cin>>i;
					if(i==1){
						s.addnewitem();getch();
						goto suppliermenu;
					}
					else if(i==2){
						system("cls");
						s.displayitems();
						getch();
						goto suppliermenu;
					}
					else if(i==3){
						s.refill();
						goto suppliermenu;
					}
					else if(i==4){
						s.removeitem();
						getch();
						goto suppliermenu;
					}
					else if(i==5){
						s.reduce();
						getch();
						goto suppliermenu;
					}
					else {
						system("cls");
						exit(0);
					}
				}
				else{
					cout<<"\n\n\nDidn't find those credentials\n\nExiting the program...\n\n";
					getch();
					exit(0);
				}
				break;
			}
		case 2:	
			{
				Retailer r;
				system("cls");
				cout<<"\n\n\n\n\n\n\n\t\t\t\t\tEnter the username letter by letter: ";
				cin >> user;
			    cout<<"\n\t\t\t\t\tEnter the password letter by letter: ";
			    cin >> pass;
				
				if(PasswordChecker(2,user,pass) == 1){
					retailermenu:
					system("cls");
					cout<<"=================================================================";
					cout<<"\n\n\t\t\tRETAILER MENU\n1. Display stock\n2. Refill\n3. Buy from Supplier\n4. Reduce stock\n5. Remove item\n6. Exit";
					cout<<"\n\n\n==========================END OF MENU=============================";
					cout<<"\n\n Enter your Choice :\t";
					cin>>i;
					if(i==1){
						system("cls");
						r.displayitems();
						getch();
						goto retailermenu;
					}
					else if(i==2){
						r.refill();
						goto retailermenu;
					}
					else if(i==3){
					r.addnewitem();
						goto retailermenu;
					}
					else if(i==4){
						r.reduce();
						goto retailermenu;
					}
					else if(i==5){
						r.reduce();
						goto retailermenu;
					}
					else{
						system("cls");
						cout<<"\n\n\n\t\t\tThank You!! Exiting the program...";
						getch();
						exit(0);
					}
				}
				else{
					cout<<"\n\n\nDidn't find those credentials\n\nExiting the program...\n\n";
					getch();
					getch();
					exit(0);
				}
			}
		case 3:
			{
				int choice;
				cout << "1. Signup if you are a new customer\n2. Sign in if you are old customer\n\nChoice: ";
				cin >> choice;
			switch(choice){
				case 1:
					{
					Customer c;
					c.Addnew();
					goto signin;
					break;
					}
				case 2:
					{
						signin:
						system("cls");
						cout<<"\n\n\n\n\n\n\n\t\t\t\t\tEnter the username letter by letter: ";
						cin >> user;
					    cout<<"\n\t\t\t\t\tEnter the password letter by letter: ";
					    cin >> pass;
					    
					    if(PasswordChecker(3,user,pass) == 1){
					    	int customernumber;
							system("cls");
					    	cout << "\nEnter the customer number: ";
					    	cin >> customernumber;
					    	Customer c;
							c = CustomerFinder(customernumber);
							customermenu:
							system("cls");
							cout<<"=================================================================";
							cout<<"\n\n\t\t\t    CUSTOMER MENU\n1. Purchase\n2. Display stock\n3. Display Your Account Details\n4. Exit:";
							cout<<"\n\n\n==========================END OF MENU=============================";
							cout<<"\n\n Enter your Choice :\t";
							cin>>i;
							
							if (i==1){
								c.Buy();
								getch();
								goto customermenu;
							}
							else if(i==2){
								system("cls");
								c.Displayitems();
								getch();
								goto customermenu;
							}
							else if(i==3){
								system("cls");
								c.Displaydetails();
								getch();
								goto customermenu;
							}
							else {
								system("cls");
								cout<<"\n\n\n\t\t\tThank You!! Exiting the program...";
								getch();
								exit(0);
							}
						}
						else {
							cout<<"\n\n\nDidn't find those credentials\n\nExiting the program...\n\n";
							getch();
							getch();
							exit(0);
						}
						break;
					}
					break;
				}
				
			}
//	system("clr");
	cout << "\n\n\n\t\t\t\t  Program has ended";

	}
}

