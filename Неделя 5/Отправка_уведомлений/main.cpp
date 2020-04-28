#include <iostream>
#include <string>

using namespace std;


void SendSms(const string& number, const string& message) {
    cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
    cout << "Send '" << message << "' to e-mail "  << email << endl;
}


class INotifier
{
public:
    virtual void Notify(const string& message) const = 0;
};

class SmsNotifier : public INotifier
{
public:
    SmsNotifier(const string& phone_number){
        phone_number_ = phone_number;
    }

    void Notify(const string& message) const override {
        SendSms(phone_number_, message);
    }

private:
    string phone_number_;
};

class EmailNotifier : public INotifier
{
public:
    EmailNotifier(const string& email_address){
        email_address_ = email_address;
    }

    void Notify(const string& message) const override {
        SendEmail(email_address_, message);
    }

private:
    string email_address_;
};

void Notify(INotifier& notifier, const string& message) {
    notifier.Notify(message);
}


int main() {
    SmsNotifier sms{"+7-495-777-77-77"};
    EmailNotifier email{"na-derevnyu@dedushke.ru"};

    Notify(sms, "I have White belt in C++");
    Notify(email, "And want a Yellow one");
    return 0;
}