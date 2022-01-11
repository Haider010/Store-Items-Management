#include<bits\stdc++.h>
#include<conio.h>
using namespace std;
class Billing{
    int product_id;
    string product_name;
    int prduct_quantity;
    float discount_on_price;
    float product_price;
    float total_price;
    public:
    void setdata();
    void writ_data();
    void show_recrd();
    void showdata();
    void modify_data();
    void del_items();
    void search_items();
};
void Billing::setdata(){
    cout<<"Enter product id : ";cin>>product_id;
    cout<<"Enter product name : ";cin>>product_name;
    cout<<"Enter product quantity : ";cin>>prduct_quantity;
    cout<<"Enter discount on price : ";cin>>discount_on_price;
    cout<<"Enter product price : ";cin>>product_price;
}
void Billing::writ_data(){
    char a;
    fstream bill;
    bill.open("bill.txt",ios::out|ios::app|ios::binary);
    do{
    setdata();
    bill.write(( char*)(this),sizeof(*this));
    cout<<"Do you want to add more products (y/n) : ";cin>>a;
    }while(a == 'y');
    bill.close();
}
void Billing::showdata(){
    cout<<"\n\nProduct id : "<<product_id<<endl;
    cout<<"The product name : "<<product_name<<endl;
    cout<<"Quantity of product : "<<prduct_quantity<<endl;
    cout<<"Discount on item : "<<discount_on_price<<"%"<<endl;
    cout<<"Product price : "<<product_price<<endl;
}
void Billing::show_recrd(){
    cout<<"\n----------ITEMS IN STORE----------"<<endl;
    fstream bill;
    bill.open("bill.txt",ios::in|ios::binary);
    if(!bill){
        cout<<"\n***** There is no item in store *****"<<endl;
        return;
    }
    bill.read((char*)(this),sizeof(*this));
    while(!bill.eof()){
        showdata();
        bill.read((char*)(this),sizeof(*this));
    }
    bill.close();    
}
void Billing::modify_data(){
    int product_idd;
    fstream bill;
    bill.open("bill.txt",ios::in|ios::out|ios::ate|ios::binary);
    if(!bill){
        cout<<"\n**** Store is empty ****"<<endl;
        return;
    }
    bill.seekg(0);
    show_recrd();
    cout<<"\n\nEnter product id to modify product : ";cin>>product_idd;
    bill.read((char*)(this),sizeof(*this));
    while(!bill.eof()){
    if(product_idd==product_id){
        setdata();
        int a=bill.tellp();
        bill.seekp((a)-(sizeof(*this)));
        bill.write((char*)(this),sizeof(*this));
    }
    bill.read((char*)(this),sizeof(*this));
    }
    bill.close();
}
void Billing::del_items(){
    fstream bill,bill1;
    bill.open("bill.txt",ios::in|ios::binary);
    if (!bill){
        cout<<"\n**** Store is empty ****"<<endl;
        return;
    }
    show_recrd();
    int delete_item;
    cout<<"\n\nEnter item id to delete : ";cin>>delete_item;
    bill.read((char*)this,sizeof(*this));
    bill1.open("bill1.txt",ios::out|ios::binary);
    while(!bill.eof()){
    if (delete_item!=product_id)
    bill1.write((char*)this,sizeof(*this));
    bill.read((char*)this,sizeof(*this));
    }    
    bill.close();
    bill1.close();
    remove("bill.txt");
    rename("bill1.txt","bill.txt");

}
void Billing::search_items(){
    fstream bill;
    bill.open("bill.txt",ios::in|ios::binary);
    if (!bill){
        cout<<"\n**** Store is empty ****"<<endl;
        return;
    }
    string item_name;
    cout<<"\nEnter product name to search : ";cin>>item_name;
    bill.read((char*)this,sizeof(*this));
    while(!bill.eof()){
        if (item_name==product_name)
        {
            showdata();
            break;
        }
        else{
            cout<<"\n\tITEM NOT FOUND"<<endl;
        }
        bill.read((char*)this,sizeof(*this));
    }
    bill.close();
}
int main()
{   Billing b;
    int choice;
    fh:
    cout<<"\n\n--------STORE MANAGEMENT SYSTEM---------"<<endl;
    cout<<"\n1 => ADD PRODUCT"<<endl;
    cout<<"2 => SHOW ALL STORE ITEMS"<<endl;
    cout<<"3 => SEARCH ITEMS FROM STORE"<<endl;
    cout<<"4 => REMOVE ITEM FROM STORE"<<endl;
    cout<<"5 => MODIFY ITEM DETAILS"<<endl;
    cout<<"6 => EXIT"<<endl;
    cout<<"\nENTER YOUR CHOICE : ";cin>>choice;
    switch(choice){
        case 1:
        b.writ_data();
        break;
        case 2:
        b.show_recrd();
        break;
        case 3:
        b.search_items();
        break;
        case 4:
        b.del_items();
        break;
        case 5:
        b.modify_data();
        break;
        case 6:
        exit(0);
        default:
        cout<<"\nINVALID CHOICE....TRY AGAIN"<<endl;
        goto fh;
    }
    cout<<"\nPRESS ANY KEY TO BACK.....";
    getch();
    goto fh;
    return 0;
}