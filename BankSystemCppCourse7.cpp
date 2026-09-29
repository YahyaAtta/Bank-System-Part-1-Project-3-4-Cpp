#include<iostream>
#include<vector>
#include<iomanip>
#include<fstream>
#include<string>

using namespace std;

const string ClientsFileName = "Clients.txt";

struct sClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

enum enColor{
	Red = 1 , White = 2
};
enum enMainMenuOption {
	eClientList = 1, eClientAdd = 2, eClientDelete = 3, eClientUpdate = 4, eClientFind = 5, eTransactions = 6, eExit = 7
};

enum enTransactionOption {
	eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eShowMainMenu = 4
};

void ShowMainMenuOptions();

void ShowTransactionsMenuOptions();


void ResetScreen() {

	system("cls");

}

void ChangeColorText(enColor Color) {
	switch (Color) {
	case enColor::Red:
		system("color 04"); break;
	case enColor::White:
		system("color 07"); break;
	   }
}

void GoBackToMainMenu() {

	cout << "\n\nPress Any Key To go back to Main Menu...";
	system("pause>0");
	ShowMainMenuOptions();

}
void TitleScreen(string Title) {

	cout << "\n------------------------------------------------\n\n";
	cout << "\t\t" << Title << " Screen \n";
	cout << "\n------------------------------------------------\n";

}
void TitleScreenExit(string Title)
{

	cout << "\n------------------------------------------------\n\n";
	cout << "\t\t" << Title << "\n";
	cout << "\n------------------------------------------------\n";

}
vector<string> SplitString(string S1, string Sperators = "#//#")
{
	short pos = 0;
	string sWord = "";
	vector<string> vStrings;
	while ((pos = S1.find(Sperators)) != string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vStrings.push_back(sWord);
		}
		S1.erase(0, pos + Sperators.length());
	}
	if (S1 != "")
	{
		vStrings.push_back(S1);
	}
	return vStrings;
}
string ConvertRecordToLine(sClient sClient, string Sperators = "#//#")
{
	string StClientRecord = "";

	StClientRecord += sClient.AccountNumber + Sperators;
	StClientRecord += sClient.PinCode + Sperators;
	StClientRecord += sClient.Name + Sperators;
	StClientRecord += sClient.Phone + Sperators;
	StClientRecord += to_string(sClient.AccountBalance);

	return StClientRecord;
}
sClient ConvertLineToRecord(string S1, string Sperators = "#//#")
{
	vector<string> vClients = SplitString(S1, Sperators);
	sClient Client;
	Client.AccountNumber = vClients[0];
	Client.PinCode = vClients[1];
	Client.Name = vClients[2];
	Client.Phone = vClients[3];
	Client.AccountBalance = stod(vClients[4]);

	return Client;
}
vector<sClient> LoadClientsDataFromFile(string FileName)
{
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	vector<sClient> vClients;
	if (MyFile.is_open())
	{
		string Line;

		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);

			vClients.push_back(Client);
		}

		MyFile.close();
	}
	return vClients;
}

void PrintTransactionRecordLine(const sClient& Client) {
	cout << "| " << left << setw(16) << Client.AccountNumber;
	cout << "| " << left << setw(32) << Client.Name;
	cout << "| " << left << setw(13) << Client.AccountBalance;
	cout << endl;
}

