#include <iostream>
#include <cpr/cpr.h>
using namespace std;
int main(int argc, char** argv) {
    cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
                      cpr::Authentication{"user", "pass"},
                      cpr::Parameters{{"anon", "true"}, {"key", "value"}});
    cout<<r.status_code<<endl;                  // 200
    cout<<r.header["content-type"]<<endl;      // application/json; charset=utf-8
    cout<<r.text<<endl;                         // JSON text string

}