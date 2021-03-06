#include "Place.hpp"

Place::Place(){
    this->radius = 0.0f;
    this->longitude = 0.0f;
    this->latitude = 0.0f;
    this->place = "NULL";
    this->nextPlace = NULL;
}

Place::Place(std::string place){
    
    std::stringstream ss;
    int i;
    for(i = 0; place[i] != ','; i++){
        ss << place[i];
    }
    this->latitude = atof(ss.str().c_str());
    i++;
    
    ss.str(std::string());
    for(i = i; place[i] != ','; i++){
        ss << place[i];
    }
    this->longitude = atof(ss.str().c_str());
    i++;
    
    ss.str(std::string());
    for(i = i; place[i] != '\0'; i++){
        ss << place[i];
    }
    this->radius = atof(ss.str().c_str());    
    this->nextPlace = new Place();
}

Place::Place(char *GPSPosition, float radius = 0.0003){
    this->radius = radius;
    
    // Make a copy before we fuck it up
    char cpy[strlen(GPSPosition)];
    for(int i=0; i < strlen(GPSPosition); i++){
        cpy[i] = GPSPosition[i];
    }
    cpy[strlen(GPSPosition)] = '\0';
    
    char* p = strtok (cpy,",");
    this->latitude = stripAndConvert(p); // North/South

    p = strtok(NULL, ",");
    this->longitude = stripAndConvert(p); // East/West
    
    std::stringstream ss;
    ss << "\"" << this->latitude << "," << this->longitude << "," << this->radius << "\"";
    this->place = ss.str();
    
    this->nextPlace = new Place();
    
}

void Place::setPlace(char *GPSPosition, float radius = 0.0003){
    this->radius = radius;

    // Make a copy before we fuck it up
    char cpy[strlen(GPSPosition)];
    for(int i=0; i < strlen(GPSPosition); i++){
        cpy[i] = GPSPosition[i];
    }
    cpy[strlen(GPSPosition)] = '\0';
    
    char* p = strtok (cpy,",");
    this->latitude = stripAndConvert(p); // North/South

    p = strtok(NULL, ",");
    this->longitude = stripAndConvert(p); // East/West
    
    std::stringstream ss;
    ss << "\"" << this->latitude << "," << this->longitude << "," << this->radius << "\"";
    this->place = ss.str();
    
    this->nextPlace = new Place();
}

void Place::setNext(Place *nextPlace){
    this->nextPlace = nextPlace;
}

Place* Place::next(){
    return this->nextPlace;
}

float Place::stripAndConvert(char *half){

    float dms[3] = {0.0f};
    int i = 0;
    int j = 0;
    int k = 0;
    char tmp[9];
    bool dot = false;

    //tmp is a string float
    float result = 0.0f;
    int len = 0;
    int dotpos = 0;
    // Finding the character whose
    // ASCII value fall under this
    // range
    
    // 3 loops, one for minutes, seconds, degrees
    while(j < 3){
        while( !((half[i] >= '0' && half[i] <= '9') || half[i] == '.') )
        {
            // Do nothing
            i++;
        }
        while((half[i] >= '0' && half[i] <= '9') || half[i] == '.')
        {
            tmp[k] = half[i];
            k++;
            i++;
        }
        tmp[k] = '\0';
        //tmp is a string float
        result = 0.0f;
        len = k;
        dotpos = 0;
        
        result = atof(tmp);
        
        dms[j] = result;
        j++;
        k = 0;
    }
    
    if(half[i+2] == 'W' || half[i+2] == 'S')
        return -(dms[0] + dms[1]/60.0 + dms[2]/3600.0);
    return (dms[0] + dms[1]/60.0 + dms[2]/3600.0);
}

float Place::getLongitude(){ return longitude; }

float Place::getLatitude(){ return latitude; }

float Place::getRadius(){ return radius;}

std::string Place::placeString(){ return place; } 