void PrintClientRecordLine(const sClient& Client) {
	cout << "| " << left << setw(16) << Client.AccountNumber;
	cout << "| " << left << setw(13) << Client.PinCode;
	cout << "| " << left << setw(32) << Client.Name;
	cout << "| " << left << setw(12) << Client.Phone;
	cout << "| " << left << setw(13) << Client.AccountBalance;
	cout << endl;
}
void PrintClientCard(const sClient& Client) {
	cout << "\nThe Following are the client details:\n";
	cout << "------------------------------------------\n";
	cout << "Account Number: " << Client.AccountNumber << endl;
	cout << "Pin Code: " << Client.PinCode << endl;
	cout << "Name: " << Client.Name << endl;
	cout << "Phone: " << Client.Phone << endl;
	cout << "Account Balance: " << Client.AccountBalance << "\n\n";
	cout << "------------------------------------------\n";
}
bool MarkClientDataForDelete(vector<sClient>& vClients, string AccountNumber)
{
	for (sClient& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			Client.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

sClient ChangeClientData(string AccountNumber) {

	sClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "\nEnter Pin Code? ";

	getline(cin >> ws, Client.PinCode);

	cout << "\nEnter Name? ";

	getline(cin, Client.Name);

	cout << "\nEnter Phone? ";

	getline(cin, Client.Phone);

	cout << "\nEnter Account Balance? ";

	cin >> Client.AccountBalance;

	return Client;
}
vector<sClient> SaveClientDataToFile(string FileName, vector<sClient>& vClients) {

	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (sClient& C : vClients) {
			if (C.MarkForDelete == false) {
				string Line;
				Line = ConvertRecordToLine(C);
				MyFile << Line << endl;
			}
		}

		MyFile.close();
	}

	return vClients;

}
void ShowAllClientsScreen()
{
	ResetScreen();
	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";

	cout << "\n_____________________________________________";
	cout << "___________________________________________________________________________\n\n";
	cout << "| " << left << setw(16) << "Account Number";
	cout << "| " << left << setw(13) << "Pin Code";
	cout << "| " << left << setw(32) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(13) << "Account Balance";
	cout << "\n_____________________________________________";
	cout << "___________________________________________________________________________\n\n";

	if (vClients.size() == 0)

		cout << "\n\t\t\t\t\tThere are no Clients in the System....\n";

	else

		for (const sClient& Client : vClients)
			PrintClientRecordLine(Client);

	cout << "\n_____________________________________________";
	cout << "___________________________________________________________________________\n\n";
}
bool ClientExistsByAccountNumber(string FileName, string AccountNumber) {
	fstream MyFile;

	vector<sClient> vClients;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {

		string Line;

		sClient Client;

		while (getline(MyFile, Line)) {

			Client = ConvertLineToRecord(Line);

			if (Client.AccountNumber == AccountNumber) {

				MyFile.close();

				return true;
			}
			vClients.push_back(Client);

		}

		MyFile.close();
	}

	return false;
}
string ReadAccountNumber() {

	string AccountNumber;

	cout << "\nPlease Enter Account Number? ";

	getline(cin >> ws, AccountNumber);

	return AccountNumber;
}
bool FindClientDataByAccountNumber(vector<sClient>& vClients, sClient& Client, string AccountNumber)
{
	for (sClient& C : vClients) {

		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;
		}

	}

	return false;

}
void FindAccountNumber(vector<sClient>& vClients, string AccountNumber) {

	sClient Client;

	if (FindClientDataByAccountNumber(vClients, Client, AccountNumber)) {

		PrintClientCard(Client);

	}
	else {

		cout << "\nThe Account Number (" << AccountNumber << ") is Not Found!\n\n";
	}

}
void FindClientScreen() {

	ResetScreen();

	TitleScreen("Find Client ");

	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	string AccountNumber = ReadAccountNumber();

	FindAccountNumber(vClients, AccountNumber);

}
sClient ReadNewClient() {

	sClient Client;

	cout << "\nEnter Account Number? ";

	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(ClientsFileName, Client.AccountNumber))
	{
		cout << "Client With " << "[" << Client.AccountNumber << "] already exists, Enter Another Account Number? ";

		getline(cin >> ws, Client.AccountNumber);

	}
	cout << "\nEnter Pin Code? ";

	getline(cin, Client.PinCode);

	cout << "\nEnter Name? ";

	getline(cin, Client.Name);

	cout << "\nEnter Phone? ";

	getline(cin, Client.Phone);

	cout << "\nEnter Account Balance? ";

	cin >> Client.AccountBalance;

	return Client;

}
void AddDataLineToFile(string FileName, string DataLine) {

	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open()) {
		MyFile << DataLine << endl;
		MyFile.close();
	}

}

void AddClient(vector<sClient>& vClients) {

	sClient Client = ReadNewClient();

	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

	cout << "Client Added Successfully, do you want to add more clients? Y/N ";

}
void AddNewClients() {

	char Answer = 'Y';
	do {
		ResetScreen();

		TitleScreen("Add New Clients");

		cout << "\nAdding New Client:\n\n";

		vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

		AddClient(vClients);

		cin >> Answer;

	} while (toupper(Answer) == 'Y');

}
void AddClientsScreen() {

	AddNewClients();
}

