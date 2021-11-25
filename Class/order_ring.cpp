#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


enum side_t {BUY, SELL};

struct Order{
    int id;
    int price;
    int quantity;
    side_t side;
    char *venue;
    Order(int i,int p,int q,side_t s,const char *v);
    Order(const Order &o);
    friend std::ostream& operator<<(std::ostream& os, const Order& dt);
};

struct OrderCircleElement{
    Order * order;
    struct OrderCircleElement *next;
    OrderCircleElement();
    OrderCircleElement(const OrderCircleElement &oc);
};


class OrderRing{
private:
    int size;
    OrderCircleElement * head;
    OrderCircleElement * find_order(int id);
    OrderCircleElement * find_previous_order(int id);
public:
    OrderRing();
    OrderRing(const OrderRing &oc);
    void add_order(struct Order &order);
    void modify_quantity_order(int id,int qty);
    void modify_venue_order(int id,const char *venue);
    void remove_order(int id);
    void display(int number_of_times);
};


std::ostream& operator<<(std::ostream& os, const Order& o)
{
    os << "[id=" << o.id << ","
            <<"price=" << o.price << ","
            <<"quantity=" << o.quantity<< ","
            <<"side=" << o.side << ","
            <<"venue=" << o.venue
            << "]";
    return os;
}


void OrderRing::display(int number_of_times=1) {
    OrderCircleElement *current=head;
    for (int nb=0;nb<number_of_times;nb++)
    {
        std::cout <<  "== iteration id=" << nb << " =="  << std::endl;
        for (int k=0; k < size; k++) {
            std::cout << *current->order << std::endl;
            current=current->next;
        }

    }
}



/*
 * Complete the following functions
 */


Order::Order(int i,int p,int q,side_t s,const char *v)
{
    id = i;
    price = p;
    quantity = q;
    side = s;
    venue = new char[strlen(v) + 1];
    strcpy(venue, v);
}

Order::Order(const Order &o)
{
    id = o.id;
    price = o.price;
    quantity = o.quantity;
    side = o.side;
    venue = new char[strlen(o.venue) + 1];
    strcpy(venue, o.venue);
}


OrderCircleElement::OrderCircleElement():order(nullptr),next(nullptr){}

OrderCircleElement::OrderCircleElement(const OrderCircleElement &oc){
    if (oc.order != nullptr){
        order = new Order(*(oc.order));
    }else{
        order = nullptr;
    }
    
    next = oc.next;
}





OrderRing::OrderRing():size(0), head(nullptr)
{
}

OrderRing::OrderRing(const OrderRing &oc)
{
    head = new OrderCircleElement(*(oc.head));
    size = oc.size;
    if (size==0){
        return;
    }
    int start_id = head->order->id;
    //auto next = oc.head->next;
    auto prev = head;
    while(true){
        auto next = prev -> next;
        if (next->order->id == start_id){
            prev->next = head;
            break;
        }
        prev -> next = new OrderCircleElement(*(next));
        prev = prev->next;
        next = next->next;
    }
    
}
void OrderRing::add_order(struct Order &order)
{
    size++;
    if (head == nullptr){
        head = new OrderCircleElement();
        head -> order = new Order(order);
        head -> next = head;
        return;
    }

    //  (0)->1-2-3
    if (head->order->price >= order.price){
        OrderCircleElement * new_head = new OrderCircleElement();
        new_head  -> order = new Order(order);
        new_head -> next = head;
        int start_id = head -> order ->id;
        auto p = head;
        while(true){
            if (p -> next == head){
                p -> next = new_head;
                break;
            }
            p = p -> next;
        }
        head = new_head;
        return;
    }
    // 1-2-(3)-4
    // 2 . 4
    // 2 -> 1
    
    auto new_p = new OrderCircleElement();
    new_p  -> order = new Order(order);
    
    auto p = head -> next;
    auto prev = head;
    int start_id = head -> order ->id;
    while (true){
        if ( (p->order->price) >= order.price || (p->order->id) == start_id){
            new_p -> next = p;
            prev -> next = new_p;
            break;
        }
        p = p ->next;
        prev = prev -> next;
    }
    // while (true){
    //     if (p -> order ->price < order.price){
    //         prev = p; //2
    //         p = p -> next;//1
    //         if (p == head){
    //             auto new_p = new OrderCircleElement();
    //             new_p -> order = new Order(order);
    //             new_p -> next = head;
    //             prev -> next = new_p;
    //             break;
    //         }
    //     }else{
    //         auto new_p = new OrderCircleElement();
    //         new_p -> order = new Order(order);
    //         new_p -> next = p;
    //         prev -> next = new_p;
    //         break;
    //     }
    // }
}
OrderCircleElement * OrderRing::find_order(int id)
{
    auto p = head;
    if (p == nullptr){return nullptr;}
    if (head->order->id == id){
        return head;
    }
    int start_id = head->order->id;
    p = p->next;
    while(p->order->id != start_id){
        if (p->order->id == id){
            return p;
        }else{
            p = p -> next;
        }
    }
    return nullptr;
}

