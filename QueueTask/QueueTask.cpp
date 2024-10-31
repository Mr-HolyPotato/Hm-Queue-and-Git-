
#include <iostream>




template<typename structType>
struct Element {

    structType data;
    Element<structType>* next;
    Element(structType data) {
        this->data = data;
        next = NULL;
    }
};

template <typename classType>
class Queue
{

private:
    Element<classType>* head;
    Element<classType>* tail;

public:
    Queue() {
        head = tail = NULL;
    }

    //add element to queue
    void enqueue(classType value)
    {

        Element<classType>* newElement = new Element<classType>(value);
        if (tail == NULL) {
            head = tail = newElement;
            return;
        }

        tail->next = newElement;
        tail = newElement;

    }

    //delete from queue
    classType dequeue()
    {
        Element<classType>* tmp = head;
        head = head->next;
        if (!head)
            tail = nullptr;

        classType res = tmp->data;
        delete tmp;
        tmp = NULL;
        return res;

    }

    bool isEmpty() const
    {
        return !head;
    }

    Element<classType>* getHead() const
    {
        return head;
    }

    int peek()
    {
        return head->data;
    }

    ~Queue() {
        while (!isEmpty())
            dequeue();
        head = tail = nullptr;
    }

};



class Request
{

private:
    char* clientName;
    char* issueDescription;

public:
    Request() : clientName{ NULL }, issueDescription{ NULL } {    }

    Request(const char* name, const char* descr) {
        clientName = new char[strlen(name) + 1];
        strcpy_s(clientName, strlen(name) + 1, name);

        issueDescription = new char[strlen(descr) + 1];
        strcpy_s(issueDescription, strlen(descr) + 1, descr);
    }
    ~Request() {
        delete[]clientName;
        delete[]issueDescription;
    }

    Request(const Request& req) {
        this->clientName = new char[strlen(req.clientName) + 1];
        strcpy_s(this->clientName, strlen(req.clientName) + 1, req.clientName);

        this->issueDescription = new char[strlen(req.issueDescription) + 1];
        strcpy_s(this->issueDescription, strlen(req.issueDescription) + 1, req.issueDescription);
    }

    void setClientName(const char* name) {
        if (clientName)
            delete[]clientName;

        clientName = new char[strlen(name) + 1];
        strcpy_s(clientName, strlen(name) + 1, name);
    }
    void setIssueDescription(const char* descr) {
        if (issueDescription)
            delete[]issueDescription;

        issueDescription = new char[strlen(descr) + 1];
        strcpy_s(issueDescription, strlen(descr) + 1, descr);
    }

    char* getClientName() {
        return clientName;
    }
    char* getIssue() {
        return issueDescription;
    }

    Request& operator=(const Request& req) {
        if (this == &req) return *this;

        if (this->clientName)
            delete[]this->clientName;
        if (this->issueDescription)
            delete[]this->issueDescription;

        this->clientName = new char[strlen(req.clientName) + 1];
        strcpy_s(this->clientName, strlen(req.clientName) + 1, req.clientName);

        this->issueDescription = new char[strlen(req.issueDescription) + 1];
        strcpy_s(this->issueDescription, strlen(req.issueDescription) + 1, req.issueDescription);

        return *this;
    }


};


class CustomerService
{
private:
    Queue<Request> requests;

public:

    void addRequest(Request request) 
    {
        requests.enqueue(request);
    }
    void processRequest() {
        if (isEmpty())
            return;

        Request tmp(requests.dequeue());
        std::cout << "Client Name: " << tmp.getClientName() << std::endl;
        std::cout << "Issue: " << tmp.getIssue() << std::endl;
    }
    bool isEmpty() const
    {
        return requests.isEmpty();
    }

    int getIssueCount() {

        Element<Request>* head = requests.getHead();

        int count = 0;

        while (head)
        {
            count++;
            head = head->next;
        }

        return count;
    }

    void printAllRequest() {
        Element<Request>* head = requests.getHead();

        int i = 1;

        while (head)
        {
            std::cout << "Request " << i++ << ": " << std::endl;
            std::cout << "\tName: " << head->data.getClientName() << std::endl;
            //std::cout << "\tIssue: " << head->data.getIssue() << std::endl;

            head = head->next;
        }
    }

};




int main()
{
    
    Request req1("Client1", "Issue descr 1");
    Request req2("Client2", "Issue descr 2");
    Request req3("Client3", "Issue descr 3");
    Request req4("Client4", "Issue descr 4");

    CustomerService serv;

    serv.addRequest(req1);
    serv.addRequest(req2);
    serv.addRequest(req3);
    serv.addRequest(req4);

    serv.printAllRequest();

    std::cout << "you have " << serv.getIssueCount() << " requests" << std::endl;

    std::cout << "\n\n";

    while (!serv.isEmpty())
    {
        serv.processRequest();
    }

    std::cout << "\n\n\n\n";

    if (serv.isEmpty())
        std::cout << "You processed all requests" << std::endl;


}
