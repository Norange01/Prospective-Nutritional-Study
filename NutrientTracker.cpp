#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include <vector>

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
    Variable(string N, int H, int S){
        name=N;
        day=-1;
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
    Element(float q){
        Nutrients= new Nutrient[20];
        nutrTail=-1;
        Q=q;
    }
    Element(float q, string nutrnames[], float nutrvals[], int arrlen){
        Q=q;
        Nutrients= new Nutrient[20];
        nutrTail=-1;
        for(int i=0; i<arrlen; i++){
            Nutrients[i].set(nutrnames[i],nutrvals[i],Q);
            nutrTail++;
        }
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
    Meal(int H){
        day=-1;
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
    void addElem(Element e[], int arrlen){
        for(int i=0; i<arrlen; i++){
            addElem(e[i]);
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
        Variables = new vector<Variable>[24];
        Outcomes = new vector<Variable>[24];
        dayIndex=-1;
    }
    Day(int ind){
        Meals = new Meal[24];
        Variables = new vector<Variable>[24];
        Outcomes = new vector<Variable>[24];
        dayIndex=ind;
        setIndex(dayIndex);
    }

    void setIndex(int index){
        dayIndex=index;
        for(int i=0; i<24; i++){
            Meals[i].set(index,i);
            for(int j=0; j<Variables[i].size(); j++){
                Variables[i][j].set(index,i);
            }
            for(int j=0; j<Outcomes[i].size(); j++){
                Outcomes[i][j].set(index,i);
            }
        }
    }
        
    

    void addMeal(Meal m){
        //adds meal to respective slot depending on time of the day
        //do array with 24 empty slots for each hour
        int h= m.getHour();
        m.set(dayIndex,h);
        Meals[h]=m;

    }

    void addMeal(Element e[], int arrlen, int h){
        Meals[h].set(dayIndex,h);
        Meals[h].addElem(e,arrlen);
    }

    void addMeal(Element e, int h){
        Meals[h].set(dayIndex,h);
        Meals[h].addElem(e);
        //cout<<e.getNutrientVal("weight")<<endl;
    }

    void addVariable(Variable v){
        int h=v.getHour();
        v.set(dayIndex,h);
        Variables[h].push_back(v);

    }

    void addVariable(string name, int scale, int h){
        for(int i=0; i<Variables[h].size();i++){
            if(Variables[h][i].getName()==name){
                Variables[h][i].set(name,dayIndex,h,scale);
            }
        }
        
    }

    void addVariable(string name, int scale){
        for(int h=0; h<24; h++){
            for(int i=0; i<Variables[h].size();i++){
                Variables[h][i].set(name,dayIndex,h,scale);
            }           
        }
    }

    void addOutcome(Variable o){
        int h=o.getHour();
        o.set(dayIndex,h);
        Outcomes[h].push_back(o);

    }

    void addOutcome(string name, int scale, int h){
        for(int i=0; i<Outcomes[h].size();i++){
            if(Outcomes[h][i].getName()==name){
                Outcomes[h][i].set(name,dayIndex,h,scale);
            }
        }
    }

    void addOutcome(string name, int scale, int h, int duration){
        for(int i=0; i<duration; i++){
            for(int j=0; j<Outcomes[h+i].size();j++){
                Outcomes[h+i][j].set(name,dayIndex,h,scale);
            }
        }
    }

    float* getNutrArr(string nutrname){
        float* nutrArr = new float[24];
        //initialize to zero
        for(int i=0; i<24; i++){
            nutrArr[i]=0;
        }
        //fill with right values
        for(int i=0; i<24; i++){
            nutrArr[i]=Meals[i].getNutrientVal(nutrname);
        }
        return nutrArr;
    }

    int* getVarArr(string varname){
        int* varArr = new int[24];
        //initialize to zero
        for(int i=0; i<24; i++){
            varArr[i]=0;
        }
        //fill with right values
        for(int i=0; i<24; i++){
            for(int j=0; j<Variables[i].size();j++){
                if(Variables[i][j].getName()==varname){
                    varArr[i]=Variables[i][j].getScale();
                }
                
            }
            
        }
        return varArr;
    }

    int* getOutcomeArr(string outname){
        int* outArr = new int[24];
        //initialize to zero
        for(int i=0; i<24; i++){
            outArr[i]=0;
        }
        //fill with right values
        for(int i=0; i<24; i++){
            for(int j=0; j<Outcomes[i].size();j++){
                if(Outcomes[i][j].getName()==outname){
                    outArr[i]=Outcomes[i][j].getScale();
                }
            }
        }
        return outArr;
    }

    int dayIndex;
    Meal *Meals;
    vector<Variable> *Variables;
    vector<Variable> *Outcomes;


};

string getMatlabArray(float Arr[], int len){
    string matlabArr="[";

    for(int i=0; i<len; i++){   
        matlabArr+=to_string(Arr[i]);
        if(i<len-1){
            matlabArr+=" ";
        }
    }
    matlabArr+="]";
    return matlabArr;
}

string getMatlabArray(int Arr[], int len){
    string matlabArr="[";

    for(int i=0; i<len; i++){   
        matlabArr+=to_string(Arr[i]);
        if(i<len-1){
            matlabArr+=" ";
        }
    }
    matlabArr+="]";
    return matlabArr;
}

float *addUpArrays(float* arr1, float* arr2, int len){
    float* arr3 = new float[len];
    for(int i=0; i<len; i++){
        arr3[i]=arr1[i]+arr2[i];
    }
    return arr3;
}

int *addUpArrays(int* arr1, int* arr2, int len){
    int* arr3 = new int[len];
    for(int i=0; i<len; i++){
        arr3[i]=arr1[i]+arr2[i];
    }
    return arr3;
}

float *stitchArr(float* arr1, int arr1Len, float* arr2, int arr2Len){
    int newLen=arr1Len+arr2Len;
    float *newArr = new float[newLen];
    int k=0;

    for(int i=0; i<arr1Len; i++){
        newArr[k]=arr1[i];
        k++;
    }
    for(int j=0; j<arr2Len; j++){
        newArr[k]=arr2[j];
        k++;
    }
    return newArr;
}

int *stitchArr(int* arr1, int arr1Len, int* arr2, int arr2Len){
    int newLen=arr1Len+arr2Len;
    int *newArr = new int[newLen];
    int k=0;

    for(int i=0; i<arr1Len; i++){
        newArr[k]=arr1[i];
        k++;
    }
    for(int j=0; j<arr2Len; j++){
        newArr[k]=arr2[j];
        k++;
    }
    return newArr;
}

string *stitchArr(string* arr1, int arr1Len, string* arr2, int arr2Len){
    int newLen=arr1Len+arr2Len;
    string *newArr = new string[newLen];
    int k=0;

    for(int i=0; i<arr1Len; i++){
        newArr[k]=arr1[i];
        k++;
    }
    for(int j=0; j<arr2Len; j++){
        newArr[k]=arr2[j];
        k++;
    }
    return newArr;
}

int *getCombinedVarArr(string varName, Day days[], int len){
    int *varArr = new int[len*24];

    for(int i=0; i<len; i++){
        int* dayVarArr = days[i].getVarArr(varName);
        for(int j=0; j<24; j++){
            varArr[(i*24)+j]=dayVarArr[j];
        }

    }
    return varArr;

}

int *getCombinedOutcomeArr(string outName, Day days[], int len){
    int *outArr = new int[len*24];

    for(int i=0; i<len; i++){
        int* dayOutArr = days[i].getOutcomeArr(outName);
        for(int j=0; j<24; j++){
            outArr[(i*24)+j]=dayOutArr[j];
        }

    }
    return outArr;

}


int main()
{
    
    int len = 30;
    Day *days = new Day[len];
    for(int i=0; i<len; i++){
        days[i].setIndex(i);
    }

    //sleep quality
    days[0].addVariable("sleepQuality",6);
    days[1].addVariable("sleepQuality",3);
    days[2].addVariable("sleepQuality",3);
    days[3].addVariable("sleepQuality",6);
    days[4].addVariable("sleepQuality",6);
    days[5].addVariable("sleepQuality",8);
    days[6].addVariable("sleepQuality",8);
    days[7].addVariable("sleepQuality",8);
    days[8].addVariable("sleepQuality",6);
    days[9].addVariable("sleepQuality",8);
    days[10].addVariable("sleepQuality",8);
    days[11].addVariable("sleepQuality",6);
    days[12].addVariable("sleepQuality",8);
    days[13].addVariable("sleepQuality",6);
    days[14].addVariable("sleepQuality",10);
    days[15].addVariable("sleepQuality",10);
    days[16].addVariable("sleepQuality",10);
    days[17].addVariable("sleepQuality",10);

    //wake up time
    days[0].addVariable("wakeUpTime",11);
    days[1].addVariable("wakeUpTime",11);
    days[2].addVariable("wakeUpTime",9);
    days[3].addVariable("wakeUpTime",11);
    days[4].addVariable("wakeUpTime",11);
    days[5].addVariable("wakeUpTime",11);
    days[6].addVariable("wakeUpTime",11);
    days[7].addVariable("wakeUpTime",11);
    days[8].addVariable("wakeUpTime",10);
    days[9].addVariable("wakeUpTime",11);
    days[10].addVariable("wakeUpTime",13);
    days[11].addVariable("wakeUpTime",12);
    days[12].addVariable("wakeUpTime",12);
    days[13].addVariable("wakeUpTime",13);
    days[14].addVariable("wakeUpTime",12);
    days[15].addVariable("wakeUpTime",13);
    days[16].addVariable("wakeUpTime",12);
    days[17].addVariable("wakeUpTime",13);

    //bedtime
    days[0].addVariable("bedtime",0);
    days[1].addVariable("bedtime",0);
    days[2].addVariable("bedtime",1);
    days[3].addVariable("bedtime",1);
    days[4].addVariable("bedtime",1);
    days[5].addVariable("bedtime",1);
    days[6].addVariable("bedtime",1);
    days[7].addVariable("bedtime",1);
    days[8].addVariable("bedtime",2);
    days[9].addVariable("bedtime",2);
    days[10].addVariable("bedtime",1);
    days[11].addVariable("bedtime",2);
    days[12].addVariable("bedtime",2);
    days[13].addVariable("bedtime",3);
    days[14].addVariable("bedtime",3);
    days[15].addVariable("bedtime",4);
    days[16].addVariable("bedtime",4);
    days[17].addVariable("bedtime",4);

    //sleep hours
    for(int i=0; i<len; i++){
        if(i!=0){
            days[i].addVariable("sleepHours",(days[i].getVarArr("wakeUpTime")[0]-days[i-1].getVarArr("bedtime")[0]));
        }
    }
    cout<<"sleep hours "<<getCombinedVarArr("sleepHours",days,len)[1];

    //tehdits, morning
    days[1].addOutcome("tehdit",7,9,4);
    days[2].addOutcome("tehdit",7,9,4);
    days[6].addOutcome("tehdit",10,9,4);
    days[9].addOutcome("tehdit",4,9,4);
    //tehdit, afternoon
    days[0].addOutcome("tehdit",7,13,5);
    days[1].addOutcome("tehdit",7,13,5);
    days[5].addOutcome("tehdit",7,13,5);
    days[8].addOutcome("tehdit",7,13,2);
    days[9].addOutcome("tehdit",9,13,5);
    days[10].addOutcome("tehdit",7,13,5);
    days[11].addOutcome("tehdit",7,15,3);
    days[13].addOutcome("tehdit",6,13,5);
    days[14].addOutcome("tehdit",7,13,5);
    days[15].addOutcome("tehdit",6,13,5);
    days[16].addOutcome("tehdit",7,13,5);
    days[17].addOutcome("tehdit",7,13,5);
    //tehdit, evening
    days[0].addOutcome("tehdit",7,20,4);
    days[1].addOutcome("tehdit",8,18,6);
    days[3].addOutcome("tehdit",7,20,4);
    days[4].addOutcome("tehdit",7,20,4);
    days[5].addOutcome("tehdit",7,18,6);
    days[6].addOutcome("tehdit",7,18,6);
    days[7].addOutcome("tehdit",7,18,6);
    days[8].addOutcome("tehdit",7,20,4);
    days[9].addOutcome("tehdit",7,18,6);
    days[11].addOutcome("tehdit",7,18,3);
    days[12].addOutcome("tehdit",9,18,6);
    days[13].addOutcome("tehdit",7,18,6);
    days[15].addOutcome("tehdit",4,20,4);
    days[16].addOutcome("tehdit",7,18,6);
    days[17].addOutcome("tehdit",7,18,6);

    //headache, morning
    days[6].addOutcome("headache",5,9,4);
    days[12].addOutcome("headache",7,9,4);
    days[13].addOutcome("headache",7,6,1);
    //headache, afternoon
    days[2].addOutcome("headache",3,13,5);
    days[6].addOutcome("headache",5,13,5);
    days[9].addOutcome("headache",3,13,5);
    days[11].addOutcome("headache",3,15,3);
    days[14].addOutcome("headache",5,13,5);
    //headache, evening
    days[0].addOutcome("headache",3,21,3);
    days[1].addOutcome("headache",4,21,3);
    days[2].addOutcome("headache",8,18,6);
    days[5].addOutcome("headache",4,18,6);
    days[6].addOutcome("headache",4,18,6);
    days[9].addOutcome("headache",3,18,6);
    days[12].addOutcome("headache",4,18,6);
    days[13].addOutcome("headache",6,18,6);
    days[17].addOutcome("headache",6,18,6);


// CREATE VECTOR/LIST FOR VAR ADDITION


    //int* sleepQualityArr = getCombinedVarArr("sleepQuality",days,len);
    //cout<<getMatlabArray(sleepQualityArr,len*24);

    int* tehdit = getCombinedOutcomeArr("tehdit",days,len);
    cout<<"tehdit = "<<getMatlabArray(tehdit,len*24);

    
    //day 0
    string nutrnames[]={"weight","energy","protein","carbs","sugar","fibre","fat","satfat","cholesterol","calcium","iron","sodium","potassium","magnesium","phosphorus","vitA","vitC","caffeine"};
    float teavals[]={250, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0.1, 8, 93, 8, 3, 0, 0, 50};
    Element tea(0.90,nutrnames,teavals,18); //energy protein carbs sugar fibre fat satfat cholesterol calcium iron sodium potassium magnetium phospoorus vitA vitC caffeine
    days[1].addMeal(tea,0);

    return 0;
}
