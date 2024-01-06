#include<iostream>
#include<conio.h>
#include<string>
#include<Windows.h>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;

//Structed....
//Structure for customer and admin login info.....
struct LogIn{
     string userId;
     string password;
};
//struct for customer more info.....
typedef struct CustomerDetail{
     LogIn cusId;
     string status;
     string name;
     string city;
     string phoneNo;
}CD;
//struct to store the info of car.....
struct CarDetail{
     string noPlate;
     string name;
     string model;
     string status="Available";
     string rentCusId="rentCusId";
     string date="date";
     int rentedDay=0;
     int numRented=0;
     float price;
};
                                  //.......................Prototype of Functions............//
// ............Other Functions.......//
void displayHeader(string str);
void carDataFetch(CarDetail *carInfo,int &NUM_OF_CAR,fstream &Fetch);
void carDataWrite(CarDetail *carInfo,int &NUM_OF_CAR,fstream &Write);
void cusDataFetch(CD *customerInfo,int &NUM_OF_CUSTOMER,fstream &Fetch);
void cusDataWrite(CD *customerInfo,int &NUM_OF_CUSTOMER,fstream &Write);
//.........Admin Block.......//
void adminPage(int &infoIdx);
void changePassword(int &infoIdx);
void addRemoveCus();
void addRemoveCar();
void viewCusCar();
void customerDataUpdate();
void reportGenerate();
//................Customer Block......//
void customerPage(int &infoIdx);
void cusViewAvailCar();
void rentCar(int &infoIdx,CD *customerInfo,int &NUM_OF_CUSTOMER);
void returnCar(int &infoIdx,CD *customerInfo,int &NUM_OF_CUSTOMER);
void cusReport(string userId);
//..............Input Validation Functions......//
void fileChecking(fstream &);
void charValidate(char &ch,string str,char mn,char mx);
void stringInput(string str,string &value);
//..........Log in Function......//
void logInPage(char choice);
void logInControl(LogIn *info,int &size,int &infoIdx);

                                                //.........Definition of Functions.......//
// ............Other Functions.......//
// Dispaly the header of page...
void displayHeader(string str){
     cout << "\n\t\t\t  " << str 
          << "\n\t--------------------------------------------------------------------------------\n";
     cout << "\n\t\t      Loading.";
     for(int i=0;i<3;i++){
     Sleep(300);
     cout <<"..";
     }
          Sleep(1000);
          system("CLS");
          cout << "\n\t\t\t " << str 
               << "\n\t--------------------------------------------------------------------------------\n";
}
//Fetch data from file using loop of customer...
void cusDataFetch(CD *customerInfo,int &NUM_OF_CUSTOMER,fstream &Fetch){
      for(int i=0;i<NUM_OF_CUSTOMER;i++){
               Fetch.ignore(256,'\n');
               getline(Fetch,customerInfo[i].cusId.userId);
               getline(Fetch,customerInfo[i].cusId.password);
               getline(Fetch,customerInfo[i].status);
               getline(Fetch,customerInfo[i].name);
               getline(Fetch,customerInfo[i].city);
               getline(Fetch,customerInfo[i].phoneNo);
          }
}
//Write data on file using loop of customer....
void cusDataWrite(CD *customerInfo,int &NUM_OF_CUSTOMER,fstream &Write){
 for(int i=0;i<NUM_OF_CUSTOMER;i++){
     if(customerInfo[i].cusId.userId!=" "){
                    Write << endl<< customerInfo[i].cusId.userId;
                    Write << endl << customerInfo[i].cusId.password;
                    Write << endl << customerInfo[i].status ;
                    Write << endl << customerInfo[i].name ;
                    Write << endl << customerInfo[i].city ;
                    Write << endl << customerInfo[i].phoneNo << endl;
     }        
  }
}
//Fetch data from file using loop of Car...
void carDataFetch(CarDetail *carInfo,int &NUM_OF_CAR,fstream &Fetch){
      for(int i=0;i<NUM_OF_CAR;i++){
          Fetch.ignore(256,'\n');
          getline(Fetch,carInfo[i].noPlate);
          getline(Fetch,carInfo[i].name);
          getline(Fetch,carInfo[i].model);
          getline(Fetch,carInfo[i].status);
          getline(Fetch,carInfo[i].rentCusId);
          getline(Fetch,carInfo[i].date);
          Fetch >> carInfo[i].rentedDay;
          Fetch >> carInfo[i].numRented;
          Fetch >> carInfo[i].price;
          Fetch.ignore();
      }
}
//Write data on file using loop of Car....
void carDataWrite(CarDetail *carInfo,int &NUM_OF_CAR,fstream &Write){
     for(int i=0;i<NUM_OF_CAR;i++){
          if(!(carInfo[i].noPlate==" ")){
               Write << endl << carInfo[i].noPlate;
               Write << endl << carInfo[i].name;
               Write << endl << carInfo[i].model;
               Write << endl << carInfo[i].status ;
               Write << endl << carInfo[i].rentCusId ;
               Write << endl << carInfo[i].date ;
               Write << endl << carInfo[i].rentedDay ;
               Write << endl << carInfo[i].numRented ;
               Write << endl << carInfo[i].price<< endl;
          }  
     } 
}
// ............End of Other Functions.......//


//..............Input Validation Functions......//
//Function To validate the choice....
void charValidate(char &ch,string str,char mn,char mx){
    do{
        cout <<  ">>> " << str << " : ";
        ch=getche();
        if(ch>=mn&&ch<=mx)
             break;
        cout << "\n\t <--- Invalid Input ! Input range from " << mn << " to " << mx << " here ....  --->\n";
    }while(true);
}
//Validate the file is open or not....
void fileChecking(fstream &file){
     if(file.fail()){
          cout << "\n\t >>> Error ! IN opening File....";
          
     }
}
//Function is use to get value of string without empty in the whole program......
void stringInput(string str,string &value){
       do{
          cout << str;
          getline(cin,value);
          if(!(value==""||value==" "))
               break;
          else
          cout << "\n>>>> Empty Value is not allowed! Plz enter correct Value...\n\n";
          }while(true);
}
//..............End of Input Validation Functions......//


