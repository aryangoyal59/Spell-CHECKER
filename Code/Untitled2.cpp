#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int found=0;

class node{
    public:
        char info;
        string Word;
        class node* ptrs[256];
        node(){
            for(int i=0;i<256;i++){
                ptrs[i]=NULL;
            }
            info=NULL;
            Word="";
        }
};

void insertword(string word,int pos,class node * root){
    if(word.length()==pos){
        root->Word=word;
        return;
    }
    if( root-> ptrs[word[pos]]==NULL ){
        node *newnode;
        newnode= new node;
        newnode->info=word[pos];
        root->ptrs[word[pos]]=newnode;
        insertword(word,pos+1,root->ptrs[word[pos]]);
    }
    else
        insertword(word,pos+1,root->ptrs[word[pos]]);
}

void find(string key,int pos, class node * root){
    if((key != root->Word) && (root->ptrs[key[pos]] != NULL))
        find(key,pos+1,root->ptrs[key[pos]]);
    else if(key==root->Word){
        cout<<"\nThe spelling of the word '"<<root->Word<<"' is correct"<<endl;
        found=1;
    }
}

void printall(class node * root){
    for(int i=0;i<256;i++)
        if(root->ptrs[i]!=NULL){
            printall(root->ptrs[i]);
        }
    if(root->Word != "")
        cout<<" -> "<<root->Word<<endl;
}

void suggest(string key,int pos, class node * root){
    if((key != root->Word) && (root->ptrs[key[pos]] != NULL)){
            suggest(key,pos+1,root->ptrs[key[pos]]);
    }
    else{
            printall(root);
    }
}

int main(){
    int cn=0,cn2=0;
    int time=0;
    ifstream in("wordlist.txt");
    string word,current="",key;
    node *root;
    root = new node;
    while(in){
        in>>word;
        insertword(word,0,root);
        time++;
    }
    in.close();

    cout<<"Do You Want to Run Spell Checker and Suggestor? [Yes(1)/No(0)] "<<endl;
    cout<<"Input = ";
    cin>>cn;
  
    if (cn!=0&&cn!=1)
    {
        cout<<"\nEnter the Input in 0 or 1"<<endl;
        cout<<"Input = ";
        cin>>cn;

        if (cn!=0&&cn!=1)
        {
            cout<<"Not Valid Input....... Exiting"<<endl;
            return 0;
        }
    }



    if (cn == 1){
        while (1){
            cout<<endl<<"Trie Construction Successful"<<endl;
            //printall(root);
            cout<<"Enter the word to be searched for : ";
            cin>>key;
            find(key,0,root);
            if(!found){
                cout<<endl<<"The spelling is incorrect, Possible suggestions are :"<<endl;
                suggest(key,0,root);
            }

            cout<<"\nDo You Want To Look Again? [Yes(1)/No(0)] "<<endl;
            cout<<"Input = ";
            cin>>cn2;

            if (cn2!=0&&cn2!=1)
            {
               cout<<"\nEnter the Input in 0 or 1"<<endl;
               cout<<"Input = ";
               cin>>cn2;

               if (cn2!=0&&cn2!=1)
               {
                  cout<<"Not Valid Input....... Exiting"<<endl;
                  return 0;
               }
           }

           if (cn2 == 1){
                found=0;
                continue;
           }

           else{
                return 0;
           }
        }
    }

    else{
        return 0;
    }
}