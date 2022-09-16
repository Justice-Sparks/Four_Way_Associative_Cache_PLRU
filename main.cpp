/******************************************************************************
> Justice W. Sparks 
> 02/25/2022
> CS - 4200 - 002
> HomeWork #4      (PLRU)
*******************************************************************************/
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>
#include <bitset>
using namespace std;

//Prototypes:
void fillInputVector( vector <uint32_t> &inputVector);

void printTable(uint32_t seq,uint32_t b2,uint32_t b3,uint32_t b4,uint32_t b5,
                uint32_t vPrint, uint32_t way, 
                std::vector<uint32_t> cPrint, string status,
                vector<uint32_t> lruPrint);

int con(std::vector<uint32_t> array);

void hitAdjustment(uint32_t tagNum, vector<uint32_t> &LRU);

void pr(vector<uint32_t> lruPrint);

int main()
{


//---------------------------------------------------------------------------//
//      ...BEGIN DECLARING & INITIALIZING VARIABLES AND DATA STRUCUTRES... 
//---------------------------------------------------------------------------//    
    
    vector <uint32_t> inputVector;      // <---- Vector to hold input addresses
    
    uint32_t setIndex;                  // <---- Value to determine cache-line
    uint32_t currentAddress;            // <---- Variable to hold address
    
    std::vector<uint32_t> aTag =     // <---- Array to hold the A.tag
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};      
    
    std::vector<uint32_t> tag0;//<---- Variables for all 16 cache tags 
    std::vector<uint32_t> tag1;
    std::vector<uint32_t> tag2; std::vector<uint32_t> tag9;
    std::vector<uint32_t> tag3; std::vector<uint32_t> tag10;
    std::vector<uint32_t> tag4; std::vector<uint32_t> tag11;
    std::vector<uint32_t> tag5; std::vector<uint32_t> tag12;
    std::vector<uint32_t> tag6; std::vector<uint32_t> tag13;
    std::vector<uint32_t> tag7; std::vector<uint32_t> tag14;
    std::vector<uint32_t> tag8; std::vector<uint32_t> tag15;
    
    uint32_t v0 = 0; uint32_t v1 = 0;   // <-- Variables told all 16 valid bits
    uint32_t v2 = 0; uint32_t v3 = 0;
    uint32_t v4 = 0; uint32_t v5 = 0;    uint32_t v6  = 0;  uint32_t v7 = 0;
    uint32_t v8 = 0; uint32_t v9 = 0;    uint32_t v10 = 0; uint32_t v11 = 0;
    uint32_t v12 = 0; uint32_t v13 = 0;  uint32_t v14 = 0; uint32_t v15 = 0;
    
    vector <uint32_t> PLRU0 {0,0,0};   // <----- Four 1x4 vectors to keep
    vector <uint32_t> PLRU1 {0,0,0};   //        track of LRU order for 
    vector <uint32_t> PLRU2 {0,0,0};   //        each cache-line 
    vector <uint32_t> PLRU3 {0,0,0};
    
    uint32_t seq = 1;                   //<--- Variable to hold sequence value 
    
    uint32_t b5; uint32_t b4;           //<--- Bits for c.tag.index and half of
                                        //      c.data.index
   
    uint32_t b3; uint32_t b2;           //<--- Rest of c.data.index
    
    uint32_t numOfHits = 0;                 //<--- To keep track of hits
    
    fillInputVector(inputVector);
    
    uint32_t vPrint = 0;  //  v-Bit       <---- Values for printing 
    uint32_t way = 0;    //   updated way 
    std::vector<uint32_t> cPrint; // c.tag for printing 
    vector<uint32_t> lruPrint;
    string status = "Miss";         // status of "hit" or "miss"
    
