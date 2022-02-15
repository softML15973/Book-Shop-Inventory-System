#include <iostream> //to import input/output functionality
#include <conio.h> //to use _getch()
#include <algorithm>//to use transform()
#include <vector> //to use vectors
#include <string> //to use getline(),cin.ignore()
using namespace std; 

//This function is used to search a book in the books vector by
//using a keyword given by the user.
void search_books(vector<string>&books, string key, int size_books)
{
	bool is_avaliable = false;

	//To transform the entire keyword into uppercase
	transform(key.begin(), key.end(), key.begin(), ::toupper);
	cout << "Avaliable books:\n";

	//This loop is used to find a book in the books vector by 
	//checking the presence of the keyword in each string and
	//print all books having that keyword in them
	for (int i = 0; i < size_books; i++)
	{
		if (books[i].find(key) != string::npos)
		{
			cout << books[i] << endl;
			is_avaliable = true;
		}
	}

	//If there are no books which contain that specific keyword
	//then following code would execute
	if (is_avaliable == false)
	{
		cout << "0 such books avalaible\n";
	}
}

//This function is used to merge left and right vectors
void merge(vector<string>&left_vect, int left_vect_size, vector<string>&right_vect, int right_vect_size, vector<string>&books)
{
	//i is used as a index of left vector strings
	//j is used as a index of right vector strings
	//k is used as a index of books vector strings
	//index_left is used as a index of left vector string's characters
	//index_right is used as a index of right vector string's characters
	int i = 0, j = 0, k = 0, index_left = 0, index_right = 0;

	//This loop will run until i becomes equal to size of left
	//vector or j becomes equal to size of right vector
	while (i != left_vect_size && j != right_vect_size)
	{
		//to check if program has reached at the end of the left
		//vector string
		if (left_vect[i][index_left] == '\0')
		{
			k++;
			i++;
			index_left = 0;
			index_right = 0;
		}
		//to check if program has reached at the end of the right
		//vector string
		else if (right_vect[j][index_right] == '\0')
		{
			k++;
			j++;
			index_left = 0;
			index_right = 0;
		}

		//to check if left vector string's character is neither
		//digit nor alphabet
		else if (!isdigit(left_vect[i][index_left]) && !isalpha(left_vect[i][index_left]))
		{
			index_left++;
		}

		//to check if right vector string's character is neither
		//digit nor alphabet
		else if (!isdigit(right_vect[j][index_right]) && !isalpha(right_vect[j][index_right]))
		{
			index_right++;
		}

		//to check if left vector string's character is digit and right vector string's character an alphabet
		else if (isdigit(left_vect[i][index_left]) && isalpha(right_vect[j][index_right]))
		{
			index_left++;
		}

		//to check if right vector string's character is digit and left vector string's character an alphabet
		else if (isdigit(right_vect[j][index_right]) && isalpha(left_vect[i][index_left]))
		{
			index_right++;
		}

		//to check if left vector string's character is less than right vector string's character in terms of their ASCII codes
		else if (left_vect[i][index_left] < right_vect[j][index_right])
		{

			//if the condition is true then overwrite the value of left vector string's over the books vector at index k
			books[k] = left_vect[i];
			i++;
			k++;
			index_left = 0;
			index_right = 0;
		}

		//to check if right vector string's character is less than left vector string's character in terms of their ASCII codes
		else if (left_vect[i][index_left] > right_vect[j][index_right])
		{

			//if the condition is true then overwrite the value of right vector string's over the books vector at index k
			books[k] = right_vect[j];
			j++;
			k++;
			index_left = 0;
			index_right = 0;
		}

		//to check if both the characters of left and right vector string are equal in terms of their ASCII codes.
		else if (left_vect[i][index_left] == right_vect[j][index_right])
		{
			index_left++;
			index_right++;
		}
	}
	if (i == left_vect_size)
	{
		//overwrite remaning uncompared values of right vector in books vector
		while (j != right_vect_size)
		{
			books[k] = right_vect[j];
			j++;
			k++;
		}
	}
	else if (j == right_vect_size)
	{
		//overwrite remaning uncompared values of left vector in books vector
		while (i != left_vect_size)
		{
			books[k] = left_vect[i];
			i++;
			k++;
		}
	}
}

