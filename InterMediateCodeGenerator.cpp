#include<bits/stdc++.h>
#include<fstream>
#include <ctype.h>
#include <sstream>

using namespace std ;

unordered_map<string,pair<string,string>>mp{

{"STOP",{"IS","00"} }, 
{"ADD" ,{"IS" ,"01"}},
{"SUB",{"IS", "02"}},
{"MULTI",{"IS","03"} },
{"MOVER",{"IS", "04"}},
{"MOVEM" ,{"IS", "05"}},
{"COMB",{"IS","06"}},
{"BC",{"IS","07"}},
{"DIV",{"IS","08"}},
{"READ",{"IS" ,"09"}},
{"PRINT",{"IS","10"}},
{"END",{"AD", "02"}},
{"STAR",{"AD", "01"} } ,
{"ORIGIN",{"AD", "03"}},
{"EQU",{"AD","04"}},
{"LTORG",{"AD","05"}} ,
{"DS",{"DL","02"}} ,
{"DC",{"DL" ,"02"}} ,
{"AREG",{"RG","01"}} ,
{"BREG",{"RG","02"}} ,
{"CREG",{"RG","03"}} ,

} ;

int LEN[23] = {1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0} ;

vector<pair<int,int>>literal ;
vector<pair<int,int>>All_literal ;
vector<pair<string,int>>symbol ;
vector<pair<string,int>>walNumSymbol ;

vector<pair<int,int>>literal_table ;
vector<pair<int,int>>symbol_table ;

vector<vector<string>>buffer ;
vector<int>Adress ;
vector<vector<string>>vt;
int preAdr ;
int I ;
int CNT ; 
ofstream myfile ("/home/vishwa/Documents/DATA_STRUCTURES/OUTPUT.txt", std::ios_base::out);

void Print()
{
    for(auto& i:buffer)
    {
        for(auto& k:i)
        {
            std::cout<<k<<"\t" ;

        }
        std::cout<<endl;
    }
}
void Decode(string str)
{
    
    istringstream ss(str);
    //ofstream ltd ("/home/vishwa/Documents/DATA_STRUCTURES/LITERAL.txt", std::ios_base::out);

        string word; // for storing each word
        
        // Traverse through all words
        // while loop till we get 
        // strings to store in string word
        vector<string>at ;

        while (ss >> word) 
        {
            // print the read word
            //std::cout << word << "\t"; 

            //take all strings into buffer to process
            at.push_back(word) ;

        }
        buffer.push_back(at) ;
        //cout<<endl ; 


        int BS = buffer[I].size() ;
        string ex = "" ;

        for(int k=0;k<BS;k++)
        {
            cout<<buffer[I][k]<<" " ;

            if( buffer[I][k] == "START" )
            {
                    Adress.push_back(stoi(buffer[I][k+1])) ;
                    preAdr = Adress[0] ;
                    break ;

            }
            else if( buffer[I][k] == "MULTI" )
            {
                myfile<<mp[buffer[I][k]].first<<" "<<mp[buffer[I][k]].second<<" ";
            }
            else if( buffer[I][k] == "ORIGIN" )
            {
                ex = buffer[I][++k] ;
                string st = "" ;

                while( !iswalnum(ex[0]) )
                {
                    ex = buffer[I][k++] ;
                }
                st = ex ;

                while( !isdigit(ex[0]) )
                {
                    ex = buffer[I][k++] ;         
                }
                
                for(auto& I:walNumSymbol)
                {
                    if( I.first == st )
                    {
                        preAdr=stoi(ex)+I.second ;
                        break ;
                    }
                }

                //preAdr=stoi(ex) ;
                myfile<<"NO IC"<<endl;
                break ;
            }
            else if( buffer[I][k] == "LTORG" )
            {
                //vector<pair<int,int>>::iterator it ;
                pair<int,int>lt ;

                for(auto& k:literal)
                {
                    k.second = preAdr++ ;
                   // lit<<k.first<<"   "<<k.second<<endl;
                    lt = {k.first,k.second} ;
                    literal_table.emplace_back(lt) ;
                    myfile<<"(DL,02) , (-) (C,"<<k.first<<")"<<endl ;
                    literal.erase(literal.begin()) ;

                }

                //literal.clear() ;
               // lit.close() ;
                break ;
            }
            else if( buffer[I][k] == "DS" )
            {
                while( !isdigit(buffer[I][k][0]) )
                    k++ ;
                preAdr+=stoi(buffer[I][k]) ;    
                myfile<<"NO IC"<<endl;
                break ;
            }
            else if( buffer[I][k] == "END" )
            {
                
                myfile<<"(DL,02) , (-) "<<"\t" ;

                for(auto& k:literal)
                {
                    k.second = preAdr++ ;
                    myfile<<"(C,"<<k.first<<"),"<<" " ;
                    literal_table.push_back({k.first,k.second}) ;
                }
                
    
                //myfile<<"(DL,02) , (-), END "<<endl ;
                break ;
            }
            else if( mp.find( buffer[I][k] ) != mp.end() )
            {
                //ex = (std::string)buffer[I][k] ;
                //cout<<buffer[I][k]<<endl ;
                if( myfile.is_open() )
                {

                    myfile<<mp[buffer[I][k]].first<<" "<<mp[buffer[I][k]].second<<" ";
                    //<<" for  : " << buffer[I][k] <<endl 

                }
                else 
                    cout << "Unable to open file";
                    //cout<<mp[buffer[I][k]].first<<"\t"<<mp[buffer[I][k]].second<<"\t" ;
            }
            else if(buffer[I][k][ buffer[I][k].length()-1 ] == ':' )
            {
                continue ;
            }
            else if( iswalnum(buffer[I][k][0]) && k == 0 )
            {
                pair<string,int>PW = { (buffer[I][k]) , preAdr } ;
                walNumSymbol.emplace_back( PW ) ;

            }
            
            else if( isalpha(buffer[I][k][0]) ) 
            {
                //cout<<"ALPHA :"<<buffer[I][k]<<endl;
                pair<string,int>PT = { (buffer[I][k]) , preAdr++ } ;
                symbol.emplace_back( PT ) ;
                break;
            }
            else if( isdigit(buffer[I][k][0]) )
            {
                pair<int,int>PR = {stoi(buffer[I][k]),preAdr++ } ;
                literal.emplace_back( PR ) ;
                All_literal.emplace_back( PR ) ;
                CNT++ ;
                break ;
            }
            
            
        }
        std::cout<<endl;
        myfile<<endl;
        I++ ;

}
  
