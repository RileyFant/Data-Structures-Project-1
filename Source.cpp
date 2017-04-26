/**
* Riley Fant -- 112936608
* Project #1
* CS 2413, Dr. Sridhar Radhakrishnan
* January 28, 2015
*/
#include <iostream>
using namespace std;

/*Represents a single user account with appropriate fields*/
class AccountInfo {
	friend ostream& operator << (ostream& s, AccountInfo* a);
private:
	char* _userLoginName; // store the login name of the user 
	char* _home; // home directory of the user
	unsigned int _uid; //user identifier
	unsigned int _gid; // identifier of user’s primary group 
	char* _password; // explained later
	char* _shell; // shell of the user
	char* _gecos; // general info of the user
	// other private methods necessary for this class
public:
	AccountInfo();//empty constructor
	AccountInfo(char* userLoginName);//constructor when only userLoginName is given
	AccountInfo(char* userLoginName, char* home, int uid, int gid, char* password, char* shell, char* gecos); //full constructor
	~AccountInfo();//destructor
	/*accessors:*/
	char* getUserLoginName();
	char* getHome();
	int getUserID();
	int getGID();
	char* getPassword();
	char* getShell();
	char* getGecos();
	/*mutators*/
	void setUserID(int newUID);
	void setGID(int newGID);
	void setShell(char* newShell);

};

//overrided ostream (<<) operator for AccountInfo
ostream& operator << (ostream& s, AccountInfo* a) {
	s << "Login: [" << a->getUserLoginName() << "]\nDirectory: [" << a->getHome() << "]\nShell: ["
		<< a->getShell() << "]\nGecos: [" << a->getGecos() << "]";
	return s;
}
/*Definitions of accessors and mutators*/
char* AccountInfo::getUserLoginName() {
	return _userLoginName;
}
char* AccountInfo::getHome() {
	return _home;
}
int AccountInfo::getUserID() {
	return _uid;
}
int AccountInfo::getGID() {
	return _gid;
}
char* AccountInfo::getPassword() {
	return _password;
}
char* AccountInfo::getShell() {
	return _shell;
}
char* AccountInfo::getGecos() {
	return _gecos;
}
void AccountInfo::setUserID(int newUID) {
	_uid = newUID;
}
void AccountInfo::setGID(int newGID) {
	_gid = newGID;
}
void AccountInfo::setShell(char* newShell) {
	_shell = newShell;
}

/*Empty constructor*/
AccountInfo::AccountInfo() {
	//empty
}

//empties out the string 'token' of size 'size'
void emptyString(char* token, int size) {
	for (int i = 0; i < size; i++){
		token[i] = '\0';
	}
}

/*Constructor when only the user login name is given*/
AccountInfo::AccountInfo(char* userLoginName) {
	//copy over the userLoginName and empty out each other field
	_userLoginName = new char[9];
	for (int i = 0; i < 9; i++) {
		_userLoginName[i] = userLoginName[i];
	}
	
	_home = new char[33];
	emptyString(_home, 33);

	_uid = 0;
	_gid = 0;
	
	_password = new char[17];
	emptyString(_password, 17);
	
	_shell = new char[17];
	emptyString(_shell, 17);
	
	_gecos = new char[65];
	emptyString(_gecos, 65);
}


/*Constructor when all seven fields are given*/
AccountInfo::AccountInfo(char* userLoginName, char* home, int uid, int gid, char* password, char* shell, char* gecos) {
	//copy over each field
	_userLoginName = new char[9];
	for (int i = 0; i < 9; i++) {
		_userLoginName[i] = userLoginName[i];
	}
	
	_home = new char[33];
	emptyString(_home, 33);
	if (home[0] != '\0') {
		for (int i = 0; i < 33; i++) {
			_home[i] = home[i];
		}
	}
	
	_uid = uid;
	_gid = gid;
	
	_password = new char[17];
	emptyString(_password, 17);
	if (password[0] != '\0') {
		for (int i = 0; i < 17; i++) {
			_password[i] = password[i];
		}
	}

	_shell = new char[17];
	emptyString(_shell, 17);
	if (shell[0] != '\0') {
		for (int i = 0; i < 17; i++) {
			_shell[i] = shell[i];
		}
	}
	else {

	}

	_gecos = new char[65];
	emptyString(_gecos, 65);
	if (gecos[0] != '\0') {
		for (int i = 0; i < 65; i++) {
			_gecos[i] = gecos[i];
		}
	}
}

//Destructor for AccountInfo
AccountInfo::~AccountInfo() {
	delete _userLoginName, _home, _shell, _gecos, _password;
}