//................Customer Block......//
//Customer Block......
void customerPage(int &infoIdx){
     bool goback;
     do{
          int NUM_OF_CUSTOMER=0;
          //Data fetch from file of customer.....
          fstream DataFetch("CustomerLogIn.txt",ios::in);
          fileChecking(DataFetch);
          DataFetch>>NUM_OF_CUSTOMER;
          CD *customerInfo=new CD[NUM_OF_CUSTOMER];
          DataFetch.ignore();
          cusDataFetch(customerInfo,NUM_OF_CUSTOMER,DataFetch);
          DataFetch.close();
          system("CLS");
          displayHeader("___>>> WeLcoMe To ' CaR rEnTaL syTseM ' aS CusToMeR <<<___");
          char choice;
          goback=true;
          cout << "\n\n *******************************************************************\n" 
               << " *                                                                **\n"
               << " 1. Want to \' View Available Car \'...                             **\n"
               << " 2. Get \' car on rent \'...                                        **\n"
               << " 3. Want to \" Return Car \"...                                     **\n"
               << " 4. Generate \' rental reports \' of their car rented...            **\n"
               << " 5. Want to \" Log Out \"...                                        **\n"
               << " *                                                                **\n"
               << " *******************************************************************\n\n";
          charValidate(choice,"Enter Choice >> ",'1','5');
          system("CLS");
          switch(choice){
               case '1':
                  cusViewAvailCar();
                    break;
               case '2':
               rentCar(infoIdx,customerInfo,NUM_OF_CUSTOMER);
                    break;
               case '3':
               returnCar(infoIdx,customerInfo,NUM_OF_CUSTOMER);
                    break;
               case '4':
               cusReport(customerInfo[infoIdx].cusId.userId);
                    break;
               default:
                    goback=false;
          }
          //write Data of CUstomer
          fstream DataWrite("CustomerLogIn.txt",ios::out);
          DataWrite<< NUM_OF_CUSTOMER<< endl;
          cusDataWrite(customerInfo,NUM_OF_CUSTOMER,DataWrite);
          DataWrite.close();
          delete[] customerInfo;//Release Memory
          customerInfo=nullptr;
     }while(goback);
}
//Function to view available Car...
void cusViewAvailCar(){
     displayHeader("___>>> viEw aVaiLabLe cAr <<<___");
     int NUM_OF_CAR=0;
     fstream Fetch("carInfo.txt",ios::in);
     fileChecking(Fetch);
     Fetch >> NUM_OF_CAR;
     Fetch.ignore();
     CarDetail *carInfo=new CarDetail[NUM_OF_CAR];
     carDataFetch(carInfo,NUM_OF_CAR,Fetch);
     Fetch.close();
     cout << "\n\n\t\t << _____ CaR DeTaiL's _____ >>\n";
     if(NUM_OF_CAR==0){
          cout << "\n<<< ---NO Car Available NOw !--- >>>\n";
     }
     int c=0;
     for (int i=0;i<NUM_OF_CAR;i++){
          if(carInfo[i].status=="Available") {
               cout << "\n\t------ Detail of Car " << ++c << " ----- \n";
               cout << " > No_Plate :: " << carInfo[i].noPlate << endl;
               cout << " > Name :: " << carInfo[i].name << endl;
               cout << " > Model :: " << carInfo[i].model << endl;
               cout << " > Status :: " << carInfo[i].status << endl;
               cout << " > Price :: " << carInfo[i].price << endl;
          }
     }
     delete [] carInfo;
     carInfo=nullptr;
     cout << "Enter any key to continue : ";
     getche();
}
//Function which can rent a car..... 
void returnCar(int &infoIdx,CD *customerInfo,int &NUM_OF_CUSTOMER){
     displayHeader("\t___>>> reTurN cAr <<<____ ");
     int NUM_OF_CAR=0;
      fstream Fetch("carInfo.txt",ios::in);
      fileChecking(Fetch);
      Fetch >> NUM_OF_CAR;
      Fetch.ignore();
      CarDetail *carInfo=new CarDetail[NUM_OF_CAR];
     carDataFetch(carInfo,NUM_OF_CAR,Fetch);
      Fetch.close();
      bool found=false;
      int no=0;char ch;//choice(return/or not)
      for (int i = 0; i < NUM_OF_CAR; i++){
          if(customerInfo[infoIdx].cusId.userId==carInfo[i].rentCusId){
              found =true;
              no=i;
              break;
          }
      }
      if(found){
          cout << "\n_________________________________________________________________________________\n";
          cout << setw(15) << "No_plate" << setw(20) << "Name" << setw(15) << "Model" << setw(15) << "Status" << setw(15) << "Price" << endl;
          cout << "\n_________________________________________________________________________________\n";
          cout << setw(15) << carInfo[no].noPlate << setw(20) << carInfo[no].name << setw(15) << carInfo[no].model;
          cout << setw(15) << carInfo[no].status  << setw(15) << carInfo[no].price << endl;
          cout << "\n_________________________________________________________________________________\n";
          cout << ">>You sure to return this car(only press 'y' for Yes) : ";
          ch=getche();
          if(ch=='y'||ch=='Y'){
               carInfo[no].status="Available";
               customerInfo[infoIdx].status="Available";
               carInfo[no].rentCusId="rentCusId";
               carInfo[no].date="date";
               carInfo[no].rentedDay=0;
               carInfo[no].status="Available";
               fstream cusReport;
               cusReport.open(customerInfo[infoIdx].cusId.userId,ios::out |ios::app);
               //report store on file as history....
               cusReport << "Return_Time : " << __TIME__ << "\t\tReturn_Date : "  << __DATE__<< endl;
               cusReport.close();
               cout << "\n\t\t<_____car Return Successfully!____>\n";
               cout << "Return_Time : " << __TIME__ << "\t\tReturn_Date : "  << __DATE__<< endl ;
               cout << "\n\t\t ____ ThAnkS YoU FoR ChOsInG mY CaR RenTaL SySteM ____ \n";
               Sleep(5000);
               remove("carInfo.txt");
               //Update car info on file..
               fstream DataWrite("carInfo.txt",ios::out);
               DataWrite << NUM_OF_CAR<< endl;
               carDataWrite(carInfo,NUM_OF_CAR,DataWrite);
               DataWrite.close();
          }
          else
            cout << "\n\t>>You cann't return your car.......\n";

      }
      else{
          cout << "\n\n\t >> ___You cann't return any car , For returning car you must get car on rent !____\n";
      }
      delete[] carInfo;//Release Memory
      carInfo=nullptr;
  cout << "Enter any key to conitune:";
  getche();
}
//Function that give car to customer as rented....
void rentCar(int &infoIdx,CD *customerInfo,int &NUM_OF_CUSTOMER){
     displayHeader("\t___>>> rEnT cAr <<<____ ");
     int NUM_OF_CAR=0;
     fstream Fetch("carInfo.txt",ios::in);
     fileChecking(Fetch);
     Fetch >> NUM_OF_CAR;
     Fetch.ignore();
     CarDetail *carInfo=new CarDetail[NUM_OF_CAR];
     carDataFetch(carInfo,NUM_OF_CAR,Fetch);
     Fetch.close();
     bool found=false;
     int no=0;char ch;//choice(return/or not)
     for (int i = 0; i < NUM_OF_CAR; i++){
          if(customerInfo[i].cusId.userId==carInfo[i].rentCusId){
              found =true;
              no=i;
              break;
          }
     }
     if(!found){
          cout << "\n\n\t\t << _____ CusToMeR cAn RenT CAr _____ >>\n\n ";
          cout << "\t\t < _____ Availble CAr _____ >\n ";          
          cout << "\n_________________________________________________________________________________\n";
          cout << setw(15) << "No_plate" << setw(20) << "Name" << setw(15) << "Model" << setw(15) << "Status" << setw(15) << "Price" << endl;
          for(int i=0;i<NUM_OF_CAR;i++){
               if(carInfo[i].status=="Available"){
                    cout << "\n_________________________________________________________________________________\n";
                    cout << setw(15) << carInfo[i].noPlate << setw(20) << carInfo[i].name << setw(15) << carInfo[i].model<< setw(15) << carInfo[i].status<<setw(15) << carInfo[i].price << endl;
               }
          } 
          cout << "\n_________________________________________________________________________________\n";
          bool foundCar,available;
          int count=0;
          CarDetail temp;
          do{
               available=true;
               foundCar=false;
               stringInput("==> Enter the No_Plate of car which You want to get as rent >> ",temp.noPlate);
               for(int i=0;i<NUM_OF_CAR;i++){
                    if(carInfo[i].noPlate==temp.noPlate){
                         foundCar=true;
                         if(!(carInfo[i].status=="Available")){
                         available=false;
                         break;
                         }
                         else{
                              count=i;
                              available=true;
                         }
                    }
               }
               if(!foundCar && available)
                    cout << "\n ______Invalid Input ! Plz give Correct No _Plate....\n";
               if(!available)
                    cout << "\n >> This car is not available at this time......\n";
          }while(!(foundCar && available));
          //Update data....
          carInfo[count].status="Rented";
          customerInfo[infoIdx].status="Rented";
          carInfo[count].rentCusId=customerInfo[infoIdx].cusId.userId;
          //Some more detail get....
          cout << "\n\t\t_____Days for car is used______\n\n";
          do{
               int tempday;
               cout << "\n==>Enter the numbers of days : ";
               cin >> tempday;
               if(tempday<=0||tempday>30){
                   cout << "\n\t>>___ days Must be greaterthan '0' and less than '30'___\n";
               }
               else{
                    carInfo[count].rentedDay=tempday;
                    break;
               }

          }while(true);
          double carRent=0.0;
          carRent=carInfo[count].price*carInfo[count].rentedDay;
          carInfo[count].date=__DATE__;
          cout << "\nWorking on your Command....\n";
          Sleep(3000);
          //Recipt show on screen..
          cout << "\n\n\t<<______ RecePiT oF CusTomeR _______>>\n\n";
          cout << "User ID : " << customerInfo[infoIdx].cusId.userId << endl << "Car No_plate : " << temp.noPlate << endl << "Time : " << __TIME__ << "\t\tDate : "  << carInfo[count].date<< endl ;
          cout << "Car Rent per Day : " << carInfo[count].price << endl << "Days for car rent : " << carInfo[count].rentedDay << "\t\tTotal Car Rent : " << carRent << endl;
          fstream cusReport;
          cusReport.open(customerInfo[infoIdx].cusId.userId,ios::out |ios::app);
          //report store on file as history....
          carInfo[count].numRented++;//Number add of rented car...
          cusReport << "User ID : " << customerInfo[infoIdx].cusId.userId << endl << "Car No_plate : " << temp.noPlate <<endl << "Issue_Time : " << __TIME__ << "\t\tIssue_Date : "  << carInfo[count].date<< endl ;
          cusReport << "Car Rent per Day : " << carInfo[count].price << endl << "Days for car rent : " << carInfo[count].rentedDay << "\t\tTotal Car Rent : " << carRent << endl ;
          cusReport.close();
          cout << "\n\t\t ____ ThAnkS YoU FoR ChOsInG mY CaR RenTaL SySteM ____ \n";
          Sleep(5000);
          remove("carInfo.txt");
          //Update car info on file..
          fstream DataWrite("carInfo.txt",ios::out);
          DataWrite << NUM_OF_CAR << endl;
          carDataWrite(carInfo,NUM_OF_CAR,DataWrite);
          DataWrite.close();
      }
      else{
          cout << "\n\t___>>> You can get car on rent one at a time ....\n";
          cout << "\n\t___>>> Which you can get ....\n";
      }
      delete[] carInfo;//Release Memory
      carInfo=nullptr;
     cout << "\nEnter any key to continue:";
     getche(); 
}
//Report Generate...
void cusReport(string userId){
    displayHeader("\t___>>> CusToMer rEpOrT <<<____ ");
    string temp;
    int count=0;
     fstream cusReport(userId,ios::in);
     while(getline(cusReport,temp)){
          count++;
          cout << temp << endl;
     }
     if(cusReport.fail()&&count==0)
        cout << "\n\t\t__>>No cAr rEnTaL rePorT oF tHis cUsToMeR<<__\n";

     cout << "Enter any key to continue : ";
     getche();
}
//................End of Customer Block......//



