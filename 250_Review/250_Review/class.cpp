#include <string>
#include <iostream>
using namespace std;

class Sports { // Create a class  
  public:             
    int id;        
    string name;  
    Sports(); // Declare constructor
    ~Sports(); //Declare destructor

    void setcategory(string cat){
      category = cat;
    }
    string getcategory(){
      return category;
    }

  private:
    string category;

};

// Constructor defined outside class
Sports::Sports()
{
    cout << "Object is being created\n";
}

// Destructor defined outside class
Sports::~Sports()
{
    cout <<"Object is being deleted";
}

int main() {
  Sports myObj;  // Create an object or instance of Sports

  // Access attributes and set values
  myObj.id = 1; 
  myObj.name = "Football";
  myObj.setcategory("outdoors");

  cout << myObj.id << " " << myObj.name << " " << myObj.getcategory() <<endl;

  return 0;
}


