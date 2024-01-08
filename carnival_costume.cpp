/*Kathryn Bodden and Aliana Palmer
This is a program to track the inventory of a Carinval Band. It allows users to register for their costume
meaning a node is added to the linked list, pay for their costume which alters the remaining payment amount,
check the status of their costume which prints the information specific to the customer as well as a message
indicating the status of the costume and lastly there is an option to collect their costume. */
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

template <typename C>
class circleList;

class Person;

template <typename C>
class Node;

template <typename C>
class Node
{
  public:
		  Node(){};                   	// default constructor
		
 	private:
		  C info; 	                	// node data
		  Node<C>* next;

      friend class circleList<C>;		// friend classes of Node	
      friend class Person;
      friend class Costume;
};

template <typename C>
class circleList
{
	// private member of circleList
    private: 
      Node<C> *cursor;
    
    // public members of circleList
    public:
      circleList()        				// constructor
      {
         cursor = new Node<C>;
         cursor = NULL;
      }

      ~circleList()       			 	// destructor
      {                 
          while(!empty())
          {
              removeFront();
          }
      }

      bool empty() const				// checks to see if the list is empty	
      {                       
          return cursor == NULL;
      }

      const C& front() const			// returns the element at the cursor
      {
          return cursor->next->info;
      }

      const C& back() const				// returns the element after cursor
      {
          return cursor->info;
      }

      void advance()					// advance the cursor
      {
          cursor = cursor->next;          
      }

      // function to add behind the cursor.
      void addBack()
      {
          string na;                    // customer's name
          string num;                   // customer's contact number
          string em;                    // customer's email
          string section_na;            // costume name 
          string package_na;            // type of package
          float pr = 0.0;               // total price

          int section_num;             	//number associated with the section
          char package;               	//type of package
            
          Node<C>* newNode = new Node<C>;  //creating new node.

          //getting user to enter customer information and choices
          cout << "Enter customer's name: ";
          cin.ignore();
          getline(cin,na);

          cout << "Enter customer's phone number: ";
          getline(cin, num);

          cout << "Enter customer's email: ";
          getline(cin, em);

          //displaying the costume section options to the user.
          cout << "The following are the section names of the costume options:"<< endl;
          cout << "1. Athena" << endl;
          cout << "2. Aphrodite" << endl;
          cout << "3. Hera" << endl;
          cout << "4. Demeter" << endl;
          cout << "5. Artemis" << endl;
          cout << "Enter a number to select a section: " << endl;

          //the do while loop is for input validation, to ensure that the user enters a number that corresponds with a section number
          do 
          {
              cin >> section_num;
              
              //switch statements to save the option chosen by the user and add the corresponding costume price
              //to the total price. 
              switch (section_num)
              {
                  case 1: section_na = "Athena";
                          pr+= 875.00;
                          break;
                  case 2: section_na = "Aphrodite";
                          pr+= 900.00;
                          break;
                  case 3: section_na = "Hera";
                          pr += 950.00;
                          break;
                  case 4: section_na = "Demeter";
                          pr+= 800.00;
                          break;
                  case 5: section_na = "Artemis";
                          pr += 850.00;
                          break;
                  default: cout << "That is not a section in our band. Please enter a valid section number.";
                          break;
                }
          }while((section_num < 0) || (section_num > 6));
            
          cout << "Enter type of package (All inclusive (A), Drinks inclusive (D), Regular(R)): ";
          cin >> package; 
          package = toupper(package);

          //while loop is for in put validation. To make sure that the user entered a letter that corresponds with 
          do 
          {
              if (package == 'A')
              {
                  package_na = "All inclusive";
                  pr+= 600.00;
              }
              else if (package == 'D')
              {
                  package_na = "Drinks Inclusive";
                  pr += 500.00;
              }
              else if (package == 'R')
              {
                  package_na = "Regular";
                  cout << "This package is included with your costume price." <<endl;
              }
          } while(package == 'A' && package == 'D' && package == 'R');
              
          // stores the information entered to the as a node to the linked list    
          newNode->info.setName(na);
          newNode->info.setPhoneNumber(num);
          newNode->info.setEmail(em);
          newNode->info.setsectionName(section_na);
          newNode->info.setPackage(package_na);  
          newNode->info.setPrice(pr);                  
      
      	  //if list is empty then cursor points to null
          if (empty())   
          { 
              newNode->next = newNode;
              cursor = newNode;
          } 
          else 
          {
              newNode->next = cursor->next;
              cursor->next = newNode;
              cursor = cursor->next; //this line adds to the back 
          }
          return;
      }

      // remove the node after the cursor
      void removeFront()
      {
          if (empty())
          {
            cout<< "There are no registered customers in the list yet."<< endl;
          }
          else
          {
            Node<C>* oldNode = cursor->next;       // this is the node being removed

            if(oldNode == cursor)
              cursor = NULL;                      // the list is empty
            else
                cursor->next = oldNode->next;       // link the cursor next to the old's next
            delete oldNode;                         // delete the old Node
          }
      }