//..........Log in Function......//
//Main Function....
int main(){
     cout << "\t\t**********************************************************************\n"
          << "\t\t*                                                                    *\n"
          << "\t\t*               WelCoMe To aLaM cAr RenTaL SysTeM                      *\n"
          << "\t\t*                                                                    *\n"
          << "\t\t**********************************************************************\n";
     char ch;//for get ch at last off the program to itreate whole program get at last of main function..
     char choice ;//Choice to check it is admin or user....
     do{
        cout << "\n\n *******************************************\n" 
              << " *                                        **\n"
              << " 1. Log In as Admin...                    **\n"
              << " 2. Log In as Customer...                 **\n"
              << " 3. Exit the Program...                   **\n"
              << " *                                        **\n"
              << " *******************************************\n\n";
          charValidate(choice,"Enter Choice >> ",'1','3');
          switch(choice){
               case '1':
               case '2':
                    logInPage(choice);
                    break;
               default:
                    cout << "\nExit the Program..."; 
                    exit(0);
          }
          cout << "\nHello ! press 'Y' for continue(another key for no): ";
          cin >> ch;
     }while(ch=='y'||ch=='Y');
     getch();
}
//Function is used to control the whole log in page and redirect separte admin and customer page as your choice... 
void logInPage(char choice){
     //Data fetch from file of admin.....
     int NUM_OF_ADMIN=0;
      fstream adDataFetch("adminLogIn.txt",ios::in);
      fileChecking(adDataFetch);
      adDataFetch>>NUM_OF_ADMIN;
     LogIn *adminLI=new LogIn[NUM_OF_ADMIN];
     for(int i=0;i<NUM_OF_ADMIN;i++){
          adDataFetch.ignore();
          getline(adDataFetch,adminLI[i].userId);
          getline(adDataFetch,adminLI[i].password);
     }
     adDataFetch.close();
     //Data fetch from file of customer.....
     int NUM_OF_CUSTOMER=0;
     fstream cusDataFetch;
     cusDataFetch.open("CustomerLogIn.txt",ios::in);
     fileChecking(cusDataFetch);
      cusDataFetch>>NUM_OF_CUSTOMER;
      cusDataFetch.ignore();
     LogIn *customerLI=new LogIn[NUM_OF_CUSTOMER];
     for(int i=0;i<NUM_OF_CUSTOMER;i++){
          cusDataFetch.ignore(256,'\n');
          getline(cusDataFetch,customerLI[i].userId);
          getline(cusDataFetch,customerLI[i].password);
          cusDataFetch.ignore(256,'\n');
          cusDataFetch.ignore(256,'\n');
          cusDataFetch.ignore(256,'\n');
          cusDataFetch.ignore(256,'\n');
     }
     cusDataFetch.close();
     int infoIdx;//idx where the data of user stored as login...
     switch(choice){
          case '1':
             displayHeader("___>>> WeLcoMe aS AdmIn | LogIn pAgE <<<____");
             logInControl(adminLI,NUM_OF_ADMIN,infoIdx);
             delete[] adminLI;
             adminLI=nullptr;
             adminPage(infoIdx);
             break;
          default:
             displayHeader("____>>> WeLcoMe aS cUsTomEr | LogIn pAgE <<<___");
             logInControl(customerLI,NUM_OF_CUSTOMER,infoIdx);
              delete[] customerLI;
             customerLI=nullptr;
             customerPage(infoIdx);
     }
}
//This function get the user id & password and validate it....
void logInControl(LogIn *info,int &size,int &infoIdx){
     int chances=5;
     LogIn getInfo;    
      do{
          if(chances==0){
               cout << "\nexit Program!";
               exit(0);
          }
         bool idfound=false;/*it check userID is match or not */
         //bool checker2=false;//it check password value is match or not
         stringInput("\n==> Enter your User ID here >>> ",getInfo.userId);
         stringInput("==> Enter your password here >>> ",getInfo.password);
         for(int i=0;i<size;i++){ //Loop for check user id & password with  all save user id & password 
             if((getInfo.userId==info[i].userId) && (getInfo.password==info[i].password) ){
                 idfound=true;
                 infoIdx=i;
                  break;
              }
         }
         if(idfound){
           break;
         }
         cout << "\n\t\t<------Invalid Parameters ----->\n";
         chances--;
         cout << "\t___You have " << chances << " chances to Log In...\n";
          
     }while(true);
 }
