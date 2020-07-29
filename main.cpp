#include<bits/stdc++.h>
#include<ctime>
using namespace std;

class Metadata
{
private:
    static int room_no_size;
    static int no_of_buildings;
    static int student_id_size;
    static int staff_id_size;
    //virtual void abstracter() = 0;//so that Metadata remains an abstract class
protected:
    bool set_room_no_size(int val)
    {
        if(val>=0 && val<8 )
        {
            room_no_size = val;
            return true;
        }
        else
        {
            cout<<"Invalid room number size"<<endl;
            cout<<"Value has to be positive and lesser than 8"<<endl;
            return false;
        }
    }
    bool set_no_of_buildings(int val)
    {
        if(val>=0 && val<1000)
        {
            no_of_buildings = val;
            return true;
        }
        else
        {
            cout<<"Invalid number of buildings"<<endl;
            cout<<"Value has to be positive and lesser than 1000"<<endl;
            return false;
        }
    }
    bool set_student_id_size(int val)
    {
        if(val>=0 && val<21)
        {
            student_id_size = val;
            return true;
        }
        else
        {
            cout<<"Invalid size for student ID"<<endl;
            cout<<"Value has to be positive and lesser than 21"<<endl;
            return false;
        }
    }
    bool set_staff_id_size(int val)
    {
        if(val>=0 && val<21)
        {
            staff_id_size = val;
            return true;
        }
        else
        {
            cout<<"Invalid size for staff ID"<<endl;
            cout<<"Value has to be positive and lesser than 21"<<endl;
            return false;
        }
    }
public:
    static int get_room_no_size(void)
    {
        return room_no_size;
    }
    static int get_no_of_buildings(void)
    {
        return no_of_buildings;
    }
    static int get_student_id_size(void)
    {
        return student_id_size;
    }
    static int get_staff_id_size(void)
    {
        return staff_id_size;
    }
    virtual void abstracter() = 0;
};
int Metadata::room_no_size = 3;
int Metadata::no_of_buildings = 3;
int Metadata::student_id_size = 9;
int Metadata::staff_id_size = 8;

class Physical_location
{
protected:
    string building_no;
    string room_no;
    void set_building_no_without_check(string val)
    {
        building_no = val;
    }
    void set_room_no_without_check (string val)
    {
        room_no = val;
    }
public:
    Physical_location()
    {
        set_building_no_without_check("");
        set_room_no_without_check("");
    }
    Physical_location(string buildval, string roomval)
    {
        set_building_no(buildval);
        set_room_no(roomval);
    }
    bool check_room_no(string val)
    {
        if(val.length()!=Metadata::get_room_no_size())
        {
            cout<<"Invalid room number"<<endl;
            cout<<"Size must be "<<Metadata::get_room_no_size()<<" characters exactly"<<endl;
            return false;
        }
        else
        {
            for(int i=0;i<val.size();i++)
            {
                if(!isdigit(val[i]))
                {
                    cout<<"Character number:"<<i+1<<" is not a digit"<<endl;
                    return false;
                }
            }
            return true;
        }
    }
    bool check_build_no(string s)
    {
        if(s.size()==1)
        {
            char c = s[0];
            int n = static_cast<int>(c);
            if(n>0 && n<= Metadata::get_no_of_buildings())
                return true;
        }
        return false;
    }
    bool set_building_no(string val)
    {
        if(check_build_no(val))
        {
            building_no = val;
            return true;
        }
        else
        {
            set_building_no_without_check("");
            return false;
        }
    }
    bool set_room_no(string val)
    {
        if(check_room_no(val))
        {
            room_no = val;
            return true;
        }
        else
        {
            set_room_no_without_check("");
            return false;
        }
    }
    string get_building_no(void)
    {
        return building_no;
    }
    string get_room_no(void)
    {
        return room_no;
    }
    string get_physical_location(void)
    {
        string s = building_no + "-" + room_no;
        return s;
    }
};