	  // function for updating a person's price balance 
      void payCostume()
      {
          string name;                            //variable to store specific customer name
          string email;                           //variable to store specific customer email
          float pay_amt;                          //variable to store amount customer would like to pay.
          int flag = 0;							  // flag variable

          //getting customer information and storing it
          cout << "Enter the name of the customer: " << endl;
          cin.ignore();
          getline(cin, name);
          cout << "Enter the email of the customer:" << endl;
          getline(cin, email);

          Node<C> *cur; //pointer to keep track of nodes and find specific customer node.

		  // finds the node with the matching name and email
          for (cur = cursor; cur != NULL; cur = cur->next)
          {
            if (name == cur->info.getName() && email == cur->info.getEmail())
			{
				flag = 1;	
              	break;
            }
          }
          
          // if a match was not found... display error message then return to the main menu
          if (flag == 0)
          {
            cout << "That name and email combination cannot be found." << endl;
            return;
          }
             
          //getting payment amount and storing it
          cout<< "Outstanding Balance: $" << cur->info.getPrice() << endl;
          cout<< "Enter the amount you would like to pay:" <<endl;
          cin >> pay_amt;
          float price = cur->info.getPrice();        // saving current total price of costume in variable to make it easier. 
          if (pay_amt == price)
          {
            cur->info.setPrice(0);                    //setting total price to 0 if the customer paid off the costume.
          }
          else 
          {                                           //calculations for new total price if customer didn't pay it off.
            float new_amt;
            new_amt = price - pay_amt;
            cur->info.setPrice(new_amt);              //setting new total price
          }
      }
      
      // this function prints a customer's costume status
      void printStatus()
      {
          string name;
          string email;
		      int flag = 0;
          int i=0;
        
          // accepts the customer's information
          cout << "Enter the name of the customer: " << endl;
          cin.ignore();
          getline(cin, name);
          cout << "Enter the email of the customer:" << endl;
          getline(cin, email);

		  Node<C> *cur = cursor;
    
    	  // // finds the node with the matching name and email
          for (cur = cursor; cur != NULL; cur = cur->next)
          {
            if (name == cur->info.getName() && email == cur->info.getEmail())
            {
              flag = 1;
              i++;
              break;
            }
          }
                    
		  // if a match was not found... display error message then return to the main menu
          if (flag == 0)
          {
            cout << "That name and email combination cannot be found." << endl;
            return;
          }
            
          //checks if the list is empty before printing; if it is return  
          if (empty())		
            {
                cout << "There are no people registered." << endl;
                return;
            }

          cout << "-------------Carnival Costume Status-------------" << endl;
          cur->info.print();                                      // calls the print function
          if ((cur->info.getPrice() == 0.0) && i ==1){
            cout << "Your carnival costume is ready for collection! You may leave the queue." << endl;
          }
          else if((cur->info.getPrice() == 0.0) && i !=1){
            cout<<"Your carnival costume is ready for collection! However, there are "<<i<<"people in front of you. Please wait until you are at the front of the queue to collect."<< endl;
          }
          else{
            cout<<"You still need to pay for your costume. The remaining balance is: "<< cur->info.getPrice()<<endl;
          }
      }
};

class Person
{
	// public members of Person
    public:
	  // constructor 
      Person(){};                                                 
      Person(string na, string pn, string em)
      {         
          name = na;
          phone_number = pn;
          email = em;
      }

      //setters
      void setName(string na){name = na;}
      void setPhoneNumber(string pn){phone_number = pn;}
      void setEmail(string em){email = em;}

      //getters
      string getName() { return name; }          
      string getPhoneNumber() { return phone_number; }      
      string getEmail() { return email; }      

	  // displays the song information
      virtual void print()            
      {
            cout << "Name: "<<name<< endl;
            cout << "Phone Number: " << phone_number << endl;
            cout << "Email: " << email << endl;
            cout << endl;        
      };

	// private members of Person
    private:
        string name;                // name of person
        string phone_number;        // person's phone number
        string email;               // person's email
};

// Costume inherits the Person class
class Costume: public Person
{
  public:
  	// constructor
    Costume(){};
    Costume(string sec, string pa, float pr){
      sectionName = sec;
      package = pa;
      price = pr;
    }

    //setters
    void setsectionName(string sec){sectionName = sec;}
    void setPackage(string pa){package = pa;}
    void setPrice(float pr){price = pr;}
    
    //getters
    string getbandName(){ return sectionName;} 
    string getPackage(){ return package;}
    float getPrice(){ return price; }

    //print function
    void print()
    {
      Person::print();
      cout << "Section Name: " << sectionName <<endl;
	  cout<< "Package Type: " <<package<< endl;
	  cout<< "Balance: $" << price<< endl;      
      cout << endl;
    }

  // private members of Costume	
  private:
    string sectionName;               
    string package;
    float price;
};

// this is the main menu function
void menu()
{
    cout << "Choose one of the following options:" <<endl;
    cout << "R to Register for your section." <<endl;
    cout << "P to Pay for your costume." <<endl;
    cout << "S to Check the Status of your costume." << endl;
    cout << "C to Collect your costume. Please note that you can only collect once the costume is fully paid." << endl;
    cout << "E to Exit the band page."<<endl;
}

// main function
int main() 
{
    char menuOption = ' ';			// menuOption is initializes as a space

    circleList<Costume> inventory;	// inventory is of data type circleList<Costume>
	
	// calls the main menu
    menu();

    do
    {
        cin >> menuOption;			// reads user input from the main menu
        menuOption = toupper(menuOption);	// changes the user input to upper case

		// a swtich statement for calling functions based on the user's input
        switch(menuOption)
        {
            case 'R':   inventory.addBack();		// calls the addBack() function 
                        menu();
                        break;
          
            case 'P':   inventory.payCostume();		// calls the payCostume() function 
                        menu();
                        break;

            case 'S':   inventory.printStatus();	// calls the printStatus() function 
            			menu();
                        break;
          
            case 'C':   inventory.removeFront();	// calls the removeFront() function 
                        menu();
                        break;
                        
            case 'E':   cout << "Thank you!" << endl;	// exits the program
                        exit(0);
                        break;

            default:    cout << "That is an invalid option" << endl;	// input validation to ensure that user entered a valid character
                        menu();
                        cin >> menuOption;
                        menuOption = toupper(menuOption);
                        break;
        }
    }while(menuOption != 'E');
    
	return 0;
}