//..........End of Log in Function......//



//.........Admin Block.......//
//Admin Block......
 void adminPage(int &InfoIdx){
     bool goback;//then true if user log out..
     do{
          system("CLS");
          displayHeader("___>>> WeLcoMe To ' CaR rEnTaL syTseM ' aS AdMiN <<<____");
          char choice;
          goback=true;
          cout << "\n\n *********************************************************\n" 
               << " *                                                      **\n"
               << " 1. Want to \"change Password \"...                       **\n"
               << " 2. View current \" Register Car & Customer \"...         **\n"
               << " 3. Add or Remove \" Customer \"...                       **\n"
               << " 4. Update \" Customer Data \"...                         **\n"
               << " 5. Add or Remove \" Car \"...                            **\n"
               << " 6. Check \" Report \" related to Customer and Car...     **\n"
               << " 7. Want to \" Log Out \"...                              **\n"
               << " *                                                      **\n"
               << " *********************************************************\n\n";
          charValidate(choice,"Enter Choice >> ",'1','7');
         system("CLS");
          switch(choice){
               case '1':
                    changePassword(InfoIdx);
                    break;
               case '2':
                    viewCusCar();
                    break;
               case '3':
                    addRemoveCus();
                    break;
               case '4':
                    customerDataUpdate();
                    break;
               case '5':
                    addRemoveCar();
                    break;
               case '6':
                    reportGenerate();
                    break;
               default:
                    goback=false;
               }
     }while(goback);
 }