class Time
{
protected:
    int hour;
    int minute;
    //These two functions shouldn't be accessed by anyone outside this class to avoid storing undesirable values
    void set_hour_without_check(int val)
    {
        hour = val;
    }
    void set_minute_without_check(int val)
    {
        minute = val;
    }
public:
    //Time is stored in 24 hour format to simplify calculations
    //Input is taken in 12 hour format
    Time()
    {
        set_hour_without_check(0);
        set_minute_without_check(0);
    }
    Time(int val_hour, int val_minute, string format)
    {
        set_hour(val_hour);
        set_minute(val_minute);
        set_format(format);
    }
    bool set_hour(int val)
    {
        //sets the hour along with checking the validity
        if(val>0 && val<=12)
        {
            set_hour_without_check(val);
            return true;
        }
        else
        {
            cout<<"Invalid hour input for time"<<endl;
            set_hour_without_check(0);
            return false;
        }
    }
    bool set_minute(int val)
    {
        //sets the minute along with checking the validity
        if(val>=0 && val<60)
        {
            set_minute_without_check(val);
            return true;
        }
        else
        {
            cout<<"Invalid minute input for time"<<endl;
            set_minute_without_check(0);
            return false;
        }
    }
    bool set_format(string val)
    {
        transform(val.begin(), val.end(), val.begin(), ::toupper); //In case of lower case input
        if(val == "AM"||val=="PM")
        {
            if(val == "PM")
            {
                set_hour(get_hour()+12);
            }
            else
            {
                set_hour(get_hour());
            }
            return true;
        }
        else
        {
            cout<<"Invalid time format"<<endl;
            cout<<"Please enter AM or PM only"<<endl;
            return false;
        }
    }
    int get_hour()
    {
        return hour;
    }
    int get_minute()
    {
        return minute;
    }
    Time operator+(Time val)
    {
        Time temp;
        int extra_hour = 0;
        int total_min = this->get_minute()+val.get_minute();
        int total_hour = this->get_hour()+val.get_hour();
        if(total_min>=60)
        {
            temp.set_minute_without_check(total_min-60);
            extra_hour++;
        }
        else
        {
            set_minute_without_check(total_min);
        }
        if(total_hour + extra_hour>=24)
        {
            temp.set_hour_without_check(total_hour + extra_hour - 24);
        }
        else
            temp.set_hour_without_check(total_hour + extra_hour);
        return temp;
    };
    Time convert_duration(int min)
    {
        //returns a Time object for the duration in the minutes
        Time temp;
        temp.set_minute_without_check(min%60);
        temp.set_hour_without_check(min/60);
        return temp;
    }
    string get_time(void)
    {
        // returns a time string in 12-hour format
        string s;
        if(hour>12)
        {
            s+=to_string(hour-12);
        }
        else if(hour==0)
        {
            s+=to_string(hour+12);
        }
        else
        {
            s+=to_string(hour);
        }
        s+=":";
        s+=to_string(minute);
        s+=" ";
        if(hour>=12)
        {
            s+="PM";
        }
        else
        {
            s+="AM";
        }
        return s;
    }
};

