#include <iostream>
#include <vector>

int main()
{
    std::string s1, s2, s3;
    s1 = "kissa";
    s3 = "koira";

    std::vector<std::string> vec;
    vec.push_back(s3);
    // s3 = "koira"

    vec.push_back(std::move(s3));
    // s3 = ""



    // unable to read memory, error reading characters of string,  "kissa" -> "issa"
    //s1 = s2;

    // unable to read memory, NULL, "kissa" -> ""
    s1 = std::move(s2);
}