OrderCircleElement * OrderRing::find_previous_order(int id)
{
    auto p = head;
    if (p == nullptr){return nullptr;}
    int nid = head->next->order->id;
    if (id == nid){
        return head;
    }
    auto prev=head->next;
    p = prev->next;
    while(true){
        if (p -> order -> id == nid){
            break;
        }
        if (p -> order -> id == id){
            return prev;
        }
        prev = prev -> next;
        p = p -> next;
    }
    return nullptr;
}


void OrderRing::modify_quantity_order(int id,int qty){
    auto p = find_order(id);
    if (p){
        p -> order -> quantity = qty;
    }
}
void OrderRing::modify_venue_order(int id,const char *venue){
    auto p = find_order(id);
    if (p){
        p -> order -> venue = new char[strlen(venue) + 1];
        strcpy(p -> order -> venue, venue);
    }
}

void OrderRing::remove_order(int id)
{
    auto p = find_order(id);
    if (p == nullptr){
        return;
    }
    if ((head -> next -> order -> id) == (head -> order -> id)){
        size = 0;
        delete head;
        head = nullptr;
        return;
    }
    int start_id = head->order->id;
    if (p == head){
        auto new_head = head->next;
        auto p2 = new_head;
        while(true){
            if (p2->next->order->id == start_id){
                break;
            }
            p2=p2->next;
        }
        p2 -> next = new_head;
        head = new_head;
        size--;
        return;
    }
    // prev -id ->,,,
    auto prev = find_previous_order(id);
    // prev - p ->...
    prev -> next = p -> next;
    delete p;
    size--;
    return;
}


void case1()
{
    std::cout << "CASE 1 - START" << std::endl;
    OrderRing a;
    Order o1(1,1,100,BUY,"SEB");
    Order o2(2,2,100,BUY,"NICE");
    Order o3(3,3,100,BUY,"SEB");
    Order o4(4,4,100,SELL,"SEB");
    a.add_order(o1);
    a.add_order(o2);
    a.add_order(o3);
    a.add_order(o4);
    a.display(1);
    std::cout << "CASE 1 - END" << std::endl;
}

void case2()
{
    std::cout << "CASE 2 - START" << std::endl;
    OrderRing a;
    Order o1(1,1,100,BUY,"SEB");
    Order o2(2,2,100,BUY,"SEB");
    Order o3(3,3,100,BUY,"SEB");
    Order o4(4,4,100,SELL,"SEB");
    a.add_order(o1);
    a.add_order(o2);
    a.add_order(o3);
    a.add_order(o4);
    a.display(2);
    std::cout << "CASE 2 - END" << std::endl;
}

void case3()
{
    std::cout << "CASE 3 - START" << std::endl;
    OrderRing a;
    Order o1(1,2,100,BUY,"SEB");
    Order o2(4,3,100,BUY,"SEB");
    Order o3(3,4,100,BUY,"NIC");
    Order o4(2,1,100,SELL,"SEB");
    a.add_order(o1);
    a.add_order(o2);
    a.add_order(o3);
    a.add_order(o4);
    a.display(2);
    std::cout << "CASE 3 - END" << std::endl;
}