class Date
{
protected:
    int day;
    int month;
    int year;
public:
    Date(void)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        set_day(ltm->tm_mday);
        set_month(1 + ltm->tm_mon);
        set_year(1900 + ltm->tm_year);
    }
    Date(int day_val, int month_val, int year_val)
    {
        set_day(day_val);
        set_month(month_val);
        set_year(year_val);
    }
    bool set_day(int val)
    {
        if(val<32 && val>0) {
            day = val;
            return true;
        }
        else
        {
            cout<<"Invalid day for date"<<endl;
            time_t now = time(0);
            tm *ltm = localtime(&now);
            set_day(ltm->tm_mday);
            cout<<"Value set to current day by default"<<endl;
            return false;
        }
    }
    bool set_month(int val)
    {
        if(val<13 && val>0)
        {
            month = val;
            return true;
        }
        else
        {
            cout<<"Invalid month for date"<<endl;
            time_t now = time(0);
            tm *ltm = localtime(&now);
            set_month(1 + ltm->tm_mon);
            cout<<"Value set to current month by default"<<endl;
            return false;
        }
    }
    bool set_year(int val)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        if(val>=1900 + ltm->tm_year)
        {
            year = val;
            return true;
        }
        else
        {
            cout<<"Invalid year for date"<<endl;
            set_year(1900 + ltm->tm_year);
            cout<<"Value set to current year by default"<<endl;
            return false;
        }
    }
    int get_day()
    {
        return day;
    }
    int get_month()
    {
        return month;
    }
    int get_year()
    {
        return year;
    }
    string get_date() //returns date for displaying or file output
    {
        string s;
        s += to_string(day);
        s += "-";
        s += to_string(month);
        s += "-";
        s += to_string(year);
        return s;
    }
};



class User
{
protected:
    string name;
    string password;
    bool check_password(string val)
    {
        if(val.length()>32)
        {
            cout<<"Password for is too long"<<endl;
            cout<<"User password must not contain more than 32 characters"<<endl;
            return false;
        }
        else if(val.length()<6)
        {
            cout<<"Password is too short"<<endl;
            cout<<"User password must contain 6 characters at least"<<endl;
            return false;
        }
        else
        {
            //check password complexity
            //must contain at least one character and one digit or something like that
            return true;
        }
    }
public:
    User()
    {
        set_name("");
        set_password("password123");
    }
    User(string nameval, string passval)
    {
        set_name(nameval);
        set_password(passval);
    }
    void set_name(string value)
    {
        name = value;
    }
    bool set_password(string val)
    {
        if(check_password(val))
        {
            password = val;
            return true;
        }
        return false;
    }
    string get_name(void)
    {
        return name;
    }
    string get_password(void)
    {
        return password;
    }
    virtual bool login() = 0;
	void add_record()//parameter list phy_loc, date, time, dur, record_array
	//Friend class Record
    {
		//The booking functions appends a record at the record file while information of rooms and records are stored
		//Before booking a record at a particular physical_location make sure that the entries don't overlap
		//
		//Search the whole record array to see that the records don't overlap
		//If it doesn't overlap... add the record and update the file(record.txt)
		//If it overlaps show an error message
		//to make it easier for you to work with these data I made some functions in date
		//and time for easier calculations and comparison
		//call those functions when necessary
	}
	void delete_record()
	{
		//sem thing, you understand, right?
	}
	void show_layout(void)
	{
		//Room and record are two seperated entities
		//They have one to many relationship
		//Physical_location is the foreign key in records
		//There will be two seperate files for rooms and records
		//
		//basically a display function which shows a list of all buildings (reads input from files)
		//you can then select a particular building and it will show all the rooms in that building
		//in our program, physical location is a combination of building number and room number
		//hence, if you want you can show the list of building no + room number at a time, provided that the list isn't too long
		//Remember to show them SERIALLY
		//you can then select a room and then it will show all the records in that room
		//you should make at least 2 seperate functions for this, one to show physical_locations
		//and another one to show all the records in a particular physical location
		//the second function will be like this
		//void display_records(Physical_location phy_loc_val)
	}
    //find classroom/search
	//{
	//	returns a physical_location after searching
	//}
};