bool DeleteClientByAccountNumber(vector<sClient>& vClients, string AccountNumber)
{
	sClient Client;

	char Answer = 'N';

	if (FindClientDataByAccountNumber(vClients, Client, AccountNumber)) {

		PrintClientCard(Client);

		cout << "\nAre You Sure you want to delete this client y/n? ";

		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {

			MarkClientDataForDelete(vClients, AccountNumber);

			SaveClientDataToFile(ClientsFileName, vClients);

			cout << "\nClient Deleted Successfully\n";

			return true;
		}
	}

	else {

		cout << "\nThe Account Number (" << AccountNumber << ") is Not Found!\n";

		return false;

	}

}
void DeleteClientScreen()
{
	ResetScreen();

	TitleScreen("Delete Client");
	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	string AccountNumber = ReadAccountNumber();

	DeleteClientByAccountNumber(vClients, AccountNumber);
}
bool UpdateScreenByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	char Answer = 'n';

	sClient Client;

	if (FindClientDataByAccountNumber(vClients, Client, AccountNumber))
	{
		PrintClientCard(Client);

		cout << "\nAre You Sure you want to update this client y/n? ";

		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber) {

					C = ChangeClientData(AccountNumber);

					break;
				}
			}

			SaveClientDataToFile(ClientsFileName, vClients);

			cout << "\nClient Updated Successfully\n";

			return true;

		}

	}

	else {

		cout << "\nThe Account Number (" << AccountNumber << ") is Not Found!\n";

		return false;

	}

}

void UpdateClientScreen() {

	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	ResetScreen();

	TitleScreen("Update Client");

	sClient Client;

	char Answer = 'N';

	string AccountNumber = ReadAccountNumber();

	UpdateScreenByAccountNumber(AccountNumber, vClients);

}

short CheckNumberValidation(string Message, short From, short To)
{
	short Number;

	cout << "\n\nChoose What do you want to do [1 to " << To << "] ? ";

	cin >> Number;


	while (cin.fail() || (Number < From || Number > To))
	{
		
      ChangeColorText(enColor::Red); 
		
		if(!cin.fail())
		{
			
	   cout << "Invalid Input Please Choose Numbers Between 1 to " << To << "\n";
			
		cin >> Number;
			
		}
	else 
		{
		cin.clear();

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << Message << endl;

		cin >> Number;
			
		}
		
	}

	ChangeColorText(enColor::White); 

	return Number;
}


enMainMenuOption ReadMainMenuOption(short From, short To)
{
	return (enMainMenuOption)CheckNumberValidation("This is Not a Number Please Enter a Number:", From, To);
}

void ExitScreen() {

	TitleScreenExit("Program Ends : -)");

}

void GoBackToTransactionMenu() {

	cout << "\n\nPress Any Key To go back to Transactions Menu...";

	system("pause>0");

	ShowTransactionsMenuOptions();

}

double ReadAmount()
{

	double DepositAmount = 0;

	cout << "\nPlease enter deposit amount? ";

	cin >> DepositAmount;
	while (cin.fail() || (DepositAmount<=0))
	{
		
      ChangeColorText(enColor::Red); 
		
		if(!cin.fail())
		{
			
	   cout << "Invalid Input Please Enter a Number? " << To << "\n";
			
		cin >> DepositAmount;
			
		}
	else 
		{
		cin.clear();

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "The Amount Can't Be Zero or Less Please Enter Amount Greater than Zero? " << endl;

		cin >> DepositAmount;
			
		}
		
	}



	ChangeColorText(enColor::White); 
	return DepositAmount;
}

bool DepositBalanceToClientByAccountNumber(vector<sClient>& vClients, double Amount, string AccountNumber) {

	char Answer = 'n';

	cout << "\nAre You Sure you want to perform this transaction? y/n ?\n";

	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		for (sClient& C : vClients) {

			if (C.AccountNumber == AccountNumber) {
				C.AccountBalance += Amount;
				SaveClientDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New Balance " << C.AccountBalance << "\n";
				return true;
			}

		}
		return false;
	}


}


void DepositClient() {

	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	string AccountNumber = ReadAccountNumber();

	sClient Client;

	double DepositAmount;

	while (!FindClientDataByAccountNumber(vClients, Client, AccountNumber))
	{

		cout << "Client with [" << AccountNumber << "] does not exists\n\n";

		AccountNumber = ReadAccountNumber();

	}

	PrintClientCard(Client);

	DepositAmount = ReadAmount();

	DepositBalanceToClientByAccountNumber(vClients, DepositAmount, AccountNumber);

}
void DepositOperationScreen() {

	TitleScreen("Deposit");

	DepositClient();

}

