#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "functions.h"
#include "interface.h"
#include "fileIO.h"

using std::cin;
using std::cout;
using std::endl;

    //������� ��� � ��������� �������! - �������
    //������� ������� ���� - 
    //������� �������� ����� input � ������ ������ - �������
    //������� ���� �� ����� - �������� fileMenuChoice::exit  
    //������� ���������� � ���� - �������
    //�� �������

int main() {
    giveGreeting();
    launchAll(false);
    return 0;
}