// //Change password...
 void changePassword(int &infoIdx){
     
     displayHeader("\t___>>> AdMiN ChAnGe PaSSwOrD <<<____ ");
     //Data fetch from file of admin.....
     int NUM_OF_ADMIN=0;
      fstream adDataFetch("adminLogIn.txt",ios::in);
      fileChecking(adDataFetch);
      adDataFetch>>NUM_OF_ADMIN;
     LogIn *adminLI=new LogIn[NUM_OF_ADMIN];
     for(int i=0;i<NUM_OF_ADMIN;i++){
           adDataFetch.ignore();
          getline(adDataFetch,adminLI[i].userId);
          getline(adDataFetch,adminLI[i].password);
     }
     adDataFetch.close();
     string newPassword,confirmPassword;
     do{
          string newPassword=" ",confirmPassword=" ";
          stringInput("\n--> Enter New Password >>>> ",newPassword);
          stringInput("--> Enter Confirm Password >>>> ",confirmPassword);
          if(newPassword==adminLI[infoIdx].password ){
               cout << "\t\t <--- Error ! your Current Password and new Password are same,Choose another password ---> \n";
               continue;
          }
          else if(newPassword!=" " && newPassword==confirmPassword){
                 adminLI[infoIdx].password=newPassword;
                 break;
          }
           cout << "\t\t <--- Error ! New Password & Confirm Password doesn't match -->\n";  
     }while(true);
     //Update Value
     for(int i=0;i<NUM_OF_ADMIN;i++){
          if(adminLI[i].userId==adminLI[infoIdx].userId)
                   adminLI[i].password=adminLI[infoIdx].password;
     }
     cout << "\n\t\t <--- Password ChaNgE SuccesSfuLly ! -->\n";
   //Write data on file
     ofstream DataWrite("adminLogIn.txt");
     DataWrite<< NUM_OF_ADMIN;
     for(int i=0;i<NUM_OF_ADMIN;i++){
          DataWrite << endl<< adminLI[i].userId;
          DataWrite << endl << adminLI[i].password << endl;
     }
     DataWrite.close();
     delete[] adminLI;
     adminLI=nullptr;
     cout << "Enter any key to continue : ";
     getche();
}
// //Function to view current Register car and Customer...
void viewCusCar(){
     char choice;
     displayHeader("\t___>>> vIeW CusToMer & cAr <<<____ ");
     cout << "\n\n ************************************************************\n" 
                    << " *                                                         **\n"
                    << " 1. View \' Current Registered Customer \'...                **\n"
                    << " 2. View \' Current Registered Car\'...                      **\n"
                    << " 3. For go Back ...                                        **\n"
                    << " *                                                         **\n"
                    << " ************************************************************\n\n";
     charValidate(choice,"==> Enter Choice here... >>>",'1','3');
     cout << "\n      =>> Working on your Command ...... \n";
     Sleep(3000);
     switch(choice){
     case '1':{
          //Data fetch from file of customer.....
          int NUM_OF_CUSTOMER=0;
          fstream DataFetch("CustomerLogIn.txt",ios::in);
          fileChecking(DataFetch);
          DataFetch>>NUM_OF_CUSTOMER;
          DataFetch.ignore();
          CD *customerInfo=new CD[NUM_OF_CUSTOMER];
          cusDataFetch(customerInfo,NUM_OF_CUSTOMER,DataFetch);
          DataFetch.close();
          int c=0;
          cout << "\n\n\t\t << _____ CusToMeR DeTaiL's _____ >>\n";
          for (int i=0;i<NUM_OF_CUSTOMER;i++){
               cout << "\n\t------ Detail of Customer " << ++c << " ----- \n";
               cout << " > User Id :: " << customerInfo[i].cusId.userId << endl;
               cout << " > Status:: " << customerInfo[i].status << endl;
               cout << " > Name:: " << customerInfo[i].name << endl;
               cout << " > City:: " << customerInfo[i].city << endl;
               cout << " > PHone NO:: " << customerInfo[i].phoneNo << endl;
               
          }          
          delete [] customerInfo; //release Memory
          customerInfo=nullptr;
     }
          break;
     case '2':{
          int NUM_OF_CAR=0;//Data of car rent...
          fstream Fetch("carInfo.txt",ios::in);
          fileChecking(Fetch);
          Fetch >> NUM_OF_CAR;
          Fetch.ignore();
          CarDetail *carInfo=new CarDetail[NUM_OF_CAR];
          carDataFetch(carInfo,NUM_OF_CAR,Fetch);
          Fetch.close();
          cout << "\n\n\t\t << _____ CaR DeTaiL's _____ >>\n";
          if(NUM_OF_CAR==0){
               cout << "\n<<< ---NO Car Available NOw !--- >>>\n";
          }
          for (int i=0;i<NUM_OF_CAR;i++){
               cout << "\n\t------ Detail of Car " << i+1 << " ----- \n";
               cout << " > No_Plate :: " << carInfo[i].noPlate << endl;
               cout << " > Name :: " << carInfo[i].name << endl;
               cout << " > Model :: " << carInfo[i].model << endl;
               cout << " > Status :: " << carInfo[i].status << endl;
               cout << " > Price :: " << carInfo[i].price << endl;
          }
          delete [] carInfo;
          carInfo=nullptr;
     }
          break;
     default:
          break;
     }
     cout << "Enter any key to continue : ";
     getche();
}
// //Function used to remove or add the customer....
void addRemoveCus(){
     char choice;
     displayHeader("\t___>>> aDD & rEmOvE CusTomEr <<<____ ");
     do{
          int NUM_OF_CUSTOMER=0;//Data fetch from file of customer.....
          fstream DataFetch("CustomerLogIn.txt",ios::in);
          fileChecking(DataFetch);
          DataFetch>>NUM_OF_CUSTOMER;
          CD *customerInfo=new CD[NUM_OF_CUSTOMER];
          DataFetch.ignore();
          cusDataFetch(customerInfo,NUM_OF_CUSTOMER,DataFetch);
          DataFetch.close();
          cout << "\n\n ****************************************************\n" 
               << " *                                                 **\n"
               << " 1. Want \' To remove Customer \'...                 **\n"
               << " 2. Want \' To add/register Customer\'...            **\n"
               << " 3. For go Back ...                                **\n"
               << " *                                                 **\n"
               << " ****************************************************\n\n";
          charValidate(choice,"Enter Choice >> ",'1','3');
          switch(choice){
               case '1':{
                    bool found;//found user id or not....
                    string tempUserId;
                         cout << "\n\t\t <-- Customer Remove -->\n";
                    do{
                         found=false;
                         stringInput("==> Enter the user Id of Customer >> ",tempUserId);
                         for(int i=0;i<NUM_OF_CUSTOMER;i++){
                              if(customerInfo[i].cusId.userId==tempUserId){
                                   found=true;
                                   if(customerInfo[i].status=="Rented"){
                                        cout << "\n\t>>>____This customer is not remove because it get car on rent !___<<\n\n";
                                        break;
                                   }
                                   else{
                                        customerInfo[i].cusId.userId=" ";
                                        //write Data of CUstomer
                                        fstream DataWrite("CustomerLogIn.txt",ios::out);
                                        DataWrite<< NUM_OF_CUSTOMER-1<< endl;
                                        cusDataWrite(customerInfo,NUM_OF_CUSTOMER,DataWrite);
                                        DataWrite.close();
                                        cout << "\n\n\t <<==  Customer Remove Successfully !  ==>>\n";
                                        break;
                                   }
                              }
                         }
                         if(!found)
                         cout << "\t\t<-- " << tempUserId << " is not found ! -->\n\t\t\tPLZ Renter.... \n";
                    }while(!found);
                         
               }
               break;
               case '2':
               {
                    CD temp;
                    bool userfound=true;
                    do{
                         cout << "\n\t\t <-- Add New Customer -->\n";
                         if(userfound){
                              stringInput("==> Enter the user Id of Customer >> ",temp.cusId.userId);
                         }
                         userfound=false;
                         for(int i=0;i<NUM_OF_CUSTOMER;i++){
                              if(customerInfo[i].cusId.userId==temp.cusId.userId)
                                   userfound=true;
                         }
                         if(userfound)
                              cout << "\n\n \t\t <<=== Customer of this User ID is exists ===>>\n\t\t Plz enter another user Id....\n\n";
                         else
                              break;
                    }while(true);
                    
                    stringInput("==> Enter the password of Customer >> ",temp.cusId.password);
                    stringInput("=>Enter the new Name:",temp.name);
                    stringInput("=>Enter the new City:",temp.city);  
                    stringInput("=>Enter the new Phone NO:",temp.phoneNo);
                    temp.status="Available";
                    //write Data of CUstomer
                    fstream DataWrite("CustomerLogIn.txt",ios::out);
                    DataWrite<< NUM_OF_CUSTOMER+1<< endl;
                    cusDataWrite(customerInfo,NUM_OF_CUSTOMER,DataWrite);
                    DataWrite<< endl<< temp.cusId.userId;
                    DataWrite << endl << temp.cusId.password ;
                    DataWrite << endl << temp.status ;
                    DataWrite << endl << temp.name ;
                    DataWrite << endl << temp.city ;
                    DataWrite << endl << temp.phoneNo << endl;
                    DataWrite.close();
                    ofstream write(temp.cusId.userId);
                    write.close();
                    cout << "\n\n\t <<==  Customer Add Successfully !  ==>>\n";
               }
                    break;
               default: 
               break;
          }
               delete[] customerInfo;//release Memory
               customerInfo=nullptr;
               cout << "\n==>> U want to add / Remove another customer  | If yes enter 'y' or enter any key for not : ";
               choice=getche();
     }while(choice=='y'|| choice=='Y');
}
// //Function to Update data of customer......
void customerDataUpdate(){
     displayHeader("\t___>>> CusTomEr DaTa UpDaTe <<<____ ");
     int NUM_OF_CUSTOMER=0;
     //Data fetch from file of customer.....
     fstream DataFetch("CustomerLogIn.txt",ios::in);
     fileChecking(DataFetch);
     DataFetch>>NUM_OF_CUSTOMER;
     CD *customerInfo=new CD[NUM_OF_CUSTOMER];
     DataFetch.ignore();
     cusDataFetch(customerInfo,NUM_OF_CUSTOMER,DataFetch);
     DataFetch.close();
     char choice;
     bool found;//found userId
     int count;
     string tempUserId;
     cout << "\n\t\t <-- Update Customer -->\n";
     do{
          count=0;
          found=false;
          stringInput("==> Enter the user Id of Customer >> ",tempUserId);
          for(int i=0;i<NUM_OF_CUSTOMER;i++){
               if(customerInfo[i].cusId.userId==tempUserId){
                    found=true;
                    count=i;
                    break;
                    }
          }
          if(!found)
               cout << "\t\t<-- " << tempUserId << " is not found ! -->\n\t\t\tPLZ Renter.... \n";
     }while(!found);
     do{
          cout << "\n Press 'y' to change Password(for no press any key) : ";
          choice=getche();
          if(choice=='y'||choice=='Y'){
               do{
               string tempPass;
               stringInput("\n==>Enter the new Password :",tempPass);
               if(tempPass==customerInfo[count].cusId.password){
                    cout << "\n\t__Password match with the old Password!__\n";
               }
               else{
                    customerInfo[count].cusId.password=tempPass;
                    cout << "\n\t<< ___Change Passsword Successfully__>>\n";
                    break;
               }
               }while(true);
          }
          cout << "\n Press 'y' to change Name(for no press any key) : ";
          choice=getche();
          if(choice=='y'||choice=='Y'){
               stringInput("\n=>Enter the new Name:",customerInfo[count].name);
          }
          cout << "\n Press 'y' to change City(for no press any key) : ";
          choice=getche();
          if(choice=='y'||choice=='Y'){
               stringInput("\n=>Enter the new City:",customerInfo[count].city);
          }
          cout << "\n Press 'y' to change Phone NO(for no press any key) : ";
          choice=getche();
          if(choice=='y'||choice=='Y'){
               stringInput("\n=>Enter the new Phone NO:",customerInfo[count].phoneNo);
          }
          cout << "\n\n____ Preview's Update Data ____\n";
          cout << "\n :::User Id : " << customerInfo[count].cusId.userId; 
          cout << "\n :::Password : " << customerInfo[count].cusId.password; 
          cout << "\n :::Name : " << customerInfo[count].name; 
          cout << "\n :::City : " << customerInfo[count].city; 
          cout << "\n :::Phone No : " << customerInfo[count].phoneNo; 
          cout << "\n Press 'y' to more change(for no press any key) : ";
          choice=getche();
          if(!(choice=='y'||choice=='Y')){
                    break;
          }
          
     }while(true);
          //write Data of CUstomer
          fstream DataWrite("CustomerLogIn.txt",ios::out);
          DataWrite<< NUM_OF_CUSTOMER<< endl;
          cusDataWrite(customerInfo,NUM_OF_CUSTOMER,DataWrite);
          DataWrite.close();
          delete[] customerInfo;//release Memmory..
          customerInfo=nullptr;
        
         cout << "\n\t<<<__Update data Successfully !__>>>\n";
 }
