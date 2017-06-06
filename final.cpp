// CPlusPlus2.cpp
//#55. Модель компьютера характеризуется кодом и названием марки компьютера, 
//типом процессора, частотой работы процессора, объемом оперативной памяти, 
//объемом жесткого диска, объемом памяти видеокарты, ценностью компьютера и
//количеством экземпляров. Поиск по типу процессора, объему ОЗУ, памяти видеокарты 
//и объему жесткого диска. 

/*5. Реализовать виртуальный магазин ПК. Магазин должен иметь два режима работы 
— клиент и сотрудник (выбирается в меню). Сотрудник имеет возможность управления магазином: 
добавление, редактирование, удаление моделей ПК. Предусмотреть вывод списка моделей ПК с сортировкой и/или фильтрацией по выбранному полю.
Пользователь имеет возможность поиска ПК по заданному критерию (любое поле, для полей типа цены и объема памяти — предусмотреть ввод диапазона)
и покупки выбранного ПК. Предусмотреть хранение истории покупок и просмотр истории сотрудником. */

#include "stdafx.h"
#include "Helper.h"
#include <ctime>


void printManagerOrClient()
{
	std::cout << "\n**********************************" << std::endl;
	std::cout << "Command list:" << std::endl;
	std::cout << " 1)Manager" << std::endl;
	std::cout << " 2)Client" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "**********************************" << std::endl;
}

void printManagerMenu()
{
	std::cout << "\n**********************************" << std::endl;
	std::cout << "Command list:" << std::endl;
	std::cout << " 1)Add" << std::endl;
	std::cout << " 2)Print" << std::endl;
	std::cout << " 3)Find(+change/delete)" << std::endl;
	std::cout << " 4)Print hisory" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "**********************************" << std::endl;
}

void printClientMenu()
{
	std::cout << "\n************SEARCH BY*************" << std::endl;
	std::cout << " 1)By code" << std::endl;
	std::cout << " 2)By mark" << std::endl;
	std::cout << " 3)By processor" << std::endl;
	std::cout << " 4)By frequency" << std::endl;
	std::cout << " 5)By RAM" << std::endl;
	std::cout << " 6)By HDD" << std::endl;
	std::cout << " 7)By Video memory" << std::endl;
	std::cout << " 8)By value" << std::endl;
	std::cout << " 9)By count" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "**********************************" << std::endl;
}

void printMenuConsoleFile()
{
	std::cout << "\n**********************************" << std::endl;
	std::cout << " 1)Console" << std::endl;
	std::cout << " 2)File" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "**********************************" << std::endl;
}

void printMenuFindParam()
{
	std::cout << "\n**********************************" << std::endl;
	std::cout << " 1)By code" << std::endl;
	std::cout << " 2)By mark" << std::endl;
	std::cout << " 3)By processor" << std::endl;
	std::cout << " 4)By frequency" << std::endl;
	std::cout << " 5)By RAM" << std::endl;
	std::cout << " 6)By HDD" << std::endl;
	std::cout << " 7)By Video memory" << std::endl;
	std::cout << " 8)By value" << std::endl;
	std::cout << " 9)By count" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "**********************************" << std::endl;
}

void printAction()
{
	std::cout << "\n**********************************" << std::endl;
	std::cout << "Action with record:" << std::endl;
	std::cout << " 1)Print" << std::endl;
	std::cout << " 2)Change" << std::endl;
	std::cout << " 3)Delete" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "**********************************" << std::endl;
}

void printBuy(int count)
{
	std::cout << "\n**********************************" << std::endl;
	std::cout << "Command list:" << std::endl;
	for (int i = 1; i < count; i++)  std::cout << " " + std::to_string(i) + ")Buy " + std::to_string(i) + " computer" << std::endl;
	std::cout << " 0)Continue search" << std::endl;
	std::cout << "**********************************" << std::endl;
}

void printChoose(int count)
{
	std::cout << "\n**********************************" << std::endl;
	std::cout << "Command list:" << std::endl;
	for (int i = 1; i < count; i++)  std::cout << " " + std::to_string(i) + ")Choose " + std::to_string(i) + " computer" << std::endl;
	std::cout << " 0)Continue search" << std::endl;
	std::cout << "**********************************" << std::endl;
}

void printPrint()
{
	std::cout << "\n**********************************" << std::endl;
	std::cout << "Command list:" << std::endl;
	std::cout << " 1)Simple" << std::endl;
	std::cout << " 2)Sort and print" << std::endl;
	std::cout << " 3)Subset" << std::endl;
	std::cout << " 0)Exit" << std::endl;
	std::cout << "**********************************" << std::endl;
}

std::string output_file_name()
{
	std::string name;
	std::cout << "Enter file name(empty string = 'defaulname'): " << std::endl;
	std::getline(std::cin, name);
	std::getline(std::cin, name);
	if (name == "") name = "defaultname";
	return name + ".txt";
}