void BuildCode()
{
    /*
        process file to remove commas, = , loop like varibles ????
    
    */

    fstream file;
    string str , t, q, filename;
    CNT = 0 ;
    // filename of the file
    filename = "/home/vishwa/Documents/DATA_STRUCTURES/example3.txt";
    
    // opening file
    file.open(filename.c_str());






     
    // extracting words from the file
    while(!file.eof())
    {
        // extracting words from the file
        getline(file,str) ;
        Decode(str) ;
        //std::cout<<str<<endl;
    }
    //Print() ;
    file.close() ;
    myfile.close() ;

}
void PrintSymLit()
{
    ofstream sym ("/home/vishwa/Documents/DATA_STRUCTURES/SYMBOL.txt", std::ios_base::out);
    ofstream Unsym ("/home/vishwa/Documents/DATA_STRUCTURES/Unique_Symbol.txt", std::ios_base::out);
    ofstream lit ("/home/vishwa/Documents/DATA_STRUCTURES/LITERAL.txt", std::ios_base::out);
    ofstream aln ("/home/vishwa/Documents/DATA_STRUCTURES/ALN.txt", std::ios_base::out);
    ofstream litTable ("/home/vishwa/Documents/DATA_STRUCTURES/LITERAL_TABLE.txt", std::ios_base::out);
    ofstream symTable ("/home/vishwa/Documents/DATA_STRUCTURES/SYMBOL_TABLE.txt", std::ios_base::out);

    set<string>st ;



    for(auto& K : symbol)
        st.insert(K.first) ;
    for(auto& K : walNumSymbol)
        st.insert(K.first) ;


        

    if( sym.is_open()  && aln.is_open() && lit.is_open() && litTable.is_open() && symTable.is_open() )
    {
    
        for(auto& K : st )
            Unsym<<K<<endl;

        for(auto& K : symbol )
            sym<<K.first<<"   "<<K.second<<endl;
        
        for(auto& K : walNumSymbol )
            aln<<K.first<<"   "<<K.second<<endl;
        
        for(auto& K : All_literal )
            lit<<K.first<<"  "<<K.second<<endl;

        for(auto& K : literal_table )
            litTable<<K.first<<"  "<<K.second<<endl ;

        for(auto& K : walNumSymbol )
            symTable<<K.first<<"  "<<K.second<<endl ;
    }
    else
        std::cout<<"Error !!! Error !!! Error !!!\n"<<endl ;

    sym.close();
    lit.close() ;
    aln.close() ;

}
void PreProcess()
{
    ifstream ifile;
    ofstream ofile("/home/vishwa/Documents/DATA_STRUCTURES/SYMBOL.txt", std::ios_base::out) ;

    string str , t , q , filename ;
  
    // filename of the file
    filename = "/home/vishwa/Documents/DATA_STRUCTURES/example.txt";
    
    // opening file
    ifile.open(filename.c_str());
     
    // extracting words from the file
    while(!ifile.eof())
    {
        // extracting words from the file
        getline(ifile,str) ;


    }
    //Print() ;
    ifile.close() ;

}
int main()
{
    I = 0 ;
    BuildCode() ;
    cout << " " << endl;
    PrintSymLit() ;
    //Print() ;

    return 0 ;
}