void WithDrawOperation() {

	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	string AccountNumber;

	sClient Client;

	double Amount;

	AccountNumber = ReadAccountNumber();

	while (!FindClientDataByAccountNumber(vClients, Client, AccountNumber))
	{

		cout << "Client with [" << AccountNumber << "] does not exists\n\n";

		AccountNumber = ReadAccountNumber();

	}

	PrintClientCard(Client);

	Amount = ReadAmount();
	while (Amount > Client.AccountBalance) {
		cout << "Excceed Balance The Maximum Balance is " << Client.AccountBalance << "\n\n";
		Amount = ReadAmount();
	}

	DepositBalanceToClientByAccountNumber(vClients, Amount * -1, AccountNumber);
}

void WithDrawOperationScreen() {

	TitleScreen("Withdraw");

	WithDrawOperation();

}


void ShowTotalBalances() {

	ResetScreen();

	double TotalBalances = 0;

	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";

	cout << "\n_____________________________________________";
	cout << "___________________________________________________________________________\n\n";

	cout << "| " << left << setw(16) << "Account Number";
	cout << "| " << left << setw(32) << "Client Name";
	cout << "| " << left << setw(13) << "Account Balance";

	cout << "\n_____________________________________________";
	cout << "___________________________________________________________________________\n\n";

	if (vClients.size() == 0)

		cout << "\n\t\t\t\t\tThere are no Clients in the System....\n";

	else
		for (const sClient& Client : vClients)
		{
			PrintTransactionRecordLine(Client);
			TotalBalances += Client.AccountBalance;
		}

	cout << "\n_____________________________________________";
	cout << "___________________________________________________________________________\n\n";

	cout << "\n\n";

	cout << "\t\t\t\t\t\tTotal Balances = ";

	cout << TotalBalances << endl;
}

void PerformTransactionsMenuOption(enTransactionOption enTransactionOption)
{

	switch (enTransactionOption)
	{

	case enTransactionOption::eDeposit:

		ResetScreen();
		DepositOperationScreen();
		GoBackToTransactionMenu();
		break;

	case enTransactionOption::eWithdraw:

		ResetScreen();
		WithDrawOperationScreen();
		GoBackToTransactionMenu();
		break;

	case enTransactionOption::eTotalBalances:

		ResetScreen();
		ShowTotalBalances();
		GoBackToTransactionMenu();
		break;

	case enTransactionOption::eShowMainMenu:

		ShowMainMenuOptions();
		break;

	}
}

enTransactionOption ReadTransactionsMenuOption(short From, short To) {

	return (enTransactionOption)CheckNumberValidation("This is Not a Number Please Enter a Number:", From, To);

}

void ShowTransactionsMenuOptions() {
	ResetScreen();
	cout << "\n==============================================\n\n";
	cout << "\tTransactions Menu Screen\n";
	cout << "\n==============================================\n\n";
	cout << "\t[1] Desposit.\n";
	cout << "\t[2] WithDraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "\n==============================================\n\n";
	PerformTransactionsMenuOption(ReadTransactionsMenuOption(1, 4));
}
void PerformMainMenuOption(enMainMenuOption enOption) {

	switch (enOption) {

	case enMainMenuOption::eClientList:

		ResetScreen();
		ShowAllClientsScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOption::eClientAdd:

		ResetScreen();
		AddClientsScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOption::eClientDelete:

		ResetScreen();
		DeleteClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOption::eClientUpdate:

		ResetScreen();
		UpdateClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOption::eClientFind:

		ResetScreen();
		FindClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOption::eTransactions:

		ShowTransactionsMenuOptions();
		break;

	case enMainMenuOption::eExit:

		ResetScreen();
		ExitScreen();
		break;

	}
}

void ShowMainMenuOptions() {

	ResetScreen();

	cout << "\n==============================================\n\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "\n==============================================\n\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "\n==============================================\n\n";

	PerformMainMenuOption(ReadMainMenuOption(1, 7));

}


void InitScreen() {
	cout << "\n==============================================\n\n";
	cout << "\t\t BANK SYSTEM\n";
	cout << "\n==============================================\n\n";
	cout << "\n\tPress Any Key To Start Program.....";
	system("pause>0");
	ShowMainMenuOptions();

}

int main()
{
	srand((unsigned)time(NULL));

	InitScreen();

	system("pause>0");

}
