#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include <iomanip>
#include<cstdio>
#include <ctime>
using namespace std;
struct Stock
{
	char name[50];
	int quantity;
};
struct inListdata
{
	Stock stock[1000];
	int nosp;
};
struct Product
{
	char name[50];
	double price;
	int quantity;
	double discount;
	double netprice;
	int type;
};
struct parTot
{
	Product partial[1000];
	Product total;
	bool nop;
};
void main_display()
{
	cout << "\n\n\t\t     ******Hakeem Sons Super Store******";
	cout << "\n\n\n\t\t*********************************************";
	cout << "\n\t\t                 Main Menu                  ";
	cout << "\n\t\t*********************************************";
	cout << "\n\n\t\t\t\t1.Customer\n";
	cout << "\t\t\t\t2.Admintrator\n";
	cout << "\t\t\t\t3.Exit!\n";
}
inListdata stockData(inListdata &s)
{
	int i = 0;
	ifstream sdata("Stock Data.txt");
	if (sdata.is_open())
	{
		while (sdata.peek() != EOF)
		{
			sdata.getline(s.stock[i].name, 51, ':');
			sdata >> s.stock[i].quantity;
			sdata.ignore(1);
			i++;
		}
		s.nosp = i;
		sdata.close();
	}
	else
	{
		cout << "Error Reading File" << endl;
		throw 0;
	}
	return s;
}
void showStock(inListdata &s)
{
	stockData(s);
	for (int i = 0; i < s.nosp; i++)
	{
		cout << s.stock[i].name << ": " << s.stock[i].quantity << endl;
	}
	system("pause");
}
bool stockCheck(parTot &p, int num)
{
	inListdata s;
	stockData(s);
	for (int i = 0; i < s.nosp; i++)
	{
		if (strcmp(p.partial[num].name, s.stock[i].name) == 0)
		{
			return true;
		}
	}
	return false;
}
int stockMatch(parTot &p, int num)
{
	inListdata s;
	stockData(s);
	int i = 0;
	while (i < s.nosp)
	{
		if (strcmp(p.partial[num].name, s.stock[i].name) == 0)
		{
			return i;
		}
		i++;
	}
}
bool isStockAvailable(char *c, inListdata &s)
{
	stockData(s);
	int i = 0;
	while (i < s.nosp)
	{
		if (strcmp(c, s.stock[i].name) == 0)
		{
			return true;
		}
		i++;
	}
	return false;
}
void writeAgain(inListdata &s)
{
	ofstream sdata("Stock Data.txt");
	if (sdata.is_open())
	{
		for (int i = 0; i < s.nosp; i++)
		{
			sdata << s.stock[i].name << ": ";
			sdata << s.stock[i].quantity << endl;
		}
		sdata.close();
	}
	else
	{
		cout << "Error Writting File" << endl;
		throw 0;
	}
}
parTot customerProd(parTot &p, inListdata &s)
{
	int i = 0;
	char argument;
	p.total.price = 0;
	p.total.quantity = 0;
	p.total.discount = 0;
	p.total.netprice = 0;
	p.nop = 0;
	stockData(s);
	while (1 == 1)
	{
		cout << "\t\t\tEnter the product Name= ";
		cin.getline(p.partial[i].name, 51);
		if (stockCheck(p, i) == 0)
		{
			cout << "\t\t\tSorry! Product Not Available" << endl;
			cout << "\n\tDo you want to enter more products , Press Y or y\n\tOtherwise any key\n\tEnter input: ";
			cin >> argument;
			cin.ignore(1);
			if (argument == 'y' || argument == 'Y')
			{
				continue;
			}
			else
			{
				p.nop++;
				break;
			}
		}
		cout << "\t\t\tEnter the Price of Product= ";
		cin >> p.partial[i].price;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');
			system("cls");
			cout << "Invalid Input!" << endl;
			continue;
		}
		p.total.price = p.total.price + p.partial[i].price;
		cout << "\t\t\tEnter the total numbers of Product= ";
		cin >> p.partial[i].quantity;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');
			system("cls");
			cout << "Invalid Input!" << endl;
			continue;
		}
		if (s.stock[stockMatch(p, i)].quantity - p.partial[i].quantity < 0)
		{
			cout << "\t\t\tSorry! Enough Quantities are not Available" << endl;
			cout << "\n\tOnly " << s.stock[stockMatch(p, i)].quantity << " are Available;\n\tIf you want to enter " << s.stock[stockMatch(p, i)].quantity << ", Press Y or y\n\tIf you  to continue other product , Press C or c\n\tOtherwise Press any key\n\tEnter input: ";
			cin >> argument;
			if (argument == 'y' || argument == 'Y')
			{
				p.partial[i].quantity = s.stock[stockMatch(p, i)].quantity;
				s.stock[stockMatch(p, i)].quantity = 0;
			}
			else if (argument == 'c' || argument == 'C')
			{
				continue;
			}
			else
			{
				p.nop++;
				break;
			}
		}
		else
		{
			s.stock[stockMatch(p, i)].quantity = s.stock[stockMatch(p, i)].quantity - p.partial[i].quantity;
		}
		p.total.quantity = p.total.quantity + p.partial[i].quantity;
		cout << "\t\t\tEnter the % Discount on Product= ";
		cin >> p.partial[i].discount;
		p.total.discount = p.total.discount + p.partial[i].discount;
		p.partial[i].netprice = (p.partial[i].quantity * p.partial[i].price) - (p.partial[i].price * (p.partial[i].discount / 100));
		p.total.netprice = p.total.netprice + p.partial[i].netprice;
		cout << "\n\tDo you want to enter more products , Press Y or y otherwise any key: ";
		cin >> argument;
		if (argument == 'y' || argument == 'Y')
		{
			i++;
		}
		else
		{
			break;
		}
		cin.ignore(1);
		cout << endl;
	}
	p.total.type = i + 1;
	writeAgain(s);
	system("cls");
	return p;
}
inListdata deleteProd(char *c, inListdata &s)
{
	stockData(s);
	int i = 0;
	bool f = 0;
	while (i < s.nosp)
	{
		if (strcmp(c, s.stock[i].name) == 0)
		{
			f = 1;
			break;
		}
		i++;
	}
	if (f == 1)
	{
		s.nosp--;
		int j = i + 1;
		while (i < s.nosp)
		{
			strcpy_s(s.stock[i].name, s.stock[j].name);
			s.stock[i].quantity = s.stock[j].quantity;
			i++;
			j++;
		}
	}
	else
	{
		cout << "\t\t\t\tProduct is not Available in Stock" << endl;
		system("pause");
	}
	writeAgain(s);
	return s;
}
inListdata updateProd(char *c, int quan, inListdata &s)
{
	stockData(s);
	int i = 0;
	while (i < s.nosp)
	{
		if (strcmp(c, s.stock[i].name) == 0)
		{
			s.stock[i].quantity = quan;
			int f = 1;
			break;
		}
		i++;
	}
	writeAgain(s);
	return s;
}
inListdata addProd(char *c, int quan, inListdata &s)
{
	stockData(s);
	int i = 0;
	int f = 0;
	while (i < s.nosp)
	{
		if (strcmp(c, s.stock[i].name) == 0)
		{
			s.stock[i].quantity = quan + s.stock[i].quantity;
			f = 1;
			break;
		}
		i++;
	}
	if (f == 0)
	{
		s.nosp++;
		strcpy_s(s.stock[s.nosp - 1].name, c);
		s.stock[s.nosp - 1].quantity = quan;
	}
	writeAgain(s);
	return s;
}
int recNo()
{
	int recno = -1;
	ifstream rec("Receipts.txt");
	while (rec.peek() != EOF)
	{
		rec.ignore(500, ':');
		rec.ignore(500, ':');
		rec >> recno;
		rec.ignore(500, ':');
		rec.ignore(500, ':');
		rec.ignore(500, ':');
		rec.ignore(500, ':');
	}
	return recno + 1;
}
void showReceipt(parTot &p)
{
	time_t res = time(0);
	char dt[26];
	ctime_s(dt, 26, &res);
	dt[strlen(dt) - 1] = '\0';
	cout << "********************************************************************************" << endl;
	cout << "|                           Hakeem Sons Super Store                            |" << endl;
	cout << "|                                 Bill Receipt                                 |" << endl;
	cout << "********************************************************************************" << endl;
	cout << "| Date & Time: " << dt << "\t\t\tReceipt No: " << setw(10) << recNo() << " |" << endl;
	cout << "________________________________________________________________________________" << endl;
	cout << "| Quantity | " << "Product Name                   | " << "Price/Each | " << "Discount | " << "Price    |" << endl;
	for (int i = 0; i < p.total.type; i++)
	{
		cout << "________________________________________________________________________________" << endl;
		cout << "| " << setw(8) << left << p.partial[i].quantity << " | " << setw(30) << left << p.partial[i].name << " | " << setw(10) << left << p.partial[i].price << " | " << setw(8) << left << p.partial[i].discount << " | " << setw(8) << left << p.partial[i].netprice << " |" << endl;
	}
	cout << "________________________________________________________________________________" << endl;
	cout << "| Total Types of Products: " << setw(15) << p.total.type << "Total Quantities: " << setw(18) << p.total.quantity << " |" << endl;
	cout << "| Total Discount: " << setw(24) << p.total.discount << "Net Price: " << setw(25) << p.total.netprice << " |" << endl;
	cout << "________________________________________________________________________________" << endl;
	return;
}
void printReceipt(parTot &p)
{
	ofstream rec("Receipts.txt", ios::app);
	time_t res = time(0);
	char dt[26];
	ctime_s(dt, 26, &res);
	dt[strlen(dt) - 1] = '\0';
	rec << "********************************************************************************" << endl;
	rec << "|                           Hakeem Sons Super Store                            |" << endl;
	rec << "|                                 Bill Receipt                                 |" << endl;
	rec << "********************************************************************************" << endl;
	rec << "| Date & Time: " << dt << "\t\t\tReceipt No: " << setw(10) << recNo() << " |" << endl;
	rec << "________________________________________________________________________________" << endl;
	rec << "| Quantity | " << "Product Name                   | " << "Price/Each | " << "Discount | " << "Price    |" << endl;
	for (int i = 0; i < p.total.type; i++)
	{
		rec << "________________________________________________________________________________" << endl;
		rec << "| " << setw(8) << left << p.partial[i].quantity << " | " << setw(30) << left << p.partial[i].name << " | " << setw(10) << left << p.partial[i].price << " | " << setw(8) << left << p.partial[i].discount << " | " << setw(8) << left << p.partial[i].netprice << " |" << endl;
	}
	rec << "________________________________________________________________________________" << endl;
	rec << "| Total Types of Products: " << setw(15) << p.total.type << "Total Quantities: " << setw(18) << p.total.quantity << " |" << endl;
	rec << "| Total Discount: " << setw(24) << p.total.discount << "Net Price: " << setw(25) << p.total.netprice << " |" << endl;
	rec << "________________________________________________________________________________" << endl;
	rec << endl;
	rec.close();
	return;
}
int main()
{
	while (1 == 1)
	{
		try
		{
			parTot prod;
			inListdata stock;
			int rand, prodquan;
			char prodname[50], argument;
			int recno = 0;
			while (1 == 1)
			{
				main_display();
				cout << "\t\t\t\tEnter your choice (1-3)= ";
				cin >> rand;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(std::numeric_limits<int>::max(), '\n');
					system("cls");
					cout << "Invalid Input!" << endl;
					continue;
				}
				cin.ignore(1);
				system("cls");
				if (rand == 1)
				{
					customerProd(prod, stock);
					if (prod.nop != 1)
					{
						showReceipt(prod);
						printReceipt(prod);
						recno++;
					}
				}
				else if (rand == 2)
				{
					while (1 == 1)
					{
						cout << "\t\t\t\t1.Add a new Product\n\t\t\t\t2.Update quantity of a Product\n\t\t\t\t3.Delete a Product\n\t\t\t\t4.Show Stock\n\t\t\t\t5.Back to Main Menu\n";
						cout << "\t\t\t\tEnter your choice (1-3)= ";
						cin >> rand;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(std::numeric_limits<int>::max(), '\n');
							system("cls");
							cout << "Invalid Input!" << endl;
							continue;
						}
						cin.ignore(1);
						if (rand == 1)
						{
							cout << "\t\t\t\tEnter product you want to add: ";
							cin.getline(prodname, 51);
							cout << "\t\t\t\tEnter quantity of that product: ";
							cin >> prodquan;
							if (cin.fail())
							{
								cin.clear();
								cin.ignore(std::numeric_limits<int>::max(), '\n');
								system("cls");
								cout << "Invalid Input!" << endl;
								continue;
							}
							cin.ignore(1);
							addProd(prodname, prodquan, stock);
						}
						else if (rand == 2)
						{
							cout << "\t\t\t\tEnter product you want to update: ";
							cin.getline(prodname, 51);
							if (isStockAvailable(prodname, stock) == 1)
							{
								cout << "\t\t\t\tEnter quantity new product: ";
								cin >> prodquan;
								if (cin.fail())
								{
									cin.clear();
									cin.ignore(std::numeric_limits<int>::max(), '\n');
									system("cls");
									cout << "Invalid Input!" << endl;
									continue;
								}
								cin.ignore(1);
								updateProd(prodname, prodquan, stock);
							}
							else
							{
								cout << "\t\t\t\tProduct is not Available in Stock" << endl;
								system("pause");
							}
						}
						else if (rand == 3)
						{
							cout << "\t\t\t\tEnter product you want to delete: ";
							cin.getline(prodname, 51);
							deleteProd(prodname, stock);
						}
						else if (rand == 4)
						{
							system("cls");
							showStock(stock);
						}
						else if (rand == 5)
						{
							break;
						}
						else
						{
							system("cls");
							cout << "Invalid Input!" << endl;
							continue;
						}
						system("cls");
						break;
					}
					continue;
				}
				else if (rand == 3)
				{
					break;
				}
				else
				{
					cout << "Invalid Input!" << endl;
					continue;
				}
				cout << "If you want to exit, Press 'E' or 'e'\nFor continue, Press anay other character\nEnter input: ";
				cin >> argument;
				cin.ignore(1);
				if (argument == 'e' || argument == 'E')
				{
					break;
				}
				else
				{
					system("cls");
				}
			}
		}
		catch (int x)
		{
			continue;
		}
		break;
	}
	return 0;
}