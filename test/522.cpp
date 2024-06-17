  #include<iostream>

  bool just(std::string a, std::string b) {
        int count = 0;//a的
        for (int i = 0; i < b.size(); i++) {
           while(count<a.size()){
            if(a[count]==b[i]){
                break;
            }
            count++;
            if(count>=a.size()){
                return false;
            }
           }
        }
        return true;
    }
    int main(){
        std::string a = "aabbcc";
        std::string b = "abc";
        if (just("abc", "abc"))
        {
            std::cout << "s";
        }
        return 0;
        }