//Function to add or remove the car........
void addRemoveCar(){
     displayHeader("\t___>>> aDD & reMoVe cAr <<<____ ");
     char choice;
     do{
          int NUM_OF_CAR=0;//Car data fetch...
          fstream Fetch("carInfo.txt",ios::in);
          fileChecking(Fetch);
          Fetch >> NUM_OF_CAR;
          Fetch.ignore();
          CarDetail *carInfo=new CarDetail[NUM_OF_CAR];
          carDataFetch(carInfo,NUM_OF_CAR,Fetch);
          Fetch.close();
          cout << "\n\n ****************************************************\n" 
               << " *                                                 **\n"
               << " 1. Want \' To remove Car \'...                      **\n"
               << " 2. Want \' To add Car\'...                          **\n"
               << " 3. For go Back ...                                **\n"
               << " *                                                 **\n"
               << " ****************************************************\n\n";
          charValidate(choice,"Enter Choice >> ",'1','3');
          cout << "\n_________________________________________________________________________________\n";
          cout << setw(15) << "No_plate" << setw(20) << "Name" << setw(15) << "Model" << setw(15) << "Status" << setw(15) << "Price" << endl;
          for(int i=0;i<NUM_OF_CAR;i++){
               cout << "\n_________________________________________________________________________________\n";
               cout << setw(15) << carInfo[i].noPlate<< setw(20) << carInfo[i].name;
               cout << setw(15) << carInfo[i].model << setw(15) << carInfo[i].status<<setw(15) << carInfo[i].price << endl;
          } 
          cout << "\n_________________________________________________________________________________\n";
          switch(choice){
               case '1':{
                    if(NUM_OF_CAR==0){
                         cout << "\n>>> NO car Detail is Stored ,i.e, No car is added in System you first add car...\n";
                         break;
                    }
                    bool found;
                    string tem;
                    int count;
                         cout << "\n\t\t <-- Remove Car -->\n";
                    do{
                         count=0;
                         found=false;
                         stringInput("==> Enter the no Plate of Car >> ",tem);
                         for(int i=0;i<NUM_OF_CAR;i++){
                              if(carInfo[i].noPlate==tem){
                                   found=true;
                                   if(carInfo[i].status=="Rented"){
                                        cout << "\n\t>>__You cann't remove this car because this car on rent....\n";
                                        break;
                                   }
                                   else{
                                        carInfo[i].noPlate=" ";
                                        cout << "\n\n Work on your command....\n\n";
                                        Sleep(3000);
                                        remove("carInfo.txt");
                                        fstream DataWrite("carInfo.txt",ios::out);
                                        DataWrite << NUM_OF_CAR-1 << endl;
                                        carDataWrite(carInfo,NUM_OF_CAR,DataWrite);
                                        DataWrite.close();
                                        cout << "\n\n\t <<==  Car Remove Successfully !  ==>>\n";
                                        break;
                                   }
                              }
                         }
                         if(!found)
                         cout << "\t\t<-- " << tem << " is not found ! -->\n\t\t\tPLZ Renter.... \n";
                    }while(!found);
               }
               break;
               case '2':
               {
                    CarDetail tem;
                    bool platefound=true;
                    char stus;
                    do{
                         cout << "\n\t\t <-- Add New Car -->\n";
                         if(platefound){
                                   stringInput("==> Enter the Plate no of Car >> ",tem.noPlate);
                                   
                         }                           
                         platefound=false;
                         for(int i=0;i<NUM_OF_CAR;i++){
                              if(carInfo[i].noPlate==tem.noPlate)
                                   platefound=true;
                         }
                         if(platefound)
                              cout << "\n\n \t\t <<=== Car of this no_Plate is exists ===>>\n\t\t Plz enter another no_plate....\n\n";
                         else
                              break;
                    }while(true);
                    stringInput("==> Enter the name of Car >> ",tem.name);
                    stringInput("==> Enter the model of Car >> ",tem.model);
                    cout << "==>Enter the Price/ Day >> ";
                    cin >> tem.price;
                    cout << "Working on your command....";
                    fstream DataWrite("carInfo.txt",ios::out);
                    DataWrite << NUM_OF_CAR+1 <<endl;
                    carDataWrite(carInfo,NUM_OF_CAR,DataWrite);
                    DataWrite << endl << tem.noPlate << endl << tem.name << endl << tem.model << endl << tem.status ;
                    DataWrite << endl << tem.rentCusId << endl << tem.date << endl << tem.rentedDay << endl << tem.numRented ;
                    DataWrite << endl << tem.price<< endl;
                    DataWrite.close();
                    cout << "\n\n\t <<==  Car Add Successfully !  ==>>\n";
               }
                    break;
               default: 
                    break;
          }
          delete [] carInfo;//relase Memory
          carInfo=nullptr;
          cout << "\n==>> Yo want to add / Remove another car  | If yes enter 'y' or enter any key for exit : ";
          choice=getche();
     }while(choice=='y'|| choice=='Y');
}
//Report all thins for admin....
void reportGenerate(){
     displayHeader("\t___>>> rEpOrT sYsTeM <<<____ ");
     char choice;
     cout << "\n\n ************************************************************\n" 
                    << " *                                                         **\n"
                    << " 1. View \' Report of Customer \'...                         **\n"
                    << " 2. View \' Report of Car\'...                               **\n"
                    << " 3. View \' Invidiual Car Report\'...                        **\n"
                    << " 4. For go Back ...                                        **\n"
                    << " *                                                         **\n"
                    << " ************************************************************\n\n";
     charValidate(choice,"==> Enter Choice here... >>>",'1','4');
     int NUM_OF_CAR=0;
     fstream Fetch("carInfo.txt",ios::in);
     fileChecking(Fetch);
     Fetch >> NUM_OF_CAR;
     Fetch.ignore();
     CarDetail *carInfo=new CarDetail[NUM_OF_CAR];
     carDataFetch(carInfo,NUM_OF_CAR,Fetch);
     Fetch.close();
     switch (choice)
     {
     case '1':{
          cout << "\n\n\t___>>  \' Report of Customer's \' <<___\n";
          string cusId;
          stringInput("==>>Enter the customer Id :",cusId);
          cusReport(cusId);
     }
          break;
     case '2':{
          cout << "\n\n\t___>>\' cAr InVenTorY rEpOrT \' <<___\n";
          
          cout << "\n\n\t_____>>> InVenTorY rEpOrT <<<_____\n\n";
          cout << "\n___________________________________________________________________________________________________\n";
          cout << setw(15) << "No_plate" << setw(20) << "Name" << setw(15) << "Model" << setw(15) << "Status" <<setw(15) << "rental Times"<< setw(15) << "Price" << endl;
          for(int i=0;i<NUM_OF_CAR;i++){
               cout << "\n_____________________________________________________________________________________________________\n";
               cout << setw(15) << carInfo[i].noPlate << setw(20) << carInfo[i].name<< setw(15) << carInfo[i].model;
               cout << setw(15) << carInfo[i].status << setw(15) << carInfo[i].numRented << setw(15) << carInfo[i].price << endl;
          } 
          cout << "\n____________________________________________________________________________________________________\n";
     }
       break;
     case '3':
     {
          cout << "\n\n\t___>>\' cAr InVenTorY rEpOrT \' <<___\n";
          string tempNoPlate;
          bool found;
          do{
               found=false;
           stringInput("==> Enter the no Plate of Car >> ",tempNoPlate);
           for(int i=0;i<NUM_OF_CAR;i++){
               if(carInfo[i].noPlate==tempNoPlate){
                    found=true;
                    cout <<"\n\t\t>>____Status Report___<<\n\n ";
                    cout << "::No_plate of Car: " << carInfo[i].noPlate << endl;
                    cout << "\n::Status : " << carInfo[i].status;
                    if(carInfo[i].rentedDay!=0){
                        cout << "\n::Issue Date of car rent : " << carInfo[i].date;

                    }
                    cout << "\n::Day for Rented : " << carInfo[i].rentedDay;
                    cout << "\n::Num for rented : " << carInfo[i].numRented;
                    cout <<"\n\t\t>>___Maintenance Report___<<\n\n ";
                    cout << "\n::Num for Maintenance car : " << carInfo[i].numRented+1;
                    if(carInfo[i].status=="Rented"){
                         cout << "\nUp comming maintenance task after returning car from rent...";
                    }
                    else{
                         cout << "\nNo Upcoming Maintenance task ....\n";
                    }
                   break;//break for loop in the case of match data...
               }
           }
           if(!found){
               cout << "\n\n\t__Car not found of this No Plate....\n";
           }
         }while(!found);
     }

        break;
     default:
          break;
     }
     delete[] carInfo;//Release Memmory
     carInfo=nullptr;
     cout << "\nEnter any key to continue : ";
     getche();
}
//.........End of Admin Block....//