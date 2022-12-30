#include <iostream>
#include <string>
#include <math.h>
#include <sstream>

using namespace std;

//propose a null object for each class

class Nutrient{
    public:
    Nutrient(string N, float amountperq, float q){
        name=N;
        amountPerQ=amountperq;
        Q=q;
    }
    Nutrient(){
        name="Null";
        amountPerQ=-1;
        Q=-1;
    }
    void set(string N, float amountperq, float q){
        name=N;
        amountPerQ=amountperq;
        Q=q;
    }
    float getVal(){
        return amountPerQ*Q;
    }
    string getName(){
        return name;
    }

    private:
    string name;
    float amountPerQ;
    float Q;
};

class Variable{
    public:
    Variable(string N, int D, int H, int S){
        name=N;
        day=D;
        hour=H;
        scale=S;
    }
    Variable(){
        name="Null";
        day=-1;
        hour=-1;
        scale=-1;
    }
    void set(string N, int D, int H, int S){
        name=N;
        day=D;
        hour=H;
        scale=S;
    }
    void set(int D, int H){
        day=D;
        hour=H;
    }
    string getName(){
        return name;
    }
    int getDay(){
        return day;
    }
    int getHour(){
        return hour;    
    }
    int getScale(){
        return scale;
    }

    private:
    string name;
    int day;
    int hour;
    int scale;

};

class Element{
    public:
    Element(int q){
        Nutrients= new Nutrient[20];
        nutrTail=-1;
        Q=q;
    }
    Element(){
        Nutrients= new Nutrient[20];
        nutrTail=-1;
        Q=-1;
    }
    void setAmount(int q){
        Q=q;
    }
    void addNutrient(string nutrname, float amountperq, float q){
        nutrTail++;
        Nutrients[nutrTail].set(nutrname, amountperq, q);
    }
    
    float getNutrientVal(string nutrName){
        for(int i=0;i<nutrTail+1;i++){
            if(Nutrients[i].getName()==nutrName){
                return Nutrients[i].getVal();
            }
        }
        cout<<"ERROR: Nutrient not found"<<endl;
    }

    private:
    Nutrient *Nutrients;
    float Q;
    int nutrTail; //index of last element in Nutrients, -1 if it's empty

};



class Meal{
    public:
    Meal(int D, int H){
        day=D;
        hour=H;
        Elems= new Element[20];
        elemTail=-1;
    }
    Meal(){
        day=-1;
        hour=-1;
        Elems= new Element[20];
        elemTail=-1;
    }
    void set(int D, int H){
        day=D;
        hour=H;
    }
    int getHour(){
        return hour;
    }
    void addElem(Element e){
        elemTail++;
        if(elemTail<20){
            Elems[elemTail]=e;
        }
        else{
            cout<<"ERROR: No space in Elem array"<<endl;
        }
    }
    float getNutrientVal(string nutrName){
        float nutrSum=0;
        for(int i=0;i<elemTail+1;i++){
            
            nutrSum+= Elems[i].getNutrientVal(nutrName);
            
        }
        return nutrSum;
    }
    Element *Elems;
    int elemTail; //index of last element in Elems, -1 if it's empty

    private:
    int day;
    int hour;
    

};

class Day{
    
    public:
    Day(){
        Meals = new Meal[24];
        Variables = new Variable[24];
        Outcomes = new Variable[24];
    }

    void setIndex(int index){
        dayIndex=index;
        for(int i=0; i<24; i++){
            Meals[i].set(index,i);
            Variables[i].set(index,i);
            Outcomes[i].set(index,i);
        }
    }
        
    

    void addMeal(Meal m){
        //adds meal to respective slot depending on time of the day
        //do array with 24 empty slots for each hour
        Meals[m.getHour()]=m;

    }

    void addVariable(Variable v){
        Variables[v.getHour()]=v;

    }

    void addOutcome(Variable o){
        Outcomes[o.getHour()]=o;

    }

    float* getNutrArr(string nutrname, float* nutrArr){
        float* nutrArr = new float[24];
        for(int i=0; i<24; i++){
            nutrArr[i]=Meals[i].getNutrientVal(nutrname);
        }
        return nutrArr;
    }

    int dayIndex;
    Meal *Meals;
    Variable *Variables;
    Variable *Outcomes;


};

string getMatlabArray(float **MajorArr, int MajorLen, int MinorLen){
    string matlabArr="[";

    for(int i=0; i<MajorLen; i++){
        float *MinorArr = MajorArr[i];
        for(int j=0; j<MinorLen; j++){
            matlabArr+=to_string(MinorArr[j]);
            matlabArr+=" ";
        }
    }
    matlabArr+="]";
    return matlabArr;
}


int main()
{
    Day *days = new Day[20];
    int len = 20;
    
    return 0;
}