class Student:public User
{
protected:
    string student_id;
    bool cr; //if CR or not
    void set_student_id_without_check(string val)
    {
        student_id = val;
    }
public:
    Student()
    {
        set_student_id_without_check("");
        set_cr(false);
    }
    Student(string val_name, string val_pass, string val_std_id, bool val_cr):User(val_name,val_pass)
    {
        set_student_id(val_std_id);
        set_cr(val_cr);
    }
    static bool check_student_id(string val)
    {
        if(val.length()!=Metadata::get_student_id_size())
        {
            cout<<"Invalid student ID"<<endl;
            cout<<"Size must be "<<Metadata::get_student_id_size()<<" characters exactly"<<endl;
            return false;
        }
        else
        {
            for(int i=0;i<val.size();i++)
            {
                if(!isdigit(val[i]))
                {
                    cout<<"Character number:"<<i+1<<" is not a digit"<<endl;
                    return false;
                }
            }
            return true;
        }
    }
    bool set_student_id(string val)
    {
        if(check_student_id(val))
        {
            set_student_id_without_check(val);
            return true;
        }
        else
        {
            set_student_id_without_check("");
            return false;
        }

    }
    void set_cr(bool val)
    {
        cr = val;
    }
    string get_student_id(void)
    {
        return student_id;
    }
    bool get_cr(void)
    {
        return  cr;
    }
    bool login(string id_val, string pass_val)
    {
        if(id_val == get_student_id() && pass_val == get_password())
        {
            return true;
        }
        else return false;
    }
};

class Staff:public User
{
protected:
    string staff_id;
    void set_staff_id_without_check(string val)
    {
        staff_id = val;
    }
public:
    Staff()
    {
        set_staff_id_without_check("");
    }
    Staff(string val_name, string val_pass, string val_staff_id):User(val_name,val_pass)
    {
        set_staff_id(val_staff_id);
    }
    static bool check_staff_id(string val)
    {
        if(val.length()!=Metadata::get_staff_id_size())
        {
            cout<<"Invalid staff ID"<<endl;
            cout<<"Size must be "<<Metadata::get_staff_id_size()<<" characters exactly"<<endl;
            return false;
        }
        else
        {
            for(int i=0;i<val.size();i++)
            {
                if(!isdigit(val[i]))
                {
                    cout<<"Character number:"<<i+1<<" is not a digit"<<endl;
                    return false;
                }
            }
            return true;
        }
    }
    bool set_staff_id(string val)
    {
        if(check_staff_id(val))
        {
            set_staff_id_without_check(val);
            return true;
        }
        else
        {
            set_staff_id_without_check("");
            return false;
        }
    }
    string get_staff_id(void)
    {
        return staff_id;
    }
    bool login(string id_val, string pass_val)
    {
        if(id_val == get_staff_id() && pass_val == get_password())
        {
            return true;
        }
        else return false;
    }
};