std::string input_file_name()
{
	std::fstream f;
	std::string res;
	std::cout << "Enter text file name(empty string = 'defaultname'): ";
	std::getline(std::cin, res);
	std::getline(std::cin, res);
	f.open(res + ".txt");
	while (!f.is_open() && res != "")
	{
		std::cout << "There are no such file, repeat input(empty string = 'defaultname'): ";
		std::getline(std::cin, res);
		f.open(res + ".txt");
	};
	f.close();
	return (res == "") ? "defaultname.txt" : res + ".txt";
}


//рекурсия


int main()
{
	MyContainer cont = MyContainer();
	MyContainer subcont = MyContainer();
	std::fstream f;
	std::string str;
	int n, a, b;
	bool found;
	int money = 10000;
	std::string fStoke = "stoke.txt";
	std::string fHistory = "history.txt";
	std::vector<Computer>::iterator it;
	

	//Downloading
	cont.fileInput(std::fstream(fStoke, std::ios::in));

	while (true)
	{
		printManagerOrClient();
		n = inputInt("Enter the command: ", 0, 2);
		if (n == 1)//MANAGER
		{
			while (true)
			{
				printManagerMenu();
				n = inputInt("Enter the command: ", 0, 4);

				if (n == 0)//EXIT
				{
					break;
				}
				switch (n)
				{
				case 1://ADD
					try { cont.add(inputComputer());
					cont.fileOutput(std::fstream(fStoke, std::ios::out));
					}
					catch (const char*) {}
					break;
				case 2://PRINT
					printPrint();
					n = inputInt("Enter the command: ", 0, 3);
					switch (n)
					{
					case 1://SIMPLE
						consoleOutput(cont);
						break;
					case 2://SORTED
						printMenuFindParam();
						n = inputInt("Enter the command: ", 0, 9);
						switch (n)
						{
						case 1://CODE
							cont.sort(CodeComp());
							consoleOutput(cont);
							break;
						case 2://MARK
							cont.sort(MarkComp());
							consoleOutput(cont);
							break;
						case 3://PROC
							cont.sort(ProcComp());
							consoleOutput(cont);
							break;
						case 4://FREQ
							cont.sort(FreqComp());
							consoleOutput(cont);
							break;
						case 5://RAM
							cont.sort(RAMComp());
							consoleOutput(cont);
							break;
						case 6://HDD
							cont.sort(HDDComp());
							consoleOutput(cont);
							break;
						case 7://VM
							cont.sort(VMComp());
							consoleOutput(cont);
							break;
						case 8://VALUE
							cont.sort(ValueComp());
							consoleOutput(cont);
							break;
						case 9://COUNT
							cont.sort(CountComp());
							consoleOutput(cont);
							break;
						case 0://EXIT
							break;
						}
						break;
					case 3://SUBSET
						printMenuFindParam();
						n = inputInt("Enter the command: ", 0, 9);
						switch (n)
						{
						case 1://CODE
							subcont = cont.findSubSetByCode(inputInt("Enter code: "));
							consoleOutput(subcont);
							break;
						case 2://MARK
							std::cout << "Enter mark: ";
							std::cin >> str;
							subcont = cont.findSubSetByMark(str);
							consoleOutput(subcont);
							break;
						case 3://PROC
							std::cout << "Enter processor type: ";
							std::cin >> str;
							subcont = cont.findSubSetByProc(str);
							consoleOutput(subcont);
							break;
						case 4://FREQ
							subcont = cont.findSubSetByFreq(inputInt("Enter frequency: ", 0));
							consoleOutput(subcont);
							break;
						case 5://RAM
							subcont = cont.findSubSetByRAM(inputInt("Enter ram amount: ", 0));
							consoleOutput(subcont);
							break;
						case 6://HDD
							subcont = cont.findSubSetByHDD(inputInt("Enter hdd capacity: ", 0));
							consoleOutput(subcont);
							break;
						case 7://VM
							subcont = cont.findSubSetByVM(inputInt("Enter vm amount: ", 0));
							consoleOutput(subcont);
							break;
						case 8://VALUE
							subcont = cont.findSubSetByValue(inputInt("Enter value: ", 0));
							consoleOutput(subcont);
							break;
						case 9://COUNT
							subcont = cont.findSubSetByCount(inputInt("Enter count: ", 0));
							consoleOutput(subcont);
							break;
						case 0://EXIT
							break;
						}
						break;
					case 0:
						break;
					}
					break;
				case 3://FIND
					printMenuFindParam();
					n = inputInt("Enter the command: ", 0, 9);
					if (n == 0)//EXIT
					{
						break;
					}
					switch (n)
					{
					case 1://CODE
						subcont = cont.findSubSetByCode(inputInt("Enter code: "));
						break;
					case 2://MARK
						std::cout << "Enter mark: ";
						std::cin >> str;
						subcont = cont.findSubSetByMark(str);
						break;
					case 3://PROC
						std::cout << "Enter processor type: ";
						std::cin >> str;
						subcont = cont.findSubSetByProc(str);
						break;
					case 4://FREQ
						subcont = cont.findSubSetByFreq(inputInt("Enter frequency: ", 0));
						break;
					case 5://RAM
						a = inputInt("Enter lower bound: ", 0);
						b = inputInt("Enter higher bound: ", a + 1);
						subcont = cont.findSubSetByRAMBounds(a, b);
						break;
					case 6://HDD
						subcont = cont.findSubSetByHDD(inputInt("Enter hdd capacity: ", 0));
						break;
					case 7://VM
						subcont = cont.findSubSetByVM(inputInt("Enter vm amount: ", 0));
						break;
					case 8://VALUE
						a = inputInt("Enter lower bound: ", 0);
						b = inputInt("Enter higher bound: ", a + 1);
						subcont = cont.findSubSetByValueBounds(a, b);
						break;
					case 9://COUNT
						subcont = cont.findSubSetByCount(inputInt("Enter count: ", 0));
						break;
					}
					if (subcont.vectSize() != 0)
					{
						consoleOutput(subcont);
						printChoose(subcont.vectSize() + 1);
						n = inputInt("Enter the command: ", 0, subcont.vectSize() + 1);
						if (n == 0) break;
						it = cont.findit(subcont.getElem(n - 1));
						while (true)
						{
							std::cout << "\n Record found \n";
							printAction();
							n = inputInt("Enter the command: ", 0, 3);
							if (n == 0) break;
							switch (n)
							{
							case 1:
								std::cout << *(it);
								break;
							case 2:
								try
								{
									*it = inputComputer(*it);
									cont.fileOutput(std::fstream(fStoke, std::ios::out));
									break;
								}
								catch (const char*)
								{
									break;
								}
							case 3:
								cont.remove(it);
								cont.fileOutput(std::fstream(fStoke, std::ios::out));
								break;
							}
							if (n == 3) break;
						}

					}
					else
						std::cout << "Computers not found \n";
					break;
					
				case 4://PRINT HISTORY
					f.open(fHistory, std::ios::in);
					if (!f.is_open())
					{
						break;
					}
					while (std::getline(f, str))
					{
						std::cout << str << std::endl;
					}
					f.close();
					break;
				}
			}
		}
		else if (n == 2)//CLIENT
		{
			while (true)
			{
				printClientMenu();
				n = inputInt("Enter the command: ", 0, 9);
				if (n == 0)//EXIT
				{
					break;
				}
				switch (n)
				{
				case 1://CODE
					subcont = cont.findSubSetByCode(inputInt("Enter code: "));
					break;
				case 2://MARK
					std::cout << "Enter mark: ";
					std::cin >> str;
					subcont = cont.findSubSetByMark(str);
					break;
				case 3://PROC
					std::cout << "Enter processor type: ";
					std::cin >> str;
					subcont = cont.findSubSetByProc(str);
					break;
				case 4://FREQ
					subcont = cont.findSubSetByFreq(inputInt("Enter frequency: ", 0));
					break;
				case 5://RAM
					a = inputInt("Enter lower bound: ", 0);
					b = inputInt("Enter higher bound: ", a+1);
					subcont = cont.findSubSetByRAMBounds(a, b);
					break;
				case 6://HDD
					subcont = cont.findSubSetByHDD(inputInt("Enter hdd capacity: ", 0));
					break;
				case 7://VM
					subcont = cont.findSubSetByVM(inputInt("Enter vm amount: ", 0));
					break;
				case 8://VALUE
					a = inputInt("Enter lower bound: ", 0);
					b = inputInt("Enter higher bound: ", a + 1);
					subcont = cont.findSubSetByValueBounds(a, b);
					break;
				case 9://COUNT
					subcont = cont.findSubSetByCount(inputInt("Enter count: ", 0));
					break;
				}
				if (subcont.vectSize() != 0)
				{
					consoleOutput(subcont);
					printBuy(subcont.vectSize() + 1);
					n = inputInt("Enter the command: ", 0, subcont.vectSize() + 1);
					if (n == 0) continue;//SKIP
					//BUY
					it = cont.findit(subcont.getElem(n-1));

					if ((*it).count == 0)
					{
						std::cout << std::endl << "No instances available" << std::endl;
					}
					else if (money >= (*it).value)
					{
						(*it).count--;
						money -= (*it).value;
						f.open(fHistory, std::ios_base::app);
						f << "Computer #" + std::to_string((*it).code) + " was sold for " + std::to_string((*it).value) << std::endl;
						f.close();

						cont.fileOutput(std::fstream(fStoke, std::ios::out));
					}
					else
						std::cout << "Not enough money\n";
					
				}
				else
					std::cout << "Computers not found \n";
			}
		}
		else//EXIT
		{
			return 0;
		}

	}

}