/*Represents a database of users (AccountInfos) with a limit of 200*/
class UserDB {
	friend ostream& operator << (ostream& s, UserDB* a);
private:
	AccountInfo* _accounts[200]; // store up to 200 accounts 
	int _size = 0; // number of account stored, incremented when addUser() is called
	int _nextUid = 1001; // next user id to be assigned 
	int _defaultGid; // default group id
	// other private methods necessary for this class
public:
	UserDB();//empty constructor
	~UserDB();//destructor
	void addUser(AccountInfo* newUser); // add a new user to // _accounts, also increment _size.
	// print out the following message after the // user is added:
	// “[userLoginName] with [uid] is added.”
	void showUsers(); // print out “List of users:” at the first
	// line, then print out all user login names
	// (one line each user login name), then print // out the following at the end according to
	// the number of users stored
	// 0 => “There’s no users found in the system.” // 1 => “1 user found in the system.”
	// k => “k users found in the system.” for k>1
	void showPasswd(); // call the ostream operator
	void finger(char* userLoginName); // call ostream operator of AccountInfo class
	// no accessors or mutators needed
};

//empty constructor
UserDB::UserDB() {
	//empty
}

//destructor for UserDB
UserDB::~UserDB() {
	for (int i = 0; i < _size; i++) {
		delete _accounts[i];
	}
	delete _accounts;
}



//overrided ostream (<<) operator for UserDB
ostream& operator << (ostream& s, UserDB* a) {
	for (int i = 0; i < a->_size; i++) {
		s << a->_accounts[i] << endl;
	}
	return s;
}

//compares two strings of equal length for equality
bool compareStrings(char* s, char* p, int length) {
	for (int i = 0; i < length; i++) {
		if (s[i] != p[i]){
			return false;
		}
	}
	return true;
}

//find if there is a user in _accounts with matching userLoginName
void UserDB::finger(char* userLoginName) {
	int length1 = 0;
	int length2 = 0;

	//find the length of the given userLoginName
	while (userLoginName[length1] != '\0') {
		length1++;
	}

	bool matching = false;//determines if we have found a match for userLogin name in _accounts yet

	//go through each user in _accounts
	for (int i = 0; i < _size; i++) {
		//find the length of _account[i]'s userLoginName
		int length2 = 0;
		while (_accounts[i]->getUserLoginName()[length2]) {
			length2++;
		}

		//string compare _account[i]'s userLoginName and userLoginName if they are the same length
		if (length1 == length2) {
			matching = compareStrings(userLoginName, _accounts[i]->getUserLoginName(), length1);
			if (matching) {//if they match, print the account. Were done here.
				cout << _accounts[i] << endl;
				return;
			}
			//otherwise, go to the next user in _accounts
		}
	}
	//if the no user with userLoginName exists in _accounts, inform the user
	cout << "no user named " << userLoginName << " was found" << endl;
}

void UserDB::addUser(AccountInfo* newUser) {
	//fields for the copy of newUser to be added to _accounts
	char userLoginName[9]; // store the login name of the new user 
	char home[33]; // home directory of the new user
	int uid = newUser->getUserID(); //new user identifier
	int gid = newUser->getGID(); // identifier of new user’s primary group 
	char password[17]; // new user's password
	char shell[17]; // shell of the new user
	char gecos[65]; // general info of the new user

	//empty out all of the strings
	emptyString(userLoginName, 9);
	emptyString(home, 33);
	emptyString(password, 17);
	emptyString(shell, 17);
	emptyString(gecos, 65);
	//these are the defaults for home and shell
	char defaultHome[] = "home /home/"; //11
	char defaultShell[] = "/bin/bash";//9

	//copy all of the newUsers data into new fields
	for (int i = 0; i < 9; i++) {
		userLoginName[i] = newUser->getUserLoginName()[i];
	}
	//if newUser has a home, copy it over
	if (newUser->getHome()[0] != '\0') {
		for (int i = 0; i < 33; i++) {
			home[i] = newUser->getHome()[i];
		}
	}
	//if newUser has no home, give user the default home ("home /home/userLoginName")
	else {
		int i = 0;
		for (; i < 11; i++) {
			home[i] = defaultHome[i];
		}
		//append newUser's userLoginName to the default home address
		for (int j = 0; j < 16; j++) {
			home[i] = newUser->getUserLoginName()[j];
			i++;
		}
	}
	//if newUser has a password, copy it over to user
	if (newUser->getPassword()[0] != '\0') {
		for (int i = 0; i < 17; i++) {
			password[i] = newUser->getPassword()[i];
		}
	}
	//if newUser has a shell, copy it over to user
	if (newUser->getShell()[0] != '\0') {
		for (int i = 0; i < 17; i++) {
			shell[i] = newUser->getShell()[i];
		}
	}
	//if newUser doesnt have a shell, give user the default shell (/bin/bash)
	else {
		int i = 0;
		for (; i < 9; i++) {
			shell[i] = defaultShell[i];
		}
	}
	//if newUser has a gecos, copy it over to user
	if (newUser->getGecos()[0] != '\0') {
		for (int i = 0; i < 65; i++) {
			gecos[i] = newUser->getGecos()[i];
		}
	}
	//if the newUser doesnt have a UID, give it the next available default uid
	if (newUser->getUserID() == 0) {
		uid = _nextUid++;
	}

	//copy the newUser into a more permanent user
	AccountInfo* user = new AccountInfo(userLoginName, home, uid, gid, password, shell, gecos);
	//add the copy of newUser into the array of users
	_accounts[_size] = user;
	cout << "[" << _accounts[_size]->getUserLoginName() << "] with [" << _accounts[_size]->getUserID() << "] is added" << endl;

	//now that the new account is added, we need to increment the size (_size) of _accounts
	_size++;
}