class Admin:public Metadata
{
private:
    string username;
    string password;
    string contact_no;
    string email_address;
    bool check_password(string val)
    {
        if(val.length()>32)
        {
            cout<<"Password for "<<get_username()<<" is too long"<<endl;
            cout<<"Admin password must not contain more than 32 characters"<<endl;
            return false;
        }
        else if(val.length()<8)
        {
            cout<<"Password for "<<get_username()<<" is too short"<<endl;
            cout<<"Admin password must contain 8 characters at least"<<endl;
            return false;
        }
        else
        {
            //check password complexity
            //must contain at least one character and one digit or something like that
            //admin password must be stronger than user password; make sure of that
            return true;
        }
    }
    bool check_contact_no_validity(string val)
    {
        if(val.size()==11)
        {
            for(int i=0;i<val.size();i++)
            {
                if(!isdigit(val[i]))
                {
                    return false;
                }
            }
            return true;
        }
        else
            return false;
    }
public:
    Admin()
    {
        set_username("system");
        set_password("system123");
    }
    Admin(string user_val, string pass_val, string cont_val,string email_val)
    {
        set_username(user_val);
        set_password(pass_val);
        set_contact_no(cont_val);
        set_email_address(email_val);
    }
    void set_username(string val)
    {
        if(val.length()>32)
        {
            cout<<val<<" is an invalid username"<<endl;
            cout<<"Username must not contain more than 32 characters"<<endl;

        }
        else if(val.length()>=6)
        {
            username = val;
            //return true;
        }
        else
        {
            cout<<val<<" is an invalid username"<<endl;
            cout<<"Username must contain 6 characters at least"<<endl;
           //return false;
        }
    }
    void set_password(string val)
    {
        if(check_password(val))
        {
           // set_password(val);
           password=val;
           // return true;
        }
       // return false;
    }
    void set_contact_no(string val)
    {
        if(check_contact_no_validity(val))
        {
            contact_no = val;
           // return true;
        }
        else
        {
            cout << "Invalid contact number" << endl;
            cout << "Make sure you DON'T write the country code before the number" << endl;
           // return false;
        }
    }
    void set_email_address(string val)
    {
        email_address = val;
    }
    string get_username(void)
    {
        return username;
    }
    string get_password(void)
    {
        return password;
    }
    string get_email_address()
    {
        return email_address;//ADDED LATER
    }
    string get_contact_no()
    {
        return contact_no;//ADDED LATER
    }
    bool login(string user_val, string pass_val)
    {
        if(user_val == get_username() && pass_val == get_password())
        {
            return true;
        }
        else
        {
            cout<<"Wrong username/password"<<endl;
            return false;
        }
    }
    //In main function we create admin with username and password
    //Admin can read and load classrooms (written)
    //Admin can read and load user_list (written)
    //Admin can check log file (written)
    //Admin can edit metadata (Done)

	create_room_file(string path)
	{
		//the purpose of this function is to create our room file
		//takes a file path as input and then reads data from that file (prefarably csv file)
		//the file is the input for the room file stored in our system
		//checks the validity of each entry of the file
		//then each entry is appended in the room.txt file of our program
		//preferable to append serially for easier access of other functions and readability
		//there are multiple ways to take input serially
		//firstly we can store all the validated data in the memory
		//then we write the whole array in the file
	}
	void add_room()//paramenter list for rooms
	{
		//checks the room doesn't prexist. Physical_location is primary key, so check that
		//for this we can pass a room[] array to this function
		//then we search that array for that particular room
		//finally we update the changed_array using create_room_file

		//adds a room in the room.txt file
	}
//	Student[] create_student_file(string path)
	//{
		//same thing we did for rooms but for student users
		//creates student.txt file
//	}
	void add_student()
	{
		//checks the student doesn't prexist in the student.txt file
		//appends a new student_user in the room.txt file
	}
//	Staff[] create_staff_file(string path)
	//{
		//same thing we did for rooms but for staff users
//	}
	void add_staff(){}
	void add_admin(){}
	//for the remove functions we pass an array of rooms. Then we remove from array of rooms
	//and then upload that array in the file
	remove_student();
	remove_staff();
	remove_admin();
	remove_room();
	void read_log(void)
	{
		//shows the log_file on the screen
		//Present the data in a user friendly way (optional)
	}
	void abstracter()
	{
	    //ADDED LATER;

	    cout<<get_username()<<endl;
	    cout<<get_password()<<endl;
	    cout<<get_email_address()<<endl;
	    cout<<get_contact_no()<<endl;

	}

};


class Record:public Physical_location, public Time, public Date
{
protected:
    int duration;
    string user_ID;
    void set_user_id_without_check(string val)
    {
        user_ID = val;
    }
public:
    Record(void)
    {
        duration = 0;
        set_user_id_without_check("");
    }
    Record(string user_val, string build_val, string room_val, int hour_val, int min_val, string form_val,
    int dur_val, int day_val, int mon_val, int year_val)
    :Physical_location(build_val, room_val),Time(hour_val, min_val, form_val),
    Date(day_val,mon_val,year_val)
    {
        set_duration(dur_val);
        set_user_ID(user_val);
    }
    bool set_duration(int value) //In minutes
    {
        if(duration<=360 && duration>0) {
            duration = value;
            return true;
        }
        else if(duration>360)
        {
            cout<<"Invalid time duration: Can not book records longer than 6 hours"<<endl;
            return false;
        }
        else
        {
            cout<<"Invalid time duration: Must be a positive integer"<<endl;
            return false;
        }
    }
    bool set_user_ID(string val)
    {
        if(Student::check_student_id(val) || Staff::check_staff_id(val))
        {
            set_user_id_without_check(val);
            return true;
        }
        else
        {
            set_user_id_without_check("0");
            return false;
        }
    }
    int get_duration(void)
    {
        return duration;
    }
    string get_user_ID(void)
    {
        return user_ID;
    }
};