void case4()
{
    std::cout << "CASE 4 - START" << std::endl;
    OrderRing a;
    for (int k = 0 ; k < 10 ; k ++)
    {
        Order o(k,k+1,(1+k)*10,(k%2)?(side_t)1:(side_t)0,"SEB");
        a.add_order(o);
    }
    a.display(2);
    std::cout << "CASE 4 - END" << std::endl;
}


void case5()
{
    std::cout << "CASE 5 - START" << std::endl;
    OrderRing a;
    for (int k = 0 ; k < 10 ; k ++)
    {
        Order o(k,k+1,(1+k)*10,(k%2)?(side_t)0:(side_t)1,"SEB");
        a.add_order(o);
    }
    a.remove_order(0);
    a.display(2);
    std::cout << "CASE 5 - END" << std::endl;
}

void case6()
{
    std::cout << "CASE 6 - START" << std::endl;
    OrderRing a;
    for (int k = 0 ; k < 10 ; k ++)
    {
        Order o(k,k+1,(1+k)*10,(k%2)?(side_t)0:(side_t)1,"SEB");
        a.add_order(o);
    }
    a.remove_order(0);
    a.display(2);
    std::cout << "CASE 6 - END" << std::endl;
}

void case7()
{
    std::cout << "CASE 7 - START" << std::endl;
    OrderRing a;
    for (int k = 0 ; k < 10 ; k ++)
    {
        Order o(k,k+1,(1+k)*10,(k%2)?(side_t)0:(side_t)1,"SEB");
        a.add_order(o);
    }

    for (int k = 0 ; k < 10 ; k ++)
    {
        if(k%2)
            a.remove_order(k);
    }

    a.display(2);
    std::cout << "CASE 7 - END" << std::endl;
}


void case8()
{
    std::cout << "CASE 8 - START" << std::endl;
    OrderRing a;
    for (int k = 0 ; k < 10 ; k ++)
    {
        Order o(k,k+1,(1+k)*10,(k%2)?(side_t)0:(side_t)1,"SEB");
        a.add_order(o);
    }

    for (int k = 0 ; k < 10 ; k ++)
    {
        if(k%2==0){
            a.modify_quantity_order(k,k*20);
            a.display();
        }
    }

    a.display(2);
    std::cout << "CASE 8 - END" << std::endl;
}

void case9()
{
    std::cout << "CASE 9 - START" << std::endl;
    OrderRing a;
    for (int k = 0 ; k < 10 ; k ++)
    {
        Order o(k,k+1,(1+k)*10,(k%2)?(side_t)0:(side_t)1,(k%2)?"NYSE":"SEBX");
        a.add_order(o);
    }

    a.display(2);
    OrderRing b(a);
    b.display(2);
    std::cout << "CASE 9 - END" << std::endl;
}

void case10()
{
    std::cout << "CASE 10 - START" << std::endl;
    OrderRing a;
    for (int k = 0 ; k < 10 ; k ++)
    {
        Order o(k,k+1,(1+k)*10,(k%2)?(side_t)0:(side_t)1,(k%2)?"NYSE":"SEBX");
        a.add_order(o);
    }


    OrderRing b(a);
    a.modify_quantity_order(2,555);
    a.modify_venue_order(4,"NASDAQ");

    a.display(2);
    b.display(2);
    std::cout << "CASE 10 - END" << std::endl;
}


void switch_test_case(int test_case_number) {

        switch(test_case_number)
    {
        case 1:
            case1();
            break;
        case 2:
            case2();
            break;
        case 3:
            case3();
            break;
        case 4:
            case4();
            break;
        case 5:
            case5();
            break;
        case 6:
            case6();
            break;
        case 7:
            case7();
            break;
        case 8:
            case8();
            break;
        case 9:
            case9();
            break;
        case 10:
            case10();
            break;
    }
}
    
int main()
{
    string test_case_number_temp;
    getline(cin, test_case_number_temp);

    int test_case_number = stoi(ltrim(rtrim(test_case_number_temp)));

    switch_test_case(test_case_number);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