//---------------------------------------------------------------------------//
//      ...BEGING LOOPING THROUGH DATA AND CACHE ALGORITHM...
//---------------------------------------------------------------------------//    
    
    
    //Loop to iterate through all 96 addresses
    for(int i = 0; i < inputVector.size(); i++)
    {
        currentAddress = inputVector[i];            //<--- Storing next address
        std::bitset<32> binAddress(currentAddress); //<---Storing binary format
        cout << "Binary Address: " <<binAddress << endl; 
        
        
        //------------------------------------------//
        //  Begin Isolating Bit Values from Address
        //------------------------------------------//
        
        b2 = binAddress[2];//                              <--- c.data.index  
        b3 = binAddress[3];//                              <--- c.data.index
        b4 = binAddress[4];// <--- Set index / c.tag.index <--- c.data.index
        b5 = binAddress[5];// <--- Set index / c.tag.index <--- c.data.index
        
       // cout << "A - TAG: ";                            // <--- Isolating A.tag  
        for(int i = 0, j = 31; i < 26 && j > 5 ; i++ , j--)
        {
            aTag[i] = binAddress[j];
           // cout << aTag[i];
        }
       // cout << endl; 
        
        cPrint = aTag;
        
        //Using bits 4 and 5 as the caches set-index:
        if(binAddress[5] == 0 && binAddress[4] == 0) //<----CACHE LINE: 0----//------------------------------//
        {
           // cout <<"Set Index / cache-line:"<< " 0 " << endl;
            
            //If zeroth way is empty: input A.tag, update v-bit, updated LRU
            if(v0 == 0) 
            {
              tag0 = aTag;  v0 = 1; cPrint = tag0; vPrint = 1; status = "miss"; 
            }
            //If zeroth way is full, but first way is empty: 
            else if( v0 == 1 && v1 == 0)
            {   
                  //fill tag#1   //Print tag 1 because it was updated 
                    tag1 = aTag;    cPrint = tag1;       
                    v1 =1;   vPrint = 1;        // <--- update v-bit 
                    way = 1;
                    PLRU0[0] = 0; PLRU0[1]= 1; 
                    status = "miss"; 
            }
            //If zeroth and first ways are full, but second way is empty: 
            else if( v0 == 1 && v1 == 1 && v2 == 0)
            {
                //fill tag#2   //Print tag 2 because it was updated 
                    tag2 = aTag;    cPrint = tag2;       
                    v2 = 1;  vPrint = 1;        // <--- update v-bit 
                    way = 2;
                    PLRU0[0] = 1; PLRU0[2] = 0; 
                    status = "miss"; 
            }
            //If zeroth, first & second ways are full, but third way is empty:
            else if( v0 == 1 && v1 == 1 && v2 == 1 && v3 == 0)
            {
                //fill tag#3   //Print tag 2 because it was updated 
                    tag3 = aTag;    cPrint = tag3;       
                    v3 = 1;  vPrint = 1;        // <--- update v-bit 
                    way = 3;        // <--- update way for print
                    PLRU0[0] = 1; PLRU0[2] = 1;
                    status = "miss"; 
            }
            else //Cache line is full and all v-bits == 1  
            {
                vPrint =1;
                //Check for hit on way #0
                if(tag0 == aTag)
                {   
                    status = " hit";   
                    cPrint = tag0;
                    PLRU0[0] = 0; PLRU0[1]=0;
                }
                //Check for hit on way #1
                else if (tag1 == aTag)
                {
                    status = " hit";   
                    cPrint = tag1;       
                    way = 1; 
                   PLRU0[0] = 0; PLRU0[1]= 1;
                }
                //Check for a hit on way #2
                else if (tag2 == aTag)
                {
                    status = " hit"; 
                    cPrint = tag2;       
                    way = 2; 
                    PLRU0[0] = 1; PLRU0[2]= 0;
                }
                //Check for a hit on way #3
                else if (tag3 == aTag)  
                {
                    status = " hit"; 
                    cPrint = tag3;       
                    way = 3; 
                    PLRU0[0] = 1; PLRU0[2]= 1;
                }
                else // No hits in cache line: replace least recently used 
                {
                  status = "miss";    
                  
                  if(PLRU0[0]== 1) // Follow opposite direction of bits to find 
                  {                // The Least recent used (Follow the zeros)
                      PLRU0[0] = 0; 
                      if(PLRU0[1] == 1) 
                      {
                        PLRU0[1] = 0; tag0 = aTag; cPrint = tag0; way = 0; 
                      }
                      else // == 0
                      {
                        PLRU0[1] = 1; tag1 = aTag; cPrint = tag1; way = 1;  
                      }
                  }
                  else // 
                  {
                      PLRU0[0] = 1; 
                      if(PLRU0[2] == 1) 
                      {
                        PLRU0[2] = 0; tag2 = aTag; cPrint = tag2; way = 2; 
                      }
                      else // == 0
                      {
                        PLRU0[2] = 1; tag3 = aTag; cPrint = tag3; way = 3;  
                      }
                  }
                  
                } 
            } 
            
            lruPrint = PLRU0;
        }
        else if(binAddress[5] == 0 && binAddress[4] == 1)//<--CACHE LINE: 1--//-------------------------------//
        {
            //cout <<"Set Index / cache-line:"<< " 1 " << endl; 
            
            //If zeroth way is empty: input A.tag, update v-bit, updated LRU
            if(v4 == 0) 
            {
              tag4 = aTag;  v4 = 1; cPrint = tag4; vPrint = 1; 
            }
            //If zeroth way is full, but first way is empty: 
            else if( v4 == 1 && v5 == 0)
            {   
                  //fill tag#1   //Print tag 1 because it was updated 
                    tag5 = aTag;    cPrint = tag5;       
                    v5 =1;   vPrint = 1;        // <--- update v-bit 
                    way = 1;
                    PLRU1[0] = 0; PLRU1[1]= 1; 
            }
            //If zeroth and first ways are full, but second way is empty: 
            else if( v4 == 1 && v5 == 1 && v6 == 0)
            {
                //fill tag#2   //Print tag 2 because it was updated 
                    tag6 = aTag;    cPrint = tag6;       
                    v6 = 1;  vPrint = 1;        // <--- update v-bit 
                    way = 2;
                    PLRU1[0] = 1; PLRU1[2] = 0; 
            }
            //If zeroth, first & second ways are full, but third way is empty:
            else if( v4 == 1 && v5 == 1 && v6 == 1 && v7 == 0)
            {
                //fill tag#3   //Print tag 2 because it was updated 
                    tag7 = aTag;    cPrint = tag7;       
                    v7 = 1;  vPrint = 1;        // <--- update v-bit 
                    way = 3;        // <--- update way for print
                    PLRU1[0] = 1; PLRU1[2] = 1;
            }
            else //Cache line is full and all v-bits == 1  
            {
                vPrint =1;
                //Check for hit on way #0
                if(tag4 == aTag)
                {   
                    status = " hit";   
                    cPrint = tag4;
                    PLRU1[0] = 0; PLRU1[1]=0;
                }
                //Check for hit on way #1
                else if (tag5 == aTag)
                {
                    status = " hit";   
                    cPrint = tag5;       
                    way = 1; 
                   PLRU1[0] = 0; PLRU1[1]= 1;
                }
                //Check for a hit on way #2
                else if (tag6 == aTag)
                {
                    status = " hit"; 
                    cPrint = tag6;       
                    way = 2; 
                    PLRU1[0] = 1; PLRU1[2]= 0;
                }
                //Check for a hit on way #3
                else if (tag7 == aTag)  
                {
                    status = " hit"; 
                    cPrint = tag7;       
                    way = 3; 
                    PLRU1[0] = 1; PLRU1[2]= 1;
                }
                else // No hits in cache line: replace least recently used 
                {
                  status = "miss";    
                  
                  if(PLRU1[0]== 1) // Follow opposite direction of bits to find 
                  {                // The Least recent used (Follow the zeros)
                      PLRU1[0] = 0; 
                      if(PLRU1[1] == 1) 
                      {
                        PLRU1[1] = 0; tag4 = aTag; cPrint = tag4; way = 0; 
                      }
                      else // == 0
                      {
                        PLRU1[1] = 1; tag5 = aTag; cPrint = tag5; way = 1;  
                      }
                  }
                  else // 
                  {
                      PLRU1[0] = 1; 
                      if(PLRU1[2] == 1) 
                      {
                        PLRU1[2] = 0; tag6 = aTag; cPrint = tag6; way = 2; 
                      }
                      else // == 0
                      {
                        PLRU1[2] = 1; tag7 = aTag; cPrint = tag7; way = 3;  
                      }
                  }
                  
                } 
            }
            
             lruPrint = PLRU1;
        }
        else if(binAddress[5] == 1 && binAddress[4] == 0)//<--CACHE LINE: 2--//-------------------------------//
        {
            //cout <<"Set Index / cache-line:"<< " 2 " << endl;
            
            //If zeroth way is empty: input A.tag, update v-bit, updated LRU
            if(v8 == 0) 
            {
              tag8 = aTag;  v8 = 1; cPrint = tag8; vPrint = 1; 
            }
            //If zeroth way is full, but first way is empty: 
            else if( v8 == 1 && v9 == 0)
            {   
                  //fill tag#1   //Print tag 1 because it was updated 
                    tag9 = aTag;    cPrint = tag9;       
                    v9 =1;   vPrint = 1;        // <--- update v-bit 
                    way = 1;
                    PLRU2[0] = 0; PLRU2[1]= 1; 
            }
            //If zeroth and first ways are full, but second way is empty: 
            else if( v8 == 1 && v9 == 1 && v10 == 0)
            {
                //fill tag#2   //Print tag 2 because it was updated 
                    tag10 = aTag;    cPrint = tag10;       
                    v10 = 1;  vPrint = 1;        // <--- update v-bit 
                    way = 2;
                    PLRU2[0] = 1; PLRU2[2] = 0; 
            }
            //If zeroth, first & second ways are full, but third way is empty:
            else if( v8 == 1 && v9 == 1 && v10 == 1 && v11 == 0)
            {
                //fill tag#3   //Print tag 2 because it was updated 
                    tag11 = aTag;    cPrint = tag11;       
                    v11 = 1;  vPrint = 1;        // <--- update v-bit 
                    way = 3;        // <--- update way for print
                    PLRU2[0] = 1; PLRU2[2] = 1;
            }
            else //Cache line is full and all v-bits == 1  
            {
                vPrint =1;
                //Check for hit on way #0
                if(tag8 == aTag)
                {   
                    status = " hit";   
                    cPrint = tag8;
                    PLRU2[0] = 0; PLRU2[1]=0;
                }
                //Check for hit on way #1
                else if (tag9 == aTag)
                {
                    status = " hit";   
                    cPrint = tag9;       
                    way = 1; 
                   PLRU2[0] = 0; PLRU2[1]= 1;
                }
                //Check for a hit on way #2
                else if (tag10 == aTag)
                {
                    status = " hit"; 
                    cPrint = tag10;       
                    way = 2; 
                    PLRU2[0] = 1; PLRU2[2]= 0;
                }
                //Check for a hit on way #3
                else if (tag11 == aTag)  
                {
                    status = " hit"; 
                    cPrint = tag11;       
                    way = 3; 
                    PLRU2[0] = 1; PLRU2[2]= 1;
                }
                else // No hits in cache line: replace least recently used 
                {
                  status = "miss";    
                  
                  if(PLRU2[0]== 1) // Follow opposite direction of bits to find 
                  {                // The Least recent used (Follow the zeros)
                      PLRU2[0] = 0; 
                      if(PLRU2[1] == 1) 
                      {
                        PLRU2[1] = 0; tag8 = aTag; cPrint = tag8; way = 0; 
                      }
                      else // == 0
                      {
                        PLRU2[1] = 1; tag9 = aTag; cPrint = tag9; way = 1;  
                      }
                  }
                  else // 
                  {
                      PLRU2[0] = 1; 
                      if(PLRU2[2] == 1) 
                      {
                        PLRU2[2] = 0; tag10 = aTag; cPrint = tag10; way = 2; 
                      }
                      else // == 0
                      {
                        PLRU2[2] = 1; tag11 = aTag; cPrint = tag11; way = 3;  
                      }
                  }
                  
                } 
            }
            
            lruPrint = PLRU2;
        }
        else  //<--------------------------------------------CACHE LINE: 3 --//----------------------------------//
        {
            //cout <<"Set Index / cache-line:"<< " 3 " << endl;
            
            //If zeroth way is empty: input A.tag, update v-bit, updated LRU
            if(v12 == 0) 
            {
              tag12 = aTag;  v12 = 1; cPrint = tag12; vPrint = 1; 
            }
            //If zeroth way is full, but first way is empty: 
            else if( v12 == 1 && v13 == 0)
            {   
                  //fill tag#1   //Print tag 1 because it was updated 
                    tag13 = aTag;    cPrint = tag13;       
                    v13 =1;   vPrint = 1;        // <--- update v-bit 
                    way = 1;
                    PLRU3[0] = 0; PLRU3[1]= 1; 
            }
            //If zeroth and first ways are full, but second way is empty: 
            else if( v12 == 1 && v13 == 1 && v14 == 0)
            {
                //fill tag#2   //Print tag 2 because it was updated 
                    tag14 = aTag;    cPrint = tag14;       
                    v14 = 1;  vPrint = 1;        // <--- update v-bit 
                    way = 2;
                    PLRU3[0] = 1; PLRU3[2] = 0; 
            }
            //If zeroth, first & second ways are full, but third way is empty:
            else if( v12 == 1 && v13 == 1 && v14 == 1 && v15 == 0)
            {
                //fill tag#3   //Print tag 2 because it was updated 
                    tag15 = aTag;    cPrint = tag15;       
                    v15 = 1;  vPrint = 1;        // <--- update v-bit 
                    way = 3;        // <--- update way for print
                    PLRU3[0] = 1; PLRU3[2] = 1;
            }
            else //Cache line is full and all v-bits == 1  
            {
                vPrint =1;
                //Check for hit on way #0
                if(tag12 == aTag)
                {   
                    status = " hit";   
                    cPrint = tag12;
                    PLRU3[0] = 0; PLRU3[1]=0;
                }
                //Check for hit on way #1
                else if (tag13 == aTag)
                {
                    status = " hit";   
                    cPrint = tag13;       
                    way = 1; 
                   PLRU3[0] = 0; PLRU3[1]= 1;
                }
                //Check for a hit on way #2
                else if (tag14 == aTag)
                {
                    status = " hit"; 
                    cPrint = tag14;       
                    way = 2; 
                    PLRU3[0] = 1; PLRU3[2]= 0;
                }
                //Check for a hit on way #3
                else if (tag15 == aTag)  
                {
                    status = " hit"; 
                    cPrint = tag15;       
                    way = 3; 
                    PLRU3[0] = 1; PLRU3[2]= 1;
                }
                else // No hits in cache line: replace least recently used 
                {
                  status = "miss";    
                  
                  if(PLRU3[0]== 1) // Follow opposite direction of bits to find 
                  {                // The Least recent used (Follow the zeros)
                      PLRU3[0] = 0; 
                      if(PLRU3[1] == 1) 
                      {
                        PLRU3[1] = 0; tag12 = aTag; cPrint = tag12; way = 0; 
                      }
                      else // == 0
                      {
                        PLRU3[1] = 1; tag13 = aTag; cPrint = tag13; way = 1;  
                      }
                  }
                  else // 
                  {
                      PLRU3[0] = 1; 
                      if(PLRU3[2] == 1) 
                      {
                        PLRU3[2] = 0; tag14 = aTag; cPrint = tag14; way = 2; 
                      }
                      else // == 0
                      {
                        PLRU3[2] = 1; tag15 = aTag; cPrint = tag15; way = 3;  
                      }
                  }
                  
                }
            }
            
            lruPrint = PLRU3;
        }
        
        //--------END OF CACHE LINES FOR LRU------------------------------------------------------------------//
        
        cout << endl;
        printTable(seq,b2,b3,b4,b5,vPrint, way,cPrint,status,lruPrint);
        
        seq++;
        
        if(status == " hit") { numOfHits++; }
        
        vPrint = 0; 
        way = 0;    
        string status = "Miss";         
    }
    
    //Reset valid bits and reset status to neutral for next address
        v0 = 0;  v1 = 0;  
        v2 = 0;  v3 = 0;
        v4 = 0;  v5 = 0;     v6  = 0;   v7 = 0;
        v8 = 0;  v9 = 0;     v10 = 0;  v11 = 0;
        v12 = 0;  v13 = 0;   v14 = 0;  v15 = 0;
        
        double num = 96;
        double ratio = ((numOfHits)/num)*100;
        
        cout <<endl<<"Hit Ratio: "<<std::setprecision(3)<<std::fixed<<ratio; 
    

    return 0;
}

