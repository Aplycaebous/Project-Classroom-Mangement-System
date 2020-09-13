#include "Record.h"


Record::Record()
{
    duration = 0;
    user_ID = "";
}

Record::Record(string user_val, Physical_location phy_val, Time time_val,int dur_val, Date date_val):Physical_location(phy_val),Time(time_val),Date(date_val)
{
    if(!set_duration(dur_val)) duration = 0;
    if(!set_user_ID(user_val)) user_ID = "";
}

bool Record::set_duration(int value) //In minutes
{
    if(value<=360 && value>0) //can't book classes for longer than 6 hours
    {
        duration = value;
        return true;
    }
    else return false;
}

bool Record::set_user_ID(string val)
{
    if(Student::check_student_id(val) || Staff::check_staff_id(val))
    {
        user_ID = val;
        return true;
    }
    else return false;
}

int Record::get_duration(void)
{
    return duration;
}

string Record::get_user_ID(void)
{
    return user_ID;
}

Physical_location Record::get_phy_loc_obj(void)
{
    return Physical_location(this->get_building_no(),this->get_room_no());
}

Time Record::get_time_obj(void)
{
    return Time(this->get_hour(),this->get_minute());
}

Date Record::get_date_obj(void)
{
    return Date(this->get_day(),this->get_month(),this->get_year());
}

bool Record::operator == (Record record_val)
{
    if(this->get_date_obj() == record_val.get_date_obj() && this->get_time_obj() == record_val.get_time_obj()
       && this->get_phy_loc_obj() == record_val.get_phy_loc_obj())
    {
        if(this->get_duration()==record_val.get_duration() && this->get_user_ID() == record_val.get_user_ID())
            return true;
        else return false;
    }
    else return false;
}

static vector<Record *> list_user_records(string id, vector<Record*> rec_in)
{
    vector<Record*> rec_out;
    for(int i=0;i<rec_in.size();i++)
    {
        if(rec_in[i]->get_user_ID() == id)
        {
            rec_out.push_back(rec_in[i]);
        }
    }
    for (int i = 0; i < rec_out.size()-1; i++)
    {
        for (int j = 0; j < rec_out.size() - i - 1; j++)
        {
            if (rec_out[j]->get_physical_location() > rec_out[j + 1]->get_physical_location())
            {
                swap(rec_out[j], rec_out[j + 1]);
                if(rec_out[j]->get_date() > rec_out[j + 1]->get_date())
                {
                    swap(rec_out[j], rec_out[j + 1]);
                    if(rec_out[j]->get_time_24()>rec_out[j]->get_time_24())
                    {
                        swap(rec_out[j], rec_out[j + 1]);
                        if(rec_out[j]->get_duration()>rec_out[j]->get_duration())
                        {
                            swap(rec_out[j], rec_out[j + 1]);
                        }
                    }
                }

            }
        }
    }
    return rec_out;
}