//prints out all of the names of the users in _accounts
void UserDB::showUsers() {
	cout << "List of users in the system:\n";
	for (int i = 0; i < _size; i++) {
		cout << _accounts[i]->getUserLoginName() << endl; //using overloaded ostream operator for AccountInfo
	}
	//determine what to print out depending on the number of users found in the system
	switch (_size) {
		case 0:
			cout << "There are no users found in the system.\n";
			break;
		case 1:
			cout << "1 user found in the system.\n";
			break;
		default:
			cout << _size << " users found in the system.\n";
	}
}

//show all of the accounts in the UserDB
void UserDB::showPasswd() {
	//print each field of each account in _accounts[]
	for (int i = 0; i < _size; i++) {
		cout << _accounts[i]->getUserLoginName() << ":";
		//check to see if the account has a password. print it if it does, print x otherwise
		if (_accounts[i]->getPassword()[0] != '\0') 
			cout << _accounts[i]->getPassword() << ":";
		else 
			cout << "x" << ":";
		cout << _accounts[i]->getUserID() << ":";
		if (_accounts[i]->getGID() > 0)
			cout << _accounts[i]->getGID() << ":";
		cout << _accounts[i]->getGecos() << ":";
		cout << _accounts[i]->getHome() << ":";
		cout << _accounts[i]->getShell() << endl;
	}
}

//gets the next string of data before the delimeter
int getNextToken(char* buffer, char* token, int startPos, int bufSize, int tokenSize, char delimeter) {
	int i, j;
	emptyString(token, tokenSize);
	i = startPos;
	j = 0;
	while ((buffer[i] == ' ') && (i < bufSize)) {
		i++; //skipblanks
	}

	if (i < 256) {
		while ((buffer[i] != delimeter) && (i < 256) && (j < tokenSize))
			token[j++] = buffer[i++];
	}
	return i;
}

//main method for manipulating a txt file to create AccountInfo's and a UserDB
int main() {
	//the temporary account that will be copied over to users
	AccountInfo* tempAccount;
	UserDB* users = new UserDB();
	char buffer[256]; //used to hold the current line
	//these are all of the field to construct tempAccount
	char uloginName[9]; 
	char homeDirectory[33];
	int userID;
	int groupID;
	char password[17];
	char shell[17];
	char gecos[65];
	int k;
	char flag[3];
	char IDString[6];
	char command[11];
	char blank = ' ';
	while (!cin.eof()) {//while there is another line
		//empty out all of the fields for addUser
		emptyString(uloginName, 9);
		emptyString(password, 17);
		emptyString(gecos, 65);
		emptyString(homeDirectory, 33);
		emptyString(shell, 17);
		userID = 0;

		//get a line and print it out
		cin.getline(buffer, 256);

		//determine the type of command the line entails
		k = getNextToken(buffer, command, 0, 256, 10, blank);
		switch (command[0]) {
		case 'a': {
			k = getNextToken(buffer, uloginName, k, 256, 9, blank);
			while (k < 256) {
				k = getNextToken(buffer, flag, k, 256, 3, blank);
				if (k < 256) {
					switch (flag[1]) {
					case 'd': k = getNextToken(buffer, homeDirectory, k, 256, 32, blank);
						break;
					case 's': k = getNextToken(buffer, shell, k, 256, 17, blank);
						break;
					case 'p': k = getNextToken(buffer, password, k, 256, 17, blank);
						break;
					case 'c': k = getNextToken(buffer, gecos, k, 256, 65, '-');
						break;
					case 'g': k = getNextToken(buffer, IDString, k, 256, 6, blank);
						groupID = atoi(IDString);
						break;
					case 'u': k = getNextToken(buffer, IDString, k, 256, 6, blank);
						userID = atoi(IDString);
						break;
					default: k = 256; break;
					} //end Switch(flag[1])
				} // end while (k < 256)
			}
			//create and add the temporary account to users
			tempAccount = new AccountInfo(uloginName, homeDirectory, userID, groupID, password, shell, gecos);
			users->addUser(tempAccount);
			break;
		} //end of adduser
		case '#': {
			break;
		}//end of comment
		case 's': {
			if (command[4] == 'u') {
				users->showUsers();
			}
			else if (command[4] = 'p') {
				users->showPasswd();
			}
			break;
		}//end of showuser and showpassword
		case 'f': {
			k = getNextToken(buffer, uloginName, k, 256, 9, blank);
			users->finger(uloginName);
			break;
		}//end of finger
		default:
			cout << "Command not found!!" << endl;
		}//end outer switch
	}//end while
}//end main