//Function for filling the input vector 
void fillInputVector( vector <uint32_t> &inputVector)
{
    inputVector ={ //Bit to make 1 = 1 for printing purposes 
                   0x158,0x28c,0x2fc,0x300,0x314,0x344,0x374,0x398,0x2d4,0x280, 
                   0x24c,0x2bc,0x154,0x280,0x2f0,0x2C0,0x250,0x27C,0x370,0x394, 
                   0x2dC,0x284,0x250,0x2aC, 0x158,0x28c,0x2fc,0x300,0x314,0x344,
                   0x374,0x398,0x2d4,0x280,0x24c,0x2bc,0x154,0x280,0x2f0,0x2C0,
                   0x250,0x27C,0x370,0x394,0x2dC,0x284,0x250,0x2aC, 0x158,0x28c,
                   0x2fc,0x300,0x314,0x344,0x374,0x398,0x2d4,0x280,0x24c,0x2bc,
                   0x154,0x280,0x2f0,0x2C0,0x250,0x27C,0x370,0x394,0x2dC,0x284,
                   0x250,0x2aC, 0x158,0x28c,0x2fc,0x300,0x314,0x344,0x374,0x398,
                   0x2d4,0x280,0x24c,0x2bc,0x154,0x280,0x2f0,0x2C0,0x250,0x27C,
                   0x370,0x394,0x2dC,0x284,0x250,0x2aC};
     
    
/*     
    //Printing InputVector To make sure we have the right values: 
    for(int i = 0 ; i < inputVector.size() ; i ++)  
    {
        cout << hex << inputVector[i] << endl; 
    }
  */
  
}