class Equipments
{
protected:
    bool AC;
    int boards;
    bool projector;
public:
    Equipments()
    {
        set_ac(0);
        set_boards(0);
        set_projector(0);
    }
    Equipments(bool ac_val, int boards_val, bool pro_val)
    {
        set_ac(ac_val);
        set_boards(boards_val);
        set_projector(pro_val);
    }
    void set_ac(bool val)
    {
        AC = val;
    }
    bool set_boards(int val)
    {
        if(val<0 || val>=10)
        {
            cout<<"Invalid no. of boards"<<endl;
            return false;
        }
        else
        {
            boards = val;
            return true;
        }
    }
    void set_projector(bool val)
    {
        projector = val;
    }
    bool get_ac()
    {
        return AC;
    }
    int get_boards()
    {
        return boards;
    }
    bool get_projector()
    {
        return projector;
    }
};

class Room: public Physical_location, public Equipments
{
protected:
    int capacity;

public:
    Room()
    {
        set_capacity(0);
    }
    Room(string build_val, string room_val, bool ac_val, int board_val, bool proj_val, int cap_val):
    Physical_location(build_val, room_val),Equipments(ac_val, board_val, proj_val)
    {
        set_capacity(cap_val);
    }
    bool set_capacity(int val)
    {
        if(val<0)
        {
            cout<<"Invalid capacity"<<endl;
            return false;
        }
        else
        {
            capacity = val;
            return true;
        }
    }
    int get_capacity(void)
    {
        return capacity;
    }
};

class System_intializer
{
	//Add a function which adds an empty Admin object if the Admin.txt file doesn't exist
	//It can show a pop-up like first time use
	//New default admin created. Username: system. Password system123
	//i.e. for first time use only
public:

	static Admin** read_admin()
	{
	     Admin* f_list[100];
	     fstream fin;
	     int counti=0;

    fin.open("Admin.csv", ios::in);
    string line,word;;
    string username,password,contact_no,email_address;

    while (fin.good()) {
           // cout<<"nana"<<endl;
        getline(fin, line);
        stringstream s(line);
        int second_count=0;

        while (getline(s, word, ',')) {
            if(second_count==0)
            {
                   username=word;
                second_count++;
            }
            else if(second_count==1)
            {
                    password=word;
                second_count++;
            }
            else if(second_count==2)
            {
                    contact_no=word;
                second_count++;
            }
            else if(second_count==3)
            {
                    email_address=word;
                second_count++;
            }


        }
        //cout<<username<<" "<<password<<" "<<contact_no<<" "<<email_address<<endl;
        f_list[counti]=new Admin(username,password,contact_no,email_address) ;
        //f_list[counti]->abstracter();
        counti++;

    }


      
        return f_list;



	}

	//static Student[] read_student();
	static * read_staff();
	static * read_record();
};

//create a log class
//{
	//log class will contain all functions that will append the log file whenever anything is done in the program
	//all the functions should be accessed by User and Admin classes
//}

int main()
{

    Admin **ad;
    ad=System_intializer::read_admin();




	//all the files (room.txt, student.txt, staff.txt, admin.txt, records.txt
	//will be read and stored in memory (class arrays) in the beginning of the function
}