//This function is used to sort the books in the alphabetically order
void merge_sort_books(vector<string>&books, int size_books)
{
	//exit the function if books vector contains less than 2 books
	if (size_books < 2)
	{
		return;
	}
	else
	{
		//to calculate mid point of the books vector
		int mid = size_books / 2;

		int left_vect_size = mid;
		int right_vect_size = size_books-mid;
		vector<string>left_vect(left_vect_size);
		vector<string>right_vect(right_vect_size);

		//to copy the values of books vector in the left vector
		for (int i = 0; i < left_vect_size; i++)
		{
			left_vect[i] = books[i];
		}

		//to copy the values of books vector in the right vector
		for (int i = 0; i < right_vect_size; i++)
		{
			right_vect[i] = books[i + mid];
		}
		//to sort the left vector
		merge_sort_books(left_vect, left_vect_size);

		//to sort the right vector
		merge_sort_books(right_vect, right_vect_size);

		//to overwrite the values of sorted left and right vectors over actual books vector 
		merge(left_vect, left_vect_size, right_vect, right_vect_size, books);
	}
}
int main()
{
	//Storing few books initially
	vector<string>books{
		"A time in Palestine 10.99$",
		"Greta Gato in Anna Karenina 5.99$",
		"gato 1.99$",
		"One Hundred Years of Solitude 5.00$",
		"Don Quixote 9.00$",
		"Beloved 12.00$",
		"C++ 20.00$",
		"Cpp(2nd version) 30.00$"
	};
	int size = books.size();

	//to transform the names of all the books in the books vector one by one in uppercase
	for (int i = 0; i < size; i++)
	{
		transform(books[i].begin(), books[i].end(), books[i].begin(), ::toupper);
	}

	//merge the books in the alphabetical order
	merge_sort_books(books, size);
	int inteface = 0, option = 0;
	bool flag = true;
	while (flag)
	{
		cout << "1.User Interface\n";
		cout << "2.Admin Interface\n";
		cout << "3.Exit\n";
		cout << "What interface do you want to use ? ";
		cin >> inteface;
		switch (inteface)
		{
		case 1:
		{
			bool user_flag = true;
			while (user_flag)
			{
				cout << "1.Show all avaliable books\n";
				cout << "2.Search for a specific book\n";
				cout << "3.Exit\n";
				cout << "Select an option: ";
				cin >> option;
				switch (option)
				{
				case 1:
				{
					//to print all books avaliable
					for (int i = 0; i < size; i++)
					{
						cout << i + 1 << ") " << books[i] << endl;
					}
				}
				break;

				case 2:
				{
					//to find a book in the books vector using a keyword or a book name entered by the user
					string book_name;
					cin.ignore();
					cout << "Enter name of the book: ";
					getline(cin, book_name);
					search_books(books, book_name, size);
				}
				break;

				case 3: user_flag = false;
				break;

				default: cout << "Invalid option number\n";
				break;
				}
			}
		}
		break;

		case 2:
		{
			bool not_access = true;
			string user_name;
			char pass_code[5] = {'a','d','m','i','n'};
			char enter_code[5]{};
			while (not_access)
			{
				cout << "Enter user name: ";
				cin >> user_name;
				cout << "Enter password: ";
				for (int i = 0; i < 5; i++)
				{
					//_getch() function pauses the program until user presses any key and then it returns the ASCII code of that key and then the character corresponding that key gets stored in the enter_code array
					enter_code[i] = _getch();
					cout << '*';
				}
				cout << endl;
				//this loop is used to check if password entered by the user is correct by comparing the characters one by one with pass_code array
				for (int i = 0; i < 5 ; i++)
				{
					if (enter_code[i] == pass_code[i])
					{
						not_access = false;
					}
					else
					{
						not_access = true;
					}
				}
				if (user_name != "admin")
				{
					not_access = true;
				}
				if (not_access == true)
				{
					cout << "Invalid user name or password\n";
				}
			}
			not_access = true;
			//once user has entered the correct user name and password then he/she can access the admin panel 
			while (not_access)
			{
				cout << "1.Add a book\n";
				cout << "2.Remove a book\n";
				cout << "3.Exit\n";
				cout << "Select an option: ";
				cin >> option;
				switch (option)
				{
				case 1:
				{
					string book_name;
					cin.ignore();
					cout << "Enter name of the book with price tag: ";
					getline(cin,book_name);

					//to transform the name of the newly entered book into uppercase.
					transform(book_name.begin(), book_name.end(), book_name.begin(), ::toupper);

					//to insert that new book into books vector
					books.push_back(book_name);

					size = books.size();

					//to sort the books again after inserting new book
					merge_sort_books(books, size);

					for (int i = 0; i < size; i++)
					{
						cout << i + 1 << ") " << books[i] << endl;
					}
				}
				break;

				case 2:
				{
					int book_number;
					for (int i = 0; i < size; i++)
					{
						cout << i + 1 << ") " << books[i] << endl;
					}
					cout << "Enter number of the book to remove: ";
					cin >> book_number;
					while (book_number<1 || book_number > size)
					{
						cout << "Invalid book number\n";
						cout << "Enter number of the book to remove: ";
						cin >> book_number;
					}

					//to erase a book from books vector
					books.erase(books.begin() + (book_number - 1));
					size = books.size();
					
					//to sort the books after removing a book
					merge_sort_books(books, size);
					for (int i = 0; i < size; i++)
					{
						cout << i + 1 << ") " << books[i] << endl;
					}
				}
				break;

				case 3: not_access = false;
				break;

				default: cout << "Invalid option number\n";
				break;
				}
			}
		}
		break;

		case 3: flag = false;
		break;

		default: cout << "Invalid interface number\n";
		break;
		}
	}
    return 0;
}