//function for printing the table:
void printTable(uint32_t seq,uint32_t b2,uint32_t b3,uint32_t b4,uint32_t b5,
                uint32_t vPrint, uint32_t way, 
                std::vector<uint32_t> cPrint, string status, 
                vector<uint32_t> lruPrint)
{
    for(int i = 0 ; i < lruPrint.size(); i++)
    {
        
    }
    
    //Printing Output Table: 
cout << "|---------------------------------------------------|" << endl;
cout << "|Seq# "<<seq<<" | Way# "<<way<<"      |----------------------------" << endl; 
cout << "|---------------------------------------------------|" << endl;
cout << "|-| v | c.tag | c.data |  c.data.index:  "<<b5<<b4<<b3<<b2<<"        "<<'\n';
cout << "|-| "<<vPrint<<" |  "<<con(cPrint)<<"   | data 01|  c.tag.index:  "<<b5<<b4<<"          " << endl;
cout << "|-------------| data 02| History Stack:  "; pr(lruPrint); cout << "       " << endl;
cout << "|-------------| data 03|        Status:  "<<status<<"        " << endl;
cout << "|-------------| data 04|----------------------------|" << endl;
cout << "|---------------------------------------------------|" << endl;
cout << endl << endl;
}

//Function to convert binary array into integer for printing c.tag
int con(std::vector<uint32_t> array)
{
    int output = 0;
    int power = 1;

    for (int i = 0; i < array.size(); i++)
    {
        output += array[(array.size() - 1) - i] * power;
        power *= 2;
    }

    return output;
}


// Function for adjusting LRU after hits: 
// If we find a hit on a tag number 'n' (3,2,1 or 0), 
// we find that number inside of the LRU,  
// Erase it from the LRU, and then push it to the back of the LRU
// So it now becomes the most recently used
void hitAdjustment(uint32_t tagNum, vector<uint32_t> &LRU )
{
    for(int i = 0 ; i < LRU.size(); i++)
    {
        if(LRU[i] == tagNum)
        {
            LRU.erase(LRU.begin()+i);
            LRU.push_back(tagNum);
        }
    }
}

//function for printing LRU 
void pr(vector<uint32_t> lruPrint)
{
    cout<<"b";
    for(int i=0; i < lruPrint.size(); i++)
    {
        cout <<lruPrint[i];
    }
}








